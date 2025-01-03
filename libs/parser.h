# include "inter.h"

Token calculate_start_position(Token tk) {
    tk.pos.col -= tk.text.length()+1;
    return tk;
}

vector<string> tokens_to_strs(vector<Token> &tokens) {
    vector<string> tempv;
    for (Token t : tokens) {
        tempv.push_back(t.text);
    }
    return tempv;
}

void parse_tokens(string &file, string &file_name, vector<Token> &tokens){
    Token temp_tk;
    temp_tk.pos.file = file_name;
    temp_tk.pos.row = 1;
    temp_tk.pos.col = 1;
    for(int i=0; i<file.length(); i++) {
        char c = file[i];
        temp_tk.pos.col++;
        if (is_delim(c, delims)) {
            if (temp_tk.text.length()){
                tokens.push_back(calculate_start_position(temp_tk));
            }
            if (c == '\n') {
                temp_tk.pos.row++;
                temp_tk.pos.col = 1;
            }
            if (is_delim(c, "<")) {
                string temp;
                temp += c;
                while (1) {
                    c = file[++i];
                    temp_tk.pos.col++;
                    if (c == '\\') {
                        c = file[++i];
                        temp_tk.pos.col++;
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
                temp_tk.text = temp;
                tokens.push_back(calculate_start_position(temp_tk));
                temp_tk.text.clear();
            }
            if (is_delim(c, "\"")) {
                string temp;
                temp += c;
                while (1) {
                    c = file[++i];
                    temp_tk.pos.col++;
                    if (c == '\\') {
                        c = file[++i];
                        temp_tk.pos.col++;
                        if (c == 'n') {
                            temp += '\n';
                        } elif (c == 't') {
                            temp += '\t';
                        } elif (c == '\\') {
                            temp += '\\';
                        } elif (c == '"') {
                            temp += '"';
                        }
                        else {
                            printf("unknown escape code:\n\t- \\%c\n", c);
                        }
                    } elif (c == '\"') {
                        temp += c;
                        break;
                    } else {
                        temp += c;
                    }
                }
                cout_debug(<< "str: '" << temp << "'\n");
                temp_tk.text = temp;
                tokens.push_back(calculate_start_position(temp_tk));
                temp_tk.text.clear();
            }
            temp_tk.text.clear();
        } else {
            temp_tk.text += c;
        }
    }
    if (temp_tk.text.length()) {
        cout_debug(<< "tk: '" << temp_tk.text << "'\n");
        tokens.push_back(calculate_start_position(temp_tk));
    }
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

void init_file(...);void init_file(string file_name, vector<Token> &tokens);

void handle_inclusion(string &file, string &file_name, vector<Token> &global_tokens) {
    int str_position;
    while (find(file, "#include", str_position) != string::npos) {
        cout_debug(<< ".");
        path p2;
        string line = get_line(file, str_position);
        cout_debug(<< str_position << endl);
        vector<Token> tokens;
        parse_tokens(line, file_name, tokens);
        vector<string> tks = tokens_to_strs(tokens);
        tokens.clear();
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
            file.erase(str_position, line.length()-1);
            // file.insert(str_position, read_file(p2())+"\n");
            init_file(p2(), global_tokens);
        } else {
            cout << "ERROR: Inclusion failed in:\n\t - " << p2 << ":" << /* line name << */ ":" << 10 << "\n";
            exit(-1);
        }
    }
}

void handle_defines(string &file, string &file_name) {
    int define_pos;
    while(find(file, "#define", define_pos) != string::npos){
        string line = get_line(file, define_pos);
        replace_where(file, line, "");
        vector<Token> tokens;
        parse_tokens(line, file_name, tokens);
        vector<string> tks = tokens_to_strs(tokens);
        tokens.clear();
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

void init_file(string file_name, vector<Token> &tokens){
    string file = read_file(file_name);
    handle_inclusion(file, file_name, tokens);
    // handle_semicolons(file);
    handle_defines(file, file_name);
    remove_comments(file);
    cout_debug(<< file << endl);
    parse_tokens(file, file_name, tokens);
}
