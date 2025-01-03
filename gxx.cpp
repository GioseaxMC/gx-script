# include <iostream>
# include <windows.h>

# include "libs\parser.h"

#define in :

using namespace std;

vector<string> arguments;

int main(int argc, char** argv) {

    bool USE_FILE_CWD = 0;
    for range(i, argc) {
        string temp = string(argv[i]);
        arguments.push_back(temp);
        if (temp == "--use-file-cwd") {
            cout << "using .gx file directory as cwd\n";
            USE_FILE_CWD = 1;
        }
    }

    if (argc >= 2) {
        string file_name = arguments[1];
        string dir_name = path(file_name).dir_name()();
        vector<Token> tokens;
        init_file(file_name, tokens);
        for (Token t in tokens) {
            cout << "token: " << t.text << " @: ";
            print_position(t);
            cout << endl;
        }
        # ifdef DEBUG
            cout << "\n--" << file << "\n--\n";
        # endif
        vector<action> program;
        parse_program(tokens, program);
        compute_crossreference(program);
        vector<void*> stack;
        for irange(i, argc) {
            string temp_str = arguments[i];
            push_to<string>(stack, new_ptr(temp_str));
        }
        if (USE_FILE_CWD) setcwd(dir_name);
        inter_main(program, stack);

    } else {
        printf("Must specify a file.\n");
    }

}