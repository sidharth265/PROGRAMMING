#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Flatten Binary Tree to Linked List
Problem Link: https://leetcode.com/problems/flatten-binary-tree-to-linked-list

Problem Statement:
Given the root of a binary tree, flatten the tree to a linked list in-place.
The linked list should use only right pointers and follow the preorder traversal of the tree.

Example:
Input:      1
           / \
          2   5
         / \   \
        3   4   6

Output: 1 - 2 - 3 - 4 - 5 - 6 (right pointers only)

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Iterative Preorder Traversal using Stack
   ------------------------------------------------------
   💡 Idea:
   Use a stack to perform preorder traversal, rewiring pointers on the go.

   🧩 Algorithm:
   1. Push root to the stack.
   2. While stack is not empty:
      a. Pop node as curr.
      b. Push curr->right if exists, then curr->left if exists.
      c. Set curr->right to stack top if stack not empty; curr->left to nullptr.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void flattenIterative(TreeNode *root) {
    if (!root) return;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* curr = st.top();
        st.pop();
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
        if (!st.empty()) curr->right = st.top();
        curr->left = nullptr;
    }
}

/* ------------------------------------------------------
   Approach 2: Recursive Reverse Postorder Traversal
   ------------------------------------------------------
   💡 Idea:
   Flatten right subtree then left, using a `prev` pointer to relink nodes in reverse preorder.

   🧩 Algorithm:
   1. Traverse right, then left subtree recursively.
   2. For each node, set root->right to prev, root->left = nullptr.
   3. Update prev to current root.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(H) (recursion stack)
------------------------------------------------------ */
void flat(TreeNode* root, TreeNode*& prev) {
    if (!root) return;
    flat(root->right, prev);
    flat(root->left, prev);
    root->right = prev;
    root->left = nullptr;
    prev = root;
}
void flattenRecursive(TreeNode* root) {
    TreeNode* prev = nullptr;
    flat(root, prev);
}

/* ------------------------------------------------------
   Approach 3: Morris Traversal (O(1) Space, In-place)
   ------------------------------------------------------
   💡 Idea:
   For each node with left child:
    - Find predecessor (rightmost of left)
    - Set predecessor->right = curr->right, relink curr->right = curr->left, left = nullptr
   Repeat for every node.

   🧩 Algorithm:
   1. Iterate with curr = root.
   2. While curr is not null:
       a. If curr->left exists:
           - Find rightmost of left as prev.
           - prev->right = curr->right;
           - curr->right = curr->left, curr->left = nullptr
       b. Move curr = curr->right.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(1)
------------------------------------------------------ */
void flattenMorris(TreeNode* root)
{
    TreeNode* curr = root;
    while(curr) {
        if(curr->left) {
            TreeNode* prev = curr->left;
            while(prev->right) prev = prev->right;
            prev->right = curr->right;
            curr->right = curr->left;
            curr->left = nullptr;
        }
        curr = curr->right;
    }
}

/* Utility: Build and Print Flattened Linked List */
TreeNode* buildExampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(6);
    return root;
}
void printRightChain(TreeNode* root) {
    while (root) {
        cout << root->val << " ";
        root = root->right;
    }
    cout << endl;
}

/* ===================== Main Function ===================== */
int main() {
    TreeNode* t1 = buildExampleTree();
    flattenIterative(t1);
    cout << "Flattened (Iterative Preorder): "; printRightChain(t1);

    TreeNode* t2 = buildExampleTree();
    flattenRecursive(t2);
    cout << "Flattened (Recursive Reverse Postorder): "; printRightChain(t2);

    TreeNode* t3 = buildExampleTree();
    flattenMorris(t3);
    cout << "Flattened (Morris In-Place): "; printRightChain(t3);

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method                | Time Complexity | Space Complexity | Notes                      |
       |-----------------------|----------------|------------------|----------------------------|
       | Iterative (Stack)     | O(N)           | O(N)             | Clean, easy to implement   |
       | Recursive (Reverse)   | O(N)           | O(H)             | Uses stack, very standard  |
       | Morris/Pointer Trick  | O(N)           | O(1)             | Truly in-place, trickiest  |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
