#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Convert Prefix Expression to Infix
Problem Link: (Hypothetical / Common Interview Problem)

Problem Statement:
You are given a string representing a prefix expression. 
Your task is to convert this prefix expression into its equivalent infix expression 
(with proper parentheses).

------------------------------------------------------------
Example 1:
Input:   "*+AB-CD"
Output:  "((A+B)*(C-D))"

Explanation:
- Prefix: * + A B - C D
- Step 1: "+AB" → "(A+B)"
- Step 2: "-CD" → "(C-D)"
- Step 3: "* (A+B) (C-D)" → "((A+B)*(C-D))"

------------------------------------------------------------
Example 2:
Input:   "+AB"
Output:  "(A+B)"

Constraints:
- Expression length n where 1 ≤ n ≤ 1000
- Expression may contain only uppercase/lowercase letters or digits (operands)
  and operators (+, -, *, /, ^).
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Stack based (Optimal)
==================================================================
💡 Idea:
- Traverse the prefix expression from right to left.
- If operand: push onto stack.
- If operator: pop two operands (first = left, second = right),
  form "(first op second)", push back into stack.
- At end, stack holds full infix expression.

🧩 Algorithm:
1. Initialize an empty stack<string>.
2. Traverse string from right to left:
   a) If alphanumeric → push it as string.
   b) Else (operator):
       - Pop top (first)
       - Pop next (second)
       - Form "(first op second)" and push back.
3. Return top of stack.

⏱ Time Complexity: O(n)   (one pass).
📦 Space Complexity: O(n) (stack stores partial expressions).
*/

string prefixToInfix(string prefix) {
    stack<string> st;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];
        if (isalnum(ch)) {
            st.push(string(1, ch));
        } else {
            string first  = st.top(); st.pop();
            string second = st.top(); st.pop();
            string result = "(" + first + ch + second + ")";
            st.push(result);
        }
    }
    return st.top();
}

/*
==================================================================
Approach 2: Expression Tree (Alternative)
==================================================================
💡 Idea:
- Build an expression tree from prefix notation.
- Then do inorder traversal with parentheses to generate infix.
- Useful for demonstrating parsing concepts.

🧩 Algorithm:
1. Parse prefix expression into an expression tree:
   - Operands = leaf nodes.
   - Operators → internal nodes with 2 children.
2. Inorder traversal of tree with parentheses → Infix.

⏱ Time Complexity: O(n).
📦 Space Complexity: O(n) (tree nodes + recursion stack).
*/

struct Node {
    string val;
    Node* left;
    Node* right;
    Node(string v) : val(v), left(NULL), right(NULL) {}
};

// Build expression tree from prefix (recursive)
Node* buildTreeHelper(const string& s, int &i) {
    if (i >= s.length()) return nullptr;
    char ch = s[i++];
    if (isalnum(ch)) {
        return new Node(string(1, ch));
    } else {
        Node* root = new Node(string(1, ch));
        root->left  = buildTreeHelper(s, i);
        root->right = buildTreeHelper(s, i);
        return root;
    }
}

Node* buildExpressionTree(const string& prefix) {
    int idx = 0;
    return buildTreeHelper(prefix, idx);
}

string inorderTraversal(Node* root) {
    if (!root) return "";
    if (!root->left && !root->right) return root->val;
    return "(" + inorderTraversal(root->left) + root->val + inorderTraversal(root->right) + ")";
}

string prefixToInfixRecursive(string prefix) {
    Node* root = buildExpressionTree(prefix);
    return inorderTraversal(root);
}


/*
==================================================================
main() function
==================================================================
*/
int main() {
    vector<string> testCases = {
        "*+AB-CD",     // Expected: ((A+B)*(C-D))
        "+AB",         // Expected: (A+B)
        "*+ABC",       // Expected: ((A+B)*C)
        "+*AB/CD",     // Expected: ((A*B)+(C/D))
    };

    for (string prefix : testCases) {
        cout << "Prefix: " << prefix << endl;
        cout << "Infix (Stack):     " << prefixToInfix(prefix) << endl;
        cout << "Infix (Recursive): " << prefixToInfixRecursive(prefix) << endl;
        cout << "---------------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Stack-based approach:
   - Clean, direct, and fast.
   - O(n), O(n).
   - BEST for interviews.

2. Recursive Expression Tree:
   - More illustrative.
   - Good for understanding parsing logic.
   - But extra overhead of tree building.
   - Also O(n), O(n).

👉 Recommendation: Use **Stack-based approach** in interviews.
==================================================================
*/
