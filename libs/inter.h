# include "paths.h"
# include "dicts.h"

# define deref(type, ptr) *((type*)(ptr))
# define elif else if
# define int64 size_t

# define range(var, end) (int var = 0; var < end; var++)
# define irange(var, end) (int var = end-1; var >= 0; var--)

# define DEBUG0

#ifdef DEBUG
    # define cout_debug(x) cout x
    # define printf_debug(x) printf x
#else
    # define cout_debug(x)
    # define printf_debug(x)
#endif

template<typename T>
void* new_ptr(void* ptr){
    int size = sizeof(T);
    void* n_ptr = malloc(size);
    memcpy(n_ptr, ptr, size);
    return n_ptr;
}

void* new_ptr(string str_ptr) {
    string* n_str = static_cast<string*>(malloc(sizeof(string)));
    if (!n_str) {
        cout << "FATAL ERROR: buy more ram... LITERALLY\n";
        exit(-1);
    }

    new (n_str) string(str_ptr);

    return static_cast<void*>(n_str);
}

Hash<int> proc_references;
Hash<void*>  let_references;

struct {
    const int PUSH = iota(1);
    const int PLUS = iota(); 
    const int DUMP = iota(); 
    const int DUP = iota();   
    const int SUB = iota();
    const int DIV = iota();
    const int MUL = iota();
    const int IF = iota();
    const int ELSE = iota();
    const int END = iota();
    const int WHILE = iota();
    const int DO = iota();
    const int LESST = iota();
    const int BIGRT = iota();
    const int CMP = iota();
    const int SWAP = iota();
    const int ROTATE = iota();
    const int STACK_DUMP = iota();
    const int DROP = iota();
    const int PAUSE = iota();
    const int NEWL = iota();
    const int STRL = iota();
    const int PUTS = iota();
    const int STR_CMP = iota();
    const int STR_DUP = iota();
    const int MALLOC = iota();
    const int PUTP = iota();
    const int AT_INT = iota();
    const int SET_INT = iota();
    const int FREE = iota();
    const int AND = iota();
    const int OR = iota();
    const int PROC = iota();
    const int REFERENCE = iota();
    const int RET = iota();
    const int PROC_NAME = iota();
    const int PTR_SUM = iota();
    const int ELIF = iota();
    const int STOI = iota();
    const int INPUT = iota();
    const int SYSTEM = iota();
    const int STR_SUM = iota();
    const int READ_FILE = iota();
    const int STACK_LEN = iota();
    const int SETCWD = iota();
    const int STRIP_RIGHT = iota();
    const int STR_LEN = iota();
    const int LET = iota();
    const int LET_NAME = iota();
    const int SDROP = iota();

    const int lenght = iota();
} op;

