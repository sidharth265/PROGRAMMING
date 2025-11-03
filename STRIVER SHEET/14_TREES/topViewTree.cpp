#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Top View of Binary Tree
 GeeksforGeeks Link: https://www.geeksforgeeks.org/top-view-of-a-binary-tree/

 Problem Statement:
 -----------------
 Given a binary tree, return the nodes visible from the top view when viewed from above.
 The top view of a binary tree is the set of nodes visible when the tree is viewed from the top.
 For each horizontal distance from the root, print the first node encountered.

 Example 1:
 Input: 
        1
       / \
      2   3
       \   \
        4   5
 Output: 2 1 3 5

 Example 2:
 Input: 
           1
         /   \
        2     3
       / \   /  \
      4   5 6    7
 Output: 4 2 1 3 7

 Constraints:
 - 1 ≤ Number of nodes ≤ 10^5
 - 1 ≤ Node data ≤ 10^5
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
 Approach 1: Brute Force – BFS with All Levels, Keep Last at Each Horizontal Distance
 -----------------------------------------
 💡 Idea:
 Use BFS traversal and for each horizontal distance (HD), keep updating the node's value.
 At the end, the last update for each HD will be the bottom view node,
 but this does not guarantee top view—so this is a reference non-optimal brute force.

 🧩 Algorithm:
 1. BFS on tree; keep a map<int, int> to store node data at each HD.
 2. For each node, update map for current HD.
 3. Insert left/right children with HD-1 / HD+1.
 4. At the end, map contains last node for each HD (bottom view).
 5. Return the result in HD order.

 ⏱ Time Complexity: O(N log N)
 📦 Space Complexity: O(N)
*/
vector<int> topViewBruteForce(Node* root) {
    if (!root) return {};
    map<int, int> m;
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        Node* temp = q.front().first;
        int d = q.front().second;
        q.pop();
        m[d] = temp->data;
        if (temp->left) q.push({temp->left, d-1});
        if (temp->right) q.push({temp->right, d+1});
    }
    vector<int> result;
    for (auto& it : m) result.push_back(it.second);
    return result;
}

/* 
==========================================
 Approach 2: Better – BFS with First Node at Each HD (Top View)
 -----------------------------------------
 💡 Idea:
 Use BFS and a map to keep only the first node encountered at each horizontal distance 
 (per BFS layer, so it's the topmost node seen from above).

 🧩 Algorithm:
 1. BFS on tree; use map<int, int> to store node data for each new HD.
 2. For each node, if HD is not yet in map, add it (first seen = top view).
 3. For left/right children add with HD-1/HD+1.
 4. At end, map contains topmost node for each HD.
 5. Return result in key-sorted order.

 ⏱ Time Complexity: O(N log N)
 📦 Space Complexity: O(N)
*/
vector<int> topViewBetter(Node* root) {
    if (!root) return {};
    map<int, int> m;
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        Node* temp = q.front().first;
        int d = q.front().second;
        q.pop();
        if (m.find(d) == m.end()) m[d] = temp->data;
        if (temp->left) q.push({temp->left, d-1});
        if (temp->right) q.push({temp->right, d+1});
    }
    vector<int> result;
    for (auto& it : m) result.push_back(it.second);
    return result;
}

/* 
==========================================
 Approach 3: Optimal – BFS with Unordered Map and Min/Max HD
 -----------------------------------------
 💡 Idea:
 Use unordered_map for O(1) lookups if the range of HD is not huge,
 and keep track of min and max HD to output the result in order.

 🧩 Algorithm:
 1. BFS on tree;
 2. Use unordered_map<int, int> to store first node at each HD, and variables for minHD/maxHD.
 3. For each node, if HD not yet seen, add to map.
 4. Output all values from minHD to maxHD at the end.

 ⏱ Time Complexity: O(N)
 📦 Space Complexity: O(N)
*/
vector<int> topViewOptimal(Node* root) {
    if (!root) return {};
    unordered_map<int, int> m;
    int minHD = 0, maxHD = 0;
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    while (!q.empty()) {
        Node* temp = q.front().first;
        int d = q.front().second;
        q.pop();
        if (!m.count(d)) m[d] = temp->data;
        minHD = min(minHD, d);
        maxHD = max(maxHD, d);
        if (temp->left) q.push({temp->left, d-1});
        if (temp->right) q.push({temp->right, d+1});
    }
    vector<int> result;
    for (int d = minHD; d <= maxHD; d++) {
        if (m.count(d)) result.push_back(m[d]);
    }
    return result;
}

// Helper to build a tree for demonstration
Node* sample1() {
    //        1
    //       / \
    //      2   3
    //       \   \
    //        4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->right->right = new Node(5);
    return root;
}

Node* sample2() {
    //         1
    //       /   \
    //      2     3
    //     / \   / \
    //    4   5 6   7
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    return root;
}

void printVector(const vector<int>& ans, const string& label) {
    cout << label << ": ";
    for (int x : ans) cout << x << " ";
    cout << endl;
}

int main() {
    Node* tree1 = sample1();
    Node* tree2 = sample2();

    cout << "Test Case 1:\n";
    printVector(topViewBruteForce(tree1), "Brute Force");
    printVector(topViewBetter(tree1), "Better");
    printVector(topViewOptimal(tree1), "Optimal");

    cout << "\nTest Case 2:\n";
    printVector(topViewBruteForce(tree2), "Brute Force");
    printVector(topViewBetter(tree2), "Better");
    printVector(topViewOptimal(tree2), "Optimal");

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview\n";
    cout << "Brute Force: O(N log N), keeps last seen node at each HD (actually gives bottom view, not top).\n";
    cout << "Better:      O(N log N), keeps first node at each HD from BFS (gives real top view).\n";
    cout << "Optimal:     O(N), unordered map + min/max for output range, faster lookups for tight HD range.\n";
    cout << "For interviews, the 'Better' or 'Optimal' approach is most correct for top view!\n";
    return 0;
}
