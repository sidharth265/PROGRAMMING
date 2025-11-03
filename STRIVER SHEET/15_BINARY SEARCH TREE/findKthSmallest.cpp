#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Kth Smallest Element in a BST
Problem Link: https://leetcode.com/problems/kth-smallest-element-in-a-bst

Problem Statement:
Given the root of a Binary Search Tree (BST) and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.

Example 1:
Input: root = [3,1,4,null,2], k = 1
Output: 1
Explanation: The smallest element is 1.

Example 2:
Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
Explanation: The 3rd smallest element is 3.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Level Order Traversal + Max Heap (Brute Force)
   ------------------------------------------------------
   💡 Idea:
   Traverse the tree level by level, pushing values into a max heap that holds at most k elements.
   The root of the max heap will be the kth smallest element after traversal.

   🧩 Algorithm:
   1. Initialize a max heap and a queue for BFS.
   2. Push root to queue.
   3. While queue is not empty:
       a. Pop element from queue.
       b. Push its value into max heap.
       c. If max heap size exceeds k, pop from max heap.
       d. Push left and right children if exist.
   4. Return the root of max heap (kth smallest).

   ⏱ Time Complexity: O(N log k)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int kthSmallestLevelOrder(TreeNode* root, int k) {
    priority_queue<int> pq;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            TreeNode* temp = q.front();
            q.pop();

            pq.push(temp->val);
            if (pq.size() > k) pq.pop();

            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }
    return pq.top();
}

/* ------------------------------------------------------
   Approach 2: Iterative Inorder Traversal (Optimal)
   ------------------------------------------------------
   💡 Idea:
   BST inorder traversal visits nodes in ascending order. 
   Use iterative inorder to traverse and stop when kth element is found.

   🧩 Algorithm:
   1. Use a stack and push all left children.
   2. Pop from stack decrementing k each pop.
   3. When k hits 0, current popped value is kth smallest.
   4. Move to right child and continue until kth element is found.

   ⏱ Time Complexity: O(H + k), where H is tree height
   📦 Space Complexity: O(H)
------------------------------------------------------ */
int kthSmallestInorder(TreeNode* root, int k) {
    stack<TreeNode*> st;
    while (root || !st.empty()) {
        while (root) {
            st.push(root);
            root = root->left;
        }
        root = st.top(); st.pop();
        k--;
        if (k == 0) break;
        root = root->right;
    }
    return root->val;
}

/* Utility: Build BST from vector (for testing) */
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

/* ===================== Main Function ===================== */
int main() {
    // Constructing BST for test
    vector<int> vals = {5, 3, 6, 2, 4, 1};
    TreeNode* root = nullptr;
    for (int v : vals) root = insertBST(root, v);

    cout << "Test Case: k = 3\n";

    cout << "Level Order + Max Heap: " << kthSmallestLevelOrder(root, 3) << endl;
    cout << "Iterative Inorder      : " << kthSmallestInorder(root, 3) << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method                   | Time Complexity | Space Complexity | Notes                |
       |--------------------------|----------------|------------------|----------------------|
       | Level Order + Max Heap    | O(N log k)     | O(N)             | Works but less optimal|
       | Iterative Inorder         | O(H + k)       | O(H)             | Preferred approach   |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
