//
// Tomás Oliveira e Silva, AED, November 2021
//
// matched-parenthesis verification
//

#include "aStack.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

int check_parenthesis(const char *s) {
    aStack<int> intStack;
    for (int i = 0; s[i] != '\0'; i++) {

      if(s[i] == '(') { intStack.push(i); }
      else if(s[i] == ')') { 
        if(intStack.is_empty()) {
          cout << "  unmatched ')' at position " << i << endl;
          return -1;
        }
        cout << "  '(' at position " << intStack.pop() << " and matching ')' at position " << i << endl;
      }
    }

    if(intStack.is_empty()) { return 0; }
    while(!intStack.is_empty()) {
      cout << "  unmatched '(' at position " << intStack.pop() << endl;
    }
    return -1;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        cerr << "usage: " << argv[0] << " [arguments...]" << endl;
        cerr << "example: " << argv[0] << " 'abc(def)ghi' 'x)(y'" << endl;
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        cout << argv[i] << endl;
        if (check_parenthesis(argv[i]) == 0)
            cout << "  good" << endl;
        else
            cout << "  bad" << endl;
    }
    return 0;
}
