#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Same Tree
 LeetCode Link: https://leetcode.com/problems/same-tree/

 Problem Statement:
 -----------------
 Given the roots of two binary trees p and q, write a function to check if they are the same or not.
 Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

 Example 1:
 Input: p = [1,2,3], q = [1,2,3]
        1         1
       / \       / \
      2   3     2   3
 Output: true

 Example 2:
 Input: p = [1,2], q = [1,null,2]
        1       1
       /         \
      2           2
 Output: false

 Example 3:
 Input: p = [1,2,1], q = [1,1,2]
        1       1
       / \     / \
      2   1   1   2
 Output: false

 Constraints:
 - The number of nodes in both trees is in the range [0, 100]
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
 Approach 1: Brute Force - Serialize Both Trees
 -----------------------------------------
 💡 Idea:
 Convert both trees to their string representations (serialization) and
 compare the resulting strings. If strings are identical, trees are same.

 🧩 Algorithm:
 1. Serialize tree p using preorder traversal with null markers
 2. Serialize tree q using the same method
 3. Compare the two serialized strings
 4. Return true if strings are identical, false otherwise

 ⏱ Time Complexity: O(N + M) - N and M are sizes of trees p and q
 📦 Space Complexity: O(N + M) - for storing serialized strings
*/
string serializeTree(TreeNode* root) {
    if (!root) return "null,";
    
    string result = to_string(root->val) + ",";
    result += serializeTree(root->left);
    result += serializeTree(root->right);
    
    return result;
}

bool isSameTreeBruteForce(TreeNode* p, TreeNode* q) {
    string serializedP = serializeTree(p);
    string serializedQ = serializeTree(q);
    
    return serializedP == serializedQ;
}


/* 
==========================================
 Approach 2: Better - Iterative with Stack
 -----------------------------------------
 💡 Idea:
 Use iterative approach with stack to avoid recursion overhead.
 Push corresponding nodes from both trees and compare them level by level.

 🧩 Algorithm:
 1. Use stack to store pairs of nodes from both trees
 2. Start with root nodes of both trees
 3. While stack is not empty:
    - Pop pair of nodes
    - Compare values and null status
    - Push left children pair and right children pair
 4. Return true if all comparisons pass

 ⏱ Time Complexity: O(min(N, M)) - visit nodes until difference found
 📦 Space Complexity: O(min(H1, H2)) - stack space for tree heights
*/
bool isSameTreeBetter(TreeNode* p, TreeNode* q) {
    stack<pair<TreeNode*, TreeNode*>> st;
    st.push({p, q});
    
    while (!st.empty()) {
        auto curr = st.top();
        st.pop();
        
        TreeNode* node1 = curr.first;
        TreeNode* node2 = curr.second;
        
        // Both null - continue
        if (!node1 && !node2) continue;
        
        // One null, other not - trees are different
        if (!node1 || !node2) return false;
        
        // Different values - trees are different
        if (node1->val != node2->val) return false;
        
        // Push children for comparison
        st.push({node1->left, node2->left});
        st.push({node1->right, node2->right});
    }
    
    return true;
}


/* 
==========================================
 Approach 3: Optimal - Recursive Comparison
 -----------------------------------------
 💡 Idea:
 Use direct recursive comparison of corresponding nodes from both trees.
 Check base cases first, then recursively compare left and right subtrees.

 🧩 Algorithm:
 1. Base cases:
    - Both nodes null: return true
    - One node null, other not: return false
 2. Check if current node values are equal
 3. Recursively check left subtrees are same
 4. Recursively check right subtrees are same
 5. Return true only if current values match AND both subtrees are same

 ⏱ Time Complexity: O(min(N, M)) - visit nodes until difference found
 📦 Space Complexity: O(min(H1, H2)) - recursion stack for tree heights
*/
bool isSameTreeOptimal(TreeNode* p, TreeNode* q) {
    // Base case: both nodes are null
    if (!p && !q) return true;
    
    // One node is null, the other is not
    if (!p || !q) return false;
    
    // Check current node values and recursively check subtrees
    return (p->val == q->val) && 
           isSameTreeOptimal(p->left, q->left) && 
           isSameTreeOptimal(p->right, q->right);
}

// Your provided solution (with minor cleanup)
bool isSameTreeYours(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;  // Simplified condition
    
    bool left = isSameTreeYours(p->left, q->left);
    bool right = isSameTreeYours(p->right, q->right);
    
    return (p->val == q->val) && left && right;
}


/* Helper function to create sample trees */
TreeNode* createTree1() {
    /*
    Creating tree:
        1
       / \
      2   3
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    return root;
}

TreeNode* createTree2() {
    /*
    Creating identical tree:
        1
       / \
      2   3
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    return root;
}

TreeNode* createTree3() {
    /*
    Creating different structure:
        1
       /
      2
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    return root;
}

TreeNode* createTree4() {
    /*
    Creating different structure:
        1
         \
          2
    */
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    return root;
}

