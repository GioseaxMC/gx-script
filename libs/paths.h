#include "strutils.h"

using namespace std;

#define elif else if

string path_delims = "\\/";

vector<string> divide_steps(string path){
    vector<string> tokens;
    string token;
    for(int i=0; i<path.length(); i++) {
        char c = path[i];
        if (is_delim(c, path_delims)) {
            if (token.length()){
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }
    if (token.length()) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<string> normalize_steps(vector<string> steps) {
    vector<string> temp;
    for(int i=0; i<steps.size(); i++){
        string step = steps[i];
        if (step == ".") {
            continue;
        } elif (step == "..") {
            if (!temp.empty() and temp.back() != "..") {
                temp.pop_back();
                continue;
            }
        }
        temp.push_back(step);
    }
    return temp;
}

class path {
    private:
    vector<string> steps;
    
    string get() {
        return "./" + join("/", steps);
    }

    public:
    void load(string path) {
        steps = divide_steps(path);
        steps = normalize_steps(steps);
    }

    void dump() {
        for(string word : steps) {
            cout << "path: '" << word << "'\n";
        }
    }

    string operator() (){ return get(); }

    friend ostream& operator<< (ostream& os, path& obj) {
        os << obj.get();
        return os;
    }

    path operator+ (path& obj) {
        path temp;
        temp.steps = steps;
        for(string str : obj.steps) {
            temp.steps.push_back(str);
        }
        temp.steps = normalize_steps(temp.steps);
        return temp;
    }

    void operator+= (path& obj) {
        for(string str : obj.steps) {
            steps.push_back(str);
        }
        steps = normalize_steps(steps);
    }

    path dir_name() {
        path temp = get();
        temp.steps.pop_back();
        return temp;
    }

    void operator= (string path) { load(path); }
    path() {}
    path(const char* path) { string str = string(path); load(str); }
    path(string path) { load(path); }
};