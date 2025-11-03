#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Ceil in a Binary Search Tree (BST)
Problem Link: https://practice.geeksforgeeks.org/problems/implement-ceil-in-bst (Sample GFG link)

Problem Statement:
Given a Binary Search Tree (BST) and a value x, find the ceil of x in the BST.
The ceil of x is the smallest element in BST greater than or equal to x.
If no such element exists, return -1.

Example 1:
Input:
        8
       / \
      4   12
     / \   \
    2   6   14
x = 5

Output: 6
Explanation: 6 is the smallest value >= 5 in BST.

Example 2:
Input:
       10
     /    \
    5      15
x = 16

Output: -1
Explanation: There is no value >= 16 in BST.

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Brute Force (Inorder Traversal)
   ------------------------------------------------------
   💡 Idea:
   Traverse the entire tree using inorder traversal and
   find the smallest value >= x.

   🧩 Algorithm:
   1. Traverse BST in inorder fashion, storing values in a vector.
   2. After traversal, scan the vector to find the first value >= x.
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

void inorder(Node* root, vector<int>& vals) {
    if (!root) return;
    inorder(root->left, vals);
    vals.push_back(root->data);
    inorder(root->right, vals);
}

int findCeilBrute(Node* root, int x) {
    vector<int> vals;
    inorder(root, vals);
    for (int val : vals) {
        if (val >= x) return val;
    }
    return -1;
}

/* ------------------------------------------------------
   Approach 2: Recursive BST Search
   ------------------------------------------------------
   💡 Idea:
   Use BST property to recursively search for ceil;
   if node's value >= x, store it and go left else go right.

   🧩 Algorithm:
   1. If node is NULL, return.
   2. If node's value >= x, update answer and recur left.
   3. Else, recur right.

   ⏱ Time Complexity: O(H) [H = height of tree]
   📦 Space Complexity: O(H) [Stack]
------------------------------------------------------ */
void findCeilRecursiveHelper(Node* root, int x, int& ans) {
    if (!root) return;
    if (root->data >= x) {
        ans = root->data;
        findCeilRecursiveHelper(root->left, x, ans);
    } else {
        findCeilRecursiveHelper(root->right, x, ans);
    }
}

int findCeilRecursive(Node* root, int x) {
    int ans = -1;
    findCeilRecursiveHelper(root, x, ans);
    return ans;
}

/* ------------------------------------------------------
   Approach 3: Iterative BST Search (Optimal)
   ------------------------------------------------------
   💡 Idea:
   Traverse down the BST; if current node's value equals x,
   return x. If node's value > x, update answer and move left.
   Else move right.

   🧩 Algorithm:
   1. Initialize ans=-1.
   2. While root is not NULL:
       a. If node's value == x, return x.
       b. If node's value > x, update ans and move left.
       c. If node's value < x, move right.
   3. Return ans.

   ⏱ Time Complexity: O(H) [H = height of tree]
   📦 Space Complexity: O(1)
------------------------------------------------------ */
int findCeilIterative(Node* root, int x) {
    int ans = -1;
    while (root) {
        if (root->data == x) return x;
        else if (root->data < x) root = root->right;
        else {
            ans = root->data;
            root = root->left;
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
    cout << "Brute Force: " << findCeilBrute(root1, 5) << endl;
    cout << "Recursive  : " << findCeilRecursive(root1, 5) << endl;
    cout << "Iterative  : " << findCeilIterative(root1, 5) << endl;
    cout << endl;

    // Example 2
    Node* root2 = nullptr;
    for (int val : {10,5,15}) root2 = insert(root2, val);

    cout << "Test Case 2 (x=16):\n";
    cout << "Brute Force: " << findCeilBrute(root2, 16) << endl;
    cout << "Recursive  : " << findCeilRecursive(root2, 16) << endl;
    cout << "Iterative  : " << findCeilIterative(root2, 16) << endl;
    cout << endl;

    // Example 3: Ceil is node value
    cout << "Test Case 3 (x=10):\n";
    cout << "Brute Force: " << findCeilBrute(root2, 10) << endl;
    cout << "Recursive  : " << findCeilRecursive(root2, 10) << endl;
    cout << "Iterative  : " << findCeilIterative(root2, 10) << endl;
    cout << endl;

    // Example 4: No ceil present
    cout << "Test Case 4 (x=20):\n";
    cout << "Brute Force: " << findCeilBrute(root1, 20) << endl;
    cout << "Recursive  : " << findCeilRecursive(root1, 20) << endl;
    cout << "Iterative  : " << findCeilIterative(root1, 20) << endl;
    cout << endl;

    // Add more custom test cases if needed

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method      | Time Complexity | Space Complexity | Suitable For           |
       |-------------|----------------|------------------|------------------------|
       | Brute Force | O(N)           | O(N)             | Small/unbalanced trees |
       | Recursive   | O(H)           | O(H)             | When stack is feasible |
       | Iterative   | O(H)           | O(1)             | Large/deep trees       |
       ------------------------------------------------------
       Iterative is preferred for interview as it is both fast and space-efficient.
    ------------------------------------------------------ */
    return 0;
}
