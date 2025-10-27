#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Construct BST from Preorder Traversal
Problem Link: https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/

Problem Statement:
Given an array of integers preorder, construct a Binary Search Tree (BST) 
by inserting the values in preorder sequence and return the root of the tree.

Example:
Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]
Explanation: BST constructed following preorder insertion rules.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Preorder + Sorted Inorder (Build BST via BT)
   ------------------------------------------------------
   💡 Idea:
   The inorder traversal of BST is the sorted preorder. Build like "BT from preorder+inorder".

   🧩 Algorithm:
   1. Copy and sort preorder to get inorder.
   2. Build map from inorder value to index.
   3. Use recursive helper with indices to split intervals.
      - The first preorder element is the root.
      - Recursively split left and right subtrees.
   4. Time: O(N log N)

   ⏱ Time Complexity: O(N log N)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildBT(int ps, int pe, vector<int>& preorder, int is, int ie, vector<int>& inorder, unordered_map<int,int>& m) {
    if(ps > pe || is > ie) return nullptr;
    TreeNode* root = new TreeNode(preorder[ps]);
    int ir = m[root->val];
    int leftLen = ir - is;
    root->left = buildBT(ps + 1, ps + leftLen, preorder, is, ir - 1, inorder, m);
    root->right = buildBT(ps + leftLen + 1, pe, preorder, ir + 1, ie, inorder, m);
    return root;
}
TreeNode* bstFromPreorder_BT(vector<int>& preorder) {
    int n = preorder.size();
    vector<int> inorder = preorder;
    sort(inorder.begin(), inorder.end());

    unordered_map<int, int> m;
    for(int i = 0; i < n; i++) m[inorder[i]] = i;

    return buildBT(0, n-1, preorder, 0, n-1, inorder, m);
}

/* ------------------------------------------------------
   Approach 2: Upper Bound Recursion (Optimal for BST)
   ------------------------------------------------------
   💡 Idea:
   Use BST property - left < root < right. Recursively build with upper bound.

   🧩 Algorithm:
   1. Use `i` pointer in recursion for preorder index.
   2. If out of bounds or value > upperBound, return null.
   3. Build node, then left-subtree (upper bound: node->val), then right (upper bound: passed).

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(H)
------------------------------------------------------ */
TreeNode* buildBST(vector<int>& preorder, int& i, int upperBound) {
    if(i == preorder.size() || preorder[i] > upperBound) return nullptr;
    TreeNode* node = new TreeNode(preorder[i++]);
    node->left = buildBST(preorder, i, node->val);
    node->right = buildBST(preorder, i, upperBound);
    return node;
}
TreeNode* bstFromPreorder_Optimal(vector<int>& preorder) {
    int i = 0;
    return buildBST(preorder, i, INT_MAX);
}

/* ------------------------------------------------------
   Approach 3: Iterative Insertion
   ------------------------------------------------------
   💡 Idea:
   Insert each preorder value into BST one by one.

   🧩 Algorithm:
   1. Start root = preorder[0].
   2. For each value, find correct spot and insert as per BST rule.

   ⏱ Time Complexity: O(N^2) worst case (can degrade if tree is unbalanced)
   📦 Space Complexity: O(1) (w/o recursion)
------------------------------------------------------ */
void insertIter(TreeNode* root, TreeNode* newNode) {
    while (true) {
        if (root->val < newNode->val) {
            if (root->right) root = root->right;
            else { root->right = newNode; break; }
        } else {
            if (root->left) root = root->left;
            else { root->left = newNode; break; }
        }
    }
}
TreeNode* bstFromPreorder_Iterative(vector<int>& preorder) {
    TreeNode* root = new TreeNode(preorder[0]);
    for (int i = 1; i < preorder.size(); i++) {
        TreeNode* newNode = new TreeNode(preorder[i]);
        insertIter(root, newNode);
    }
    return root;
}

/* Utility: Print Level Order for Validation */
void printLevel(TreeNode* root) {
    if (!root) { cout << "Empty\n"; return; }
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        cout << node->val << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    cout << endl;
}

/* ===================== Main Function ===================== */
int main() {
    vector<int> preorder = {8,5,1,7,10,12};

    TreeNode* t1 = bstFromPreorder_BT(preorder);
    cout << "BST from Preorder (BT style): ";
    printLevel(t1);

    TreeNode* t2 = bstFromPreorder_Optimal(preorder);
    cout << "BST from Preorder (Upper Bound): ";
    printLevel(t2);

    TreeNode* t3 = bstFromPreorder_Iterative(preorder);
    cout << "BST from Preorder (Iterative Insert): ";
    printLevel(t3);

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method                | Time Complexity | Space Complexity | Notes                       |
       |-----------------------|-----------------|------------------|-----------------------------|
       | BT from Inorder+Pre   | O(N log N)      | O(N)             | Clean, requires sorting     |
       | Upper Bound Recursion | O(N)            | O(H)             | Optimal, most efficient     |
       | Iterative Insert      | O(N^2)          | O(1)             | Naive, worst case slow      |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
