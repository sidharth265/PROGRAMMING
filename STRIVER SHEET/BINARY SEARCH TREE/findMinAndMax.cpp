#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Find Minimum and Maximum in Binary Search Tree (BST)
 Problem Link: https://www.geeksforgeeks.org/dsa/find-the-minimum-element-in-a-binary-search-tree/

 Problem Statement:
 -----------------
 Given a Binary Search Tree (BST), find the minimum and maximum valued nodes.

 Details:
 - In BST, the left subtree of a node contains nodes with values less than the node's value.
 - The right subtree contains nodes with values greater than the node's value.
 - The minimum value in BST is the leftmost node.
 - The maximum value in BST is the rightmost node.

 Example:
 Input:
              10
             /  \
            5    15
           / \     \
          3   7     20

 Output:
  Minimum value: 3
  Maximum value: 20

 Explanation:
 The leftmost node in the BST is 3 and rightmost is 20.
====================================================
*/

/*
==========================================
 Approach 1: Iterative Traversal to Leftmost and Rightmost Nodes
------------------------------------------
💡 Idea:
- For minimum, traverse left child pointers until no more left child exists.
- For maximum, traverse right child pointers until no more right child exists.

🧩 Algorithm:
1. Start at root.
2. For minimum: repeatedly go to left child until nullptr.
3. For maximum: repeatedly go to right child until nullptr.
4. Return the node value found at the end of these traversals.

⏱ Time Complexity: O(h) where h is height of BST.
📦 Space Complexity: O(1) since no extra structures needed.
*/
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int findMin(TreeNode* root) {
    if (!root) throw runtime_error("Empty tree");
    TreeNode* curr = root;
    while (curr->left != nullptr)
        curr = curr->left;
    return curr->val;
}

int findMax(TreeNode* root) {
    if (!root) throw runtime_error("Empty tree");
    TreeNode* curr = root;
    while (curr->right != nullptr)
        curr = curr->right;
    return curr->val;
}

/* Helper: Insert for BST */
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insert(root->left, val);
    else if (val > root->val) root->right = insert(root->right, val);
    return root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Find Min and Max in BST ===\n";
    TreeNode* root = nullptr;
    vector<int> vals = {10, 5, 15, 3, 7, 20};
    for (int v : vals) root = insert(root, v);

    cout << "Minimum value in BST: " << findMin(root) << "\n";
    cout << "Maximum value in BST: " << findMax(root) << "\n";

    return 0;
}

/*
✅ Approach Overview:
- Uses BST property by traversing left for minimum and right for maximum.
- Runs in O(h), faster than traversal of entire tree.
- Space complexity O(1), only pointer usage.
- Simple and efficient for BST min/max queries.
*/
