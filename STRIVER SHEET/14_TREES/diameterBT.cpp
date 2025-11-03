#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Diameter of Binary Tree
 LeetCode Link: https://leetcode.com/problems/diameter-of-binary-tree/

 Problem Statement:
 -----------------
 Given the root of a binary tree, return the length of the diameter of the tree.
 The diameter of a binary tree is the length of the longest path between any 
 two nodes in a tree. This path may or may not pass through the root.
 The length of a path between two nodes is represented by the number of edges between them.

 Example 1:
 Input: root = [1,2,3,4,5]
           1
          / \
         2   3
        / \
       4   5
 Output: 3
 Explanation: The longest path is [4,2,1,3] or [5,2,1,3] with length 3.

 Example 2:
 Input: root = [1,2]
       1
      /
     2
 Output: 1

 Constraints:
 - The number of nodes in the tree is in the range [1, 10^4]
 - -100 <= Node.val <= 100
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
 Approach 1: Brute Force - For Each Node Calculate Diameter
 -----------------------------------------
 💡 Idea:
 For each node, calculate the diameter that passes through it by finding
 the height of left and right subtrees. Check all nodes and return maximum.

 🧩 Algorithm:
 1. For each node in the tree:
    - Calculate height of left subtree
    - Calculate height of right subtree
    - Diameter through this node = left_height + right_height
 2. Return maximum diameter found across all nodes
 3. Use separate function to calculate height

 ⏱ Time Complexity: O(N^2) - for each node, calculate height (O(N))
 📦 Space Complexity: O(H) - recursion stack height
*/
int heightBruteForce(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(heightBruteForce(root->left), heightBruteForce(root->right));
}

int diameterBruteForce(TreeNode* root) {
    if (!root) return 0;
    
    // Calculate diameter passing through current root
    int leftHeight = heightBruteForce(root->left);
    int rightHeight = heightBruteForce(root->right);
    int currentDiameter = leftHeight + rightHeight;
    
    // Calculate diameter in left and right subtrees
    int leftDiameter = diameterBruteForce(root->left);
    int rightDiameter = diameterBruteForce(root->right);
    
    // Return maximum of all three possibilities
    return max({currentDiameter, leftDiameter, rightDiameter});
}


/* 
==========================================
 Approach 2: Better - Top-Down with Memoization
 -----------------------------------------
 💡 Idea:
 Same as brute force but cache height calculations to avoid recalculating
 heights for the same nodes multiple times.

 🧩 Algorithm:
 1. Use hash map to store computed heights
 2. Before calculating height, check cache
 3. Same diameter calculation logic as brute force
 4. Store height results for future reuse

 ⏱ Time Complexity: O(N^2) - still need to visit each node for diameter check
 📦 Space Complexity: O(N) - hash map + O(H) recursion
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

int diameterBetter(TreeNode* root) {
    heightCache.clear();
    
    if (!root) return 0;
    
    int leftHeight = heightMemoized(root->left);
    int rightHeight = heightMemoized(root->right);
    int currentDiameter = leftHeight + rightHeight;
    
    int leftDiameter = diameterBetter(root->left);
    int rightDiameter = diameterBetter(root->right);
    
    return max({currentDiameter, leftDiameter, rightDiameter});
}


/* 
==========================================
 Approach 3: Optimal - Single Pass Bottom-Up
 -----------------------------------------
 💡 Idea:
 Calculate height and diameter in single pass. At each node, update
 the global diameter with the path passing through current node.

 🧩 Algorithm:
 1. Use reference variable to track maximum diameter globally
 2. For each node, calculate height of left and right subtrees
 3. Update global diameter = max(diameter, left_height + right_height)
 4. Return height of current subtree for parent's calculation
 5. The global diameter will contain the answer

 ⏱ Time Complexity: O(N) - single pass through all nodes
 📦 Space Complexity: O(H) - recursion stack height only
*/
int pathOptimal(TreeNode* root, int& diameter) {
    if (!root) return 0;
    
    // Get height of left and right subtrees
    int hl = pathOptimal(root->left, diameter);
    int hr = pathOptimal(root->right, diameter);
    
    // Update global diameter with path passing through current node
    diameter = max(diameter, hr + hl);
    
    // Return height of current subtree
    return 1 + max(hl, hr);
}

