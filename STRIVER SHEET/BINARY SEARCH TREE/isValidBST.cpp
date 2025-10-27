#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Validate Binary Search Tree
Problem Link: https://leetcode.com/problems/validate-binary-search-tree

Problem Statement:
Given the root of a binary tree, determine if it is a valid Binary Search Tree (BST).
A valid BST must satisfy:
1. The left subtree of a node contains only nodes with keys less than the node's key.
2. The right subtree of a node contains only nodes with keys greater than the node's key.
3. Both left and right subtrees must also be BSTs.

Example 1:
Input:
    2
   / \
  1   3
Output: true

Example 2:
Input:
    5
   / \
  1   4
     / \
    3   6
Output: false
Explanation: The node 4's left child 3 is less than 5 but located in the right subtree of 5.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Recursion with Range Limits
   ------------------------------------------------------
   💡 Idea:
   Use recursion to validate each node's value lies within a valid range.
   For each node, values in the left subtree must be in (low, node->val),
   and in the right subtree (node->val, high).

   🧩 Algorithm:
   1. Start with low = LONG_MIN and high = LONG_MAX.
   2. At each node, check if node->val is within (low, high).
      - If not, return false.
   3. Recursively validate left subtree with updated high = node->val.
   4. Recursively validate right subtree with updated low = node->val.
   5. Return true if all validations pass.

   ⏱ Time Complexity: O(N) - each node is checked once.
   📦 Space Complexity: O(H) - recursion stack, H is tree height.
------------------------------------------------------ */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool isValid(TreeNode* root, long low, long high) {
    if (!root) return true;
    if (root->val <= low || root->val >= high) return false;
    return isValid(root->left, low, root->val) &&
           isValid(root->right, root->val, high);
}

bool isValidBST(TreeNode* root) {
    return isValid(root, LONG_MIN, LONG_MAX);
}

/* ===================== Main Function ===================== */
int main() {
    /*
      Construct the following trees to test:
      Example 1: Valid BST
            2
           / \
          1   3

      Example 2: Invalid BST
            5
           / \
          1   4
             / \
            3   6
    */

    // Example 1
    TreeNode* root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(3);

    cout << "Example 1: " << (isValidBST(root1) ? "Valid BST" : "Invalid BST") << endl;

    // Example 2
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(3);
    root2->right->right = new TreeNode(6);

    cout << "Example 2: " << (isValidBST(root2) ? "Valid BST" : "Invalid BST") << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method                      | Time Complexity | Space Complexity | Notes                          |
       |-----------------------------|----------------|------------------|--------------------------------|
       | Recursion with Range Limits | O(N)           | O(H)             | Clean and efficient            |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
