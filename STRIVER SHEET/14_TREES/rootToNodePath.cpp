#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Root to Node Path in Binary Tree
 Problem Link: (Custom / Generic Problem)

 Problem Statement:
 -----------------
 Given a binary tree and a target value x, find and return the path from the root to the 
 node containing x as a vector. If no such node exists, return an empty vector.

 Example:
 Input:
       1
      / \
     2   3
    / \
   4   5

 Target: 5
 Output: [1, 2, 5]
 Explanation: The path from root to node 5 is 1 -> 2 -> 5.

 Constraints:
 - Number of nodes in the tree: up to 10^5
 - Node values are unique.
====================================================
*/

template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

/* 
==========================================
 Approach 1: DFS Backtracking to Find Path
-----------------------------------------
💡 Idea:
Traverse the tree via DFS maintaining a path vector.
Push current node value; check if it is target.
If yes, return true.
If searching left or right subtree returns true, propagate success.
If not found, pop the current node and backtrack.

🧩 Algorithm:
1. Start from root, push its value to path.
2. If current node matches target, return true.
3. Recursively search left subtree; if found return true.
4. Recursively search right subtree; if found return true.
5. If not found in either, pop node from path and return false.
6. Call this recursive function from main function and return the path vector.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(H)
*/
template <typename T>
bool generate(TreeNode<T>* root, vector<T>& result, T x) {
    if (!root) return false;
    result.push_back(root->data);
    if (root->data == x) return true;
    if (generate(root->left, result, x) || generate(root->right, result, x))
        return true;
    result.pop_back();
    return false;
}

template <typename T>
vector<T> pathInATree(TreeNode<T>* root, T x) {
    vector<T> result;
    generate(root, result, x);
    return result;
}

/* Helper to create sample tree */
TreeNode<int>* createSampleTree() {
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);
    return root;
}

/* Helper to delete tree */
template <typename T>
void deleteTree(TreeNode<T>* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Root to Node Path in Binary Tree ===\n\n";

    TreeNode<int>* root = createSampleTree();
    int target = 5;

    vector<int> path = pathInATree(root, target);
    if (!path.empty()) {
        cout << "Path to node " << target << ": ";
        for (int val : path) cout << val << " ";
        cout << "\n";
    } else {
        cout << "Node " << target << " not found in tree.\n";
    }

    deleteTree(root);
    return 0;
}

/*
✅ Approach Overview:
- This DFS with backtracking approach runs in O(N) time visiting each node once.
- Space complexity is O(H), height of tree, due to recursion and path storage.
- This approach effectively finds root-to-node path or returns empty if none.
- No meaningful alternative brute or better approach exists since the problem is a standard path search.
*/