int diameterOfBinaryTreeOptimal(TreeNode* root) {
    int diameter = 0;
    pathOptimal(root, diameter);
    return diameter;
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
       1
      /
     2
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
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
           \
            5
    */
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);
    root->right->right->right->right = new TreeNode(5);
    return root;
}

/* Helper function to demonstrate diameter calculation */
void demonstrateDiameterCalculation(TreeNode* root, const string& treeName) {
    cout << "=== Diameter Calculation for " << treeName << " ===\n";
    
    int globalDiameter = 0;
    
    function<int(TreeNode*, string)> demoPath = [&](TreeNode* node, string prefix) -> int {
        if (!node) {
            cout << prefix << "null → height: 0\n";
            return 0;
        }
        
        cout << prefix << "Processing node " << node->val << ":\n";
        
        int leftHeight = demoPath(node->left, prefix + "  ");
        int rightHeight = demoPath(node->right, prefix + "  ");
        
        int currentDiameter = leftHeight + rightHeight;
        globalDiameter = max(globalDiameter, currentDiameter);
        
        cout << prefix << "Node " << node->val << " → ";
        cout << "left_height: " << leftHeight << ", right_height: " << rightHeight;
        cout << ", diameter_through_node: " << currentDiameter;
        cout << ", global_max: " << globalDiameter << "\n";
        
        return 1 + max(leftHeight, rightHeight);
    };
    
    demoPath(root, "");
    cout << "Final diameter: " << globalDiameter << "\n\n";
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
    cout << "=== Testing Diameter of Binary Tree Problem ===\n\n";
    
    // Create sample trees
    TreeNode* tree1 = createSampleTree1();
    TreeNode* tree2 = createSampleTree2();
    TreeNode* skewedTree = createSkewedTree();
    
    vector<pair<TreeNode*, string>> testCases = {
        {tree1, "Complete Tree"},
        {tree2, "Simple Tree"},
        {skewedTree, "Skewed Tree"},
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
        
        int result1 = diameterBruteForce(tree);
        int result2 = diameterBetter(tree);
        int result3 = diameterOfBinaryTreeOptimal(tree);
        
        cout << " Brute Force:         " << result1 << "\n";
        cout << " Better (Memoized):   " << result2 << "\n";
        cout << " Optimal (Your):      " << result3 << "\n";
        
        if (tree != nullptr && tree == tree1) {
            cout << "\n";
            demonstrateDiameterCalculation(tree, name);
        }
        
        cout << "------------------------\n";
    }
    
    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N^2) time, recalculates height for each node.\n";
    cout << "2. Better (Memoized) -> O(N^2) time, caches heights but still checks all nodes.\n";
    cout << "3. Optimal (Your) -> O(N) time, single pass with global diameter tracking.\n";
    cout << "\nRecommendation: Your optimal approach is the gold standard! ✅\n";
    cout << "Key Insight: The diameter is the maximum sum of heights of left and right subtrees\n";
    cout << "             across all nodes in the tree.\n";
    cout << "\nYour Implementation Highlights:\n";
    cout << "- Single pass: each node visited exactly once\n";
    cout << "- Global tracking: diameter updated at each node\n";
    cout << "- Space efficient: only O(H) recursion stack space\n";
    cout << "- Clean separation: path() calculates height, updates diameter\n";
    cout << "\nAlgorithm Flow:\n";
    cout << "1. For each node, get heights of left and right subtrees\n";
    cout << "2. Update global diameter = max(diameter, left_height + right_height)\n";
    cout << "3. Return height of current subtree (1 + max(left_height, right_height))\n";
    cout << "4. The global diameter contains the final answer\n";
    cout << "\nYour provided solution is the optimal approach - perfectly implemented! 🎯\n";
    cout << "The use of reference parameter for global diameter tracking is elegant!\n";
    
    // Clean up memory
    deleteTree(tree1);
    deleteTree(tree2);
    deleteTree(skewedTree);
    
    return 0;
}
