#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Two Sum IV - Input is a BST
Problem Link: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/

Problem Statement:
Given the root of a Binary Search Tree and an integer k,
return true if there exist two elements in the BST such that their sum is equal to k.

Example:
Input: root = [5,3,6,2,4,null,7], k = 9
Output: true
Explanation: 2 + 7 = 9.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Brute Force - Inorder Traversal + Two Pointer
   ------------------------------------------------------
   💡 Idea:
   Get sorted node values by inorder traversal and use two pointers to find if sum exists.

   🧩 Algorithm:
   1. Inorder traversal to get sorted values.
   2. Use two pointers at start and end.
   3. Move pointers until sum == k or pointers cross.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool findTargetBrute(TreeNode* root, int k) {
    vector<int> inorder;
    stack<TreeNode*> st;
    TreeNode* curr = root;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        inorder.push_back(curr->val);
        curr = curr->right;
    }
    int i = 0, j = (int)inorder.size() - 1;
    while (i < j) {
        int sum = inorder[i] + inorder[j];
        if (sum == k) return true;
        else if (sum > k) j--;
        else i++;
    }
    return false;
}

/* ------------------------------------------------------
   Approach 2: Better - DFS + HashSet
   ------------------------------------------------------
   💡 Idea:
   Use DFS with a hash set to check for the complement of each value during traversal.

   🧩 Algorithm:
   1. Traverse BST using DFS.
   2. For each node, check if (k - node->val) is in the set.
   3. If yes, return true.
   4. Else, insert node->val into the set.
   5. Return false if no pair found.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
bool dfsHash(TreeNode* root, int k, unordered_set<int>& s) {
    if (!root) return false;
    if (s.count(k - root->val)) return true;
    s.insert(root->val);
    return dfsHash(root->left, k, s) || dfsHash(root->right, k, s);
}

bool findTargetBetter(TreeNode* root, int k) {
    unordered_set<int> s;
    return dfsHash(root, k, s);
}

/* ------------------------------------------------------
   Approach 3: Optimal - Two Iterators (Inorder and Reverse Inorder)
   ------------------------------------------------------
   💡 Idea:
   Use two iterators simulating two pointers without extra space except recursion stack:
   - One does standard inorder traversal (ascending)
   - One does reverse inorder traversal (descending)
   Move iterators towards each other checking sums.

   🧩 Algorithm:
   1. Use two stacks to simulate two BST iterators.
   2. Initialize left iterator with leftmost nodes.
   3. Initialize right iterator with rightmost nodes.
   4. While values from iterators don’t cross:
       - If sum == k, return true.
       - If sum < k, advance left iterator.
       - If sum > k, advance right iterator.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(H), height of tree
------------------------------------------------------ */
class BSTIterator {
    stack<TreeNode*> st;
    bool reverse;
    void pushAll(TreeNode* node) {
        while (node) {
            st.push(node);
            node = reverse ? node->right : node->left;
        }
    }
public:
    BSTIterator(TreeNode* root, bool isReverse) : reverse(isReverse) {
        pushAll(root);
    }
    int next() {
        TreeNode* topNode = st.top(); st.pop();
        if (reverse) pushAll(topNode->left);
        else pushAll(topNode->right);
        return topNode->val;
    }
    bool hasNext() {
        return !st.empty();
    }
};

bool findTargetOptimal(TreeNode* root, int k) {
    if (!root) return false;
    BSTIterator leftIt(root, false);
    BSTIterator rightIt(root, true);
    int i = leftIt.next();
    int j = rightIt.next();
    while (i < j) {
        int sum = i + j;
        if (sum == k) return true;
        else if (sum < k) {
            if (leftIt.hasNext()) i = leftIt.next();
            else break;
        } else {
            if (rightIt.hasNext()) j = rightIt.next();
            else break;
        }
    }
    return false;
}

/* ===================== Main Function ===================== */
int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(7);

    int k1 = 9, k2 = 28;

    cout << "Brute Force (k=9): " << (findTargetBrute(root, k1) ? "True" : "False") << endl;
    cout << "Better       (k=9): " << (findTargetBetter(root, k1) ? "True" : "False") << endl;
    cout << "Optimal      (k=9): " << (findTargetOptimal(root, k1) ? "True" : "False") << endl;

    cout << "Brute Force (k=28): " << (findTargetBrute(root, k2) ? "True" : "False") << endl;
    cout << "Better       (k=28): " << (findTargetBetter(root, k2) ? "True" : "False") << endl;
    cout << "Optimal      (k=28): " << (findTargetOptimal(root, k2) ? "True" : "False") << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method        | Time Complexity | Space Complexity | Notes                    |
       |---------------|-----------------|------------------|--------------------------|
       | Brute Force   | O(N)            | O(N)             | Uses full inorder vector  |
       | Better (Hash) | O(N)            | O(N)             | HashSet for complements   |
       | Optimal       | O(N)            | O(H)             | Two BST iterators         |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