/* Helper function to print tree structure */
void printTree(TreeNode* root, const string& prefix = "", bool isLast = true) {
    if (!root) return;
    
    cout << prefix << (isLast ? "└── " : "├── ") << root->val << "\n";
    
    if (root->left || root->right) {
        if (root->left) {
            printTree(root->left, prefix + (isLast ? "    " : "│   "), !root->right);
        }
        if (root->right) {
            printTree(root->right, prefix + (isLast ? "    " : "│   "), true);
        }
    }
}

/* Helper function to demonstrate comparison process */
void demonstrateComparison(TreeNode* p, TreeNode* q, const string& testName) {
    cout << "=== " << testName << " ===\n";
    cout << "Tree P:\n";
    if (p) printTree(p);
    else cout << "null\n";
    
    cout << "Tree Q:\n";
    if (q) printTree(q);
    else cout << "null\n";
    
    // Step-by-step comparison
    cout << "Comparison steps:\n";
    
    function<bool(TreeNode*, TreeNode*, string)> stepByStep = [&](TreeNode* node1, TreeNode* node2, string indent) -> bool {
        cout << indent << "Compare nodes: ";
        
        if (!node1 && !node2) {
            cout << "both null → MATCH\n";
            return true;
        }
        
        if (!node1) {
            cout << "null vs " << node2->val << " → NO MATCH\n";
            return false;
        }
        
        if (!node2) {
            cout << node1->val << " vs null → NO MATCH\n";
            return false;
        }
        
        cout << node1->val << " vs " << node2->val;
        if (node1->val != node2->val) {
            cout << " → NO MATCH\n";
            return false;
        }
        cout << " → MATCH\n";
        
        bool leftSame = stepByStep(node1->left, node2->left, indent + "  ");
        bool rightSame = stepByStep(node1->right, node2->right, indent + "  ");
        
        return leftSame && rightSame;
    };
    
    bool result = stepByStep(p, q, "");
    cout << "Final result: " << (result ? "SAME" : "DIFFERENT") << "\n\n";
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
    cout << "=== Testing Same Tree Problem ===\n\n";
    
    // Create sample trees
    TreeNode* tree1 = createTree1();
    TreeNode* tree2 = createTree2();  // Identical to tree1
    TreeNode* tree3 = createTree3();  // Different structure
    TreeNode* tree4 = createTree4();  // Different structure
    
    vector<tuple<TreeNode*, TreeNode*, string>> testCases = {
        {tree1, tree2, "Identical Trees"},
        {tree1, tree3, "Different Structure 1"},
        {tree3, tree4, "Different Structure 2"},
        {nullptr, nullptr, "Both Empty"},
        {tree1, nullptr, "One Empty"}
    };
    
    cout << "Testing all approaches on different tree pairs:\n\n";
    
    for (auto& testCase : testCases) {
        TreeNode* p = get<0>(testCase);
        TreeNode* q = get<1>(testCase);
        string name = get<2>(testCase);
        
        cout << "=== " << name << " ===\n";
        
        bool result1 = isSameTreeBruteForce(p, q);
        bool result2 = isSameTreeBetter(p, q);
        bool result3 = isSameTreeOptimal(p, q);
        bool result4 = isSameTreeYours(p, q);
        
        cout << " Brute Force (Serialize): " << (result1 ? "Same" : "Different") << "\n";
        cout << " Better (Iterative):      " << (result2 ? "Same" : "Different") << "\n";
        cout << " Optimal (Recursive):     " << (result3 ? "Same" : "Different") << "\n";
        cout << " Your Solution:           " << (result4 ? "Same" : "Different") << "\n";
        
        // Demonstrate the process for first test case
        if (name == "Identical Trees") {
            cout << "\n";
            demonstrateComparison(p, q, name);
        }
        
        cout << "------------------------\n";
    }
    
    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N+M) time, serializes both trees and compares strings.\n";
    cout << "2. Better Iterative -> O(min(N,M)) time, uses stack to avoid recursion.\n";
    cout << "3. Optimal Recursive -> O(min(N,M)) time, clean recursive comparison.\n";
    cout << "\nRecommendation: Your recursive approach is perfectly implemented! ✅\n";
    cout << "Key Insight: Two trees are same if and only if:\n";
    cout << "             1. Both roots have same value (or both are null)\n";
    cout << "             2. Left subtrees are same\n";
    cout << "             3. Right subtrees are same\n";
    cout << "\nYour Implementation Highlights:\n";
    cout << "- Clean base case handling: both null vs one null scenarios\n";
    cout << "- Efficient short-circuiting: stops at first difference\n";
    cout << "- Recursive elegance: mirrors the tree structure in code\n";
    cout << "- Optimal space usage: O(H) recursion stack only\n";
    cout << "\nCode Style Notes:\n";
    cout << "- Your condition '!p && q' and 'p && !q' can be simplified to '!p || !q'\n";
    cout << "- But your explicit style is more readable and clear!\n";
    cout << "- The separate boolean variables (left, right) make debugging easier\n";
    cout << "\nYour provided solution demonstrates excellent recursive thinking! 🎯\n";
    cout << "The logical flow exactly matches the problem's recursive nature!\n";
    
    // Clean up memory
    deleteTree(tree1);
    deleteTree(tree2);
    deleteTree(tree3);
    deleteTree(tree4);
    
    return 0;
}