string get_name(int idx) {
    if (idx == op.PUSH) {
        return "PUSH";
    } elif (idx == op.PLUS) {
        return "PLUS";
    } elif (idx == op.DUMP) {
        return "DUMP";
    } elif (idx == op.DUP) {
        return "dup";
    } elif (idx == op.SUB) {
        return "sub";
    } elif (idx == op.DIV) {
        return "div";
    } elif (idx == op.MUL) {
        return "mul";
    } elif (idx == op.IF) {
        return "if";
    } elif (idx == op.ELSE) {
        return "else";
    } elif (idx == op.END) {
        return "end";
    } elif (idx == op.WHILE) {
        return "while";
    } elif (idx == op.DO) {
        return "do";
    } elif (idx == op.LESST) {
        return "less-than";
    } elif (idx == op.BIGRT) {
        return "bigger-than";
    } elif (idx == op.CMP) {
        return "compare";
    } elif (idx == op.SWAP) {
        return "swap";
    } elif (idx == op.ROTATE) {
        return "rotate";
    } elif (idx == op.STACK_DUMP) {
        return "stack_dump";
    } elif (idx == op.DROP) {
        return "drop";
    } elif (idx == op.PAUSE) {
        return "pause";
    } elif (idx == op.NEWL) {
        return "NEWLINE";
    } elif (idx == op.STRL) {
        return "string-literal";
    } elif (idx == op.PUTS) {
        return "puts";
    } elif (idx == op.STR_CMP) {
        return "str-cmp";
    } elif (idx == op.STR_DUP) {
        return "str-dup";
    } elif (idx == op.MALLOC) {
        return "alloc";
    } elif (idx == op.PUTP) {
        return "putp";
    } elif (idx == op.AT_INT) {
        return "deref.int";
    } elif (idx == op.SET_INT) {
        return "set.int";
    } elif (idx == op.FREE) {
        return "free";
    } elif (idx == op.AND) {
        return "and";
    } elif (idx == op.OR) {
        return "or";
    } elif (idx == op.PROC) {
        return "proc";
    } elif (idx == op.RET) {
        return "return";
    } elif (idx == op.REFERENCE) {
        return "reference";
    } elif (idx == op.PROC_NAME) {
        return "proc-name";
    } elif (idx == op.PTR_SUM) {
        return "ptr+";
    } elif (idx == op.ELIF) {
        return "if*";
    } elif (idx == op.STOI) {
        return "stoi";
    } elif (idx == op.INPUT) {
        return "input";
    } elif (idx == op.SYSTEM) {
        return "system";
    } elif (idx == op.STR_SUM) {
        return "str-sum";
    } elif (idx == op.READ_FILE) {
        return "read-file";
    } elif (idx == op.STACK_LEN) {
        return "stack-len";
    } elif (idx == op.SETCWD) {
        return "chdir";
    } elif (idx == op.STRIP_RIGHT) {
        return "strip-right";
    } elif (idx == op.STR_LEN) {
        return "string-length";
    } elif (idx == op.LET) {
        return "let-word";
    } elif (idx == op.LET_NAME) {
        return "let-name";
    } elif (idx == op.SDROP) {
        return "soft-drop";
    }
    else {
        return "-";
    }
}

struct Position {
    string file;
    int row;
    int col;
};

struct Token {
    string text;
    Position pos;
};

#define print_position(tk) \
    cout << tk.pos.file << ":" << tk.pos.row << ":" << tk.pos.col;

struct action {
    int id;
    void* value = malloc(sizeof(void*)); // alloc s(void*) bytes for pointers.

    Position pos;
};

template<typename T>
action push(T value) {
    action temp;
    temp.id = op.PUSH;
    deref(int, temp.value) = value;
    return temp;
}

action sum() {
    action temp;
    temp.id = op.PLUS;
    return temp;
}

action dump(){
    action temp;
    temp.id = op.DUMP;
    return temp;
}

action dup() {
    action temp;
    temp.id = op.DUP;
    return temp;
}

action sub() {
    action temp;
    temp.id = op.SUB;
    return temp;
}

action div() {
    action temp;
    temp.id = op.DIV;
    return temp;
}

action mul() {
    action temp;
    temp.id = op.MUL;
    return temp;
}

action iff() {
    action temp;
    temp.id = op.IF;
    return temp;
}

action _else() {
    action temp;
    temp.id = op.ELSE;
    return temp;
}

action end() {
    action temp;
    temp.id = op.END;
    return temp;
}

action whl() {
    action temp;
    temp.id = op.WHILE;
    return temp;
}

action doo() {
    action temp;
    temp.id = op.DO;
    return temp;
}

action lesst() {
    action temp;
    temp.id = op.LESST;
    return temp;
}

action bigger() {
    action temp;
    temp.id = op.BIGRT;
    return temp;
}

action cmp() {
    action temp;
    temp.id = op.CMP;
    return temp;
}

action swap() {
    action temp;
    temp.id = op.SWAP;
    return temp;
}

action rotate() {
    action temp;
    temp.id = op.ROTATE;
    return temp;
}

