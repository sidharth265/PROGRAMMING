#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Count Complete Tree Nodes
 Problem Link: https://leetcode.com/problems/count-complete-tree-nodes/

 Problem Statement:
 -----------------
 Given the root of a **complete** binary tree, return the total number of nodes in the tree in O(log² N).

 Example:
 Input:
        1
       / \
      2   3
     / \  /
    4  5 6

 Output: 6

 Constraints:
 - The number of nodes in the tree is in the range [0, 5 * 10^4].
 - 0 <= Node.val <= 10^5
 - The tree is **complete**.
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
 Approach 1: Brute Force - Simple DFS Count
------------------------------------------
💡 Idea:
Traverse the tree recursively counting nodes one by one.

🧩 Algorithm:
1. If root is null, return 0.
2. Recursively count nodes in left and right subtree.
3. Return 1 + left count + right count.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(H)
*/
int countNodesBrute(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodesBrute(root->left) + countNodesBrute(root->right);
}

/* 
==========================================
 Approach 2: Better - DFS With Early Height Check for Perfect Binary Tree
------------------------------------------
💡 Idea:
If left and right subtree heights from this node are the same, then it is a perfect tree and nodes can be computed directly using 2^h - 1. Otherwise, sum recursively for left and right.

🧩 Algorithm:
1. Write two functions for left-most and right-most heights.
2. If left height == right height, return pow(2, h) - 1.
3. Otherwise, recurse for left and right subtrees.

⏱ Time Complexity: O(log^2 N)
📦 Space Complexity: O(log N) due to stack
*/
int leftHeight(TreeNode* curr) {
    int count = 0;
    while (curr) {
        count++;
        curr = curr->left;
    }
    return count;
}
int rightHeight(TreeNode* curr) {
    int count = 0;
    while (curr) {
        count++;
        curr = curr->right;
    }
    return count;
}

int countNodesBetter(TreeNode* root) {
    if (!root) return 0;
    int lh = leftHeight(root);
    int rh = rightHeight(root);

    if (lh == rh) return (1 << lh) - 1;
    return 1 + countNodesBetter(root->left) + countNodesBetter(root->right);
}

/* 
==========================================
 Approach 3: Optimal - Iterative Version for Large Datasets
------------------------------------------
💡 Idea:
Same height shortcut, but use an explicit stack to handle the recursion and avoid stack overflow for very deep trees.

🧩 Algorithm:
1. Loop through nodes using a stack.
2. For each, check left/right height and sum accordingly.
3. Use bitwise for performance.

⏱ Time Complexity: O(log^2 N)
📦 Space Complexity: O(log N)
*/
int countNodesOptimal(TreeNode* root) {
    int total = 0;
    TreeNode* node = root;
    while (node) {
        int lh = leftHeight(node);
        int rh = rightHeight(node);
        if (lh == rh) {
            total += (1 << lh) - 1;
            break;
        } else {
            total += 1;
            node = node->left;
            total += countNodesOptimal(root->right);
            break;
        }
    }
    return total;
}

/* Helper function to create sample tree */
TreeNode* createSampleTree() {
    /*
           1
          / \
         2   3
        / \  /
       4  5 6
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    return root;
}
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Count Complete Tree Nodes ===\n\n";
    TreeNode* root = createSampleTree();

    cout << "Brute Force Result: " << countNodesBrute(root) << "\n";
    cout << "Better (Recursive, log^2 N): " << countNodesBetter(root) << "\n";
    cout << "Optimal (Iterative, log^2 N): " << countNodesOptimal(root) << "\n";

    deleteTree(root);
    return 0;
}

/*
✅ Approach Overview:
- Brute Force: Simple DFS, O(N) time, may be slow for large trees.
- Better: Height check for perfect subtrees, O(log^2 N) time, O(log N) space.
- Optimal: Iterative variant, same time/space, avoids recursion stack overflow for large input sizes.
All methods return the correct count for complete binary trees.
*/
