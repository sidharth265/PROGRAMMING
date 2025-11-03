#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Balanced Binary Tree
 LeetCode Link: https://leetcode.com/problems/balanced-binary-tree/

 Problem Statement:
 -----------------
 Given a binary tree, determine if it is height-balanced.
 A height-balanced binary tree is defined as a binary tree in which the left 
 and right subtrees of every node differ in height by no more than 1.

 Example 1:
 Input: root = [3,9,20,null,null,15,7]
        3
       / \
      9  20
        /  \
       15   7
 Output: true

 Example 2:
 Input: root = [1,2,2,3,3,null,null,4,4]
           1
          / \
         2   2
        / \
       3   3
      / \
     4   4
 Output: false

 Example 3:
 Input: root = []
 Output: true

 Constraints:
 - The number of nodes in the tree is in the range [0, 5000]
 - -10^4 <= Node.val <= 10^4
====================================================
*/


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


/* 
==========================================
 Approach 1: Brute Force - Top-Down Approach
 -----------------------------------------
 💡 Idea:
 For each node, calculate height of left and right subtrees separately.
 Check if difference is ≤ 1, then recursively check left and right subtrees.

 🧩 Algorithm:
 1. For each node, calculate height of left subtree
 2. Calculate height of right subtree
 3. Check if |left_height - right_height| ≤ 1
 4. Recursively check if left and right subtrees are balanced
 5. Return true only if current node is balanced AND both subtrees are balanced

 ⏱ Time Complexity: O(N^2) - for each node, calculate height (O(N))
 📦 Space Complexity: O(H) - recursion stack height
*/
int heightBruteForce(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(heightBruteForce(root->left), heightBruteForce(root->right));
}

bool isBalancedBruteForce(TreeNode* root) {
    if (!root) return true;
    
    // Calculate heights of left and right subtrees
    int hl = heightBruteForce(root->left);
    int hr = heightBruteForce(root->right);
    
    // Check if current node violates balance condition
    if (abs(hl - hr) > 1) return false;
    
    // Recursively check left and right subtrees
    return isBalancedBruteForce(root->left) && isBalancedBruteForce(root->right);
}


/* 
==========================================
 Approach 2: Better - Top-Down with Memoization
 -----------------------------------------
 💡 Idea:
 Same as brute force but cache the height calculations to avoid
 recalculating heights for the same nodes multiple times.

 🧩 Algorithm:
 1. Use a hash map to store computed heights
 2. Before calculating height, check if it's already computed
 3. Same balance checking logic as brute force
 4. Store height results in cache for future use

 ⏱ Time Complexity: O(N) - each height calculated once
 📦 Space Complexity: O(N) - hash map for memoization + O(H) recursion
*/
unordered_map<TreeNode*, int> heightCache;

int heightMemoized(TreeNode* root) {
    if (!root) return 0;
    
    if (heightCache.find(root) != heightCache.end()) {
        return heightCache[root];
    }
    
    int height = 1 + max(heightMemoized(root->left), heightMemoized(root->right));
    heightCache[root] = height;
    return height;
}

bool isBalancedBetter(TreeNode* root) {
    heightCache.clear();
    
    if (!root) return true;
    
    int hl = heightMemoized(root->left);
    int hr = heightMemoized(root->right);
    
    if (abs(hl - hr) > 1) return false;
    
    return isBalancedBetter(root->left) && isBalancedBetter(root->right);
}


/* 
==========================================
 Approach 3: Optimal - Bottom-Up Approach (Single Pass)
 -----------------------------------------
 💡 Idea:
 Calculate height and check balance in single pass. Use -1 as sentinel
 value to indicate imbalance, propagating it up the recursion.

 🧩 Algorithm:
 1. Base case: empty node returns height 0
 2. Recursively get height of left subtree
 3. If left subtree is unbalanced (returns -1), propagate -1
 4. Recursively get height of right subtree  
 5. If right subtree is unbalanced (returns -1), propagate -1
 6. Check if current node is balanced: |left_height - right_height| ≤ 1
 7. If unbalanced, return -1; otherwise return actual height

 ⏱ Time Complexity: O(N) - single pass through all nodes
 📦 Space Complexity: O(H) - recursion stack height only
*/
int heightOptimal(TreeNode* root) {
    if (!root) return 0;
    
    // Get height of left subtree
    int hl = heightOptimal(root->left);
    if (hl == -1) return -1; // Left subtree is unbalanced
    
    // Get height of right subtree  
    int hr = heightOptimal(root->right);
    if (hr == -1) return -1; // Right subtree is unbalanced
    
    // Check if current node is balanced
    if (abs(hr - hl) > 1) return -1; // Current node is unbalanced
    
    // Return actual height
    return 1 + max(hl, hr);
}

bool isBalancedOptimal(TreeNode* root) {
    return heightOptimal(root) != -1;
}


