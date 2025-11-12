#include <iostream>
using namespace std;

/*
====================================================
 Problem Title: Binary Search Tree (BST) Implementation

 Algorithm:
 1. Define a TreeNode struct with integer value, and left/right pointers.
 2. To insert a value in BST:
    - If the tree is empty, create a new node.
    - If value < node's value, insert into left subtree.
    - If value > node's value, insert into right subtree.
    - (No insert for duplicate values.)
 3. To search a value:
    - If tree is empty, return false.
    - If value == node value, found.
    - If value < node value, search left.
    - If value > node value, search right.
 4. Traversals (inorder, preorder, postorder) in O(N).

 Time Complexity:
 - Insert/Search: O(H) (O(log N) if balanced, O(N) if skewed)
 - Traversal: O(N)
 Space Complexity: O(N) for the tree, O(H) for recursion stack
====================================================
*/

// BST Node definition
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Insert value into BST
TreeNode* insert(TreeNode* root, int val) {
    if(!root) return new TreeNode(val);
    if(val < root->val)
        root->left = insert(root->left, val);
    else if(val > root->val)
        root->right = insert(root->right, val);
    return root;
}

// Search for value in BST
bool search(TreeNode* root, int val) {
    if(!root) return false;
    if(root->val == val) return true;
    if(val < root->val) return search(root->left, val);
    return search(root->right, val);
}

// Inorder traversal
void inorder(TreeNode* root) {
    if(!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Binary Search Tree Implementation ===\n\n";
    TreeNode* root = nullptr;
    int arr[] = {10, 5, 15, 3, 7, 12, 18};
    for(int v : arr) root = insert(root, v);

    cout << "Inorder Traversal (sorted): ";
    inorder(root);
    cout << "\n";

    int target = 7;
    cout << "Search " << target << ": " << (search(root, target) ? "Found" : "Not found") << "\n";

    target = 20;
    cout << "Search " << target << ": " << (search(root, target) ? "Found" : "Not found") << "\n";

    // Deletion and other BST operations omitted for brevity

    return 0;
}

/*
✅ Approach Overview:
- Standard BST insert, search, and inorder traversal implemented.
- All operations are O(H), where H is tree height.
- Demonstrates correct BST ordering and queries.
*/
