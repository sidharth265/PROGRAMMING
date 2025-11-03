#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Convert Postfix Expression to Infix
Problem Link: (Hypothetical / Interview Problem)

Problem Statement:
You are given a string representing a postfix (Reverse Polish Notation) expression. 
Your task is to convert this postfix expression into its equivalent infix expression 
with proper parenthesis.

------------------------------------------------------------
Example 1:
Input:  "ab+cde+**"
Output: "((a+b)*(c*(d+e)))"

Explanation:
- Postfix "ab+" → "(a+b)"
- Next push "c"
- Next push "d"
- Next push "e"
- "d e +" → "(d+e)"
- "c (d+e) *" → "(c*(d+e))"
- "(a+b) (c*(d+e)) *" → "((a+b)*(c*(d+e)))"

------------------------------------------------------------
Example 2:
Input:  "ab+"
Output: "(a+b)"

------------------------------------------------------------
Constraints:
- Expression length n where 1 ≤ n ≤ 1000
- Expression may contain only lowercase/uppercase letters and +,-,*,/ operators
------------------------------------------------------------
*/

/* 
==================================================================
Approach 1: Using Stack (Optimal)
==================================================================
💡 Idea:
- Traverse postfix expression from left to right.
- If character is an operand, push onto stack.
- If it's an operator, pop top two operands, form "(first op second)",
  and push back into stack.
- Final element in stack will be the infix expression.

🧩 Algorithm:
1. Initialize an empty stack of strings.
2. Traverse each character `ch` in postfix string:
   a) If operand (alnum), push it as string.
   b) If operator, pop the top two strings:
       - second ← top, pop
       - first ← next, pop
       - form newExpr = "(" + first + ch + second + ")"
       - push newExpr
3. At end, stack top has full infix expression.

⏱ Time Complexity: O(n)  (each character processed once)
📦 Space Complexity: O(n) (stack stores partial expressions)
*/

string postToInfix(string postfix) {
    stack<string> st;
    for (char ch : postfix) {
        if (isalnum(ch)) {
            st.push(string(1, ch));
        } else {
            string second = st.top(); st.pop();
            string first  = st.top(); st.pop();
            string result = "(" + first + ch + second + ")";
            st.push(result);
        }
    }
    return st.top();
}

/*
==================================================================
Approach 2: Recursive Construction (Alternative, Less Common)
==================================================================
💡 Idea:
- Treat postfix expression like a syntax tree.
- Last operator divides expression into left/right subtrees.
- Recursively build tree, then perform inorder traversal to get infix.

🧩 Algorithm (High Level):
1. Parse postfix string into a binary expression tree.
2. Each operator node has left & right children.
3. Leaf nodes are operands.
4. Perform inorder traversal with parentheses → infix expression.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) due to tree and recursion stack.

(This is less direct and involves extra data structure.)
*/

// Node structure for expression tree
struct Node {
    string val;
    Node* left;
    Node* right;
    Node(string v) : val(v), left(NULL), right(NULL) {}
};

// Helper: Build expression tree from postfix
Node* buildExpressionTree(string postfix) {
    stack<Node*> st;
    for (char ch : postfix) {
        if (isalnum(ch)) {
            st.push(new Node(string(1, ch)));
        } else {
            Node* right = st.top(); st.pop();
            Node* left  = st.top(); st.pop();
            Node* root = new Node(string(1, ch));
            root->left = left;
            root->right = right;
            st.push(root);
        }
    }
    return st.top();
}

// Helper: Inorder traversal with parentheses
string inorderTraversal(Node* root) {
    if (!root) return "";
    if (!root->left && !root->right) return root->val; // operand
    return "(" + inorderTraversal(root->left) + root->val + inorderTraversal(root->right) + ")";
}

string postToInfixRecursive(string postfix) {
    Node* root = buildExpressionTree(postfix);
    return inorderTraversal(root);
}

/*
==================================================================
main() function
==================================================================
*/
int main() {
    vector<string> testCases = {
        "ab+cde+**",  // expected ((a+b)*(c*(d+e)))
        "ab+",        // expected (a+b)
        "abc*+",      // expected (a+(b*c))
        "ab*cd*+"     // expected ((a*b)+(c*d))
    };

    for (string postfix : testCases) {
        cout << "Postfix: " << postfix << endl;
        cout << "Infix (Stack):      " << postToInfix(postfix) << endl;
        cout << "Infix (Recursive): " << postToInfixRecursive(postfix) << endl;
        cout << "-----------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Stack-based approach:
   - Easiest, most common, direct solution.
   - O(n) time, O(n) space.

2. Recursive / Expression Tree approach:
   - More illustrative, good for understanding compiler parsing.
   - Builds tree, then inorder → infix.
   - O(n) time, O(n) extra space.

For interviews → Prefer **stack approach** (clean & faster to implement).
==================================================================
*/
