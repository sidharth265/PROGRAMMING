#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Convert Prefix Expression to Postfix
Problem Link: (Hypothetical / Common Interview Problem)

Problem Statement:
You are given a string representing a prefix notation expression.  
Your task is to convert it into its equivalent postfix (Reverse Polish Notation) form.

------------------------------------------------------------
Example 1:
Input:   "*-A/BC-/AKL"
Output:  "ABC/-AK/L-*"

Explanation (Step-by-step):
Prefix:  * - A / B C - / A K L
- "- A / B C"  → "A B C / -"
- "- / A K L"  → "A K / L -"
- "* (A B C / -) (A K / L -)" → "ABC/-AK/L-*"

------------------------------------------------------------
Example 2:
Input:   "+AB"
Output:  "AB+"

Explanation:
Prefix: + A B  
Output: "AB+"

------------------------------------------------------------
Constraints:
- Expression length n where 1 ≤ n ≤ 1000
- Expression may contain only lowercase/uppercase letters or digits (operands),
  and operators {+, -, *, /, ^}
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Direct Stack Method (Optimal)
==================================================================
💡 Idea:
- Traverse prefix expression from right to left.
- If operand → push onto stack.
- If operator → pop two operands (first, second), form "first second operator" 
  (postfix order), push back.
- At the end, stack top is the postfix expression.

🧩 Algorithm:
1. Initialize stack<string>.
2. Traverse prefix from right → left:
   a) If operand → push it.
   b) If operator:
       - Pop top (first), 
       - Pop next (second).
       - Form newExpr = first + second + op.
       - Push back.
3. Top of stack = full postfix.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

string prefixToPostfix(string prefix) {
    stack<string> st;
    for (int i = prefix.length()-1; i >= 0; i--) {
        char ch = prefix[i];
        if (isalnum(ch)) {
            st.push(string(1, ch));
        } else {
            string first = st.top();  st.pop();
            string second = st.top(); st.pop();
            string res = first + second + ch;
            st.push(res);
        }
    }
    return st.top();
}

/*
==================================================================
Approach 2: Prefix → Infix → Postfix Conversion (Alternative)
==================================================================
💡 Idea:
- Convert to infix first using stack (Prefix → Infix).
- Then apply Infix → Postfix standard algorithm.

🧩 Algorithm (High level):
1. Prefix → Infix: process right to left, put parentheses properly.
2. Infix → Postfix: Use operator precedence stack algorithm.
3. Return result.

⏱ Time Complexity: O(n), but does 2 passes.
📦 Space Complexity: O(n).
*/

// Step 1: Prefix → Infix
string prefixToInfix(string prefix) {
    stack<string> st;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];
        if (isalnum(ch)) {
            st.push(string(1, ch));
        } else {
            string first = st.top();  st.pop();
            string second = st.top(); st.pop();
            string res = "(" + first + ch + second + ")";
            st.push(res);
        }
    }
    return st.top();
}

// Step 2: Infix → Postfix
string infixToPostfix(string infix) {
    unordered_map<char, int> prec = {
        {'^', 3}, {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1}, {'(', 0}
    };

    stack<char> st;
    string result = "";
    for (char ch : infix) {
        if (isalnum(ch)) {
            result += ch;
        }
        else if (ch == '(') st.push(ch);
        else if (ch == ')') {
            while(!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop(); // remove '('
        }
        else { // operator
            while(!st.empty() && prec[st.top()] >= prec[ch]) {
                result += st.top();
                st.pop();
            }
            st.push(ch);
        }
    }
    while(!st.empty()) {
        result += st.top(); st.pop();
    }
    return result;
}

string prefixToPostfix_viaInfix(string prefix) {
    string infix = prefixToInfix(prefix);
    return infixToPostfix(infix);
}

/*
==================================================================
main() function
==================================================================
*/

int main() {
    vector<string> testCases = {
        "*-A/BC-/AKL",  // Expected: ABC/-AK/L-*
        "+AB",          // Expected: AB+
        "*+ABC",        // Expected: AB+C*
        "+*AB/CD"       // Expected: AB*CD/+
    };

    for (string prefix : testCases) {
        cout << "Prefix: " << prefix << endl;
        cout << "Postfix (Direct):     " << prefixToPostfix(prefix) << endl;
        cout << "Postfix (via Infix):  " << prefixToPostfix_viaInfix(prefix) << endl;
        cout << "----------------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Direct Stack Approach:
   - Simple, clean, O(n).
   - Stack stores partial postfix strings.
   - Recommended in interviews.

2. Indirect (Prefix → Infix → Postfix):
   - Good to know for learning.
   - Involves two conversions, slightly more overhead.
   - Still O(n).

👉 Final Suggestion: In interviews, use the **Direct Stack Approach**.
==================================================================
*/