action stk_dmp() {
    action temp;
    temp.id = op.STACK_DUMP;
    return temp;
}

action drop() {
    action temp;
    temp.id = op.DROP;
    return temp;
}

action pause() {
    action temp;
    temp.id = op.PAUSE;
    return temp;
}

action newline() {
    action temp;
    temp.id = op.NEWL;
    return temp;
}

action str_literal() {
    action temp;
    temp.id = op.STRL;
    return temp;
}

action puts() {
    action temp;
    temp.id = op.PUTS;
    return temp;
}

action str_cmp() {
    action temp;
    temp.id = op.STR_CMP;
    return temp;
}

action str_dup() {
    action temp;
    temp.id = op.STR_DUP;
    return temp;
}

action alloc() {
    action temp;
    temp.id = op.MALLOC;
    return temp;
}

action putp() {
    action temp;
    temp.id = op.PUTP;
    return temp;
}

action atint() {
    action temp;
    temp.id = op.AT_INT;
    return temp;
}

action setint() {
    action temp;
    temp.id = op.SET_INT;
    return temp;
}

action mfree() {
    action temp;
    temp.id = op.FREE;
    return temp;
}

action _and() {
    action temp;
    temp.id = op.AND;
    return temp;
}

action _or() {
    action temp;
    temp.id = op.OR;
    return temp;
}

action proc() {
    action temp;
    temp.id = op.PROC;
    return temp;
}

action ref(string &name) { // TODO: figure out if must be removed
    action temp;
    string* str_ptr = new string(name);
    temp.id = op.REFERENCE;
    temp.value = str_ptr;
    return temp;
}

action proc_name(string &name) {
    action temp;
    string* str_ptr = new string(name);
    proc_references.add(name, -1);
    temp.value = str_ptr;
    temp.id = op.PROC_NAME;
    return temp;
}

action ret() {
    action temp;
    temp.id = op.RET;
    return temp;
}

action ptr_sum() {
    action temp;
    temp.id = op.PTR_SUM;
    return temp;
}

action _elif() {
    action temp;
    temp.id = op.ELIF;
    return temp;
}

action _stoi() {
    action temp;
    temp.id = op.STOI;
    return temp;
}

action input() {
    action temp;
    temp.id = op.INPUT;
    return temp;
}

action _system() {
    action temp;
    temp.id = op.SYSTEM;
    return temp;
}

action str_sum() {
    action temp;
    temp.id = op.STR_SUM;
    return temp;
}

action _read_file() {
    action temp;
    temp.id = op.READ_FILE;
    return temp;
}

action _stack_len() {
    action temp;
    temp.id = op.STACK_LEN;
    return temp;
}

action _setcwd() {
    action temp;
    temp.id = op.SETCWD;
    return temp;
}

action _strright() {
    action temp;
    temp.id = op.STRIP_RIGHT;
    return temp;
}

action _strlen() {
    action temp;
    temp.id = op.STR_LEN;
    return temp;
}

action _let() {
    action temp;
    temp.id = op.LET;
    return temp;
}

action _let_name(string &name) {
    action temp;
    string* str_ptr = new string(name);
    let_references.add(name, nullptr);
    temp.value = str_ptr;
    temp.id = op.LET_NAME;
    return temp;
}

action soft_drop() {
    action temp;
    temp.id = op.SDROP;
    return temp;
}

void compiler_error(action& act, string err_t, string str) {
    print_position(act);
    cout << ": " << err_t << ": " << str << "\n";
    exit(-1);
}

action CURRENT_ACT;

template<typename T>
T pop_value(vector<void*> &stack) {
    if (stack.size()) {
        T x = deref(T, stack.back());
        cout_debug(<< "stack back: " << stack.back() << ", variable location: " << &x << "\n");
        free(stack.back());
        stack.pop_back();
        return x;
    } else {
        compiler_error(CURRENT_ACT, "Segmentation fault", "stack size is: " + string(1, stack.size()));
    }
}