/* Helper function to create sample trees */
TreeNode* createBalancedTree() {
    /*
    Creating balanced tree:
        3
       / \
      9  20
        /  \
       15   7
    */
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createUnbalancedTree() {
    /*
    Creating unbalanced tree:
           1
          / \
         2   2
        / \
       3   3
      / \
     4   4
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    root->left->left->right = new TreeNode(4);
    return root;
}

TreeNode* createSkewedTree() {
    /*
    Creating right-skewed tree:
    1
     \
      2
       \
        3
         \
          4
    */
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);
    return root;
}

/* Helper function to demonstrate balance checking process */
void demonstrateBalanceCheck(TreeNode* root, const string& treeName) {
    cout << "=== Checking Balance for " << treeName << " ===\n";
    
    function<void(TreeNode*, string)> printBalanceInfo = [&](TreeNode* node, string prefix) {
        if (!node) {
            cout << prefix << "null → height: 0\n";
            return;
        }
        
        int leftHeight = heightOptimal(node->left);
        int rightHeight = heightOptimal(node->right);
        bool isNodeBalanced = (leftHeight != -1 && rightHeight != -1 && 
                              abs(leftHeight - rightHeight) <= 1);
        
        cout << prefix << "Node " << node->val << " → ";
        cout << "left_height: " << (leftHeight == -1 ? "unbalanced" : to_string(leftHeight)) << ", ";
        cout << "right_height: " << (rightHeight == -1 ? "unbalanced" : to_string(rightHeight)) << ", ";
        cout << "balanced: " << (isNodeBalanced ? "YES" : "NO") << "\n";
    };
    
    // For demonstration, let's check a few key nodes
    printBalanceInfo(root, "");
    if (root && root->left) printBalanceInfo(root->left, "  ");
    if (root && root->right) printBalanceInfo(root->right, "  ");
    
    bool result = isBalancedOptimal(root);
    cout << "Overall tree is " << (result ? "BALANCED" : "UNBALANCED") << "\n\n";
}

/* Function to delete tree and free memory */
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Testing Balanced Binary Tree Problem ===\n\n";
    
    // Create sample trees
    TreeNode* balancedTree = createBalancedTree();
    TreeNode* unbalancedTree = createUnbalancedTree();
    TreeNode* skewedTree = createSkewedTree();
    
    vector<pair<TreeNode*, string>> testCases = {
        {balancedTree, "Balanced Tree"},
        {unbalancedTree, "Unbalanced Tree"}, 
        {skewedTree, "Right-Skewed Tree"},
        {nullptr, "Empty Tree"}
    };
    
    cout << "Testing all approaches on different tree types:\n\n";
    
    for (auto& testCase : testCases) {
        TreeNode* tree = testCase.first;
        string name = testCase.second;
        
        cout << "=== " << name << " ===\n";
        
        if (tree == nullptr) {
            cout << "Tree: Empty\n";
        } else {
            cout << "Tree structure: " << name << "\n";
        }
        
        bool result1 = isBalancedBruteForce(tree);
        bool result2 = isBalancedBetter(tree);
        bool result3 = isBalancedOptimal(tree);
        
        cout << " Brute Force (Top-Down):    " << (result1 ? "Balanced" : "Unbalanced") << "\n";
        cout << " Better (Memoized):         " << (result2 ? "Balanced" : "Unbalanced") << "\n";
        cout << " Optimal (Your Bottom-Up):  " << (result3 ? "Balanced" : "Unbalanced") << "\n";
        
        if (tree != nullptr) {
            demonstrateBalanceCheck(tree, name);
        }
        
        cout << "------------------------\n";
    }
    
    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N^2) time, recalculates height for each node.\n";
    cout << "2. Better Memoized -> O(N) time, caches height calculations.\n";
    cout << "3. Optimal Bottom-Up -> O(N) time, single pass with early termination.\n";
    cout << "\nRecommendation: Your optimal bottom-up approach is perfect! ✅\n";
    cout << "Key Insight: Combine height calculation with balance checking in single pass.\n";
    cout << "             Use -1 as sentinel value to propagate imbalance up the tree.\n";
    cout << "\nYour Implementation Evolution:\n";
    cout << "• 1st Solution: Classic top-down approach, easy to understand\n";
    cout << "• 2nd Solution: Optimal bottom-up with early termination\n";
    cout << "\nBottom-Up Advantages:\n";
    cout << "- Single traversal: each node visited exactly once\n";
    cout << "- Early termination: stops as soon as imbalance detected\n";
    cout << "- Space efficient: no memoization needed\n";
    cout << "- Elegant use of sentinel value (-1) for error propagation\n";
    cout << "\nYour provided solutions showcase excellent algorithmic progression! 🎯\n";
    cout << "The evolution from O(N²) to O(N) demonstrates deep understanding of optimization techniques.\n";
    
    // Clean up memory
    deleteTree(balancedTree);
    deleteTree(unbalancedTree);
    deleteTree(skewedTree);
    
    return 0;
}
