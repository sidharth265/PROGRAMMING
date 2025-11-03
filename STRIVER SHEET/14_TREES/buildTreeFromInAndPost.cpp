#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Construct Binary Tree from Inorder and Postorder Traversal
 Problem Link: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

 Problem Statement:
 -----------------
 Given two integer arrays inorder and postorder where inorder is the inorder traversal of 
 a binary tree and postorder is the postorder traversal of the same tree, construct and 
 return the binary tree.

 Example:
 Input:
  inorder = [9,3,15,20,7]
  postorder = [9,15,7,20,3]

 Output:
      3
     / \
    9  20
       / \
      15  7

 Constraints:
 - 1 <= inorder.length <= 3000
 - postorder.length == inorder.length
 - -3000 <= inorder[i], postorder[i] <= 3000
 - inorder and postorder consist of unique values.
 - Each value of postorder also appears in inorder.
====================================================
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

/* 
==========================================
 Approach 1: Recursive Construction with HashMap
------------------------------------------
💡 Idea:
The last element in postorder is the root. Find the root in inorder for splitting subtrees.

🧩 Algorithm:
1. The root is postorder[postEnd].
2. Find root index in inorder (using hashmap for O(1)).
3. Calculate left subtree length.
4. Recursively build left and right subtrees.
5. Return constructed root.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
TreeNode* build(int postStart, int postEnd, vector<int>& postorder,
                int inStart, int inEnd, vector<int>& inorder, unordered_map<int, int>& m) {
    if (postStart > postEnd || inStart > inEnd) return nullptr;
    TreeNode* root = new TreeNode(postorder[postEnd]);
    int inRoot = m[root->val];
    int leftLen = inRoot - inStart;

    root->left = build(postStart, postStart + leftLen - 1, postorder, inStart, inRoot - 1, inorder, m);
    root->right = build(postStart + leftLen, postEnd - 1, postorder, inRoot + 1, inEnd, inorder, m);
    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int n = (int)inorder.size();
    unordered_map<int, int> m;
    for (int i = 0; i < n; ++i) m[inorder[i]] = i;
    return build(0, n - 1, postorder, 0, n - 1, inorder, m);
}

/* Helper function for inorder traversal to verify tree */
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Construct Tree from Inorder and Postorder ===\n\n";

    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};

    TreeNode* root = buildTree(inorder, postorder);

    cout << "Inorder traversal of constructed tree: ";
    printInorder(root); // should print 9 3 15 20 7
    cout << "\n";

    // Cleanup omitted for brevity
    return 0;
}

/*
✅ Approach Overview:
- Uses hashmap for O(1) inorder index lookups.
- Recursion processes N nodes with balanced splits, yielding O(N) time.
- Space for recursion stack and hashmap is O(N).
- Elegant standard solution for this problem.
*/