template<typename T>
void push_to(vector<void*> &stack, void* value){
    cout_debug(<< "pushing '" << value << "', which is equal to '" << deref(T, value) << "' to stack.\n");
    stack.push_back(value);
}

void parse_program(vector<Token> tokens, vector<action> &action_vec){
    string str;
    Token tk;
    for(int i=0; i<tokens.size(); ++i) {
        tk = tokens[i];
        str = tk.text;
        if (str == "dump") {
            action_vec.push_back(dump());
        } elif (str == "dup") {
            action_vec.push_back(dup());
        } elif (str == "+") {
            action_vec.push_back(sum());
        } elif (str == "-") {
            action_vec.push_back(sub());
        } elif (str == "/") {
            action_vec.push_back(div());
        } elif (str == "*") {
            action_vec.push_back(mul());
        } elif (is_numeric(str)) {
            action_vec.push_back(push(stoi(str)));
        } elif (str == "if") {
            action_vec.push_back(iff());
        } elif (str == "else") {
            action_vec.push_back(_else());
        } elif (str == "end") {
            action_vec.push_back(end());
        } elif (str == "while") {
            action_vec.push_back(whl());
        } elif (str == "do") {
            action_vec.push_back(doo());
        } elif (str == "<") {
            action_vec.push_back(lesst());
        } elif (str == ">") {
            action_vec.push_back(bigger());
        } elif (str == "=") {
            action_vec.push_back(cmp());
        } elif (str == "swap") {
            action_vec.push_back(swap());
        } elif (str == "rotate") {
            action_vec.push_back(rotate());
        } elif (str == "stack_dump") {
            action_vec.push_back(stk_dmp());
        } elif (str == "drop") {
            action_vec.push_back(drop());
        } elif (str == "pause") {
            action_vec.push_back(pause());
        } elif (str == "newl") {
            action_vec.push_back(newline());
        } elif (represents_string(str)) {
            string strn = derep_str(str);
            action act = str_literal();
            free(act.value);
            act.value = new_ptr(strn);
            cout_debug(<< "pushed: '" << deref(string, act.value) << "'\n");
            action_vec.push_back(act);
        } elif (str == "puts") {
            action_vec.push_back(puts());
        } elif (str == "str.cmp") {
            action_vec.push_back(str_cmp());
        } elif (str == "str.dup") {
            action_vec.push_back(str_dup());
        } elif (str == "malloc") {
            action_vec.push_back(alloc());
        } elif (str == "putp") {
            action_vec.push_back(putp());
        } elif (str == "R.int") {
            action_vec.push_back(atint());
        } elif (str == "W.int") {
            action_vec.push_back(setint());
        } elif (str == "free") {
            action_vec.push_back(mfree());
        } elif (str == "&&") {
            action_vec.push_back(_and());
        } elif (str == "||") {
            action_vec.push_back(_or());
        } elif (str == "proc") {
            action_vec.push_back(proc());
            action_vec.back().pos = tk.pos;
            action_vec.push_back(proc_name(tokens[++i].text));
            cout_debug(<< "declared proc: " << tokens[i].text << endl);
        } elif (str == "return") {
            action_vec.push_back(ret());
        } elif (str == "ptr+") {
            action_vec.push_back(ptr_sum());
        } elif (str == "if*") {
            action_vec.push_back(_elif());
        } elif (str == "stoi") {
            action_vec.push_back(_stoi());
        } elif (str == "input") {
            action_vec.push_back(input());
        } elif (str == "system") {
            action_vec.push_back(_system());
        } elif (str == "strsum") {
            action_vec.push_back(str_sum());
        } elif (str == "read_file") {
            action_vec.push_back(_read_file());
        } elif (str == "stk.len") {
            action_vec.push_back(_stack_len());
        } elif (str == "chdir") {
            action_vec.push_back(_setcwd());
        } elif (str == "str.rstrip") {
            action_vec.push_back(_strright());
        } elif (str == "str.len") {
            action_vec.push_back(_strlen());
        } elif (str == "let.ptr") {
            action_vec.push_back(_let());
            action_vec.back().pos = tk.pos;
            action_vec.push_back(_let_name(tokens[++i].text));
            cout_debug(<< "declared let: " << tokens[i].text << endl);
        } elif (str == "soft-drop") {
            action_vec.push_back(soft_drop());
        }
        else {
            if (proc_references.contains(str)) {
                action_vec.push_back(ref(str));
                cout_debug(<< "referenced: " << str << endl);
            } elif (let_references.contains(str)) {
                action_vec.push_back(ref(str));
            } else {
                print_position(tk);
                cout << ": error: unknown word '" << tk.text << "'\n";
                exit(-1);
            }   
        }
        action_vec.back().pos = tk.pos;
        // cout << "checking:\n";
        // print_position(tk);
        // cout << "\n";
        // print_position(action_vec.back());
        // cout << "\n";
    }
}

