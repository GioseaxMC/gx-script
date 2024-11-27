# include <fstream>
# include <sstream>
# include <iostream>
# include <string>
# include <vector>

#define derep_head derep_str

using namespace std;

const string delims = " \n\"";

bool represents_string(string str){
    return str[0] == '"' and str[str.length()-1] == '"';
}

bool represents_header(string str){
    return str[0] == '<' and str[str.length()-1] == '>';
}

string derep_str(string str) {
    return str.substr(1, str.length()-2);
}

string replace_filename(string original_path, string new_filename) {
    size_t last_slash_pos = original_path.find_last_of("/\\");
    
    if (last_slash_pos != string::npos) {
        string new_path = original_path.substr(0, last_slash_pos + 1) + new_filename;
        return new_path;
    } else {
        return new_filename;
    }
}

size_t iota(char reset = 0){
    static int counter = 0;
    if (reset) {
        counter = 0;
    }
    return counter++;
}

bool is_delim(char ch, const string delimiters) {
    return delimiters.find(ch) != string::npos;
}

string read_file(string file_name){
    ifstream file(file_name);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

string readline(string str, int count) {
    string temp;
    int lines = 0;
    for(char c : str) {
        if (is_delim(c, "\n")){
            if (lines >= count) {
                return temp;
            } else {
                temp.clear();
                lines++;
            }
        } else {
            temp += c;
        }
    }
    return temp;
}

string strip(string &str, string chr = "\n") {
    while(1) {
        int finder = str.find(chr);
        if (finder == string::npos) {
            return str;
        }
        str.erase(finder, 1);
    }
}

string join(string chr, vector<string> vec, int start = 0){
    string temp;
    for (int i=start; i<vec.size(); ++i) {
        temp += vec[i];
        if (i != vec.size()-1) {
            temp += chr;
        }
    }
    return temp;
}

string replace_where(string &text, string str_r, string str_n){
    // int used_pos = 0;
    while (1) {
        int pos = text.find(str_r);
        if (pos != string::npos) {
            // cout << "new: " << str_n << " old: " << str_r << endl;
            text.replace(pos, str_r.length(), str_n);
            // used_pos = pos+str_n.length();
        } else {
            break;
        }
    }
    return text;
}

bool is_numeric(string str) {
    if (str.empty()){
        return 0;
    }
    if (str[0] == '-') {
        if (str.length() == 1) {
            return 0;
        }
        str.erase(0,1);
    }
    if (str.empty()){
        return 0;
    }
    for(char c : str) {
        if (!isdigit(c)) {
            return 0;
        }
    }
    return 1;
}

vector<string> split(string &file, char chr = ' ') {
    vector<string> temp;
    string temp_str;
    for (int i=0; i<file.length(); ++i) {
        if(file[i] == chr) {
            temp.push_back(temp_str);
            temp_str.clear();
        } else {
            temp_str += file[i];
        }
    }
    if (temp_str.length()) {
            temp.push_back(temp_str);
            temp_str.clear();
    }
    return temp;
}
