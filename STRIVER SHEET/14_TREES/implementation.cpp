#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Binary Tree Node Implementation and Operations
 GeeksForGeeks Link: https://www.geeksforgeeks.org/binary-tree-data-structure/

 Problem Statement:
 -----------------
 Implement a Binary Tree Node class and demonstrate various binary tree operations
 including traversals, construction, and common algorithms.

 Node Structure:
 - Each node contains integer data
 - Left and right child pointers
 - Constructor to initialize node

 Common Operations:
 - Tree traversals (Inorder, Preorder, Postorder, Level Order)
 - Tree construction from different inputs
 - Tree properties (height, size, etc.)

 Example Tree:
        1
       / \
      2   3
     / \
    4   5

 Inorder: 4 2 5 1 3
 Preorder: 1 2 4 5 3  
 Postorder: 4 5 2 3 1
 Level Order: 1 2 3 4 5

 Constraints:
 - Node values can be any integer
 - Tree can be empty (root = nullptr)
 - No duplicate handling specified (depends on use case)
====================================================
*/


class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};


/* 
==========================================
 Approach 1: Brute Force - Recursive Tree Operations
 -----------------------------------------
 💡 Idea:
 Implement basic tree operations using simple recursion without any
 optimization. Clear and straightforward recursive approach.

 🧩 Algorithm:
 For each operation, use direct recursion:
 - Traversals: visit nodes in specified order
 - Height: recursively find max depth
 - Size: recursively count all nodes
 - Search: recursively check left and right subtrees

 ⏱ Time Complexity: O(N) - visit each node once
 📦 Space Complexity: O(H) - recursion stack, H = height
*/
class BinaryTreeBruteForce {
public:
    // Tree Traversals
    void inorderTraversal(Node* root) {
        if (root == nullptr) return;
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
    
    void preorderTraversal(Node* root) {
        if (root == nullptr) return;
        cout << root->data << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
    
    void postorderTraversal(Node* root) {
        if (root == nullptr) return;
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->data << " ";
    }
    
    // Tree Properties
    int getHeight(Node* root) {
        if (root == nullptr) return 0;
        return 1 + max(getHeight(root->left), getHeight(root->right));
    }
    
    int getSize(Node* root) {
        if (root == nullptr) return 0;
        return 1 + getSize(root->left) + getSize(root->right);
    }
    
    // Search Operation
    bool search(Node* root, int target) {
        if (root == nullptr) return false;
        if (root->data == target) return true;
        return search(root->left, target) || search(root->right, target);
    }
};


/* 
==========================================
 Approach 2: Better - Iterative with Stack/Queue
 -----------------------------------------
 💡 Idea:
 Use iterative approaches with explicit stack/queue data structures
 to avoid recursion overhead and have better control over traversal.

 🧩 Algorithm:
 - Inorder: Use stack, go left, process, go right
 - Preorder: Use stack, process, push right, push left
 - Postorder: Use two stacks or modified approach
 - Level Order: Use queue for BFS traversal

 ⏱ Time Complexity: O(N) - visit each node once
 📦 Space Complexity: O(W) - W is maximum width of tree
*/
class BinaryTreeBetter {
public:
    void inorderIterative(Node* root) {
        stack<Node*> st;
        Node* curr = root;
        
        while (curr != nullptr || !st.empty()) {
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top();
            st.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }
    
    void preorderIterative(Node* root) {
        if (root == nullptr) return;
        stack<Node*> st;
        st.push(root);
        
        while (!st.empty()) {
            Node* curr = st.top();
            st.pop();
            cout << curr->data << " ";
            
            if (curr->right) st.push(curr->right);
            if (curr->left) st.push(curr->left);
        }
    }

    void postorderIterative(Node* root) {
        if (root == nullptr) return;
        stack<Node*> st1, st2;
        st1.push(root);
        
        while (!st1.empty()) {
            Node* curr = st1.top();
            st1.pop();
            st2.push(curr);
            if (curr->left) st1.push(curr->left);
            if (curr->right) st1.push(curr->right);
        }
        
        while (!st2.empty()) {
            cout << st2.top()->data << " ";
            st2.pop();
        }
    }

    void postorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode* curr = root;
        while(curr || !st.empty()) {
            if(curr) {
                st.push(curr);
                curr = curr->left;
            }
            else {
                TreeNode* temp = st.top()->right;
                if(!temp) {
                    do{
                        temp = st.top();
                        st.pop();
                        cout << temp->val << " ";
                    }
                    while(!st.empty() && temp == st.top()->right);
                }
                else curr = temp;
            }
        }
    }
    
    void levelOrderTraversal(Node* root) {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            cout << curr->data << " ";
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    // Level-wise printing
    void levelOrderLevelWise(Node* root) {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node* curr = q.front();
                q.pop();
                cout << curr->data << " ";
                
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            cout << "\n"; // New line for each level
        }
    }
};


/* 
==========================================
 Approach 3: Optimal - Advanced Tree Operations
 -----------------------------------------
 💡 Idea:
 Implement advanced tree operations and optimizations including
 tree construction, validation, and complex algorithms.

 🧩 Algorithm:
 - Build tree from different traversal combinations
 - Tree validation and property checking
 - Advanced algorithms like diameter, LCA, etc.
 - Memory-efficient operations

 ⏱ Time Complexity: Varies by operation (O(N) to O(N^2))
 📦 Space Complexity: O(H) for most operations
*/
class BinaryTreeOptimal {
private:
    int index; // Helper for tree construction
    
public:
    // Build tree from preorder and inorder
    Node* buildTree(vector<int>& preorder, vector<int>& inorder, int start, int end) {
        if (start > end) return nullptr;
        
        Node* root = new Node(preorder[index++]);
        
        if (start == end) return root;
        
        int rootIndex = find(inorder.begin() + start, inorder.begin() + end + 1, root->data) 
                        - inorder.begin();
        
        root->left = buildTree(preorder, inorder, start, rootIndex - 1);
        root->right = buildTree(preorder, inorder, rootIndex + 1, end);
        
        return root;
    }
    
    Node* buildTreeFromTraversals(vector<int>& preorder, vector<int>& inorder) {
        index = 0;
        return buildTree(preorder, inorder, 0, inorder.size() - 1);
    }
    
    // Check if tree is balanced
    int checkBalanced(Node* root) {
        if (root == nullptr) return 0;
        
        int leftHeight = checkBalanced(root->left);
        if (leftHeight == -1) return -1;
        
        int rightHeight = checkBalanced(root->right);
        if (rightHeight == -1) return -1;
        
        if (abs(leftHeight - rightHeight) > 1) return -1;
        
        return 1 + max(leftHeight, rightHeight);
    }
    
    bool isBalanced(Node* root) {
        return checkBalanced(root) != -1;
    }
    
    // Find diameter of tree
    int diameterHelper(Node* root, int& diameter) {
        if (root == nullptr) return 0;
        
        int leftHeight = diameterHelper(root->left, diameter);
        int rightHeight = diameterHelper(root->right, diameter);
        
        diameter = max(diameter, leftHeight + rightHeight);
        
        return 1 + max(leftHeight, rightHeight);
    }
    
    int getDiameter(Node* root) {
        int diameter = 0;
        diameterHelper(root, diameter);
        return diameter;
    }
    
    // Lowest Common Ancestor
    Node* findLCA(Node* root, int n1, int n2) {
        if (root == nullptr) return nullptr;
        
        if (root->data == n1 || root->data == n2) return root;
        
        Node* leftLCA = findLCA(root->left, n1, n2);
        Node* rightLCA = findLCA(root->right, n1, n2);
        
        if (leftLCA && rightLCA) return root;
        
        return (leftLCA != nullptr) ? leftLCA : rightLCA;
    }
};


/* Helper function to create a sample tree */
Node* createSampleTree() {
    /*
    Creating tree:
        1
       / \
      2   3
     / \
    4   5
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    return root;
}

/* Helper function to create another sample tree */
Node* createSampleTree2() {
    /*
    Creating tree:
        10
       /  \
      20   30
     / \   /
    40 50 60
    */
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);
    root->right->left = new Node(60);
    return root;
}

/* Function to delete tree and free memory */
void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Binary Tree Operations Demonstration ===\n\n";
    
    // Create sample trees
    Node* tree1 = createSampleTree();
    Node* tree2 = createSampleTree2();
    
    BinaryTreeBruteForce btBrute;
    BinaryTreeBetter btBetter;
    BinaryTreeOptimal btOptimal;
    
    cout << "Tree 1 Structure:\n";
    cout << "    1\n   / \\\n  2   3\n / \\\n4   5\n\n";
    
    cout << "=== Brute Force Recursive Traversals ===\n";
    cout << "Inorder:   ";
    btBrute.inorderTraversal(tree1);
    cout << "\nPreorder:  ";
    btBrute.preorderTraversal(tree1);
    cout << "\nPostorder: ";
    btBrute.postorderTraversal(tree1);
    cout << "\n\n";
    
    cout << "Tree Properties:\n";
    cout << "Height: " << btBrute.getHeight(tree1) << "\n";
    cout << "Size: " << btBrute.getSize(tree1) << "\n";
    cout << "Search for 4: " << (btBrute.search(tree1, 4) ? "Found" : "Not Found") << "\n";
    cout << "Search for 7: " << (btBrute.search(tree1, 7) ? "Found" : "Not Found") << "\n\n";
    
    cout << "=== Better Iterative Traversals ===\n";
    cout << "Inorder (Iterative):   ";
    btBetter.inorderIterative(tree1);
    cout << "\nPreorder (Iterative):  ";
    btBetter.preorderIterative(tree1);
    cout << "\nLevel Order:           ";
    btBetter.levelOrderTraversal(tree1);
    cout << "\n\nLevel Order (Level-wise):\n";
    btBetter.levelOrderLevelWise(tree1);
    cout << "\n";
    
    cout << "=== Advanced Operations (Tree 2) ===\n";
    cout << "Tree 2 Structure:\n";
    cout << "     10\n    /  \\\n   20   30\n  / \\   /\n 40 50 60\n\n";
    
    cout << "Is Tree 2 Balanced: " << (btOptimal.isBalanced(tree2) ? "Yes" : "No") << "\n";
    cout << "Diameter of Tree 2: " << btOptimal.getDiameter(tree2) << "\n";
    
    Node* lca = btOptimal.findLCA(tree2, 40, 50);
    cout << "LCA of 40 and 50: " << (lca ? to_string(lca->data) : "nullptr") << "\n\n";
    
    cout << "=== Tree Construction from Traversals ===\n";
    vector<int> preorder = {1, 2, 4, 5, 3};
    vector<int> inorder = {4, 2, 5, 1, 3};
    
    cout << "Preorder: [";
    for (int i = 0; i < preorder.size(); i++) {
        cout << preorder[i];
        if (i < preorder.size() - 1) cout << ", ";
    }
    cout << "]\n";
    
    cout << "Inorder:  [";
    for (int i = 0; i < inorder.size(); i++) {
        cout << inorder[i];
        if (i < inorder.size() - 1) cout << ", ";
    }
    cout << "]\n";
    
    Node* constructedTree = btOptimal.buildTreeFromTraversals(preorder, inorder);
    cout << "Constructed tree level order: ";
    btBetter.levelOrderTraversal(constructedTree);
    cout << "\n\n";
    
    /* ✅ Approach Overview */
    cout << "✅ Binary Tree Implementation Overview:\n";
    cout << "1. Brute Force -> Simple recursive operations, easy to understand.\n";
    cout << "2. Better -> Iterative approaches using stack/queue, more control.\n";
    cout << "3. Optimal -> Advanced operations like tree construction and validation.\n";
    cout << "\nKey Operations Implemented:\n";
    cout << "• Tree Traversals (Recursive & Iterative)\n";
    cout << "• Tree Properties (Height, Size, Balance Check)\n";
    cout << "• Tree Construction from Traversals\n";
    cout << "• Advanced Algorithms (Diameter, LCA)\n";
    cout << "\nYour Node class provides the perfect foundation for implementing\n";
    cout << "all binary tree operations efficiently! The clean structure with\n";
    cout << "data, left, and right pointers is the standard approach. 🎯\n";
    
    // Clean up memory
    deleteTree(tree1);
    deleteTree(tree2);
    deleteTree(constructedTree);
    
    return 0;
}
