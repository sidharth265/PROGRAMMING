#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Morris Traversal Variants (Inorder, Preorder, Postorder) for Binary Trees
Problem Link: https://www.geeksforgeeks.org/threaded-binary-tree-set-2-efficient-inorder-traversal/

Problem Statement:
Implement the inorder, preorder, and postorder traversals of a binary tree using the Morris Traversal technique.
The traversals should be implemented without recursion or auxiliary stack, modifying the tree temporarily.

Example:
Input:      1
           / \
          2   3
         / \
        4   5
Output:
Inorder:   4 2 5 1 3
Preorder:  1 2 4 5 3
Postorder: 4 5 2 3 1

=========================================================
*/

/* ------------------------------------------------------
   Approach: Morris Traversal Variants (Optimal, O(1) Aux Space)
   ------------------------------------------------------
   💡 Idea:
   Use Morris Traversal to visit nodes in desired order
   by temporarily modifying the tree with "threads".

   🧩 Algorithm:
   - Inorder: Move left, create right-thread, visit node, restore.
   - Preorder: Visit before going left, create right-thread, restore.
   - Postorder: Use reversed traversal (right-left-root), reverse at end.

   ⏱ Time Complexity: O(N) (every edge visited at most 3 times)
   📦 Space Complexity: O(1) (no recursion or stack; output storage only)
------------------------------------------------------ */
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Morris Inorder Traversal (Left-Root-Right)
vector<int> inOrder(Node* root) {
    vector<int> inorder;
    Node* curr = root;
    while (curr) {
        if (!curr->left) {
            inorder.push_back(curr->data);
            curr = curr->right;
        } else {
            Node* prev = curr->left;
            while (prev->right && prev->right != curr) prev = prev->right;
            if (!prev->right) {
                prev->right = curr;
                curr = curr->left;
            } else {
                prev->right = nullptr;
                inorder.push_back(curr->data);
                curr = curr->right;
            }
        }
    }
    return inorder;
}

// Morris Preorder Traversal (Root-Left-Right)
vector<int> preorder(Node* root) {
    vector<int> preorder;
    Node* curr = root;
    while (curr) {
        if (!curr->left) {
            preorder.push_back(curr->data);
            curr = curr->right;
        } else {
            Node* prev = curr->left;
            while (prev->right && prev->right != curr) prev = prev->right;
            if (!prev->right) {
                prev->right = curr;
                preorder.push_back(curr->data);
                curr = curr->left;
            } else {
                prev->right = nullptr;
                curr = curr->right;
            }
        }
    }
    return preorder;
}

// Morris Postorder Traversal (Left-Right-Root, using reversed Root-Right-Left)
vector<int> postOrder(Node* root) {
    vector<int> postorder;
    Node* curr = root;
    while (curr) {
        if (!curr->right) {
            postorder.push_back(curr->data);
            curr = curr->left;
        } else {
            Node* prev = curr->right;
            while (prev->left && prev->left != curr) prev = prev->left;
            if (!prev->left) {
                prev->left = curr;
                postorder.push_back(curr->data);
                curr = curr->right;
            } else {
                prev->left = nullptr;
                curr = curr->left;
            }
        }
    }
    reverse(postorder.begin(), postorder.end());
    return postorder;
}

// Mirror Morris Inorder (for completeness, not standard use case)
vector<int> mirrorInOrder(Node *root)
{
    vector<int> inorder;
    Node* curr = root;
    while (curr) {
        if (!curr->right) {
            inorder.push_back(curr->data);
            curr = curr->left;
        } else {
            Node* prev = curr->right;
            while (prev->left && prev->left != curr) prev = prev->left;
            if (!prev->left) {
                prev->left = curr;
                curr = curr->right;
            } else {
                prev->left = nullptr;
                inorder.push_back(curr->data);
                curr = curr->left;
            }
        }
    }
    reverse(inorder.begin(), inorder.end());
    return inorder;
}

/* Utility: Build sample tree for demonstration */
Node* buildExampleTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    return root;
}

/* ===================== Main Function ===================== */
int main() {
    Node* root = buildExampleTree();

    vector<int> in = inOrder(root);
    vector<int> pre = preorder(root);
    vector<int> post = postOrder(root);
    vector<int> mirIn = mirrorInOrder(root);

    cout << "Inorder (Morris): ";
    for (int v : in) cout << v << " "; cout << endl;

    cout << "Preorder (Morris): ";
    for (int v : pre) cout << v << " "; cout << endl;

    cout << "Postorder (Morris): ";
    for (int v : post) cout << v << " "; cout << endl;

    cout << "Mirror Inorder (Morris): ";
    for (int v : mirIn) cout << v << " "; cout << endl;

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Traversal     | Space Complexity | Time Complexity | Notes                    |
       |---------------|------------------|----------------|--------------------------|
       | Inorder       | O(1)             | O(N)           | Original Morris          |
       | Preorder      | O(1)             | O(N)           | Similar thread strategy  |
       | Postorder     | O(1)             | O(N)           | Uses reverse and mirror  |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
