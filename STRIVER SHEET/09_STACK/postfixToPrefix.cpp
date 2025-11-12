#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Convert Postfix Expression to Prefix
Problem Link: (Hypothetical / Common Interview Problem)

Problem Statement:
You are given a string representing a postfix (Reverse Polish Notation) expression. 
Your task is to convert this postfix expression into its equivalent prefix expression.

------------------------------------------------------------
Example 1:
Input:  "ab+cde+**"
Output: "*+a*b+cde"

Explanation (step-based):
Postfix = "ab+cde+**"
- "ab+" → "+ab"
- Next "c" → "c"
- Next "de+" → "+de"
- "c +de *" → "*c+de"
- "+ab *c+de *" → "*(+ab)(*c+de)"
= "*+ab*c+de"

------------------------------------------------------------
Example 2:
Input:  "ab+"
Output: "+ab"

Constraints:
- Expression length n where 1 ≤ n ≤ 1000
- Expression may contain only lowercase/uppercase letters and +,-,*,/ operators
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Stack Based Prefix Construction (Optimal & Direct)
==================================================================
💡 Idea:
- Similar to postfix-to-infix conversion, but directly build prefix.
- Traverse postfix expression left → right:
  - If operand: push onto stack.
  - If operator: pop top two strings (second, first),
    then push "operator + first + second".

🧩 Algorithm:
1. Create empty stack<string>.
2. Traverse characters of postfix expression:
   - If operand → push as string.
   - If operator → pop second, pop first, form newExpr = op + first + second, push it.
3. At end, top of stack is full prefix expression.

⏱ Time Complexity: O(n) 
📦 Space Complexity: O(n)
*/

string postToPrefix(string postfix) {
    stack<string> st;
    for (char ch : postfix) {
        if (isalnum(ch)) {
            st.push(string(1, ch));
        } else {
            string second = st.top(); st.pop();
            string first  = st.top(); st.pop();
            string result = string(1, ch) + first + second;
            st.push(result);
        }
    }
    return st.top();
}


/*
==================================================================
Approach 2: Postfix → Infix → Prefix Conversion (Less Efficient)
==================================================================
💡 Idea:
- First convert Postfix → Infix (with parentheses)
- Then convert Infix → Prefix using conversion rules.

🧩 Algorithm:
1. Postfix → Infix using stack (same as earlier problem)
2. Infix → Prefix:
   - Reverse the expression.
   - Swap '(' with ')'.
   - Convert reversed infix to postfix.
   - Reverse postfix → prefix.

⏱ Time Complexity: O(n) but involves extra passes.
📦 Space Complexity: O(n) extra space.

(We include it for completeness, but **stack-based direct prefix** is cleaner.)
*/

// Step 1: Postfix → Infix
string postToInfix(string s) {
    stack<string> st;
    for (char ch : s) {
        if (isalnum(ch)) {
            st.push(string(1, ch));
        } else {
            string second = st.top(); st.pop();
            string first  = st.top(); st.pop();
            string res = "(" + first + ch + second + ")";
            st.push(res);
        }
    }
    return st.top();
}

// Step 2: Infix → Prefix
string infixToPrefix(string s) {
    // Reverse and swap brackets
    reverse(s.begin(), s.end());
    for (char &ch : s) {
        if (ch == '(') ch = ')';
        else if (ch == ')') ch = '(';
    }

    unordered_map<char,int> prec = {
        {'^',3}, {'*',2}, {'/',2}, {'+',1}, {'-',1}, {'(',0}
    };

    stack<char> st;
    string result;
    for (char ch : s) {
        if (isalnum(ch)) result += ch;
        else if (ch == '(') st.push(ch);
        else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top(); st.pop();
            }
            st.pop(); // remove '('
        } else {
            while (!st.empty() && prec[st.top()] > prec[ch]) {
                result += st.top(); st.pop();
            }
            st.push(ch);
        }
    }
    while (!st.empty()) {
        result += st.top(); st.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}

string postfixToPrefix_viaInfix(string postfix) {
    string infix = postToInfix(postfix);
    return infixToPrefix(infix);
}


/*
==================================================================
main() function
==================================================================
*/

int main() {
    vector<string> testCases = {
        "ab+cde+**",   // Expected: *+ab*c+de
        "ab+",         // Expected: +ab
        "abc*+",       // Expected: +a*bc
        "ab*cd*+"      // Expected: +*ab*cd
    };

    for (string postfix : testCases) {
        cout << "Postfix: " << postfix << endl;
        cout << "Prefix (Direct Stack): " << postToPrefix(postfix) << endl;
        cout << "Prefix (via Infix):    " << postfixToPrefix_viaInfix(postfix) << endl;
        cout << "--------------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Direct Stack Method:
   - Clean & direct (recommended in interviews).
   - O(n), O(n).

2. Indirect Method (Postfix → Infix → Prefix):
   - Educational, shows relationship between conversion steps.
   - More overhead, but still O(n).

👉 Final Recommendation: USE **Direct Stack Method** in interviews.
==================================================================
*/
