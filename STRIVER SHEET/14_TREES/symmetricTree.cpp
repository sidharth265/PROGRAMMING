#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Symmetric Tree
 Problem Link: https://leetcode.com/problems/symmetric-tree/

 Problem Statement:
 -----------------
 Given a binary tree, check whether it is a mirror of itself (symmetric around its center).

 Example:
 Input: root = [1,2,2,3,4,4,3]
        1
       / \
      2   2
     / \ / \
    3  4 4  3
    
 Output: true
 Explanation: The tree is symmetric.

 Constraints:
 - Number of nodes in the tree is in the range [1, 1000].
 - -100 <= Node.val <= 100
====================================================
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* 
==========================================
 Approach 1: Brute Force - Mirror Check Recursively
-----------------------------------------
💡 Idea:
Check recursively if left subtree is mirror of right subtree by comparing corresponding nodes 
and structure.

🧩 Algorithm:
1. Define a helper function that takes two nodes (root1, root2).
2. If both are null, return true.
3. If one is null and other is not, return false.
4. Compare values of root1 and root2.
5. Recursively check if root1's left subtree is mirror of root2's right subtree and vice versa.
6. Result is true only if all conditions hold.

⏱ Time Complexity: O(N), visiting every node once.
📦 Space Complexity: O(H), recursion stack.
*/
bool isSym(TreeNode* root1, TreeNode* root2) {
    if (!root1 || !root2) return root1 == root2;
    return (root1->val == root2->val)
           && isSym(root1->left, root2->right)
           && isSym(root1->right, root2->left);
}

bool isSymmetricBruteForce(TreeNode* root) {
    if (!root) return true;
    return isSym(root->left, root->right);
}

/* 
==========================================
 Approach 2: Better - Iterative Using Queue
-----------------------------------------
💡 Idea:
Use a queue to iteratively compare pairs of nodes that need to be mirror images.

🧩 Algorithm:
1. Initialize a queue and push the pair (root->left, root->right).
2. While queue not empty:
   - Pop two nodes.
   - If both null, continue.
   - If one null or values differ, return false.
   - Enqueue children in order to compare mirror nodes:
     (left->left, right->right) and (left->right, right->left).
3. If all pairs matched, return true.

⏱ Time Complexity: O(N).
📦 Space Complexity: O(H), queue size.
*/
bool isSymmetricBetter(TreeNode* root) {
    if (!root) return true;
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);

    while (!q.empty()) {
        TreeNode* t1 = q.front(); q.pop();
        TreeNode* t2 = q.front(); q.pop();

        if (!t1 && !t2) continue;
        if (!t1 || !t2) return false;
        if (t1->val != t2->val) return false;

        q.push(t1->left);
        q.push(t2->right);

        q.push(t1->right);
        q.push(t2->left);
    }
    return true;
}

/* 
==========================================
 Approach 3: Optimal - Same as Approach 1 (Recursive)
-----------------------------------------
💡 Idea:
The recursive approach is already optimal with O(N) time and O(H) space.

(No further optimization applicable.)

🧩 Algorithm:
Same as Approach 1.

⏱ Time Complexity: O(N).
📦 Space Complexity: O(H).
*/
bool isSymmetricOptimal(TreeNode* root) {
    return isSymmetricBruteForce(root);
}

/* Helper function to create sample tree */
TreeNode* createSampleTree() {
    /*
         1
        / \
       2   2
      / \ / \
     3  4 4  3
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);
    return root;
}

/* Helper function to delete tree */
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Symmetric Tree Problem ===\n\n";

    TreeNode* tree = createSampleTree();

    cout << "Approach 1 (Recursive) result: " << (isSymmetricBruteForce(tree) ? "true" : "false") << "\n";
    cout << "Approach 2 (Iterative) result: " << (isSymmetricBetter(tree) ? "true" : "false") << "\n";
    cout << "Approach 3 (Optimal - Recursive) result: " << (isSymmetricOptimal(tree) ? "true" : "false") << "\n";

    deleteTree(tree);
    return 0;
}

/*
✅ Approach Overview:
- Approach 1: Recursive mirror check using depth-first traversal, clean and intuitive.
- Approach 2: Iterative using queue to simulate recursion stack, avoids recursion overhead.
- Approach 3: Same as Approach 1; recursion is optimal for this problem.
All three approaches operate in O(N) time and O(H) space, with slight tradeoffs between recursion and iteration.
*/
