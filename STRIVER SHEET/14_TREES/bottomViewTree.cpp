#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Bottom View of Binary Tree
 Problem Link: https://practice.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1

 Problem Statement:
 -----------------
 Given a binary tree, return the bottom view of the binary tree from left to right.
 The bottom view of the tree is the set of nodes visible when the tree is viewed
 from the bottom. For each horizontal distance (hd) from the root, only the bottom-most
 node is visible.

 Example:
 Input:
          20
         /  \
        8   22
       / \    \
      5  3    25
        / \
       10 14

 Output: 5 10 3 14 25
 Explanation: The nodes visible from the bottom are 5, 10, 3, 14, and 25.

 Constraints:
 - Number of nodes in the tree: 1 to 10^5
 - Node values range: 0 to 10^5
====================================================
*/

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

/* 
==========================================
 Approach 1: Brute Force - Explore All Paths with Horizontal Distance Tracking
-----------------------------------------
💡 Idea:
For each node, find all vertical paths passing through it by traversing the entire tree,
recording nodes at each horizontal distance and depth, then determine which node is bottom-most.

🧩 Algorithm:
1. Traverse tree, store each node's horizontal distance (hd) and depth.
2. For each hd, track the node with max depth (bottom-most).
3. Use DFS for every node carrying hd and depth info.
4. After traversal, output nodes sorted by hd.

⏱ Time Complexity: O(N^2) - Repeatedly traversing to check depths for each node.
📦 Space Complexity: O(N) - Maps and recursion stack for DFS.
*/
void dfsBruteForce(Node* node, int hd, int depth,
                   map<int, pair<int,int> >& hdDepthNodeMap) {
    if (!node) return;
    // Update if current node is deeper at the same hd
    if (hdDepthNodeMap.find(hd) == hdDepthNodeMap.end() || depth >= hdDepthNodeMap[hd].first) {
        hdDepthNodeMap[hd] = make_pair(depth, node->data);
    }
    dfsBruteForce(node->left, hd - 1, depth + 1, hdDepthNodeMap);
    dfsBruteForce(node->right, hd + 1, depth + 1, hdDepthNodeMap);
}

vector<int> bottomViewBruteForce(Node* root) {
    map<int, pair<int,int> > hdDepthNodeMap; // hd -> (maxDepth, nodeData)
    dfsBruteForce(root, 0, 0, hdDepthNodeMap);

    vector<int> bottomViewNodes;
    for (map<int, pair<int,int> >::iterator it = hdDepthNodeMap.begin(); it != hdDepthNodeMap.end(); ++it) {
        bottomViewNodes.push_back(it->second.second);
    }
    return bottomViewNodes;
}

/* 
==========================================
 Approach 2: Better - Level Order with Overwrite in Map
-----------------------------------------
💡 Idea:
Use a level order traversal with horizontal distance tracking.
For each horizontal distance, overwrite the existing node data at that hd, so the last node 
at that horizontal distance (the bottom-most at that level) stays in the map.

🧩 Algorithm:
1. Initialize queue with root at hd = 0.
2. For each node in the queue:
    - Update map[hd] = node data (overwrite).
    - Enqueue left child with hd - 1.
    - Enqueue right child with hd + 1.
3. After BFS, map contains bottom-most nodes for each hd.
4. Extract values from map by ascending hd.

⏱ Time Complexity: O(N), where N is number of nodes.
📦 Space Complexity: O(N), due to queue and map size.
*/
vector<int> bottomViewBetter(Node* root) {
    if (!root) return vector<int>();

    map<int, int> hdNodeMap;
    queue<pair<Node*, int> > q;
    q.push(make_pair(root, 0));

    while (!q.empty()) {
        pair<Node*, int> front = q.front();
        q.pop();

        Node* node = front.first;
        int hd = front.second;

        // Overwrite the node at horizontal distance hd
        hdNodeMap[hd] = node->data;

        if (node->left)
            q.push(make_pair(node->left, hd - 1));
        if (node->right)
            q.push(make_pair(node->right, hd + 1));
    }

    vector<int> result;
    for (map<int, int>::iterator it = hdNodeMap.begin(); it != hdNodeMap.end(); ++it) {
        result.push_back(it->second);
    }
    return result;
}


/* 
==========================================
 Approach 3: Optimal - Level Order with Unordered Map + Track Min and Max Hd
-----------------------------------------
💡 Idea:
Same as Approach 2 but use an unordered_map for O(1) average insertion.
Track minimum and maximum horizontal distances during traversal to extract results in order.

🧩 Algorithm:
1. Use unordered_map<int, int> to keep hd -> node data.
2. Track minHd, maxHd while processing nodes.
3. Level order traversal similar to Approach 2.
4. After traversal, iterate from minHd to maxHd to build result vector.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
vector<int> bottomViewOptimal(Node* root) {
    if (!root) return vector<int>();

    unordered_map<int, int> hdNodeMap;
    queue<pair<Node*, int> > q;
    q.push(make_pair(root, 0));

    int minHd = 0, maxHd = 0;

    while (!q.empty()) {
        pair<Node*, int> front = q.front();
        q.pop();

        Node* node = front.first;
        int hd = front.second;

        hdNodeMap[hd] = node->data;
        if (hd < minHd) minHd = hd;
        if (hd > maxHd) maxHd = hd;

        if (node->left)
            q.push(make_pair(node->left, hd - 1));
        if (node->right)
            q.push(make_pair(node->right, hd + 1));
    }

    vector<int> result;
    for (int hd = minHd; hd <= maxHd; ++hd) {
        if (hdNodeMap.find(hd) != hdNodeMap.end())
            result.push_back(hdNodeMap[hd]);
    }

    return result;
}

/* Helper function to create a sample tree */
Node* createSampleTree() {
    /*
            20
           /  \
          8   22
         / \    \
        5  3    25
          / \
         10 14
    */
    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(5);
    root->left->right = new Node(3);
    root->right->right = new Node(25);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);
    return root;
}

/* Helper function to delete tree nodes */
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Bottom View of Binary Tree ===\n\n";

    Node* root = createSampleTree();

    // Lambda for printing vector<int> is C++14+, using normal function instead:
    // Print vector elements separated by space
    auto printVector = [](const vector<int>& vec) {
        for (size_t i = 0; i < vec.size(); ++i)
            cout << vec[i] << " ";
        cout << "\n";
    };

    vector<int> res1 = bottomViewBruteForce(root);
    cout << "Brute Force Result: ";
    printVector(res1);

    vector<int> res2 = bottomViewBetter(root);
    cout << "Better BFS Result: ";
    printVector(res2);

    vector<int> res3 = bottomViewOptimal(root);
    cout << "Optimal BFS Result: ";
    printVector(res3);

    deleteTree(root);
    return 0;
}

/*
✅ Approach Overview:
- Brute Force: DFS with depth tracking per horizontal distance (O(N^2)), computationally expensive.
- Better BFS: Level order with map overwrite tracking (O(N)), simple and effective.
- Optimal BFS: Uses unordered_map and tracks hd bounds to build result efficiently (O(N)).
Recommendation: The optimal BFS approach is best practice for large-scale inputs and clarity.
*/
