#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Vertical Order Traversal of a Binary Tree
 LeetCode Link: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/

 Problem Statement:
 -----------------
 Given the root of a binary tree, return the vertical order traversal of its nodes' values.
 Nodes are sorted first by column from left to right, then by row from top to bottom,
 and if two nodes share the same row and column, they are sorted by node value.

 Example 1:
 Input:
        3
       / \
      9  20
         /  \
        15   7
 Output:
 [
  [9],
  [3, 15],
  [20],
  [7]
 ]

 Example 2:
 Input:
        1
       / \
      2   3
     / \ / \
    4  6 5  7
 Output:
 [
  [4],
  [2],
  [1, 5, 6],
  [3],
  [7]
 ]

 Constraints:
 - Number of nodes in tree is in range [1, 1000]
 - Node values range from 0 to 1000
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
 Approach 1: Brute Force - BFS with Nested Maps
 ------------------------------------------
 💡 Idea:
 Perform BFS traversal, store nodes in a nested map structure with keys
 (column, row). Sort nodes by value if multiple nodes share the same position.

 🧩 Algorithm:
 1. Use a queue for BFS, track each node's row and column.
 2. Insert nodes into map<col, map<row, vector<value>>>
 3. After traversal, iterate maps and flatten vectors in sorted order.
 4. Return the list of columns with their node values in vertical order.

 ⏱ Time Complexity: O(N log N) due to sorting of node vectors.
 📦 Space Complexity: O(N) for the map and queue.
*/
vector<vector<int>> verticalTraversalBruteForce(TreeNode* root) {
    if (!root) return {};

    map<int, map<int, vector<int>>> nodesMap;
    queue<tuple<TreeNode*, int, int>> q; // node, row, col
    q.push({root, 0, 0});

    while (!q.empty()) {
        TreeNode* node; int row, col;
        std::tie(node, row, col) = q.front();
        q.pop();

        nodesMap[col][row].push_back(node->val);

        if (node->left)
            q.push({node->left, row + 1, col - 1});
        if (node->right)
            q.push({node->right, row + 1, col + 1});
    }

    vector<vector<int>> result;
    for (const auto& colPair : nodesMap) {
        vector<int> colVals;
        for (const auto& rowPair : colPair.second) {
            vector<int> values = rowPair.second;
            sort(values.begin(), values.end());
            colVals.insert(colVals.end(), values.begin(), values.end());
        }
        result.push_back(colVals);
    }
    return result;
}


/*
==========================================
 Approach 2: Better - DFS and Sort Collected Nodes
 ------------------------------------------
 💡 Idea:
 Use DFS to collect all nodes as tuples (col, row, value),
 sort them globally then group by column for final output.

 🧩 Algorithm:
 1. Recursively traverse tree, collecting tuples of (col, row, value).
 2. Sort all tuples by column, then row, then value.
 3. Group sorted tuples by column index.
 4. Return grouped node values as vertical traversal.

 ⏱ Time Complexity: O(N log N) due to sorting.
 📦 Space Complexity: O(N) for storing node tuples.
*/
void dfsCollect(TreeNode* root, int row, int col, vector<array<int,3>>& nodes) {
    if (!root) return;
    nodes.push_back({col, row, root->val});
    dfsCollect(root->left, row + 1, col - 1, nodes);
    dfsCollect(root->right, row + 1, col + 1, nodes);
}

vector<vector<int>> verticalTraversalBetter(TreeNode* root) {
    if (!root) return {};
    vector<array<int,3>> nodes;
    dfsCollect(root, 0, 0, nodes);

    sort(nodes.begin(), nodes.end(), [](const array<int,3>& a, const array<int,3>& b) {
        if (a[0] != b[0]) return a[0] < b[0];
        if (a[1] != b[1]) return a[1] < b[1];
        return a[2] < b[2];
    });

    vector<vector<int>> result;
    int prevCol = INT_MIN;

    for (const auto& node : nodes) {
        if (node[0] != prevCol) {
            result.emplace_back();
            prevCol = node[0];
        }
        result.back().push_back(node[2]);
    }

    return result;
}


