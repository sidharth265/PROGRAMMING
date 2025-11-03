#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Binary Tree Zigzag Level Order Traversal
 LeetCode Link: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

 Problem Statement:
 -----------------
 Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. 
 (i.e., from left to right, then right to left for the next level and alternate between).

 Example 1:
 Input: root = [3,9,20,null,null,15,7]
        3
       / \
      9  20
        /  \
       15   7
 Output: [[3],[20,9],[15,7]]
 Explanation: 
 - Level 0: [3] (left to right)
 - Level 1: [20,9] (right to left) 
 - Level 2: [15,7] (left to right)

 Example 2:
 Input: root = [1,2,3,4,null,null,5]
           1
          / \
         2   3
        /     \
       4       5
 Output: [[1],[3,2],[4,5]]

 Example 3:
 Input: root = [1]
 Output: [[1]]

 Constraints:
 - The number of nodes in the tree is in the range [0, 2000]
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
 Approach 1: Brute Force - Level Order + Reverse Alternate Levels
 -----------------------------------------
 💡 Idea:
 Perform normal level order traversal, collect all nodes at each level,
 then reverse alternate levels after traversal is complete.

 🧩 Algorithm:
 1. Do standard BFS level order traversal
 2. Store each level in separate vectors
 3. After traversal, reverse levels at odd indices (1, 3, 5...)
 4. Return the modified result

 ⏱ Time Complexity: O(N) - visit each node once + O(N) for reversing
 📦 Space Complexity: O(W) - W is maximum width of tree (queue space)
*/
vector<vector<int>> zigzagLevelOrderBruteForce(TreeNode* root) {
    if (!root) return {};
    
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);
    
    // Standard level order traversal
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            currentLevel.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(currentLevel);
    }
    
    // Reverse alternate levels (levels 1, 3, 5...)
    for (int i = 1; i < result.size(); i += 2) {
        reverse(result[i].begin(), result[i].end());
    }
    
    return result;
}


/* 
==========================================
 Approach 2: Better - Two Stacks for Alternating Direction
 -----------------------------------------
 💡 Idea:
 Use two stacks to alternate between left-to-right and right-to-left
 traversal. One stack for current level, another for next level.

 🧩 Algorithm:
 1. Use two stacks: currentLevel and nextLevel
 2. Use boolean flag to track direction
 3. Left-to-right: push left child first, then right child
 4. Right-to-left: push right child first, then left child
 5. Swap stacks after processing each level

 ⏱ Time Complexity: O(N) - visit each node exactly once
 📦 Space Complexity: O(W) - two stacks store at most W nodes
*/
vector<vector<int>> zigzagLevelOrderBetter(TreeNode* root) {
    if (!root) return {};
    
    vector<vector<int>> result;
    stack<TreeNode*> currentLevel;
    stack<TreeNode*> nextLevel;
    
    currentLevel.push(root);
    bool leftToRight = true;
    
    while (!currentLevel.empty()) {
        vector<int> levelValues;
        
        while (!currentLevel.empty()) {
            TreeNode* node = currentLevel.top();
            currentLevel.pop();
            levelValues.push_back(node->val);
            
            if (leftToRight) {
                // For left-to-right, push left first then right
                if (node->left) nextLevel.push(node->left);
                if (node->right) nextLevel.push(node->right);
            } else {
                // For right-to-left, push right first then left
                if (node->right) nextLevel.push(node->right);
                if (node->left) nextLevel.push(node->left);
            }
        }
        
        result.push_back(levelValues);
        swap(currentLevel, nextLevel);
        leftToRight = !leftToRight;
    }
    
    return result;
}


/* 
==========================================
 Approach 3: Optimal - Single Queue with Smart Indexing
 -----------------------------------------
 💡 Idea:
 Use single queue for BFS but pre-allocate level array and use smart indexing
 to place elements in correct positions based on traversal direction.

 🧩 Algorithm:
 1. Use standard BFS with queue
 2. For each level, pre-allocate vector of exact size
 3. Use flag to determine insertion direction:
    - Left-to-right: insert at index i
    - Right-to-left: insert at index (n-1-i)
 4. Toggle flag after each level

 ⏱ Time Complexity: O(N) - single pass through all nodes
 📦 Space Complexity: O(W) - queue space for maximum tree width
*/
vector<vector<int>> zigzagLevelOrderOptimal(TreeNode* root) {
    if (!root) return {};
    
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);
    bool flag = true; // true = left-to-right, false = right-to-left
    
    while (!q.empty()) {
        int n = q.size();
        vector<int> level(n); // Pre-allocate with exact size
        
        for (int i = 0; i < n; i++) {
            TreeNode* temp = q.front();
            q.pop();
            
            // Add children to queue for next level
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
            
            // Smart indexing based on direction
            if (flag) {
                level[i] = temp->val;        // Left-to-right: normal index
            } else {
                level[n-1-i] = temp->val;    // Right-to-left: reverse index
            }
        }
        
        result.push_back(level);
        flag = !flag; // Toggle direction for next level
    }
    
    return result;
}


