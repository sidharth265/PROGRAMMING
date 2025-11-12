#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Inorder Predecessor and Successor in BST
Problem Link: https://practice.geeksforgeeks.org/problems/predecessor-and-successor/1

Problem Statement:
Given the root of a Binary Search Tree (BST) and a key, 
find the inorder predecessor and successor of the key in the BST.
- Predecessor: The largest value smaller than key.
- Successor: The smallest value greater than key.
If either does not exist, return nullptr for that node.

Example:
Input:      20
           /  \
          8    22
         / \
        4   12
           /  \
         10   14
Key = 10

Output: Predecessor = 8, Successor = 12

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Brute Force (Inorder Traversal + Linear Scan)
   ------------------------------------------------------
   💡 Idea:
   Generate the inorder traversal, then linearly scan the array for predecessor and successor.

   🧩 Algorithm:
   1. Do an inorder traversal, storing all nodes' values in a vector.
   2. Scan the vector to find the key.
   3. Predecessor is element just before key, successor is just after.
   4. If key not present, predecessor is the largest < key, successor is the smallest > key.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

void inorderVector(Node* root, vector<Node*>& vec) {
    if (!root) return;
    inorderVector(root->left, vec);
    vec.push_back(root);
    inorderVector(root->right, vec);
}

vector<Node*> findPreSucBrute(Node* root, int key) {
    vector<Node*> inorderNodes;
    inorderVector(root, inorderNodes);
    Node* pred = nullptr, *succ = nullptr;

    for (int i = 0; i < (int)inorderNodes.size(); ++i) {
        if (inorderNodes[i]->data < key) pred = inorderNodes[i];
        if (inorderNodes[i]->data > key) {
            succ = inorderNodes[i];
            break;
        }
    }
    return {pred, succ};
}

/* ------------------------------------------------------
   Approach 2: Better (Inorder, Single Scan On The Fly)
   ------------------------------------------------------
   💡 Idea:
   Traverse inorder, track predecessor as last node < key, successor as first node > key.

   🧩 Algorithm:
   1. Use a single in-order traversal.
   2. Keep updating predecessor when node->data < key.
   3. On first node->data > key, that's the successor.
   4. Can return immediately after finding both.

   ⏱ Time Complexity: O(N)
   📦 Space Complexity: O(H) [Call stack]
------------------------------------------------------ */
void inorderOnFly(Node* root, int key, Node*& pred, Node*& succ, bool& foundSucc) {
    if (!root || foundSucc) return;
    inorderOnFly(root->left, key, pred, succ, foundSucc);
    if (root->data < key) pred = root;
    if (!foundSucc && root->data > key) {
        succ = root;
        foundSucc = true;
        return;
    }
    inorderOnFly(root->right, key, pred, succ, foundSucc);
}

vector<Node*> findPreSucBetter(Node* root, int key) {
    Node* pred = nullptr, *succ = nullptr; bool foundSucc = false;
    inorderOnFly(root, key, pred, succ, foundSucc);
    return {pred, succ};
}

/* ------------------------------------------------------
   Approach 3: Optimal (BST Traversal without extra space)
   ------------------------------------------------------
   💡 Idea:
   Use BST properties to traverse:
   - For successor: move left if data > key, remembering possible successor.
   - For predecessor: move right if data < key, remembering possible predecessor.

   🧩 Algorithm:
   1. Initialize predecessor and successor to nullptr.
   2. To find successor, traverse from root:
      - If node->data > key, set successor = node, go left.
      - Else, go right.
   3. To find predecessor, traverse from root:
      - If node->data < key, set predecessor = node, go right.
      - Else, go left.

   ⏱ Time Complexity: O(H)
   📦 Space Complexity: O(1)
------------------------------------------------------ */
vector<Node*> findPreSucOptimal(Node* root, int key) {
    Node* successor = nullptr;
    Node* curr = root;
    while(curr) {
        if(curr->data > key) {
            successor = curr;
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    Node* predecessor = nullptr;
    curr = root;
    while(curr) {
        if(curr->data < key) {
            predecessor = curr;
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    return {predecessor, successor};
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
    // Build BST:      20
    //                /  \
    //               8    22
    //              / \
    //             4   12
    //                 / \
    //                10  14
    Node* root = nullptr;
    vector<int> values = {20, 8, 22, 4, 12, 10, 14};
    for (int v : values) root = insertBST(root, v);

    vector<int> testKeys = {10, 8, 22, 2};

    for (int key : testKeys) {
        auto res1 = findPreSucBrute(root, key);
        auto res2 = findPreSucBetter(root, key);
        auto res3 = findPreSucOptimal(root, key);

        cout << "\nKey: " << key << endl;
        cout << "Brute Force:      Predecessor = " << (res1[0] ? to_string(res1[0]->data) : "None")
             << ", Successor = " << (res1[1] ? to_string(res1[1]->data) : "None") << endl;
        cout << "Better:           Predecessor = " << (res2[0] ? to_string(res2[0]->data) : "None")
             << ", Successor = " << (res2[1] ? to_string(res2[1]->data) : "None") << endl;
        cout << "Optimal (BST prop): Predecessor = " << (res3[0] ? to_string(res3[0]->data) : "None")
             << ", Successor = " << (res3[1] ? to_string(res3[1]->data) : "None") << endl;
    }

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method         | Time Complexity | Space Complexity | Notes                      |
       |----------------|-----------------|------------------|----------------------------|
       | Brute Force    | O(N)            | O(N)             | Uses full inorder vector   |
       | Better         | O(N)            | O(H)             | On-the-fly traversal       |
       | Optimal        | O(H)            | O(1)             | Direct BST logic, best     |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
