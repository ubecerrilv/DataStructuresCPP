//
// Created by ubecerril on 1/12/26.
//

#include <iostream>
#include <stack>

using namespace std;

// Prototype functions
bool balancedSymbols(const string& exp);
string infixToPostfix(const string& exp);
int evaluatePostfix(const string& exp);

// Auxiliar functions for infix to postfix
bool hasLowerPrecedenceThan(char a, char b);
int getPrecedence(char c);

int main() {
    cout << "This program proves 3 of the most common uses for the stack structure, it takes an infix expression, checks for balanced parenthesis,\n"
         << "transform the expression to postfix and evaluate this expression." << endl;
    const string exp{"(1+2)*(3+(4*5))"};

    if (balancedSymbols(exp)) {
        cout << "Expression \"" << exp << "\" has balanced parenthesis." << endl;

        const string postfixExp = infixToPostfix(exp);
        cout << "The postfix expression is: " << postfixExp << endl;

        const int result = evaluatePostfix(postfixExp);
        cout << "The evaluation result is: " << result << endl;
    }else {
        cerr << "Expression \"" << exp << "\" has no balanced parenthesis, check that." << endl;
    }

    return 0;
}

bool balancedSymbols(const string& exp) {
    cout << "1. Balancing symbols" << endl;

    // Make an empty list
    stack<char> st {};

    // Read each character into the stack
    for (auto c : exp) {
        // If opening symbol
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } // If closing symbol
        else if (c == ')' || c == '}' || c == ']') {
            if (st.empty()) {
                return false;
            }

            const char top = st.top();
            st.pop();
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;
                }
        }
    }

    if (st.empty()) {
        return true;
    }
    return false;
}
string infixToPostfix(const string& exp) {
    cout << "2. Infix to postfix expressions. " << endl;

    // Make an empty list
    stack<char> st {};
    // Variable to save the output
    string output {};

    // Read each character onto the stack
    for (auto c : exp) {
        // If it is a number we output
        if (isdigit(c)) {
            output += c;
        }else { // If an operator is found
            // If it is a right parenthesis we pop until we find the corresponding left parenthesis
            if (c == ')') {
                while (st.top() != '(') {
                    output += st.top();
                    st.pop();
                }
                st.pop();

            // We find any other symbol
            }else if (st.empty()) {
                st.push(c);
            }else {
                while ((!hasLowerPrecedenceThan(st.top(), c)) && st.top() != '(') {
                    output += st.top();
                    st.pop();
                    if (st.empty())
                        break;
                }
                st.push(c);
            }
        }
    }

    while (!st.empty()) {
        const char c = st.top();
        st.pop();
        output += c;
    }
    return output;
}
int evaluatePostfix(const string& exp) {
    cout << "3. Evaluate postfix expressions" << endl;

    // Make an empty list
    stack<int> st {};

    // Read each character onto the stack
    for (auto& c : exp) {
        // When a number is seen it is push into the stack
        if (isdigit(c)) {
            st.push(c - '0');
        }
        // When an operator is seen we apply this operator to the last 2 numbers
        else {
            const int a = st.top();
            st.pop();
            const int b = st.top();
            st.pop();

            switch (c) {
                case '+':
                    st.push(a + b);
                    break;
                case '-':
                    st.push(a - b);
                    break;
                case '*':
                    st.push(a * b);
                    break;
                default: ;
            }
        }
    }
    return st.top();
}


bool hasLowerPrecedenceThan(const char a, const char b) {
    return getPrecedence(a) < getPrecedence(b);
}
int getPrecedence(const char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
            return 2;
        case '(':
            return 3;
        default:
            return 0;
    }
}