void stack_dump(vector<void*> &stack) {
    cout << "stack dump:\n";
    for(void* v : stack){
        cout << deref(int, v) << " - " << v << "\n";
    }
    cout << "\n";
}

void actions_dump(vector<action> &acts) {
    for(action act : acts) {
        cout << "act type: " << get_name(act.id) << endl;
    }
}

#define bid op_stack.back()->id
void compute_crossreference(vector<action> &acts) {
    vector<action*> op_stack; // Moved this outside the loop
    // actions_dump(acts);
    int i = 0;
    while (i < acts.size()) {
        action* act = &acts[i];
        int id = act->id;
        i++;
        
        printf_debug(("COMP: crossreferencing instruction '%s'\n", get_name(id).c_str()));
        
        if (id == op.IF or id == op.ELIF) { // IF
            op_stack.push_back(act);

        } elif (id == op.ELSE) { // ELSE
            if (!op_stack.empty()) {
                int type = (op_stack.back()->id == op.IF) - (op_stack.back()->id == op.ELIF);
                if (type) {
                    deref(int, op_stack.back()->value) = i;
                    cout_debug(<< "setting else-1 which is: " << get_name(op_stack.back()->id) << endl);
                    op_stack.pop_back();
                    if (type == -1) {
                        if (op_stack.empty()) compiler_error(*act, "crossreference error", "'if*' should only be used after an else, maybe you meant 'if'");
                        if (op_stack.back()->id == op.ELSE) {
                            deref(int, op_stack.back()->value) = i-1;
                            cout_debug(<< "setting else-2 which is: " << get_name(op_stack.back()->id) << endl);
                            op_stack.pop_back();
                        } else {
                            compiler_error(*act, "crossreference error", "'if*' should only be used after an else, maybe you meant 'if'");
                        }
                    }
                } else {
                    compiler_error(*act, "crossreference error", "'else' can only be used after if or if*");
                }
                
            } else {
                compiler_error(*act, "crossreference error", "'else' is expected to be used after 'if' or 'if*' but nothing present");
            }
            op_stack.push_back(act);
        
        } elif (id == op.END) { // END
            if (!op_stack.empty()) {
                if (bid != op.DO and bid != op.ELSE and bid != op.IF and bid != op.ELIF) compiler_error(*act, "crossreference error", "'end' cannot be used after '" + get_name(bid) + "'");
                bool is_else = bid == op.ELSE;
                deref(int, op_stack.back()->value) = i;
                cout_debug(<< "END: cleared previous which was: " << get_name(op_stack.back()->id) << endl);
                op_stack.pop_back();
                if ((!op_stack.empty()) and !is_else) {
                    if (op_stack.back()->id == op.WHILE) {
                        int temp = deref(int, op_stack.back()->value);
                        deref(int, act->value) = temp;
                        cout_debug(<< "END: setting self to reference WHILE\n"); 
                        op_stack.pop_back();
                    } elif (op_stack.back()->id == op.ELSE) {
                        deref(int, op_stack.back()->value) = i;
                        cout_debug(<< "END: setting last (else) to reference NEXT\n");
                        op_stack.pop_back();
                        act->value = nullptr;
                    } else {
                        cout_debug(<< "END: last is not crossreference-able\n");
                        act->value = nullptr;
                    }
                } else {
                    act->value = nullptr;
                }
            } else {
                compiler_error(*act, "crossreference error", "unexpected use of 'end'");
            }
        
        } elif (id == op.DO) { // DO
            op_stack.push_back(act); // Push 'DO' to the stack
        } elif (id == op.WHILE) {
            deref(int, act->value) = i;
            op_stack.push_back(act); // Push 'WHILE' to the stack
        }
          elif (id == op.PROC) {
            op_stack.push_back(act);
            // print_position((*act));
            cout_debug(<< "PROC: setting up procedure name for: " << deref(string, acts[i].value) << endl);
            proc_references[deref(string, acts[i].value)] = i+1;
        } elif (id == op.RET) {
            if (op_stack.empty()) compiler_error(*act, "crossreference error", "'return' must close 'proc' but there's nothing to close");
            if (bid != op.PROC) compiler_error(*act, "crossreference error", "'return' can only close 'proc' but got used after '" + get_name(bid) + "'");
            deref(int, op_stack.back()->value) = i; // set the PROC pointer to after the end so we skip the funzion at execution.
            op_stack.pop_back();
        }

        else {
            // printf_debug((" - instruction with name '%s' is not crossreference-able.\n", get_name(id).c_str()));
        }
        printf_debug((".Done crossreferencing '%s'.\n", get_name(id).c_str()));
        cout_debug(<< "[");
        for range(i, op_stack.size()) {
            cout_debug(<< get_name(op_stack[i]->id) << "; ");
        } cout_debug(<< "]\n");
        printf_debug(("\n"));
    }
    if (!op_stack.empty()) {
        printf("ERROR: unmatched if, while statement or procedure.\n");
        cout << "crossreference stack dump:\n";
        for(action* a : op_stack) {
            cout << "file: " << a->pos.file;
            // print_position(a);
            cout << " action: " << get_name(a->id) << "\n";
        }
        exit(-1);
    }
    cout_debug(<< "got to crossreferecing end\n");
}

