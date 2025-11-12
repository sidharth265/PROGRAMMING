#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Infix to Prefix Conversion
 Problem Link: (Common algorithm problem)

 Problem Statement:
 Given an infix expression string `s` with operands, operators (+, -, *, /, ^), 
 and parentheses, convert it to prefix notation.

 Operators have precedence:
  - '^' highest, right-associative
  - '*', '/' next, left-associative
  - '+', '-' lowest, left-associative

-------------------------------------------------
 Example:
 Input: "A+B*(C^D-E)"
 Output: "+A*B^-CDE"
 Explanation:
 Convert considering reversed order and operator precedence.
-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Reverse Infix + Modified Shunting Yard for Prefix
// -------------------------------------------------
/*
💡 Idea:
   - Reverse infix expression.
   - Swap '(' with ')' and vice versa.
   - Convert reversed expression to postfix (using precedence and associativity rules).
   - Reverse postfix to get prefix expression.

🧩 Algorithm:
   1. Reverse string, swap brackets.
   2. Use operator stack based on precedence:
       - For '^' (right associative), pop while top's precedence >= current.
       - For others (left associative), pop while top's precedence > current.
   3. Append operands directly.
   4. At the end, pop remaining operators.
   5. Reverse output string to get prefix.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

string infixToPrefix(string s) {
    reverse(s.begin(), s.end());
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == '(') s[i] = ')';
        else if (s[i] == ')') s[i] = '(';
    }
    stack<char> st;
    string result;
    for (char ch : s) {
        if (isalnum(ch)) {
            result += ch;
        } else if (ch == '(') {
            st.push(ch);
        } else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();
        } else {
            // Operator
            if (ch == '^') {
                while (!st.empty() && precedence(st.top()) > 0 
                       && precedence(st.top()) >= precedence(ch)) {
                    result += st.top();
                    st.pop();
                }
            } else {
                while (!st.empty() && precedence(st.top()) > 0 
                       && precedence(st.top()) > precedence(ch)) {
                    result += st.top();
                    st.pop();
                }
            }
            st.push(ch);
        }
    }
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    string infix = "A+B*(C^D-E)";
    string prefix = infixToPrefix(infix);
    cout << "Infix:  " << infix << endl;
    cout << "Prefix: " << prefix << endl; // Expected: +A*B^-CDE

    vector<string> tests = {
        "a+b*c",
        "(a+b)*c",
        "a+b+c",
        "a^b^c",
        "((A+B)*C)-(D-E)*(F+G)"
    };
    for (const auto& exp : tests) {
        cout << "Infix: " << exp << " --> Prefix: " << infixToPrefix(exp) << "\n";
    }

    // ✅ Approach Overview
    /*
    - Reverses infix and converts to postfix with tweaks.
    - Handles precedence and right-associativity carefully.
    - Result reversed at end to get prefix.
    */

    return 0;
}
