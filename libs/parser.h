# include "inter.h"

vector<string> parse_tokens(string file){
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

string init_file(string file_name);

string compute_heading(string &file, string file_name){
    int read = 0;
    while (file.find("#") != string::npos) {
        replace_where(file, "\\\n", " ");
        printf_debug(("."));
        string str = readline(file, read++);
        // cout << "reading line: " << read-1 << " content: " << str << "\n";
        if(str.length()){
            if(str[0] == '#'){
                string str_remover = str + "\n";
                // cout << "removing string: '" << str << "' from file.\n";
                replace_where(file, str_remover, "\n");
                vector<string> tks = parse_tokens(str);
                if (tks[0] == "#define") {
                    string target = tks[1];
                    string substr = join(" ", tks, 2);
                    replace_where(file, target, substr);
                    cout_debug(<< "DEFINE: reading define at " << read << ":\n\t'" << str << "'\n\treplacing '" << target << "' with '" << substr << "'\n");
                    // cout << "\tfile after define\n" << file << "\n";
                } elif (tks[0] == "#include") {
                    path p2 = file_name;
                    int represented = (int)represents_string(tks[1]) - (int)represents_header(tks[1]);
                    if (represented) {
                        string target = derep_str(tks[1]);
                        path ptarget = target;
                        cout_debug(<< "INCLUDE: including file at '" << p2 << "'\n");
                        if (represented == 1) {
                            p2 = p2.dir_name();
                            p2 += ptarget;
                        } elif (represented == -1) {
                            p2 = ptarget;
                        }
                        // cout_debug<< "file after include\n" << file << "\n";
                        file = read_file(p2()) + "\n" + file;
                        read = 0;
                    }
                    else {
                        cout << "ERROR: Inclusion failed in:\n\t - " << p2 << ":" << read << ":" << 10 << "\n";
                        throw -1;
                    }
                }
            }
        }
        // cout << file << "\n";
        // system("pause");
    }
}

string init_file(string file_name){
    string file = read_file(file_name);
    compute_heading(file, file_name);
    return file;
}
