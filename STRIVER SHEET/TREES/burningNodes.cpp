#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Minimum Time to Burn Binary Tree from Target
 Problem Link: https://practice.geeksforgeeks.org/problems/burning-tree/1

 Problem Statement:
 -----------------
 Given a binary tree and a target node value,
 find the minimum time required to burn the entire tree starting from the target node. 
 Burning spreads each time unit to parent, left child, and right child.

 Example:
 Input:
         1
        / \
       2   3
      / \
     4   5
 Target: 2

 Output: 2
 Explanation: Fire starts at node 2:
  - Time 0: 2
  - Time 1: 4, 5, and 1
  - Time 2: 3

 Constraints:
 - 1 <= number of nodes <= 1000
 - Node values are unique
====================================================
*/

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/*
==========================================
 Approach 1: Brute Force - DFS from Every Node
------------------------------------------
💡 Idea:
For each node, perform BFS to find the time to burn entire tree starting from that node.
Take the minimum for all.

🧩 Algorithm:
1. For each node, run BFS and find the time required to reach all nodes.
2. Keep minimum time among all possible starting nodes.
3. Return minimum.

⏱ Time Complexity: O(N^2)
📦 Space Complexity: O(N)
*/
void collectAllNodes(Node* root, vector<Node*>& nodes) {
    if (!root) return;
    nodes.push_back(root);
    collectAllNodes(root->left, nodes);
    collectAllNodes(root->right, nodes);
}

int burnTimeFromNode(Node* start, unordered_map<Node*, Node*>& parentof) {
    unordered_set<Node*> visited;
    queue<Node*> q;
    q.push(start);
    visited.insert(start);
    int time = 0;
    while (!q.empty()) {
        int sz = q.size();
        bool spread = false;
        for (int i = 0; i < sz; ++i) {
            Node* curr = q.front(); q.pop();
            for (Node* neighbor : {curr->left, curr->right, parentof[curr]}) {
                if (neighbor && !visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                    spread = true;
                }
            }
        }
        if (spread) time++;
    }
    return time;
}

int minTimeBrute(Node* root, int target) {
    unordered_map<Node*, Node*> parentof;
    vector<Node*> nodes;
    Node* targetNode = nullptr;
    function<void(Node*, Node*)> buildParent = [&](Node* node, Node* parent) {
        if (!node) return;
        parentof[node] = parent;
        if (node->data == target) targetNode = node;
        buildParent(node->left, node);
        buildParent(node->right, node);
    };
    buildParent(root, nullptr);

    collectAllNodes(root, nodes);
    int minAns = INT_MAX;
    for (Node* node : nodes) {
        minAns = min(minAns, burnTimeFromNode(node, parentof));
    }
    return minAns;
}

/*
==========================================
 Approach 2: Better - DFS Parent Mapping + DFS Spread (Recursive)
------------------------------------------
💡 Idea:
Build parent pointers using DFS. Locate the target node.
Run recursive DFS from target node exploring left, right, and parent while tracking time.

🧩 Algorithm:
1. DFS to set parent pointers and find target node.
2. DFS propagate burning, marking visited, incrementing time for every step.
3. Update answer with every leaf/burned node.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
void setParent(Node* root, Node* parent, unordered_map<Node*, Node*>& parentof, Node*& curr, int target) {
    if (!root) return;
    if (root->data == target) curr = root;
    parentof[root] = parent;
    setParent(root->left, root, parentof, curr, target);
    setParent(root->right, root, parentof, curr, target);
}

void generate(Node* curr, unordered_map<Node*, Node*>& parentof, unordered_map<Node*, bool>& visited, int& ans, int i) {
    if (!curr) {
        ans = max(ans, i - 1);
        return;
    }
    if (visited[curr]) return;
    visited[curr] = true;
    generate(curr->left, parentof, visited, ans, i + 1);
    generate(curr->right, parentof, visited, ans, i + 1);
    generate(parentof[curr], parentof, visited, ans, i + 1);
}

int minTimeBetter(Node* root, int target) {
    unordered_map<Node*, Node*> parentof;
    Node* curr = nullptr;
    setParent(root, nullptr, parentof, curr, target);
    int ans = 0;
    unordered_map<Node*, bool> visited;
    generate(curr, parentof, visited, ans, 0);
    return ans;
}

/*
==========================================
 Approach 3: Optimal - BFS from Target Node After Parent Mapping
------------------------------------------
💡 Idea:
Build parent mapping in O(N). Find target node. 
BFS from target and count burning steps for each level until all nodes are burned.

🧩 Algorithm:
1. BFS to set parent pointers, find target node.
2. BFS from target node, visiting neighbors (left, right, parent) per level, using visited set.
3. Each level of BFS is one time unit; last BFS level depth tracked as min burn time.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
void buildParentMap(Node* root, unordered_map<Node*, Node*>& parentof) {
    queue<Node*> q;
    q.push(root);
    parentof[root] = nullptr;
    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        if (node->left) {
            parentof[node->left] = node;
            q.push(node->left);
        }
        if (node->right) {
            parentof[node->right] = node;
            q.push(node->right);
        }
    }
}

Node* findNode(Node* root, int target) {
    if (!root) return nullptr;
    if (root->data == target) return root;
    Node* l = findNode(root->left, target);
    if (l) return l;
    return findNode(root->right, target);
}

int minTimeOptimal(Node* root, int target) {
    unordered_map<Node*, Node*> parentof;
    buildParentMap(root, parentof);
    Node* start = findNode(root, target);
    if (!start) return 0;

    unordered_set<Node*> visited;
    queue<Node*> q;
    q.push(start);
    visited.insert(start);
    int time = 0;
    while (!q.empty()) {
        int sz = q.size();
        bool spread = false;
        for (int i = 0; i < sz; ++i) {
            Node* curr = q.front(); q.pop();
            for (Node* neighbor : {curr->left, curr->right, parentof[curr]}) {
                if (neighbor && !visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                    spread = true;
                }
            }
        }
        if (spread) ++time;
    }
    return time;
}

/* Helper to create sample tree */
Node* createSampleTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    return root;
}
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Minimum Time to Burn Binary Tree ===\n\n";
    Node* root = createSampleTree();
    int target = 2;

    cout << "Brute Force Result: " << minTimeBrute(root, target) << "\n";
    cout << "Better (DFS) Result: " << minTimeBetter(root, target) << "\n";
    cout << "Optimal (BFS) Result: " << minTimeOptimal(root, target) << "\n";

    deleteTree(root);
    return 0;
}

/*
✅ Approach Overview:
- Brute Force: Try burning from every node, O(N^2).
- Better: DFS parent mapping + recursive DFS, O(N).
- Optimal: BFS after parent mapping, robust and clear for large/deep trees, O(N).
Optimal approach is recommended for interviews and real systems.
*/
