#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Maximum Width of Binary Tree
 Problem Link: https://leetcode.com/problems/maximum-width-of-binary-tree/

 Problem Statement:
 -----------------
 Given the root of a binary tree, return the maximum width of the tree. The width 
 of one level is defined as the length between the end-nodes (the leftmost and rightmost 
 non-null nodes), where null nodes between the end-nodes are also counted into the length.

 Example:
 Input:
           1
          / \
         3   2
        / \   \
       5   3   9

 Output: 4
 Explanation: The maximum width is between nodes 5 and 9 in the last level.

 Constraints:
 - Number of nodes in the tree in range [1, 3000]
 - Node values are integers
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
 Approach 1: Brute Force - Track All Indices Per Level
-----------------------------------------
💡 Idea:
Perform level order traversal storing positions for all nodes in each level, then compute widths.

🧩 Algorithm:
1. Traverse tree by level using BFS with a queue storing pairs (node, index).
2. Track indices of nodes in the current level in a vector.
3. For each level, width = last index - first index + 1.
4. Update max width.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
int widthOfBinaryTreeBrute(TreeNode* root) {
    if (!root) return 0;

    int maxWidth = 0;
    queue<pair<TreeNode*, unsigned long long>> q;
    q.push({root, 0});

    while (!q.empty()) {
        int size = q.size();
        vector<unsigned long long> levelIndices;
        for (int i = 0; i < size; ++i) {
            auto front = q.front();
            q.pop();
            TreeNode* node = front.first;
            unsigned long long idx = front.second;
            levelIndices.push_back(idx);

            if (node->left) q.push({node->left, 2 * idx + 1});
            if (node->right) q.push({node->right, 2 * idx + 2});
        }
        int currWidth = (int)(levelIndices.back() - levelIndices.front() + 1);
        maxWidth = max(maxWidth, currWidth);
    }
    return maxWidth;
}

/* 
==========================================
 Approach 2: Optimal - Normalize Indices Per Level to Prevent Overflow
-----------------------------------------
💡 Idea:
In BFS, subtract minimum index of level from all indices to normalize and prevent overflow.

🧩 Algorithm:
1. Use BFS queue of (node, index).
2. At each level, get min index from first node.
3. For each node, subtract min index from current index to normalize.
4. Calculate width as last node’s normalized index - first node’s normalized index + 1.
5. Update max width accordingly.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
int widthOfBinaryTree(TreeNode* root) {
    if (!root) return 0;

    int maxWidth = 0;
    queue<pair<TreeNode*, unsigned long long>> q;
    q.push({root, 0});

    while (!q.empty()) {
        int size = q.size();
        unsigned long long minIdx = q.front().second;
        unsigned long long first = 0, last = 0;

        for (int i = 0; i < size; ++i) {
            auto front = q.front();
            q.pop();
            TreeNode* node = front.first;
            unsigned long long currIdx = front.second - minIdx;

            if (i == 0) first = currIdx;
            if (i == size - 1) last = currIdx;

            if (node->left) q.push({node->left, 2 * currIdx + 1});
            if (node->right) q.push({node->right, 2 * currIdx + 2});
        }
        int currWidth = (int)(last - first + 1);
        maxWidth = max(maxWidth, currWidth);
    }

    return maxWidth;
}

/* Helper function to create test tree */
TreeNode* createSampleTree() {
    /*
            1
           / \
          3   2
         / \   \
        5   3   9
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(9);
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
    cout << "=== Maximum Width of Binary Tree ===\n\n";

    TreeNode* root = createSampleTree();

    cout << "Brute Force Result: " << widthOfBinaryTreeBrute(root) << "\n";
    cout << "Optimal Result:     " << widthOfBinaryTree(root) << "\n";

    deleteTree(root);
    return 0;
}

/*
✅ Approach Overview:
- Brute Force: Tracks all indices of nodes per level explicitly, then computes width.
- Optimal: Normalizes indices level-wise to prevent overflow and ensures O(N) time and space.
- Both approaches are efficient and suitable; optimal is preferred for better memory safety.
*/
