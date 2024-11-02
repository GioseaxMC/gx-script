/* ===========================================================================================
 *  FILE PURPOSE: TESTING AND NOTHING MORE
 * ===========================================================================================
 * 
 * This file, as it stands, serves no functional or operational purpose within the broader
 * context of the project, application, or system in which it resides. It is designed purely
 * for the purpose of experimentation, debugging, or preliminary testing and is not intended
 * to contribute to the end functionality, performance, or value of any of the final software
 * deliverables. 
 * 
 * Indeed, its primary and sole reason for existence is as a "test file," wherein code 
 * snippets, functions, or other constructs may be written and executed with the expectation
 * of achieving nothing significant or impactful. It is a sandbox, a playground of sorts, 
 * a repository for temporary implementations, exploratory code fragments, and various 
 * trial-and-error mechanisms. This file exists to absorb all manner of unpolished, 
 * unrefined, and possibly throwaway code as the developer sees fit, without any concern for 
 * efficiency, cleanliness, or adherence to the standards of production-ready code.
 * 
 * Should a developer or programmer happen to find themselves reading this comment in search 
 * of deeper insight or practical information about the contents of this file, let it be 
 * known here and now: there is none to be found. The contents within are devoid of any 
 * meaningful logic, impactful calculations, or strategic implementations relevant to any 
 * real-world application.
 * 
 * In summation, this file is what may colloquially be referred to as "filler." It is 
 * "placeholder" material, absent of utility, and laden with code that is, by design, 
 * disposable and dispensable. It is merely a testing ground, a means for checking syntax,
 * experimenting with compiler behavior, or otherwise conducting work that, in and of 
 * itself, serves no purpose in the final product.
 * 
 * Therefore, any and all code, comments, variables, and functions within should be treated 
 * with due regard as strictly temporary, transient, and fleeting in nature. The entirety 
 * of this file is meant to be considered a "useless test" file, and thus, should not be 
 * relied upon or utilized as part of any meaningful or long-lasting implementation. 
 * In essence, this file is, in the most sincere terms, purposeless beyond the bounds of 
 * testing, prototyping, and exploration.
 * ===========================================================================================
 */

# include <iostream>

#define bitsize(xs) (sizeof(xs)*8)
#define deref(t, xs, idx) *((t*)(xs)+(idx))
#define getbit(num, bit) bool(num & (1 << bit))

using namespace std;

typedef unsigned long long word;

string showbyte(char value) {
    string temp = "";
    for(int i=7; i>=0; --i) {
        temp += ((getbit(value, i)) ? "1" : "0");
    }
    return temp;
}

int ptr_main(void){
    printf("sizeof(char*) = %i\n", sizeof(char*));
    printf("sizeof(char**) = %i\n", sizeof(char**));
    printf("sizeof(int) = %i\n", sizeof(int));
    printf("sizeof(string) = %i\n", sizeof(string));
    printf("sizeof(string*) = %i\n", sizeof(string*));
    
    // string str = "ciao";
    // deref(string*, ptr, 0) = &str;
    
    // cout << *deref(string*, ptr, 0) << endl;

    deref(char, ptr, 0) = 254;
    deref(char, ptr, 1) = 10;

    printf("ptr.string.0 = ");
    for (int i=0; i<2*sizeof(char); ++i) {
        printf("%s-",showbyte(deref(char, ptr, i)).c_str());
    }
    printf("\ndone showing.\n");
    
    
    system("pause");
}