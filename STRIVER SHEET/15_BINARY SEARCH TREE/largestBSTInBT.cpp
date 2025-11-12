#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Largest BST Subtree
Problem Link: https://leetcode.com/problems/largest-bst-subtree/

Problem Statement:
Given a binary tree root, return the size of the largest subtree which is also a Binary Search Tree (BST).

Example:
Input: root = [10,5,15,1,8,null,7]
Output: 3
Explanation: The largest BST subtree is [5,1,8].

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Brute Force with Validation on Every Node
   ------------------------------------------------------
   💡 Idea:
   For every node, calculate the size of its subtree and check if it is BST.
   Keep track of the largest BST size found.

   🧩 Algorithm:
   1. For each node, recursively calculate subtree size.
   2. Check if subtree is BST using range validation.
   3. Update largest size if valid.
   4. Return subtree size.

   ⏱ Time Complexity: O(N^2) - Each node’s subtree checked with validation O(N)
   📦 Space Complexity: O(H) for recursion stack
------------------------------------------------------ */
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

bool validBST(Node *root, int low, int high) {
    if (!root) return true;
    return (root->data < high && root->data > low) &&
           validBST(root->left, low, root->data) &&
           validBST(root->right, root->data, high);
}

int generateBrute(Node *root, int& largest) {
    if (!root) return 0;
    int size = generateBrute(root->left, largest) + generateBrute(root->right, largest) + 1;
    if (size > largest) {
        if (validBST(root, INT_MIN, INT_MAX))
            largest = size;
    }
    return size;
}

int largestBstBrute(Node *root) {
    int largest = 0;
    generateBrute(root, largest);
    return largest;
}

/* ------------------------------------------------------
   Approach 2: Optimal Bottom-Up Dynamic Programming
   ------------------------------------------------------
   💡 Idea:
   Use postorder traversal, returning:
   - size of largest BST in subtree
   - min and max value in subtree
   If current root's value > max of left subtree and < min of right subtree,
   it forms a BST with left and right subtrees.

   🧩 Algorithm:
   1. For null node return {size=0, max=INT_MIN, min=INT_MAX}.
   2. Recursively get values from left and right subtree.
   3. Check if current node forms BST.
   4. Return:
      - {size, max_value, min_value} if BST,
      - else {max(left_size, right_size), INT_MAX, INT_MIN} as invalid.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(H)
------------------------------------------------------ */
vector<int> generateOptimal(Node* root) {
    if (!root) return {0, INT_MIN, INT_MAX};  // {size, max, min}

    vector<int> l = generateOptimal(root->left);
    vector<int> r = generateOptimal(root->right);

    // Check if valid BST
    if (root->data > l[1] && root->data < r[2]) {
        int size = l[0] + r[0] + 1;
        int maxVal = max(root->data, r[1]);
        int minVal = min(root->data, l[2]);
        return {size, maxVal, minVal};
    }

    // If not BST, propagate max size from children with invalid min-max
    return {max(l[0], r[0]), INT_MAX, INT_MIN};
}

int largestBstOptimal(Node* root) {
    return generateOptimal(root)[0];
}

/* ===================== Main Function ===================== */
int main() {
    /*
      Construct tree:
            10
           /  \
          5    15
         / \     \
        1   8     7
      Largest BST subtree is [5,1,8] with size = 3
    */
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(1);
    root->left->right = new Node(8);
    root->right->right = new Node(7);

    cout << "Largest BST subtree size (Brute): " << largestBstBrute(root) << endl;
    cout << "Largest BST subtree size (Optimal): " << largestBstOptimal(root) << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method    | Time Complexity | Space Complexity | Notes                        |
       |-----------|-----------------|------------------|------------------------------|
       | Brute     | O(N^2)          | O(H)             | Straightforward but slow      |
       | Optimal   | O(N)            | O(H)             | Bottom-up DP, efficient       |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
