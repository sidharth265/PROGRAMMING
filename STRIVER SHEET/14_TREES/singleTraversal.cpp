#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: All Tree Traversals in One Go
 CodingNinjas Link: https://www.codingninjas.com/codestudio/problems/tree-traversal_981269

 Problem Statement:
 -----------------
 Given the root of a binary tree, return the inorder, preorder, and postorder 
 traversals of its nodes' values in a single pass.

 Return a 2D vector where:
 - result[0] = preorder traversal
 - result[1] = inorder traversal  
 - result[2] = postorder traversal

 Example:
 Input: Binary Tree
        1
       / \
      2   3
     / \
    4   5

 Output: [[1,2,4,5,3], [4,2,5,1,3], [4,5,2,3,1]]
 Explanation:
 - Preorder:  1 2 4 5 3
 - Inorder:   4 2 5 1 3
 - Postorder: 4 5 2 3 1

 Constraints:
 - The number of nodes in the tree is in the range [0, 100]
 - -100 <= Node.val <= 100
====================================================
*/


struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
};


/* 
==========================================
 Approach 1: Brute Force - Three Separate DFS
 -----------------------------------------
 💡 Idea:
 Perform three separate recursive traversals of the tree to get
 preorder, inorder, and postorder results.

 🧩 Algorithm:
 1. Perform preorder traversal: root → left → right
 2. Perform inorder traversal: left → root → right
 3. Perform postorder traversal: left → right → root
 4. Return all three results in a 2D vector

 ⏱ Time Complexity: O(3*N) = O(N) - visit each node 3 times
 📦 Space Complexity: O(H) - recursion stack height
*/
void preorderHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    result.push_back(root->data);
    preorderHelper(root->left, result);
    preorderHelper(root->right, result);
}

void inorderHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    inorderHelper(root->left, result);
    result.push_back(root->data);
    inorderHelper(root->right, result);
}

void postorderHelper(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    postorderHelper(root->left, result);
    postorderHelper(root->right, result);
    result.push_back(root->data);
}

vector<vector<int>> getTreeTraversalBruteForce(TreeNode* root) {
    vector<vector<int>> result(3);
    
    if (root == nullptr) return result;
    
    // Get all three traversals separately
    preorderHelper(root, result[0]);   // Preorder
    inorderHelper(root, result[1]);    // Inorder
    postorderHelper(root, result[2]);  // Postorder
    
    return result;
}


/* 
==========================================
 Approach 2: Better - Three Separate Iterative Traversals
 -----------------------------------------
 💡 Idea:
 Use three separate iterative traversals with stacks to avoid
 recursion overhead and have better control.

 🧩 Algorithm:
 1. Preorder: Use stack, process node, push right then left
 2. Inorder: Use stack, go left, process, go right
 3. Postorder: Use two stacks or reverse preorder technique
 4. Combine all results

 ⏱ Time Complexity: O(3*N) = O(N) - three separate passes
 📦 Space Complexity: O(H) - stack space for each traversal
*/
vector<vector<int>> getTreeTraversalBetter(TreeNode* root) {
    vector<vector<int>> result(3);
    
    if (root == nullptr) return result;
    
    // Preorder traversal
    stack<TreeNode*> st1;
    st1.push(root);
    while (!st1.empty()) {
        TreeNode* curr = st1.top();
        st1.pop();
        result[0].push_back(curr->data);
        
        if (curr->right) st1.push(curr->right);
        if (curr->left) st1.push(curr->left);
    }
    
    // Inorder traversal
    stack<TreeNode*> st2;
    TreeNode* curr = root;
    while (curr != nullptr || !st2.empty()) {
        while (curr != nullptr) {
            st2.push(curr);
            curr = curr->left;
        }
        curr = st2.top();
        st2.pop();
        result[1].push_back(curr->data);
        curr = curr->right;
    }
    
    // Postorder traversal (using two stacks)
    stack<TreeNode*> st3, st4;
    st3.push(root);
    while (!st3.empty()) {
        TreeNode* curr = st3.top();
        st3.pop();
        st4.push(curr);
        
        if (curr->left) st3.push(curr->left);
        if (curr->right) st3.push(curr->right);
    }
    while (!st4.empty()) {
        result[2].push_back(st4.top()->data);
        st4.pop();
    }
    
    return result;
}


/* 
==========================================
 Approach 3: Optimal - Single Pass with State Tracking
 -----------------------------------------
 💡 Idea:
 Use a single stack with state tracking. Each node goes through 3 states:
 0 = first visit (preorder), 1 = second visit (inorder), 2 = third visit (postorder)

 🧩 Algorithm:
 1. Use stack with pairs: (node, state)
 2. State 0: Add to preorder, increment state, push left child
 3. State 1: Add to inorder, increment state, push right child
 4. State 2: Add to postorder, pop from stack
 5. Continue until stack is empty

 ⏱ Time Complexity: O(N) - single pass through all nodes
 📦 Space Complexity: O(H) - one stack for state tracking
*/
vector<vector<int>> getTreeTraversalOptimal(TreeNode* root) {
    vector<vector<int>> result(3);
    
    if (root == nullptr) return result;
    
    stack<pair<TreeNode*, int>> st;
    st.push({root, 0});
    
    while (!st.empty()) {
        if (st.top().second == 0) {
            // First visit - Preorder
            result[0].push_back(st.top().first->data);
            st.top().second++;
            if (st.top().first->left) {
                st.push({st.top().first->left, 0});
            }
        }
        else if (st.top().second == 1) {
            // Second visit - Inorder
            result[1].push_back(st.top().first->data);
            st.top().second++;
            if (st.top().first->right) {
                st.push({st.top().first->right, 0});
            }
        }
        else {
            // Third visit - Postorder
            result[2].push_back(st.top().first->data);
            st.pop();
        }
    }
    
    return result;
}


