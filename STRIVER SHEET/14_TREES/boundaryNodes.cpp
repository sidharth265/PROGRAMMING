#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Boundary Traversal of Binary Tree
 GeeksForGeeks Link: https://www.geeksforgeeks.org/boundary-traversal-of-binary-tree/

 Problem Statement:
 -----------------
 Given a Binary Tree, find its Boundary Traversal. The traversal should be in 
 the following order:
 1. Left boundary nodes: defined as the path from root to the left-most leaf 
    node via the left boundary. Don't include leaf nodes in this.
 2. Leaf nodes: All the leaf nodes, from left to right.
 3. Reverse right boundary nodes: defined as the path from the right-most leaf 
    node to the root via the right boundary. Don't include leaf nodes in this.

 Example 1:
 Input: Binary Tree = 
        1
       / \
      2   3
     / \   \
    4   5   6
       / \
      7   8
 Output: 1 2 4 7 8 6 3
 Explanation: 
 - Left boundary: 1, 2
 - Leaf nodes: 4, 7, 8, 6  
 - Right boundary (reverse): 3

 Example 2:
 Input: Binary Tree =
           20
          /  \
         8   22
        / \    \
       4  12   25
         / \
        10 14
 Output: 20 8 4 10 14 25 22

 Constraints:
 - 1 ≤ Number of nodes ≤ 10^5
 - 1 ≤ Data of a node ≤ 10^5
====================================================
*/


struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};


/* 
==========================================
 Approach 1: Brute Force - DFS with Node Marking
 -----------------------------------------
 💡 Idea:
 Perform DFS traversal and mark each node as left boundary, right boundary,
 or leaf node. Then collect nodes in the required order.

 🧩 Algorithm:
 1. Use DFS to traverse the entire tree and mark node types
 2. Create separate lists for left boundary, leaves, and right boundary
 3. For each node, determine its type:
    - Left boundary: path from root to leftmost leaf via left edges
    - Leaf: nodes with no children
    - Right boundary: path from root to rightmost leaf via right edges
 4. Combine the three lists in correct order

 ⏱ Time Complexity: O(N^2) - multiple traversals to determine node types
 📦 Space Complexity: O(N) - storing node classifications
*/
vector<int> boundaryTraversalBruteForce(Node* root) {
    if (!root) return {};
    
    vector<int> result;
    set<Node*> visited;
    
    // Helper to check if node is leaf
    auto isLeaf = [](Node* node) {
        return node && !node->left && !node->right;
    };
    
    // Add root if not leaf
    if (!isLeaf(root)) {
        result.push_back(root->data);
        visited.insert(root);
    }
    
    // Collect left boundary (excluding leaves)
    Node* curr = root->left;
    while (curr) {
        if (!isLeaf(curr) && visited.find(curr) == visited.end()) {
            result.push_back(curr->data);
            visited.insert(curr);
        }
        if (curr->left) curr = curr->left;
        else curr = curr->right;
    }
    
    // Collect all leaves using DFS
    function<void(Node*)> collectLeaves = [&](Node* node) {
        if (!node) return;
        if (isLeaf(node)) {
            result.push_back(node->data);
            return;
        }
        collectLeaves(node->left);
        collectLeaves(node->right);
    };
    
    collectLeaves(root);
    
    // Collect right boundary (excluding leaves) in reverse
    vector<int> rightBoundary;
    curr = root->right;
    while (curr) {
        if (!isLeaf(curr) && visited.find(curr) == visited.end()) {
            rightBoundary.push_back(curr->data);
        }
        if (curr->right) curr = curr->right;
        else curr = curr->left;
    }
    
    // Add right boundary in reverse order
    reverse(rightBoundary.begin(), rightBoundary.end());
    for (int val : rightBoundary) {
        result.push_back(val);
    }
    
    return result;
}

/* 
==========================================
 Approach 2: Optimal - Your Clean Implementation
 -----------------------------------------
 💡 Idea:
 Use clean, modular functions for each boundary part. Your implementation
 demonstrates excellent code organization and efficiency.

 🧩 Algorithm:
 1. isLeaf(): Simple check for leaf nodes
 2. left(): Traverse left boundary iteratively, add non-leaf nodes
 3. leaf(): Recursively collect all leaf nodes from left to right
 4. right(): Traverse right boundary, collect in temp, add in reverse
 5. Main function combines all parts with root handling

 ⏱ Time Complexity: O(N) - each node visited exactly once
 📦 Space Complexity: O(H) - recursion depth for leaf collection
*/
bool isLeaf(Node* root) {
    return (!root->left && !root->right);
}

void left(Node* root, vector<int>& result) {
    Node* curr = root->left;
    while (curr) {
        if (!isLeaf(curr)) result.push_back(curr->data);
        if (curr->left) curr = curr->left;
        else curr = curr->right;
    }
}

void leaf(Node* root, vector<int>& result) {
    if (isLeaf(root)) {
        result.push_back(root->data);
        return;
    }
    if (root->left) leaf(root->left, result);
    if (root->right) leaf(root->right, result);
}

void right(Node* root, vector<int>& result) {
    Node* curr = root->right;
    vector<int> leafNodes;
    while (curr) {
        if (!isLeaf(curr)) leafNodes.push_back(curr->data);
        if (curr->right) curr = curr->right;
        else curr = curr->left;
    }
    for (int i = leafNodes.size() - 1; i >= 0; i--) {
        result.push_back(leafNodes[i]);
    }
}

vector<int> boundaryTraversal(Node* root) {
    if (!root) return {};
    vector<int> result;
    if (!isLeaf(root)) result.push_back(root->data);
    
    left(root, result);
    leaf(root, result);
    right(root, result);
    return result;
}