vector<int> address_stack;

#define stackn(x) stack[stack.size()+(x)]
int inter_main(vector<action> &program, vector<void*> &stack){
    int i = 0;
    while (i < program.size()) {
        action& act = program[i];
        CURRENT_ACT = program[i];
        cout_debug(<< "intepreting act at:" << i << "\n\ttype = " << get_name(act.id) << \
                ",\n\t(int)value = " << deref(int, act.value) << ",\n\t(int)value = " << deref(int, act.value) << "\n");
        ++i;
        switch (act.id) {
            case 0:{ // PUSH
                push_to<int>(stack, new_ptr<int>(act.value));
                break;
                

            } case 1: { // SUM
                int x = pop_value<int>(stack);
                int y = pop_value<int>(stack);
                int temp = x+y;
                push_to<int>(stack, new_ptr<int>(&temp));
                break;
                

            } case 2: { // DUMP
                int x = pop_value<int>(stack);
                cout << x;
                break;
                

            } case 3: { // DUP
                stack.push_back(new_ptr<void*>(stack.back()));
                break;
                

            } case 4: { // SUB
                int x = pop_value<int>(stack);
                int y = pop_value<int>(stack);
                int temp = y - x;
                push_to<int>(stack, new_ptr<int>(&temp));
                break;
                

            } case 5: { // DIV
                int x = pop_value<int>(stack);
                int y = pop_value<int>(stack);
                int temp = y / x;
                push_to<int>(stack, new_ptr<int>(&temp));
                break;
                

            } case 6: { // MUL
                int x = pop_value<int>(stack);
                int y = pop_value<int>(stack);
                int temp = y * x;
                push_to<int>(stack, new_ptr<int>(&temp));
                break;
                

            } case 7: { // IF
                bool cond = !(bool)pop_value<int>(stack);
                cout_debug(<< "condition is: " << cond << "\n");
                if (cond) {
                    i = deref(int, act.value);
                    cout_debug(<< "IF: setting 'i' to: " << i << "\n");
                }
                break;
                

            } case 8: { // ELSE
                i = deref(int, act.value);
                cout_debug(<< "ELSE: setting 'i' to: " << i << "\n");
                break;
                

            } case 9: { // END
                if (act.value != nullptr) {
                    i = deref(int, act.value); 
                }
                break;
                

            } case 10: { // WHILE
                break;
                

            } case 11: { // DO
                int cond = pop_value<int>(stack);
                cout_debug(<< "condition is: " << cond << "\n");
                if (!cond) {
                    i = deref(int, act.value);
                }
                break;
                

            } case 12: { // LESS
                int x = pop_value<int>(stack);
                int y = pop_value<int>(stack);
                int temp = y < x;
                push_to<int>(stack, new_ptr<int>(&temp));
                break;
                

            } case 13: { // GREATER
                int x = pop_value<int>(stack);
                int y = pop_value<int>(stack);
                int temp = y > x;
                push_to<int>(stack, new_ptr<int>(&temp));
                break;
                

            } case 14: { // LESS
                int x = pop_value<int>(stack);
                int y = pop_value<int>(stack);
                int temp = y == x;
                push_to<int>(stack, new_ptr<int>(&temp));
                break;
                

            } case 15: { // SWAP
                void* x = stackn(-1);
                stackn(-1) = stackn(-2);
                stackn(-2) = x;
                break;
                

            } case 16: { // ROTATE
                void* x = stackn(-1);
                void* y = stackn(-2);
                void* z = stackn(-3);
                stackn(-3) = y;
                stackn(-2) = x;
                stackn(-1) = z;
                break;
                

            } case 17: { // STK_DUMP
                stack_dump(stack);
                break;
                

            } case 18: { // DROP
                pop_value<int>(stack);
                break;
                

            } case 19: { // PAUSE
                system("pause");
                break;
                

            } case 20: { // NEWL
                cout << "\n";
                break;
                

            } case 21: { // STRING-LITERAL
                string str = deref(string, act.value);
                push_to<string>(stack, new_ptr(str));
                break;
                

            } case 22: { // PUTS
                cout_debug(<< "trying to print\n");
                string str = pop_value<string>(stack);
                cout << str;
                break;
                

            } case 23: { // STR-CMP
                string s1 = pop_value<string>(stack);
                string s2 = pop_value<string>(stack);
                int cond = s1 == s2;
                push_to<int>(stack, new_ptr<int>(&cond));
                break;
            
            
            } case 24: { // STR-DUP
                stack.push_back(new_ptr(deref(string, stack.back())));
                break;


            } case 25: { // MALLOC
                void* memory = malloc(pop_value<int>(stack));
                stack.push_back(new_ptr<void*>(&memory));
                break;


            } case 26: { // PUTP
                cout << pop_value<void*>(stack);
                break;


            } case 27: { // R.int
                int val = deref(int, deref(void*, stack.back()));
                push_to<int>(stack, new_ptr<int>(&val));
                break;


            } case 28: { // W.int
                int val = pop_value<int>(stack);
                deref(int, deref(void*, (stack.back()))) = val;
                break;
                

            } case 29: { // FREE
                void* addr = pop_value<void*>(stack);
                free(addr);
                break;


            } case 30: { // AND 
                int cond = pop_value<int>(stack) and pop_value<int>(stack);
                push_to<int>(stack, new_ptr<int>(&cond));
                break;


            } case 31: { // OR
                int x = pop_value<int>(stack);
                int cond = pop_value<int>(stack) or x;
                push_to<int>(stack, new_ptr<int>(&cond));
                break;


            } case 32: { // PROC
                i = deref(int, act.value);
                cout_debug(<< "skipping after the return located at: " << i << endl);
                break;


            } case 33: { // reference
                string refn = deref(string, act.value);
                if (proc_references.contains(refn)) {
                    address_stack.push_back(i);
                    i = proc_references[refn];
                } elif (let_references.contains(refn)) {
                    push_to<void*>(stack, new_ptr<void*>(let_references[refn]));
                }
                // cout << "referencing to: " << deref(string, act.value) << ", setting IP to: " << i << endl;
                break;


            } case 34: { // RETURN
                i = address_stack.back();
                cout_debug(<< "resetting IP to: " << i << endl);
                address_stack.pop_back();
                break;
            
            
            } case 35: { // dummy for proc name
                break;
            } case 36: { // PTR SUM
                // cout << "popped\n";
                int64 x = pop_value<int64>(stack);
                int64 y = pop_value<int64>(stack);
                int64 temp = x + y;
                // cout << "summed\n";
                push_to<int64>(stack, new_ptr<int64>(&temp));
                // cout << "pushed\n";
                break;
            

            } case 37: { // ELIF
                bool cond = !(bool)pop_value<int>(stack);
                cout_debug(<< "condition is: " << cond << "\n");
                if (cond) {
                    i = deref(int, act.value);
                    cout_debug(<< "IF: setting 'i' to: " << i << "\n");
                }
                break;
                

            } case 38: { // STOI
                string str = pop_value<string>(stack);
                int temp = stoi(str);
                push_to<int>(stack, new_ptr<int>(&temp));
                break;


            } case 39: { // INPUT
                string str;
                getline(cin, str);
                // cout << "received: " << str << endl;
                push_to<string>(stack, new_ptr(str));
                break;


            } case 40: { // SYSTEM
                string cmd = pop_value<string>(stack);
                cout << "command: " << cmd << endl;
                system(cmd.c_str());
                break;


            } case 41: { // STRSUM
                string s1 = pop_value<string>(stack);
                string s2 = pop_value<string>(stack);
                s2 += s1;
                push_to<string>(stack, new_ptr(s2));
                break;


            } case 42: { // READ FILE
                string str = read_file(pop_value<string>(stack));
                push_to<string>(stack, new_ptr(str));
                break;

                
            } case 43: { // STK.LEN
                int temp = stack.size();
                push_to<int>(stack, new_ptr<int>(&temp));
                break;
            
            
            } case 44: { // CHDIR // SETCWD
                string str = pop_value<string>(stack);
                setcwd(str);
                break;


            } case 45: { // STRIP RIGHT
                string str = deref(string, stack.back());
                string str_right = str.substr(str.length()-1, str.length());
                string str_left  = str.substr(0, str.length()-1);
                push_to<string>(stack, new_ptr(str_left));
                push_to<string>(stack, new_ptr(str_right));
                break;


            } case 46: {
                string str = deref(string, stack.back());
                int strlen = str.length();
                push_to<int>(stack, new_ptr<int>(&strlen));
                break;


            } case 47: { // LET
                break;
            } case 48: { // LET NAME
                // printf("called let name\n");
                let_references[deref(string, act.value)] = new_ptr<void*>(stack.back());
                stack.pop_back();
                break;

            } case 49: { // SOFT DROP
                stack.pop_back();
                break;
            
            } default:{
                break;
                

            }
        }
        # ifdef DEBUG
            stack_dump(stack);
            system("pause");
            cout << "NEXT UP: idx: " << i << " with name " << get_name(program[i].id) << "\n";
            cout << "instruction idx: " << i-1 << " with name " << get_name(act.id) << " @ ";
        # endif
    }
    // cout << proc_references["swap_buffers"] << endl;
}