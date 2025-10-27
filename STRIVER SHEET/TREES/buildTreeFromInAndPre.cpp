#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Construct Binary Tree from Preorder and Inorder Traversal
 Problem Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

 Problem Statement:
 -----------------
 Given two integer arrays, preorder and inorder, construct the binary tree and return its root.
 
 Example:
 Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 Output: 
    3
   / \
  9  20
     / \
    15  7

 Constraints:
 - 1 <= preorder.length <= 3000
 - inorder.length == preorder.length
 - Values in preorder/inorder are unique
====================================================
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* 
==========================================
 Approach 1: Brute Force - Find Root in Inorder for Every Call
------------------------------------------
💡 Idea:
At each recursive step, find the root from preorder, then search for it in inorder to split left and right subtrees.

🧩 Algorithm:
1. Root is always preorder[ps].
2. Search for root in inorder between indices is and ie.
3. Recursively build left and right subtrees.

⏱ Time Complexity: O(N^2) because of repeated sequential search in inorder.
📦 Space Complexity: O(N) recursion + output
*/
TreeNode* buildTreeBrute(vector<int>& preorder, vector<int>& inorder, int ps, int pe, int is, int ie) {
    if (ps > pe || is > ie) return nullptr;
    int rootVal = preorder[ps];
    TreeNode* root = new TreeNode(rootVal);

    int ir = is;
    while (ir <= ie && inorder[ir] != rootVal) ir++;
    int leftLen = ir - is;

    root->left = buildTreeBrute(preorder, inorder, ps + 1, ps + leftLen, is, ir - 1);
    root->right = buildTreeBrute(preorder, inorder, ps + leftLen + 1, pe, ir + 1, ie);

    return root;
}

/* 
==========================================
 Approach 2: Better - Use Hashmap to Find Root Index in O(1)
------------------------------------------
💡 Idea:
Preprocess inorder positions with a hashmap for O(1) lookup.

🧩 Algorithm:
1. Precompute indices in a hash map.
2. Recursively build tree using mapped indices.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
TreeNode* build(int ps, int pe, vector<int>& preorder, int is, int ie, vector<int>& inorder, unordered_map<int, int>& m) {
    if (ps > pe || is > ie) return nullptr;
    TreeNode* root = new TreeNode(preorder[ps]);
    int ir = m[root->val];
    int leftLen = ir - is;
    root->left = build(ps + 1, ps + leftLen, preorder, is, ir - 1, inorder, m);
    root->right = build(ps + leftLen + 1, pe, preorder, ir + 1, ie, inorder, m);
    return root;
}

TreeNode* buildTreeBetter(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> m;
    for (int i = 0; i < (int)inorder.size(); ++i) m[inorder[i]] = i;
    return build(0, preorder.size() - 1, preorder, 0, inorder.size() - 1, inorder, m);
}

/*
==========================================
 Approach 3: Optimal - Iterative with Stack
------------------------------------------
💡 Idea:
Simulate recursion using a stack, with pointers and inorder index tracking; avoids explicit recursion.

🧩 Algorithm:
1. Push root from preorder onto stack.
2. Track position in inorder.
3. Attach left as long as stack top doesn't match inorder.
4. Backtrack and attach right children.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
TreeNode* buildTreeOptimal(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.empty()) return nullptr;
    TreeNode* root = new TreeNode(preorder[0]);
    stack<TreeNode*> stk;
    stk.push(root);
    int i = 1, j = 0;
    while (i < (int)preorder.size()) {
        TreeNode* node = stk.top();
        if (node->val != inorder[j]) {
            node->left = new TreeNode(preorder[i++]);
            stk.push(node->left);
        } else {
            while (!stk.empty() && stk.top()->val == inorder[j]) {
                node = stk.top(); stk.pop(); j++;
            }
            node->right = new TreeNode(preorder[i++]);
            stk.push(node->right);
        }
    }
    return root;
}

/* Helper for printing inorder traversal of constructed tree */
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Construct Binary Tree from Preorder and Inorder ===\n\n";
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};

    TreeNode* tree1 = buildTreeBrute(preorder, inorder, 0, preorder.size()-1, 0, inorder.size()-1);
    cout << "Brute Force Inorder: ";
    printInorder(tree1); cout << "\n";

    TreeNode* tree2 = buildTreeBetter(preorder, inorder);
    cout << "Better Inorder: ";
    printInorder(tree2); cout << "\n";

    TreeNode* tree3 = buildTreeOptimal(preorder, inorder);
    cout << "Optimal Inorder: ";
    printInorder(tree3); cout << "\n";

    // Deletion omitted for brevity
    return 0;
}

/*
✅ Approach Overview:
- Brute Force: Recursively searches for root in inorder every time (O(N^2)).
- Better: Hashmap for O(1) root lookup, yields O(N) time and space.
- Optimal: Iterative stack method avoids recursion, same time/space, may be preferred for very deep trees.
*/
