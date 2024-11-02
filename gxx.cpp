# include <iostream>
# include <windows.h>

# include "libs\parser.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc >= 2) {
        string file_name = string(argv[1]);
        string file = init_file(file_name);
        # ifdef DEBUG
            cout << "\n--" << file << "\n--\n";
        # endif
        vector<string> tokens = parse_tokens(file);
        vector<action> program;
        parse_program(tokens, program);
        compute_crossreference(program);
        vector<void*> stack;
        inter_main(program, stack);
    } else {
        printf("Must specify a file.\n");
    }

}