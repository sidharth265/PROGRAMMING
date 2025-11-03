#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Recover Binary Search Tree
Problem Link: https://leetcode.com/problems/recover-binary-search-tree/

Problem Statement:
You are given the root of a binary search tree (BST), where exactly two nodes have been swapped by mistake.  
Recover the tree without changing its structure.

Example:
Input: root = [1,3,null,null,2]
  1
   \
    3
   /
  2
Output: [3,1,null,null,2]
Explanation: 3 and 1 are swapped.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Brute Force (Inorder Traversal + Sorting)
   ------------------------------------------------------
   💡 Idea:
   Convert the tree to inorder sequence, sort it, and reassign the values during another inorder traversal.

   🧩 Algorithm:
   1. Do an inorder traversal, store node values in a vector.
   2. Sort the vector to get correct inorder sequence.
   3. Traverse tree again inorder, overwrite node values from sorted vector.
   4. Tree structure is not changed—only values fixed.

   ⏱ Time Complexity: O(N log N)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void recoverTreeBrute(TreeNode* root) {
    vector<int> traversal;
    stack<TreeNode*> st;
    TreeNode* curr = root;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        traversal.push_back(curr->val);
        curr = curr->right;
    }
    vector<int> inorder = traversal;
    sort(inorder.begin(), inorder.end());

    st = stack<TreeNode*>();
    int i = 0; 
    curr = root;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        curr->val = inorder[i++];  // assignment, not comparison
        curr = curr->right;
    }
}

/* ------------------------------------------------------
   Approach 2: Better (Iterative Inorder - Find Swapped Nodes)
   ------------------------------------------------------
   💡 Idea:
   During an inorder traversal, two pairs violate order if swapped. Find them and swap nodes.

   🧩 Algorithm:
   1. Use iterative inorder traversal with "last" pointer.
   2. If a node's value < last node, store pointers as "first" and "second" swapped nodes.
   3. After traversal, swap values of these two nodes.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(H) - stack depth
------------------------------------------------------ */
void recoverTreeBetter(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode *curr = root, *one = nullptr, *two = nullptr, *last = nullptr;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        if (last && curr->val < last->val) {
            if (!one) one = last;
            two = curr;
        }
        last = curr;
        curr = curr->right;
    }
    if (one && two) swap(one->val, two->val);
}

/* ------------------------------------------------------
   Approach 3: Optimal (Morris Inorder, O(1) Space)
   ------------------------------------------------------
   💡 Idea:
   Use Morris Inorder traversal for O(1) space. 
   Detect the two swapped nodes as above during traversal.

   🧩 Algorithm:
   1. Do Morris inorder traversal.
   2. Detect first and second out-of-order nodes exactly the same as Better approach.
   3. Swap their values at the end.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(1)
------------------------------------------------------ */
void recoverTreeOptimal(TreeNode* root) {
    TreeNode *curr = root, *one = nullptr, *two = nullptr, *last = nullptr;
    while (curr) {
        if (!curr->left) {
            if (last && curr->val < last->val) {
                if (!one) one = last;
                two = curr;
            }
            last = curr;
            curr = curr->right;
        } else {
            TreeNode* prev = curr->left;
            while (prev->right && prev->right != curr) prev = prev->right;
            if (!prev->right) {
                prev->right = curr;
                curr = curr->left;
            } else {
                prev->right = nullptr;
                if (last && curr->val < last->val) {
                    if (!one) one = last;
                    two = curr;
                }
                last = curr;
                curr = curr->right;
            }
        }
    }
    if (one && two) swap(one->val, two->val);
}

/* Utility: Inorder traversal print */
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

/* ===================== Main Function ===================== */
int main() {
    /*
     * Original BST:     3
     *                 /   \
     *                1     4
     *                   /
     *                  2
     * Swap nodes 2 and 3, BST becomes:
     *         2
     *        / \
     *       1   4
     *          /
     *         3
     */
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->right->left = new TreeNode(3);

    cout << "Before recovery (inorder): "; inorder(root); cout << endl;
    recoverTreeBrute(root);
    cout << "After brute recovery       : "; inorder(root); cout << endl;

    // Swap again for next trial
    swap(root->val, root->right->left->val);
    cout << "Corrupted again (inorder) : "; inorder(root); cout << endl;
    recoverTreeBetter(root);
    cout << "After better recovery      : "; inorder(root); cout << endl;

    // Swap again for next trial
    swap(root->val, root->right->left->val);
    cout << "Corrupted again (inorder) : "; inorder(root); cout << endl;
    recoverTreeOptimal(root);
    cout << "After optimal recovery     : "; inorder(root); cout << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method      | Time Complexity | Space Complexity | Notes                        |
       |-------------|-----------------|------------------|------------------------------|
       | Brute Force | O(N log N)      | O(N)             | Uses extra space, simple      |
       | Better      | O(N)            | O(H)             | Stack, fast and practical     |
       | Optimal     | O(N)            | O(1)             | Morris Inorder, strict best   |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
