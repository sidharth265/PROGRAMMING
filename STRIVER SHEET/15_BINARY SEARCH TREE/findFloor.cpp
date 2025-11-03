#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Floor in a Binary Search Tree (BST)
Problem Link: https://practice.geeksforgeeks.org/problems/implement-floor-in-bst

Problem Statement:
Given a Binary Search Tree (BST) and a value x, find the floor of x in the BST.
The floor of x is the greatest element in BST less than or equal to x.
If no such element exists, return -1.

Example 1:
Input:
        8
       / \
      4   12
     / \   \
    2   6   14
x = 5

Output: 4
Explanation: 4 is the largest value <= 5 in BST.

Example 2:
Input:
       10
     /    \
    5      15
x = 16

Output: 15
Explanation: 15 is the largest value <= 16 in BST.

Example 3:
Input:
       10
     /    \
    5      15
x = 2

Output: -1
Explanation: No value <= 2 in BST.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Brute Force (Inorder Traversal)
   ------------------------------------------------------
   💡 Idea:
   Traverse the entire BST in inorder order, find the largest value <= x.

   🧩 Algorithm:
   1. Traverse BST in inorder fashion, storing values in a vector.
   2. After traversal, scan the vector and find rightmost value <= x.
   3. If no such value, return -1.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void inorderFloor(Node* root, vector<int>& vals) {
    if (!root) return;
    inorderFloor(root->left, vals);
    vals.push_back(root->data);
    inorderFloor(root->right, vals);
}

int floorBrute(Node* root, int x) {
    vector<int> vals;
    inorderFloor(root, vals);
    int ans = -1;
    for (int val : vals) {
        if (val <= x) ans = val;
        else break;
    }
    return ans;
}

/* ------------------------------------------------------
   Approach 2: Recursive BST Search
   ------------------------------------------------------
   💡 Idea:
   Use BST property to recursively search for floor;
   if node's value <= x, store it and go right; else go left.

   🧩 Algorithm:
   1. If node is NULL, return.
   2. If node's value <= x, update answer and recur right.
   3. Else recur left.

   ⏱ Time Complexity: O(H) [H = height of tree]
   📦 Space Complexity: O(H) [Stack]
------------------------------------------------------ */
void floorRecursiveHelper(Node* root, int x, int& ans) {
    if (!root) return;
    if (root->data <= x) {
        ans = root->data;
        floorRecursiveHelper(root->right, x, ans);
    } else {
        floorRecursiveHelper(root->left, x, ans);
    }
}

int floorRecursive(Node* root, int x) {
    int ans = -1;
    floorRecursiveHelper(root, x, ans);
    return ans;
}

/* ------------------------------------------------------
   Approach 3: Iterative BST Search (Optimal)
   ------------------------------------------------------
   💡 Idea:
   Traverse down the BST; if current node's value equals x,
   return x. If node's value < x, update answer and move right.
   Else move left.

   🧩 Algorithm:
   1. Initialize ans = -1.
   2. While root is not NULL:
      a. If node's value == x, return x.
      b. If node's value < x, update ans and move right.
      c. If node's value > x, move left.
   3. Return ans.

   ⏱ Time Complexity: O(H) [H = height of tree]
   📦 Space Complexity: O(1)
------------------------------------------------------ */
int floorIterative(Node* root, int x) {
    int ans = -1;
    while (root) {
        if (root->data == x) return x;
        else if (root->data > x) root = root->left;
        else {
            ans = root->data;
            root = root->right;
        }
    }
    return ans;
}

/* Utility: Build sample BST for test cases */
Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

/* ===================== Main Function ===================== */
int main() {
    // Example 1
    Node* root1 = nullptr;
    for (int val : {8,4,12,2,6,14}) root1 = insert(root1, val);

    cout << "Test Case 1 (x=5):\n";
    cout << "Brute Force: " << floorBrute(root1, 5) << endl;
    cout << "Recursive  : " << floorRecursive(root1, 5) << endl;
    cout << "Iterative  : " << floorIterative(root1, 5) << endl;
    cout << endl;

    // Example 2
    Node* root2 = nullptr;
    for (int val : {10,5,15}) root2 = insert(root2, val);

    cout << "Test Case 2 (x=16):\n";
    cout << "Brute Force: " << floorBrute(root2, 16) << endl;
    cout << "Recursive  : " << floorRecursive(root2, 16) << endl;
    cout << "Iterative  : " << floorIterative(root2, 16) << endl;
    cout << endl;

    // Example 3: Floor is node value
    cout << "Test Case 3 (x=10):\n";
    cout << "Brute Force: " << floorBrute(root2, 10) << endl;
    cout << "Recursive  : " << floorRecursive(root2, 10) << endl;
    cout << "Iterative  : " << floorIterative(root2, 10) << endl;
    cout << endl;

    // Example 4: No floor present
    cout << "Test Case 4 (x=2):\n";
    cout << "Brute Force: " << floorBrute(root2, 2) << endl;
    cout << "Recursive  : " << floorRecursive(root2, 2) << endl;
    cout << "Iterative  : " << floorIterative(root2, 2) << endl;
    cout << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method      | Time Complexity | Space Complexity | Suitable For           |
       |-------------|----------------|------------------|------------------------|
       | Brute Force | O(N)           | O(N)             | Small/unbalanced trees |
       | Recursive   | O(H)           | O(H)             | When stack is feasible |
       | Iterative   | O(H)           | O(1)             | Large/deep trees       |
       ------------------------------------------------------
       Iterative is preferred for interviews as it is both fast and space-efficient.
    ------------------------------------------------------ */
    return 0;
}
