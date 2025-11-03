#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Infix to Postfix Conversion
 Problem Link: (Common algorithm problem)

 Problem Statement:
 Given an infix expression string `exp`, convert it to postfix notation.
 The expression can contain:
 - operands (alphabets and digits),
 - operators (+, -, *, /, ^),
 - parentheses.

 The precedence is: ^ (highest), * and /, then + and -,
 Operators with equal precedence, except ^, are left associative.
 ^ is right associative.

-------------------------------------------------
 Example:
 Input: "A+B*(C^D-E)"
 Output: "ABD^E-C*+"
 Explanation:
 Standard conversion of infix to postfix respecting precedence and associativity.
-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Using Stack for Operators
// -------------------------------------------------
/*
💡 Idea:
   - Use stack to hold operators and parentheses.
   - Append operands directly to the result.
   - When encountering operator:
       - Pop stack while top operator has higher or equal precedence (consider associativity).
       - Push current operator.
   - On '(' push it, on ')' pop until '('.
   - At end, pop remaining operators.

🧩 Algorithm:
   1. Define operator precedence map.
   2. For each char ch:
       - If operand: append to output.
       - If '(': push it.
       - If ')': pop until '('.
       - Else (operator):
          - While stack not empty and precedence top >= ch:
                - Pop and append to output.
          - Push ch.
   3. Pop remaining from stack.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Helper function to check if operator is right associative (^)
bool isRightAssociative(char op) {
    return op == '^';
}

string infixToPostfix(const string& exp) {
    stack<char> st;
    string result;

    for (char ch : exp) {
        if (isalnum(ch)) {  // operand: letter or digit
            result += ch;
        } else if (ch == '(') {
            st.push(ch);
        } else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();  // pop '('
        } else {  // operator
            while (!st.empty() && st.top() != '(') {
                char topOp = st.top();
                int topPrec = precedence(topOp);
                int currPrec = precedence(ch);
                if ((topPrec > currPrec) || (topPrec == currPrec && !isRightAssociative(ch))) {
                    result += topOp;
                    st.pop();
                } else {
                    break;
                }
            }
            st.push(ch);
        }
    }

    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    string infix = "A+B*(C^D-E)";
    string postfix = infixToPostfix(infix);
    cout << "Infix:   " << infix << endl;
    cout << "Postfix: " << postfix << endl;  // Expected: ABD^E-C*+

    // Additional test cases
    vector<string> tests = {
        "a+b*c",
        "(a+b)*c",
        "a+b+c",
        "a^b^c",
        "((A+B)*C)-(D-E)*(F+G)"
    };
    for (auto &exp : tests) {
        cout << "Infix: " << exp << " --> Postfix: " << infixToPostfix(exp) << endl;
    }

    // ✅ Approach Overview
    /*
    - Uses stack to maintain operators respecting precedence and associativity.
    - Parses expression left to right, outputting operands immediately.
    - Runs in linear time relative to expression length.
    */

    return 0;
}
