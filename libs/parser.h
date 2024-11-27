# include "inter.h"

vector<string> parse_tokens(string &file, vector<vector<int>> positions){
    vector<string> tokens;
    string token;
    for(int i=0; i<file.length(); i++) {
        char c = file[i];
        if (is_delim(c, delims)) {
            if (token.length()){
                tokens.push_back(token);
            }
            if (!is_delim(c, " \n\"")) {
                tokens.push_back(string(1, c));
            }
            if (is_delim(c, "<")) {
                string temp;
                temp += c;
                while (1) {
                    c = file[++i];
                    if (c == '\\') {
                        c = file[++i];
                        if (c == 'n') {
                            temp += '\n';
                        } elif (c == 't') {
                            temp += '\t';
                        } elif (c == '\\') {
                            temp += '\\';
                        }
                        else {
                            printf("unknown escape code:\n\t- \\%c\n", c);
                        }
                    } else {
                        temp += c;
                    }
                    if (c == '>') {
                        break;
                    }
                }
                cout_debug(<< "head: '" << temp << "'\n");

                tokens.push_back(temp);
                temp.clear();
            }
            if (is_delim(c, "\"")) {
                string temp;
                temp += c;
                while (1) {
                    c = file[++i];
                    if (c == '\\') {
                        c = file[++i];
                        if (c == 'n') {
                            temp += '\n';
                        } elif (c == 't') {
                            temp += '\t';
                        } elif (c == '\\') {
                            temp += '\\';
                        }
                        else {
                            printf("unknown escape code:\n\t- \\%c\n", c);
                        }
                    } else {
                        temp += c;
                    }
                    if (c == '\"') {
                        break;
                    }
                }
                cout_debug(<< "str: '" << temp << "'\n");
                tokens.push_back(temp);
                temp.clear();
            }
            token.clear();
        } else {
            token += c;
        }
    }
    if (token.length()) {
        cout_debug(<< "tk: '" << token << "'\n");
        tokens.push_back(token);
    }
    return tokens;
}

int find(string &haystack, string needle, int &__end_position) {
    __end_position = haystack.find(needle);
    return __end_position;
}

string get_line(string &file, int __start_pos) {
    string temp;
    for(int i=__start_pos; i<file.length(); ++i) {
        temp += file[i];
        if (file[i] == '\n') {
            break;
        }
    }
    return temp;
}

void handle_inclusion(string &file, string file_name) {
    int str_position;
    while (find(file, "#include", str_position) != string::npos) {
        cout_debug(<< ".");
        path p2 = file_name;
        string line = get_line(file, str_position);
        cout_debug(<< str_position << endl);
        vector<vector<int>> _;
        vector<string> tks = parse_tokens(line, _);
        _.clear();
        int header_type = (int)represents_string(tks[1]) - (int)represents_header(tks[1]); // 1 if local else -1
        if (header_type) {
            string target_header = derep_str(tks[1]);
            path header_path = target_header;
            cout_debug(<< "INCLUDE: including file at '" << p2 << "'\n");
            if (header_type == 1) {
                p2 = p2.dir_name();
                p2 += header_path;
            } elif (header_type == -1) {
                p2 = header_path;
            }
            file.erase(str_position, line.length());
            file.insert(str_position, read_file(p2())+"\n");
        } else {
            cout << "ERROR: Inclusion failed in:\n\t - " << p2 << ":" << /* line name << */ ":" << 10 << "\n";
            throw -1;
        }
    }
}

void handle_defines(string &file, string file_name) {
    int define_pos;
    while(find(file, "#define", define_pos) != string::npos){
        string line = get_line(file, define_pos);
        replace_where(file, line, "");
        vector<vector<int>> _;
        vector<string> tks = parse_tokens(line, _);
        _.clear();
        string target = tks[1];
        string substr = join(" ", tks, 2);
        replace_where(file, target+"\n", substr+"\n");
        replace_where(file, target+" ", substr+" ");
    }
}

void handle_semicolons(string &file) {
    replace_where(file, "\\\n", " ");
    replace_where(file, ";\n", " ");
}

void remove_comments(string &file) {
    for(int i=0; i<file.length(); ++i) {
        if (file[i] == '#') {
            while(file.length() - i) {
                file.erase(i, 1);
                if (file[i] != '\n') {
                } else {
                    break;
                }
            }
        }
    }
}

string init_file(string file_name){
    string file = read_file(file_name);
    handle_inclusion(file, file_name);
    handle_semicolons(file);
    handle_defines(file, file_name);
    remove_comments(file);
    replace_where(file, "\n\n", "\n");
    cout_debug(<< file << endl);
    return file;
}
