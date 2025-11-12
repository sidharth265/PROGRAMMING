#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Children Sum Property
 Problem Link: https://practice.geeksforgeeks.org/problems/children-sum-property/1

 Problem Statement:
 -----------------
 Given a binary tree, check if the tree satisfies the children sum property.
 The property states that for every node, the node's value must be equal to 
 the sum of values of its left and right child nodes (if they exist).
 Leaf nodes are considered as satisfying the property.

 Example:
 Input:
        10
       /  \
      8    2
     / \  
    3   5 

 Output: 1 (True)
 Explanation: 10 = 8 + 2, 8 = 3 + 5 and leaf nodes satisfy.

 Constraints:
 - Number of nodes in the tree is up to 10^5
 - Node values are integers.
====================================================
*/

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/* 
==========================================
 Approach 1: Recursive Check for Children Sum Property
-----------------------------------------
💡 Idea:
Use recursion to check the property for every node.
If the node is a leaf, it automatically satisfies the property.
For other nodes, verify if node data equals sum of children's data 
and recursively check for left and right subtrees.

🧩 Algorithm:
1. If root is null, return true.
2. If root is leaf node, return true.
3. Recursively check left and right subtree.
4. Sum left and right child data if they exist.
5. Check if root data equals this sum.
6. Return true only if all conditions hold.

⏱ Time Complexity: O(N), visiting all nodes once.
📦 Space Complexity: O(H), recursion stack height.
*/
int isSumProperty(Node* root) {
    if (!root) return 1;
    if (!root->left && !root->right) return 1;

    if (!isSumProperty(root->left)) return 0;
    if (!isSumProperty(root->right)) return 0;

    int leftData = (root->left) ? root->left->data : 0;
    int rightData = (root->right) ? root->right->data : 0;

    return (root->data == leftData + rightData) ? 1 : 0;
}

/* Helper function to create sample tree */
Node* createSampleTree() {
    /*
          10
         /  \
        8    2
       / \  
      3   5 
    */
    Node* root = new Node(10);
    root->left = new Node(8);
    root->right = new Node(2);
    root->left->left = new Node(3);
    root->left->right = new Node(5);
    return root;
}

/* Helper function to delete tree */
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Children Sum Property Check ===\n\n";

    Node* tree = createSampleTree();

    cout << "Does tree satisfy children sum property? ";
    cout << (isSumProperty(tree) ? "Yes" : "No") << "\n";

    deleteTree(tree);

    return 0;
}

/*
✅ Approach Overview:
- Recursive DFS ensures checking all nodes.
- Leaf nodes are trivially accepted.
- Time complexity O(N), space O(H).
- This is the standard and optimal approach for this problem.
*/
