# include <iostream>
# include <windows.h>

# include "libs\parser.h"

using namespace std;

vector<string> arguments;

int main(int argc, char** argv) {
    for range(i, argc) {
        arguments.push_back(string(argv[i]));
    }

    if (argc >= 2) {
        string file_name = arguments[1];
        string file = init_file(file_name);
        # ifdef DEBUG
            cout << "\n--" << file << "\n--\n";
        # endif
        vector<vector<int>> t_positions;
        vector<string> tokens = parse_tokens(file, t_positions);
        vector<action> program;
        parse_program(tokens, program);
        compute_crossreference(program);
        vector<void*> stack;
        for irange(i, argc) {
            string temp_str = arguments[i];
            push_to<string>(stack, new_ptr(temp_str));
        }
        inter_main(program, stack);

    } else {
        printf("Must specify a file.\n");
    }

}