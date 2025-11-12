#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Insert into Binary Search Tree (BST)
Problem Link: https://leetcode.com/problems/insert-into-a-binary-search-tree

Problem Statement:
Given the root node of a Binary Search Tree (BST) and a value to insert into the tree,
insert the value into its correct position in the BST. Return the root node of the BST after insertion.
If the tree is empty, the new node becomes the root.

Example 1:
Input: root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]
Explanation: 5 is inserted as the left child of 7.

Example 2:
Input: root = [], val = 8
Output: [8]
Explanation: 8 becomes the root since the tree is empty.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Recursive Insertion
   ------------------------------------------------------
   💡 Idea:
   Recursively traverse the BST and insert the value at the correct position.

   🧩 Algorithm:
   1. If root is NULL, create and return a new node.
   2. If val < root->val, recur into left subtree.
   3. If val > root->val, recur into right subtree.
   4. Return the root.

   ⏱ Time Complexity: O(H)
   📦 Space Complexity: O(H) [due to recursion stack]
------------------------------------------------------ */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

TreeNode* insertBSTRecursive(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insertBSTRecursive(root->left, val);
    else root->right = insertBSTRecursive(root->right, val);
    return root;
}

/* ------------------------------------------------------
   Approach 2: Iterative Insertion (Optimal)
   ------------------------------------------------------
   💡 Idea:
   Traverse the BST iteratively to find the correct spot for the new value, 
   then insert.

   🧩 Algorithm:
   1. If root is NULL, create and return a new node.
   2. Traverse down the tree:
      a. If val < curr->val, go left.
      b. If val > curr->val, go right.
      c. Continue until a NULL child is found.
   3. Insert as child of last node.
   4. Return root.

   ⏱ Time Complexity: O(H)
   📦 Space Complexity: O(1)
------------------------------------------------------ */
TreeNode* insertBSTIterative(TreeNode* root, int val) {
    TreeNode* node = new TreeNode(val);
    if (!root) return node;
    TreeNode* curr = root;
    while (true) {
        if (val < curr->val) {
            if (!curr->left) {
                curr->left = node;
                break;
            } else {
                curr = curr->left;
            }
        } else {
            if (!curr->right) {
                curr->right = node;
                break;
            } else {
                curr = curr->right;
            }
        }
    }
    return root;
}

/* ------------------------------------------------------
   Approach 3: Iterative Insertion (Variant given in Query)
   ------------------------------------------------------
   💡 Idea:
   Traverse using curr pointer until left or right child is NULL, then insert.

   🧩 Algorithm:
   1. If root is NULL, create and return a new node.
   2. While curr has left or right child:
       a. If val > curr->val and curr->right exists, curr = curr->right.
       b. If val < curr->val and curr->left exists, curr = curr->left.
       c. Otherwise, break.
   3. Insert as left or right child.
   4. Return root.

   ⏱ Time Complexity: O(H)
   📦 Space Complexity: O(1)
------------------------------------------------------ */
TreeNode* insertIntoBSTVariant(TreeNode* root, int val) {
    TreeNode* curr = root;
    TreeNode* next = new TreeNode(val);
    if (!curr) return next;
    while (true) {
        if (val > curr->val) {
            if (curr->right) curr = curr->right;
            else break;
        } else {
            if (curr->left) curr = curr->left;
            else break;
        }
    }
    if (val > curr->val) curr->right = next;
    else curr->left = next;
    return root;
}

/* Utility: Print BST Inorder */
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

/* ===================== Main Function ===================== */
int main() {
    // Build initial BST: [4,2,7,1,3]
    TreeNode* root = nullptr;
    vector<int> initial = {4,2,7,1,3};
    for (int x : initial) root = insertBSTIterative(root, x);

    vector<int> insertVals = {5, 8};
    for (int val : insertVals) {
        cout << "Insert " << val << " (Recursive): ";
        TreeNode* root1 = insertBSTRecursive(root, val);
        inorder(root1); cout << endl;

        cout << "Insert " << val << " (Iterative): ";
        TreeNode* root2 = insertBSTIterative(root, val);
        inorder(root2); cout << endl;

        cout << "Insert " << val << " (Variant): ";
        TreeNode* root3 = insertIntoBSTVariant(root, val);
        inorder(root3); cout << endl;
        cout << endl;
    }

    // Insert on empty tree
    TreeNode* emptyRoot = nullptr;
    TreeNode* res1 = insertBSTRecursive(emptyRoot, 8);
    cout << "Insert 8 into empty (Recursive): "; inorder(res1); cout << endl;

    TreeNode* res2 = insertBSTIterative(emptyRoot, 8);
    cout << "Insert 8 into empty (Iterative): "; inorder(res2); cout << endl;

    TreeNode* res3 = insertIntoBSTVariant(emptyRoot, 8);
    cout << "Insert 8 into empty (Variant): "; inorder(res3); cout << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method       | Time Complexity | Space Complexity | Notes                  |
       |--------------|----------------|------------------|------------------------|
       | Recursive    | O(H)           | O(H)             | Concise, readable      |
       | Iterative    | O(H)           | O(1)             | Preferred for interview|
       | QueryVariant | O(H)           | O(1)             | Works, less standard   |
    ------------------------------------------------------ */
    return 0;
}
