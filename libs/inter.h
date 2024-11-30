# include "paths.h"
# include "dicts.h"

# define deref(type, ptr) *((type*)(ptr))
# define elif else if

# define int64 uint64_t

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
        throw bad_alloc();
    }

    new (n_str) string(str_ptr);

    return static_cast<void*>(n_str);
}

Hash<int> references;

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
    }
    else {
        return "-";
    }
}

struct action{
    int id;
    void* value = malloc(sizeof(void*)); // alloc s(void*) bytes for pointers
};

template<typename T>
action push(T value){
    action temp;
    temp.id = op.PUSH;
    deref(int, temp.value) = value;
    return temp;
}

action sum(){
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
    references.add(name, -1);
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

template<typename T>
T pop_value(vector<void*> &stack) {
    if (stack.size()) {
        T x = deref(T, stack.back());
        cout_debug(<< "stack back: " << stack.back() << ", variable location: " << &x << "\n");
        free(stack.back());
        stack.pop_back();
        return x;
    } else {
        printf("Error: Segmentation fault : stack size is %i\n", stack.size());
        throw -1;
    }
}

template<typename T>
void push_to(vector<void*> &stack, void* value){
    cout_debug(<< "pushing '" << value << "', which is equal to '" << deref(T, value) << "' to stack.\n");
    stack.push_back(value);
}

void parse_program(vector<string> tokens, vector<action> &temp){
    string str;
    for(int i=0; i<tokens.size(); ++i) {
        str = tokens[i];
        if (str == "dump") {
            temp.push_back(dump());
        } elif (str == "dup") {
            temp.push_back(dup());
        } elif (str == "+") {
            temp.push_back(sum());
        } elif (str == "-") {
            temp.push_back(sub());
        } elif (str == "/") {
            temp.push_back(div());
        } elif (str == "*") {
            temp.push_back(mul());
        } elif (is_numeric(str)) {
            temp.push_back(push(stoi(str)));
        } elif (str == "if") {
            temp.push_back(iff());
        } elif (str == "else") {
            temp.push_back(_else());
        } elif (str == "end") {
            temp.push_back(end());
        } elif (str == "while") {
            temp.push_back(whl());
        } elif (str == "do") {
            temp.push_back(doo());
        } elif (str == "<") {
            temp.push_back(lesst());
        } elif (str == ">") {
            temp.push_back(bigger());
        } elif (str == "=") {
            temp.push_back(cmp());
        } elif (str == "swap") {
            temp.push_back(swap());
        } elif (str == "rotate") {
            temp.push_back(rotate());
        } elif (str == "stack_dump") {
            temp.push_back(stk_dmp());
        } elif (str == "drop") {
            temp.push_back(drop());
        } elif (str == "pause") {
            temp.push_back(pause());
        } elif (str == "newl") {
            temp.push_back(newline());
        } elif (represents_string(str)) {
            string strn = derep_str(str);
            action act = str_literal();
            free(act.value);
            act.value = new_ptr(strn);
            cout_debug(<< "pushed: '" << deref(string, act.value) << "'\n");
            temp.push_back(act);
        } elif (str == "puts") {
            temp.push_back(puts());
        } elif (str == "strcmp") {
            temp.push_back(str_cmp());
        } elif (str == "strdup") {
            temp.push_back(str_dup());
        } elif (str == "malloc") {
            temp.push_back(alloc());
        } elif (str == "putp") {
            temp.push_back(putp());
        } elif (str == "R.int") {
            temp.push_back(atint());
        } elif (str == "W.int") {
            temp.push_back(setint());
        } elif (str == "free") {
            temp.push_back(mfree());
        } elif (str == "&&") {
            temp.push_back(_and());
        } elif (str == "||") {
            temp.push_back(_or());
        } elif (str == "proc") {
            temp.push_back(proc());
            temp.push_back(proc_name(tokens[++i]));
            cout_debug(<< "declared proc: " << tokens[i] << endl);
        } elif (str == "return") {
            temp.push_back(ret());
        } elif (str == "ptr+") {
            temp.push_back(ptr_sum());
        } elif (str == "if*") {
            temp.push_back(_elif());
        } elif (str == "stoi") {
            temp.push_back(_stoi());
        } elif (str == "input") {
            temp.push_back(input());
        } elif (str == "system") {
            temp.push_back(_system());
        } elif (str == "strsum") {
            temp.push_back(str_sum());
        }
        else {
            if (references.contains(str)) {
                temp.push_back(ref(str));
                cout_debug(<< "referenced: " << str << endl);
            } else {
                printf("unknown instruction '%s' at position '%i'\n", str.c_str(), i);
            }   
        }
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

void compute_crossreference(vector<action> &acts) {
    vector<action*> op_stack; // Moved this outside the loop
    // actions_dump(acts);
    int i = 0;
    while (i < acts.size()) {
        action* act = &acts[i];
        int id = act->id;
        i++;
        
        // printf_debug(("crossreferencing instruction '%s'\n", get_name(id).c_str()));
        
        if (id == op.IF or id == op.ELIF) { // IF
            op_stack.push_back(act);

        } elif (id == op.ELSE) { // ELSE
            if (!op_stack.empty()) {
                int type = (op_stack.back()->id == op.IF) - (op_stack.back()->id == op.ELIF);
                if (type) {
                    deref(int, op_stack.back()->value) = i;
                    cout_debug(<< "setting else-1 which is: " << get_name(op_stack.back()->id) << endl);
                    op_stack.pop_back();
                    if (type == -1 and !op_stack.empty()) {
                        if (op_stack.back()->id == op.ELSE) {
                            deref(int, op_stack.back()->value) = i-1;
                            cout_debug(<< "setting else-2 which is: " << get_name(op_stack.back()->id) << endl);
                            op_stack.pop_back();
                        }
                    }
                }
                
            }
            op_stack.push_back(act);
        
        } elif (id == op.END) { // END
            if (!op_stack.empty()) {
                deref(int, op_stack.back()->value) = i;
                cout_debug(<< "end cleared previous which was: " << get_name(op_stack.back()->id) << endl);
                op_stack.pop_back();
                if ((!op_stack.empty())) {
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
                        act->value = nullptr;
                    }
                }
            }
        
        } elif (id == op.DO) { // DO
            op_stack.push_back(act); // Push 'DO' to the stack
        } elif (id == op.WHILE) {
            deref(int, act->value) = i;
            op_stack.push_back(act); // Push 'WHILE' to the stack
        }
          elif (id == op.PROC) {
            op_stack.push_back(act);
            cout_debug(<< "setting up procedure name for: " << deref(string, acts[i].value) << endl);
            references[deref(string, acts[i].value)] = i+1;
        } elif (id == op.RET) {
            deref(int, op_stack.back()->value) = i; // set the PROC pointer to after the end so we skip the funzion at execution.
            op_stack.pop_back();
        }
        else {
            // printf_debug((" - instruction with name '%s' is not crossreference-able.\n", get_name(id).c_str()));
        }
        printf_debug((" -- Done crossreferencing '%s'.\n", get_name(id).c_str()));
    }
    if (!op_stack.empty()) {
        printf("ERROR: unmatched if or while statement.\n");
        cout << "crossreference stack dump:\n";
        for(action* a : op_stack) {
            cout << "\n\taction: " << get_name(a->id) << "\n";
        }
        throw -1;
    }
    cout_debug(<< "got to crossreferecing end\n");
}

vector<int> address_stack;

#define stackn(x) stack[stack.size()+(x)]
int inter_main(vector<action> &program, vector<void*> &stack){
    int i = 0;
    while (i < program.size()) {
        action& act = program[i];
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
                void* addr =  pop_value<void*>(stack);
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
                address_stack.push_back(i);
                i = references[deref(string, act.value)];
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
                system(pop_value<string>(stack).c_str());
                break;


            } case 41: { // STRSUM
                string s1 = pop_value<string>(stack);
                string s2 = pop_value<string>(stack);
                s2 += s1;
                push_to<string>(stack, new_ptr(s2));
                break;


            }
            default:{
                break;
                

            }
        }
        # ifdef DEBUG
            stack_dump(stack);
            // system("pause");
            cout << "instruction idx: " << i-1 << " with name " << get_name(act.id) << "\n";
        # endif
    }
    // cout << references["swap_buffers"] << endl;
}