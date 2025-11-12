#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Lowest Common Ancestor of a Binary Tree
 Problem Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

 Problem Statement:
 -----------------
 Given the root of a binary tree, and two nodes p and q, find their lowest common ancestor (LCA).
 The LCA of two nodes is defined as the deepest node that has both p and q as descendants
 (where a node can be a descendant of itself).

 Example:
 Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
          3
         / \
        5   1
       / \ / \
      6  2 0  8
        / \
       7   4

 Output: 3
 Explanation: The LCA of nodes 5 and 1 is 3.

 Constraints:
 - The number of nodes in the tree is in the range [2, 10^5].
 - All node values are unique.
 - p and q are different nodes and both exist in the tree.
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
 Approach 1: Brute Force - Path Recording for Both Nodes
-----------------------------------------
💡 Idea:
Find root-to-p and root-to-q paths using DFS. Then compare the paths to find the last common node.

🧩 Algorithm:
1. Write a function to find the path from root to a target node (p/q) and store both paths in vectors.
2. Loop through both vectors, and the last matching node is the LCA.
3. Return the found node.

⏱ Time Complexity: O(N), two traversals.
📦 Space Complexity: O(H) for each path.
*/
bool getPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
    if (!root) return false;
    path.push_back(root);
    if (root == target) return true;
    if (getPath(root->left, target, path) || getPath(root->right, target, path))
        return true;
    path.pop_back();
    return false;
}

TreeNode* lowestCommonAncestorBrute(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> path1, path2;
    getPath(root, p, path1);
    getPath(root, q, path2);
    int n = min(path1.size(), path2.size());
    TreeNode* lca = nullptr;
    for (int i = 0; i < n; ++i) {
        if (path1[i] == path2[i]) lca = path1[i];
        else break;
    }
    return lca;
}

/* 
==========================================
 Approach 2: Better - Recursive DFS for LCA
-----------------------------------------
💡 Idea:
Recursively traverse the tree. If root is NULL, p, or q, return root.
Otherwise, search left and right; if both are non-null, root is LCA; else, propagate non-null result.

🧩 Algorithm:
1. Base case: if root is NULL, p or q, return root.
2. Recursively search left and right subtrees.
3. If both sides return non-null, root is the LCA.
4. Otherwise, return the non-null value.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(H) stack.
*/
TreeNode* lowestCommonAncestorBetter(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* l = lowestCommonAncestorBetter(root->left, p, q);
    TreeNode* r = lowestCommonAncestorBetter(root->right, p, q);
    if (l && r) return root;
    return l ? l : r;
}

/* 
==========================================
 Approach 3: Optimal - Single Pass Bottom-Up DFS with Early Return
-----------------------------------------
💡 Idea:
Same as Approach 2; this is already optimal for a general binary tree. For added efficiency, 
can short-circuit traversal if LCA already found by passing a reference.

🧩 Algorithm:
1. Add extra logic to pass an LCA pointer by reference and set when found.
2. Otherwise, logic is identical to Approach 2.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(H)
*/
bool dfsOptimal(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& lca) {
    if (!root) return false;
    int left = dfsOptimal(root->left, p, q, lca) ? 1 : 0;
    int right = dfsOptimal(root->right, p, q, lca) ? 1 : 0;
    int mid = (root == p || root == q) ? 1 : 0;
    if (left + right + mid >= 2) lca = root;
    return (left + right + mid) > 0;
}

TreeNode* lowestCommonAncestorOptimal(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* lca = nullptr;
    dfsOptimal(root, p, q, lca);
    return lca ? lca : root;
}

/* Helper function to build test tree */
TreeNode* findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    TreeNode* l = findNode(root->left, val);
    if (l) return l;
    return findNode(root->right, val);
}

TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
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
    cout << "=== Lowest Common Ancestor of a Binary Tree ===\n\n";

    TreeNode* root = createSampleTree();
    TreeNode* p = findNode(root, 5);
    TreeNode* q = findNode(root, 1);

    TreeNode* res1 = lowestCommonAncestorBrute(root, p, q);
    cout << "Brute Force: LCA of " << p->val << " and " << q->val << " is " << res1->val << "\n";

    TreeNode* res2 = lowestCommonAncestorBetter(root, p, q);
    cout << "Better: LCA of " << p->val << " and " << q->val << " is " << res2->val << "\n";

    TreeNode* res3 = lowestCommonAncestorOptimal(root, p, q);
    cout << "Optimal: LCA of " << p->val << " and " << q->val << " is " << res3->val << "\n";

    deleteTree(root);
    return 0;
}

/*
✅ Approach Overview:
- Brute Force: O(N) paths, then compare root-to-node paths.
- Better: Recursive DFS, efficient and elegant for general trees.
- Optimal: Bottom-up DFS with early LCA marking; matches better approach in practice for this problem.
All approaches are O(N) time and O(H) space; recursion is the preferred approach in interviews.
*/