/*
==========================================
 Approach 3: Optimal - Pre-Calculate Bounds and Use DFS
 ------------------------------------------
 💡 Idea:
 First find the minimum and maximum column indices to size the output vector.
 Then use DFS to store nodes with adjusted zero-based column indices,
 sort and group nodes by column accordingly.

 🧩 Algorithm:
 1. Calculate leftmost and rightmost column indices with recursive traversals.
 2. DFS to generate tuples (adjusted column, row, value).
 3. Sort all tuples in column > row > value order.
 4. Pre-allocate result vector size to span all columns.
 5. Group nodes into result by adjusted column index.

 ⏱ Time Complexity: O(N log N) due to sorting.
 📦 Space Complexity: O(N).
*/
int findLeftMost(TreeNode* root, int col) {
    if (!root) return INT_MAX;
    return min({col, findLeftMost(root->left, col - 1), findLeftMost(root->right, col + 1)});
}

int findRightMost(TreeNode* root, int col) {
    if (!root) return INT_MIN;
    return max({col, findRightMost(root->left, col - 1), findRightMost(root->right, col + 1)});
}

void generateNodes(TreeNode* root, vector<vector<int>>& nodes, int row, int col, int leftMost) {
    if (!root) return;
    nodes.push_back({col - leftMost, row, root->val});
    generateNodes(root->left, nodes, row + 1, col - 1, leftMost);
    generateNodes(root->right, nodes, row + 1, col + 1, leftMost);
}

vector<vector<int>> verticalTraversalOptimal(TreeNode* root) {
    if (!root) return {};
    int leftMost = findLeftMost(root, 0);
    int rightMost = findRightMost(root, 0);
    vector<vector<int>> nodes;
    generateNodes(root, nodes, 0, 0, leftMost);

    sort(nodes.begin(), nodes.end());

    vector<vector<int>> result(rightMost - leftMost + 1);
    for (const auto& node : nodes) {
        result[node[0]].push_back(node[2]);
    }
    return result;
}


/* Helper function to print results */
void printTraversalResult(const vector<vector<int>>& result, const string& approachName) {
    cout << approachName << ":\n";
    for (size_t i = 0; i < result.size(); i++) {
        cout << "Column " << i << ": ";
        for (size_t j = 0; j < result[i].size(); j++) {
            cout << result[i][j];
            if (j != result[i].size() - 1) cout << ", ";
        }
        cout << "\n";
    }
    cout << "\n";
}

/* Sample tree creation for tests */
TreeNode* createSampleTree1() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

TreeNode* createSampleTree2() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(6);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    return root;
}

/* Main function with test cases and summary */
int main() {
    vector<pair<TreeNode*, string>> testCases = {
        {createSampleTree1(), "Sample Tree 1"},
        {createSampleTree2(), "Sample Tree 2"},
        {nullptr, "Empty Tree"}
    };

    for (const auto& testCase : testCases) {
        TreeNode* tree = testCase.first;
        string name = testCase.second;

        cout << "=== " << name << " ===\n";

        auto resBrute = verticalTraversalBruteForce(tree);
        auto resBetter = verticalTraversalBetter(tree);
        auto resOptimal = verticalTraversalOptimal(tree);

        printTraversalResult(resBrute, "Brute Force (BFS + Map)");
        printTraversalResult(resBetter, "Better (DFS + Sort)");
        printTraversalResult(resOptimal, "Optimal (Bounds + DFS)");

        cout << "-----------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force: BFS + nested maps; clear but can be slower due to nested structure.\n";
    cout << "2. Better: DFS list collection + single sort; simpler and flexible sorting.\n";
    cout << "3. Optimal: Pre-calculate bounds + adjusted columns + DFS; best balance of clarity & efficiency.\n";
    cout << "All approaches fully correct with O(N log N) time due to sorting.\n";
    cout << "Use optimal for best practical performance in interviews.\n";

    return 0;
}