/* Helper function to create sample trees */
TreeNode* createSampleTree1() {
    /*
    Creating tree:
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

TreeNode* createSampleTree2() {
    /*
    Creating tree:
           1
          / \
         2   3
        /     \
       4       5
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    return root;
}

TreeNode* createCompleteTree() {
    /*
    Creating complete tree:
           1
          / \
         2   3
        / \ / \
       4 5 6  7
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    return root;
}

/* Helper function to print results */
void printResult(const vector<vector<int>>& result, const string& method) {
    cout << method << ": [";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]\n";
}

/* Helper function to demonstrate zigzag process */
void demonstrateZigzagProcess(TreeNode* root, const string& treeName) {
    cout << "=== Zigzag Process for " << treeName << " ===\n";
    
    if (!root) {
        cout << "Empty tree\n\n";
        return;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    int level = 0;
    
    while (!q.empty()) {
        int n = q.size();
        cout << "Level " << level << " (" << (leftToRight ? "left-to-right" : "right-to-left") << "): ";
        
        vector<int> levelNodes(n);
        vector<TreeNode*> currentNodes;
        
        // Collect all nodes at current level
        for (int i = 0; i < n; i++) {
            TreeNode* temp = q.front();
            q.pop();
            currentNodes.push_back(temp);
            
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
        
        // Place nodes in correct positions
        for (int i = 0; i < n; i++) {
            if (leftToRight) {
                levelNodes[i] = currentNodes[i]->val;
            } else {
                levelNodes[n-1-i] = currentNodes[i]->val;
            }
        }
        
        cout << "[";
        for (int i = 0; i < n; i++) {
            cout << levelNodes[i];
            if (i < n - 1) cout << ",";
        }
        cout << "]\n";
        
        leftToRight = !leftToRight;
        level++;
    }
    cout << "\n";
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
    cout << "=== Testing Binary Tree Zigzag Level Order Traversal ===\n\n";
    
    // Create sample trees
    TreeNode* tree1 = createSampleTree1();
    TreeNode* tree2 = createSampleTree2();
    TreeNode* completeTree = createCompleteTree();
    
    vector<pair<TreeNode*, string>> testCases = {
        {tree1, "Sample Tree 1"},
        {tree2, "Sample Tree 2"},
        {completeTree, "Complete Binary Tree"},
        {nullptr, "Empty Tree"}
    };
    
    for (auto& testCase : testCases) {
        TreeNode* tree = testCase.first;
        string name = testCase.second;
        
        cout << "=== " << name << " ===\n";
        
        if (tree) {
            auto result1 = zigzagLevelOrderBruteForce(tree);
            auto result2 = zigzagLevelOrderBetter(tree);
            auto result3 = zigzagLevelOrderOptimal(tree);
            
            printResult(result1, " Brute Force");
            printResult(result2, " Better (Two Stacks)");
            printResult(result3, " Optimal (Your)");
            
            // Demonstrate process for first tree
            if (name == "Sample Tree 1") {
                cout << "\n";
                demonstrateZigzagProcess(tree, name);
            }
        } else {
            cout << "Empty tree: []\n";
        }
        
        cout << "------------------------\n";
    }
    
    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N) time, does level order then reverses alternate levels.\n";
    cout << "2. Better (Two Stacks) -> O(N) time, uses alternating stacks for direction control.\n";
    cout << "3. Optimal (Your) -> O(N) time, single queue with smart indexing.\n";
    cout << "\nRecommendation: Your optimal approach is brilliantly efficient! ✅\n";
    cout << "Key Insight: Pre-allocate level vector and use smart indexing to place elements\n";
    cout << "             in correct positions based on traversal direction.\n";
    cout << "\nYour Implementation Highlights:\n";
    cout << "- Single data structure: only one queue needed\n";
    cout << "- Smart indexing: flag ? level[i] : level[n-1-i]\n";
    cout << "- Pre-allocation: vector<int> level(n) avoids resizing\n";
    cout << "- Clean direction toggle: flag = !flag\n";
    cout << "- Optimal space usage: O(W) where W is tree width\n";
    cout << "\nAlgorithm Flow:\n";
    cout << "- Even levels (0,2,4...): left-to-right → normal indexing [0,1,2...]\n";
    cout << "- Odd levels (1,3,5...): right-to-left → reverse indexing [...,2,1,0]\n";
    cout << "\nYour provided solution is the most elegant approach for this problem! 🎯\n";
    cout << "The smart indexing technique eliminates the need for reversing or multiple stacks!\n";
    
    // Clean up memory
    deleteTree(tree1);
    deleteTree(tree2);
    deleteTree(completeTree);
    
    return 0;
}