/* Helper function to create sample trees */
TreeNode* createSampleTree1() {
    /*
    Creating tree:
        1
       / \
      2   3
     / \
    4   5
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
}

TreeNode* createSampleTree2() {
    /*
    Creating tree:
        10
       /  \
      20   30
     /    / \
    40   50  60
    */
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(20);
    root->right = new TreeNode(30);
    root->left->left = new TreeNode(40);
    root->right->left = new TreeNode(50);
    root->right->right = new TreeNode(60);
    return root;
}

/* Helper function to print traversal results */
void printTraversals(const vector<vector<int>>& result, const string& method) {
    cout << method << ":\n";
    vector<string> names = {"Preorder ", "Inorder  ", "Postorder"};
    
    for (int i = 0; i < 3; i++) {
        cout << "  " << names[i] << ": [";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    cout << "\n";
}

/* Helper function to demonstrate step-by-step optimal process */
void demonstrateOptimalProcess(TreeNode* root) {
    cout << "=== Step-by-Step Optimal Single Pass Demonstration ===\n";
    
    vector<vector<int>> result(3);
    stack<pair<TreeNode*, int>> st;
    st.push({root, 0});
    
    int step = 1;
    
    while (!st.empty()) {
        cout << "Step " << step++ << ": ";
        TreeNode* node = st.top().first;
        int state = st.top().second;
        
        cout << "Process node " << node->data << " (state " << state << ") → ";
        
        if (state == 0) {
            cout << "PREORDER: Add " << node->data << " to preorder\n";
            result[0].push_back(node->data);
            st.top().second++;
            if (node->left) {
                cout << "         Push left child " << node->left->data << " to stack\n";
                st.push({node->left, 0});
            } else {
                cout << "         No left child\n";
            }
        }
        else if (state == 1) {
            cout << "INORDER: Add " << node->data << " to inorder\n";
            result[1].push_back(node->data);
            st.top().second++;
            if (node->right) {
                cout << "         Push right child " << node->right->data << " to stack\n";
                st.push({node->right, 0});
            } else {
                cout << "         No right child\n";
            }
        }
        else {
            cout << "POSTORDER: Add " << node->data << " to postorder, pop from stack\n";
            result[2].push_back(node->data);
            st.pop();
        }
        
        cout << "         Stack size: " << st.size() << "\n\n";
    }
    
    cout << "Final Results:\n";
    printTraversals(result, "Single Pass Result");
}

/* Function to delete tree and free memory */
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Testing All Tree Traversals in Single Pass ===\n\n";
    
    // Create sample trees
    TreeNode* tree1 = createSampleTree1();
    TreeNode* tree2 = createSampleTree2();
    
    cout << "Test Case 1:\n";
    cout << "Tree Structure:\n";
    cout << "    1\n   / \\\n  2   3\n / \\\n4   5\n\n";
    
    auto result1_brute = getTreeTraversalBruteForce(tree1);
    auto result1_better = getTreeTraversalBetter(tree1);
    auto result1_optimal = getTreeTraversalOptimal(tree1);
    
    printTraversals(result1_brute, "Brute Force (3 Separate DFS)");
    printTraversals(result1_better, "Better (3 Separate Iterative)");
    printTraversals(result1_optimal, "Optimal (Your Single Pass)");
    
    cout << "Test Case 2:\n";
    cout << "Tree Structure:\n";
    cout << "     10\n    /  \\\n   20   30\n  /    / \\\n 40   50  60\n\n";
    
    auto result2_brute = getTreeTraversalBruteForce(tree2);
    auto result2_better = getTreeTraversalBetter(tree2);
    auto result2_optimal = getTreeTraversalOptimal(tree2);
    
    printTraversals(result2_brute, "Brute Force (3 Separate DFS)");
    printTraversals(result2_better, "Better (3 Separate Iterative)");
    printTraversals(result2_optimal, "Optimal (Your Single Pass)");
    
    // Demonstrate the step-by-step process for tree1
    demonstrateOptimalProcess(tree1);
    
    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(3*N) time, three separate recursive traversals.\n";
    cout << "2. Better -> O(3*N) time, three separate iterative traversals.\n";
    cout << "3. Optimal (Your) -> O(N) time, single pass with state tracking.\n";
    cout << "\nRecommendation: Your optimal single-pass approach is brilliant! ✅\n";
    cout << "Key Insight: Each node is visited exactly 3 times in DFS:\n";
    cout << "             1st visit → Preorder, 2nd visit → Inorder, 3rd visit → Postorder\n";
    cout << "\nYour Implementation Highlights:\n";
    cout << "- State tracking: (node, state) where state ∈ {0, 1, 2}\n";
    cout << "- State 0: First visit - add to preorder, push left child\n";
    cout << "- State 1: Second visit - add to inorder, push right child\n";
    cout << "- State 2: Third visit - add to postorder, pop from stack\n";
    cout << "\nThis is the most space and time efficient solution possible!\n";
    cout << "Your provided solution demonstrates excellent understanding of DFS mechanics! 🎯\n";
    
    // Clean up memory
    deleteTree(tree1);
    deleteTree(tree2);
    
    return 0;
}