/* Helper function to create sample trees */
Node* createSampleTree1() {
    /*
    Creating tree:
        1
       / \
      2   3
     / \   \
    4   5   6
       / \
      7   8
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);
    root->left->right->left = new Node(7);
    root->left->right->right = new Node(8);
    return root;
}

Node* createSampleTree2() {
    /*
    Creating tree:
           20
          /  \
         8   22
        / \    \
       4  12   25
         / \
        10 14
    */
    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(4);
    root->left->right = new Node(12);
    root->right->right = new Node(25);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);
    return root;
}

/* Helper function to print results */
void printResult(const vector<int>& result, const string& method) {
    cout << method << ": [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

/* Helper function to demonstrate boundary process */
void demonstrateBoundaryProcess(Node* root, const string& treeName) {
    cout << "=== Boundary Process for " << treeName << " ===\n";
    
    if (!root) {
        cout << "Empty tree\n\n";
        return;
    }
    
    vector<int> result;
    
    cout << "Step 1 - Root: ";
    if (!isLeaf(root)) {
        result.push_back(root->data);
        cout << root->data;
    } else {
        cout << "(root is leaf, will be added in leaf step)";
    }
    cout << "\n";
    
    cout << "Step 2 - Left Boundary: ";
    vector<int> leftBoundary;
    Node* curr = root->left;
    while (curr) {
        if (!isLeaf(curr)) {
            leftBoundary.push_back(curr->data);
            cout << curr->data << " ";
        }
        if (curr->left) curr = curr->left;
        else curr = curr->right;
    }
    if (leftBoundary.empty()) cout << "(none)";
    cout << "\n";
    
    cout << "Step 3 - Leaf Nodes: ";
    vector<int> leaves;
    function<void(Node*)> collectLeaves = [&](Node* node) {
        if (!node) return;
        if (isLeaf(node)) {
            leaves.push_back(node->data);
            cout << node->data << " ";
            return;
        }
        collectLeaves(node->left);
        collectLeaves(node->right);
    };
    collectLeaves(root);
    if (leaves.empty()) cout << "(none)";
    cout << "\n";
    
    cout << "Step 4 - Right Boundary (reverse): ";
    vector<int> rightBoundary;
    curr = root->right;
    while (curr) {
        if (!isLeaf(curr)) {
            rightBoundary.push_back(curr->data);
        }
        if (curr->right) curr = curr->right;
        else curr = curr->left;
    }
    for (int i = rightBoundary.size() - 1; i >= 0; i--) {
        cout << rightBoundary[i] << " ";
    }
    if (rightBoundary.empty()) cout << "(none)";
    cout << "\n";
    
    // Combine all parts
    for (int val : leftBoundary) result.push_back(val);
    for (int val : leaves) result.push_back(val);
    for (int i = rightBoundary.size() - 1; i >= 0; i--) {
        result.push_back(rightBoundary[i]);
    }
    
    printResult(result, "Final boundary traversal");
    cout << "\n";
}

/* Function to delete tree and free memory */
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Testing Boundary Traversal of Binary Tree ===\n\n";
    
    // Create sample trees
    Node* tree1 = createSampleTree1();
    Node* tree2 = createSampleTree2();
    Node* singleNode = new Node(42);
    
    vector<pair<Node*, string>> testCases = {
        {tree1, "Sample Tree 1"},
        {tree2, "Sample Tree 2"},
        {singleNode, "Single Node Tree"},
        {nullptr, "Empty Tree"}
    };
    
    for (auto& testCase : testCases) {
        Node* tree = testCase.first;
        string name = testCase.second;
        
        cout << "=== " << name << " ===\n";
        
        if (tree) {
            auto result1 = boundaryTraversalBruteForce(tree);
            auto result2 = boundaryTraversal(tree);
            
            printResult(result1, " Brute Force");
            printResult(result2, " Optimal (Your)");
            
            // Demonstrate process for first tree
            if (name == "Sample Tree 1") {
                cout << "\n";
                demonstrateBoundaryProcess(tree, name);
            }
        } else {
            cout << "Empty tree: []\n";
        }
        
        cout << "------------------------\n";
    }
    
    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N^2) time, uses multiple traversals with node marking.\n";
    cout << "2. Optimal (Your) -> O(N) time, modular design with excellent readability.\n";
    cout << "\nRecommendation: Your optimal approach is perfectly structured! ✅\n";
    cout << "Key Insight: Boundary traversal consists of three distinct parts that can\n";
    cout << "             be handled independently: left boundary, leaves, right boundary.\n";
    cout << "\nYour Implementation Highlights:\n";
    cout << "- Clean separation: each function has single responsibility\n";
    cout << "- Efficient traversal: each node visited exactly once\n";
    cout << "- Smart boundary handling: iterative for boundaries, recursive for leaves\n";
    cout << "- Edge case handling: root as leaf, empty tree, single node\n";
    cout << "- Memory efficient: minimal extra space usage\n";
    cout << "\nAlgorithm Flow:\n";
    cout << "1. Add root (if not leaf)\n";
    cout << "2. Left boundary: traverse left, add non-leaves\n";
    cout << "3. Leaf nodes: inorder traversal, collect all leaves\n";
    cout << "4. Right boundary: traverse right, collect in temp, add reverse\n";
    cout << "\nYour provided solution demonstrates excellent modular programming! 🎯\n";
    cout << "The clean function names and logical flow make it interview-perfect!\n";
    
    // Clean up memory
    deleteTree(tree1);
    deleteTree(tree2);
    deleteTree(singleNode);
    
    return 0;
}
