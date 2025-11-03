#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Kth Largest Element in a BST
Problem Link: https://leetcode.com/problems/kth-largest-element-in-a-bst (conceptually similar)

Problem Statement:
Given the root of a Binary Search Tree (BST) and an integer k, return the kth largest value (1-indexed) of all the values of the nodes in the tree.

Example 1:
Input: root = [5,3,6,2,4,null,null,1], k = 1
Output: 6
Explanation: The largest element is 6.

Example 2:
Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 4
Explanation: The 3rd largest element is 4.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Iterative Reverse Inorder Traversal (Optimal)
   ------------------------------------------------------
   💡 Idea:
   Reverse inorder traversal visits nodes in descending order.
   Traverse iteratively, decrement k until zero, then return node’s value.

   🧩 Algorithm:
   1. Use a stack to simulate reverse inorder: right -> node -> left.
   2. Push right children first going deep.
   3. Pop from stack, decrement k.
   4. When k == 0, this is the kth largest element.
   5. Move to left subtree to continue.

   ⏱ Time Complexity: O(H + k), where H is height of the BST
   📦 Space Complexity: O(H)
------------------------------------------------------ */

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

int kthLargest(Node *root, int k) {
    stack<Node*> st;
    while(root || !st.empty()) {
        while(root) {
            st.push(root);
            root = root->right;
        }
        root = st.top();
        st.pop();
        k--;
        if(k == 0) break;
        root = root->left;
    }
    return root->data;
}

/* Utility: Insert node in BST */
Node* insertBST(Node* root, int val) {
    if(!root) return new Node(val);
    if(val < root->data) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

/* ===================== Main Function ===================== */
int main() {
    vector<int> vals = {5, 3, 6, 2, 4, 1};
    Node* root = nullptr;
    for (int v : vals) root = insertBST(root, v);

    cout << "Test Case k=1 (largest): " << kthLargest(root, 1) << endl;
    cout << "Test Case k=3 (3rd largest): " << kthLargest(root, 3) << endl;
    cout << "Test Case k=6 (smallest): " << kthLargest(root, 6) << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method                   | Time Complexity | Space Complexity | Notes               |
       |--------------------------|----------------|------------------|---------------------|
       | Iterative Reverse Inorder | O(H + k)       | O(H)             | Efficient and clear |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
