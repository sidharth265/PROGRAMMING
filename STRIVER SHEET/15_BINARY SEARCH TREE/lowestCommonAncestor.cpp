#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Lowest Common Ancestor in a BST
Problem Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree

Problem Statement:
Given a Binary Search Tree (BST), find the lowest common ancestor (LCA) of two given nodes p and q.
The LCA of two nodes p and q is the lowest node in the BST that has both p and q as descendants 
(where we allow a node to be a descendant of itself).

Example 1:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The lowest common ancestor of nodes 2 and 8 is 6.

Example 2:
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The lowest common ancestor of nodes 2 and 4 is 2, since a node can be a descendant of itself.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Recursive BST LCA Search
   ------------------------------------------------------
   💡 Idea:
   Utilize BST property to compare node values and determine if
   both p and q lie on one side of the current root. Move accordingly until split is found.

   🧩 Algorithm:
   1. If root is NULL, return NULL.
   2. If both p and q values are greater than root's value, search right subtree.
   3. If both are smaller, search left subtree.
   4. Otherwise, root is the LCA.
   5. Return root.

   ⏱ Time Complexity: O(H), where H is height of BST.
   📦 Space Complexity: O(H) due to recursion stack.
------------------------------------------------------ */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;

    if (p->val > root->val && q->val > root->val)
        return lowestCommonAncestor(root->right, p, q);

    if (p->val < root->val && q->val < root->val)
        return lowestCommonAncestor(root->left, p, q);

    // If one value is on one side and the other is on another side, root is LCA
    return root;
}

/* Utility: Insert node in BST for testing */
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

/* Utility: Find node by value */
TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    if (val < root->val) return findNode(root->left, val);
    else return findNode(root->right, val);
}

/* ===================== Main Function ===================== */
int main() {
    // Construct BST
    vector<int> vals = {6,2,8,0,4,7,9,3,5};
    TreeNode* root = nullptr;
    for (int v : vals) root = insertBST(root, v);

    TreeNode* p = findNode(root, 2);
    TreeNode* q = findNode(root, 8);
    TreeNode* lca = lowestCommonAncestor(root, p, q);
    cout << "LCA of 2 and 8: " << (lca ? lca->val : -1) << endl;

    p = findNode(root, 2);
    q = findNode(root, 4);
    lca = lowestCommonAncestor(root, p, q);
    cout << "LCA of 2 and 4: " << (lca ? lca->val : -1) << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method                    | Time Complexity | Space Complexity | Notes               |
       |---------------------------|----------------|------------------|---------------------|
       | Recursive BST LCA Search  | O(H)           | O(H)             | Intuitive and efficient |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
