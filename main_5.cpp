#include <iostream>
#include <string>

enum State {
    START,      
    LT,         // '<'
    GT,         // '>'
    EQ,         // '='
    EXCL,       // '!'
    EQ_EQ,      // "=="
    EXCL_EQ,    // "!="
    LT_EQ,      // "<="
    GT_EQ,      // ">="
    REJECT      
};

                                                   // проверяем строку на соответствие операторам сравнения
bool isComparisonOperator(const std::string& s) {
    if (s.empty()) 
        return false;

    State state = START;

    for (char c : s) {
        if (state == START) {
            if (c == '<') state = LT;
            else if (c == '>') state = GT;
            else if (c == '=') state = EQ;
            else if (c == '!') state = EXCL;
            else state = REJECT;
        }
        else if (state == LT) {
            if (c == '=') state = LT_EQ;
            else state = REJECT;
        }
        else if (state == GT) {
            if (c == '=') state = GT_EQ;
            else state = REJECT;
        }
        else if (state == EQ) {
            if (c == '=') state = EQ_EQ;
            else state = REJECT;
        }
        else if (state == EXCL) {
            if (c == '=') state = EXCL_EQ;
            else state = REJECT;
        }
        else if (state == EQ_EQ || state == EXCL_EQ || 
                 state == LT_EQ || state == GT_EQ) {
            state = REJECT;
        }

        if (state == REJECT)
            return false;
    }

    return (state == LT ||        // "<"
            state == GT ||        // ">"
            state == EQ_EQ ||     // "=="
            state == EXCL_EQ ||   // "!="
            state == LT_EQ ||     // "<="
            state == GT_EQ);      // ">="
}

int main() {
    std::string input = ">=";  

    if (isComparisonOperator(input)) {
        std::cout << "\"" << input << "\" -> оператор\n";
    } else {
        std::cout << "\"" << input << "\" -> не оператор\n";
    }

    return 0;
}