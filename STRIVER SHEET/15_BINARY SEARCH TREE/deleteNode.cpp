#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Delete Node in a BST
Problem Link: https://leetcode.com/problems/delete-node-in-a-bst

Problem Statement:
Given the root of a Binary Search Tree (BST) and a key, delete the node with the given key in the BST.
Return the root of the modified BST. The deletion should preserve the BST property.

Example:
Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation:
Node 3 is deleted and replaced by node 4.

=========================================================
*/

/* ------------------------------------------------------
   Approach: Iterative Deletion using Helper Function
   ------------------------------------------------------
   💡 Idea:
   If the node to delete has:
   - No child or one child: return the non-null child or null.
   - Two children: find rightmost node in left subtree (inorder predecessor),
     attach right subtree of deleted node to rightmost's right,
     and return left subtree.

   🧩 Algorithm:
   1. If root is null, return null.
   2. If node to delete is root, call helper to reattach subtrees.
   3. Otherwise, traverse the tree to find node with given key:
      - Track parent and if node is left or right child.
   4. Replace parent's pointer with helper(node to delete).
   5. Return original root.

   ⏱ Time Complexity: O(H)
   📦 Space Complexity: O(1)
------------------------------------------------------ */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Helper deletes root node and reconnects subtrees properly
TreeNode* helper(TreeNode* root) {
    if (!root->left) 
        return root->right;
    if (!root->right) 
        return root->left;

    TreeNode* rightMost = root->left;
    while (rightMost->right) 
        rightMost = rightMost->right;

    rightMost->right = root->right;
    return root->left;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;

    if (root->val == key) 
        return helper(root);

    TreeNode* tempRoot = root;

    while (root) {
        if (root->val > key) {
            if (root->left && root->left->val == key) {
                root->left = helper(root->left);
                break;
            } else {
                root = root->left;
            }
        } else {
            if (root->right && root->right->val == key) {
                root->right = helper(root->right);
                break;
            } else {
                root = root->right;
            }
        }
    }

    return tempRoot;
}

/* Utility: Insert node in BST */
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

/* Utility: Inorder Print for Testing */
void inorderPrint(TreeNode* root) {
    if (!root) return;
    inorderPrint(root->left);
    cout << root->val << " ";
    inorderPrint(root->right);
}

/* ===================== Main Function ===================== */
int main() {
    TreeNode* root = nullptr;
    vector<int> values = {5, 3, 6, 2, 4, 7};
    for (int v : values) root = insertBST(root, v);

    cout << "Original Tree Inorder: ";
    inorderPrint(root);
    cout << endl;

    int key = 3;
    root = deleteNode(root, key);
    cout << "After deleting " << key << ": ";
    inorderPrint(root);
    cout << endl;

    key = 5;
    root = deleteNode(root, key);
    cout << "After deleting " << key << ": ";
    inorderPrint(root);
    cout << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method           | Time Complexity | Space Complexity | Notes                  |
       |------------------|-----------------|------------------|------------------------|
       | Iterative Helper | O(H)            | O(1)             | Compact, iterative     |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
