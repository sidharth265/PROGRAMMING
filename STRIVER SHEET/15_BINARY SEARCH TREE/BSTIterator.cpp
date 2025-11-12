#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: BST Iterator
Problem Link: https://leetcode.com/problems/binary-search-tree-iterator/

Problem Statement:
Implement an iterator over a Binary Search Tree (BST). Your iterator will be initialized with the root node of a BST.
Calling next() will return the next smallest number in the BST.
Calling hasNext() will return whether the next smallest number is available.

Example:
Input: BST = [7,3,15,null,null,9,20]
Operations: next() -> 3, next() -> 7, hasNext() -> true, next() -> 9, hasNext() -> true, next() -> 15, hasNext() -> true, next() -> 20, hasNext() -> false

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Brute Force (Inorder traversal at construction)
   ------------------------------------------------------
   💡 Idea:
   - Perform complete inorder traversal at construction.
   - Store the traversal in a vector.
   - next() and hasNext() simply operate on the vector.

   🧩 Algorithm:
   1. During constructor, use stack to perform iterative inorder traversal.
   2. Store sorted values in vector.
   3. Maintain an index pointing to next element.
   4. next() returns element and increments index.
   5. hasNext() checks if index < vector size.

   ⏱ Time Complexity:
   - Constructor: O(N)
   - next(), hasNext(): O(1)
   📦 Space Complexity: O(N)
------------------------------------------------------ */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BSTIterator_Brute {
    vector<int> inorder;
    int idx;
public:
    BSTIterator_Brute(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode* curr = root;
        while (curr || !st.empty()) {
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top(); st.pop();
            inorder.push_back(curr->val);
            curr = curr->right;
        }
        idx = 0;
    }

    int next() {
        return inorder[idx++];
    }

    bool hasNext() {
        return idx < (int)inorder.size();
    }
};

/* ------------------------------------------------------
   Approach 2: Optimal - Controlled Inorder Traversal
   ------------------------------------------------------
   💡 Idea:
   Instead of storing all nodes, lazily traverse using a stack to 
   keep track of nodes to visit.
   Push leftmost nodes initially, then next() pops one and pushes 
   right child’s leftmost nodes.

   🧩 Algorithm:
   1. At construction, push all leftmost nodes from root onto stack.
   2. hasNext() checks if stack not empty.
   3. next():
      - Pop top node.
      - Push all leftmost nodes from popped node’s right child.
      - Return popped node’s value.

   ⏱ Time Complexity:
   - Constructor: O(H)
   - next(), hasNext(): O(1) amortized
   📦 Space Complexity: O(H)
------------------------------------------------------ */

class BSTIterator_Optimal {
    stack<TreeNode*> st;

    void pushLeft(TreeNode* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    }

public:
    BSTIterator_Optimal(TreeNode* root) {
        pushLeft(root);
    }

    int next() {
        TreeNode* topNode = st.top(); st.pop();
        if (topNode->right) pushLeft(topNode->right);
        return topNode->val;
    }

    bool hasNext() {
        return !st.empty();
    }
};

/* ===================== Main Function ===================== */
int main() {
    /*
       Construct BST:
             7
            / \
           3  15
              / \
             9  20
    */
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);

    BSTIterator_Brute it1(root);
    cout << "Brute Force Iterator: ";
    while (it1.hasNext()) cout << it1.next() << " ";
    cout << "\n";

    BSTIterator_Optimal it2(root);
    cout << "Optimal Iterator: ";
    while (it2.hasNext()) cout << it2.next() << " ";
    cout << "\n";

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method           | Time Complexity   | Space Complexity | Notes                    |
       |------------------|-------------------|------------------|--------------------------|
       | Brute Force      | O(N) construction | O(N)             | Simple but uses extra space|
       | Optimal Inorder  | O(H) construction | O(H)             | Space efficient, lazy     |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
