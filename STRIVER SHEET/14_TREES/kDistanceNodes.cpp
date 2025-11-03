#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: All Nodes Distance K in Binary Tree
 Problem Link: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/

 Problem Statement:
 -----------------
 Given the root of a binary tree, a target node, and an integer K, return the values of all nodes that are exactly distance K from the target node.
 The distance between two nodes is the number of edges in the shortest path connecting them.

 Example:
 Input:
          3
         / \
        5   1
       / \  / \
      6  2 0  8
        / \
       7   4

 Target: 5, K=2
 Output: [7,4,1]
 Explanation: Nodes at distance 2 from node 5 are 7, 4, and 1.

 Constraints:
 - Number of nodes is at most 500.
 - Nodes values are unique.
====================================================
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

/*
==========================================
Approach 1: DFS Parent Mapping + DFS Search (Recursive)
------------------------------------------
💡 Idea:
- Use DFS to map each node to its parent.
- Perform DFS from target node exploring neighbors: left child, right child, and parent.
- Track visited nodes to avoid cycles.
- Add nodes to answer when distance equals K.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
void setParent(TreeNode* root, TreeNode* parent, unordered_map<TreeNode*, TreeNode*>& parentof) {
    if (!root) return;
    parentof[root] = parent;
    setParent(root->left, root, parentof);
    setParent(root->right, root, parentof);
}

void generateDFS(TreeNode* curr, vector<int>& ans, unordered_map<TreeNode*, TreeNode*>& parentof,
                 unordered_map<TreeNode*, bool>& visited, int k, int dist) {
    if (!curr || visited[curr]) return;
    if (dist == k) {
        ans.push_back(curr->val);
        return;
    }
    visited[curr] = true;
    generateDFS(curr->left, ans, parentof, visited, k, dist + 1);
    generateDFS(curr->right, ans, parentof, visited, k, dist + 1);
    if (parentof.find(curr) != parentof.end())
        generateDFS(parentof[curr], ans, parentof, visited, k, dist + 1);
}

vector<int> distanceK_DFS(TreeNode* root, TreeNode* target, int k) {
    unordered_map<TreeNode*, TreeNode*> parentof;
    setParent(root, nullptr, parentof);
    unordered_map<TreeNode*, bool> visited;
    vector<int> ans;
    generateDFS(target, ans, parentof, visited, k, 0);
    return ans;
}

/*
==========================================
Approach 2: BFS Parent Mapping + Level Order Traversal (Optimal)
------------------------------------------
💡 Idea:
- Use BFS to map parents.
- Perform BFS from target node moving through left, right, and parent.
- Track visited nodes to avoid cycles.
- Stop when distance reaches K.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
void buildParentMap(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parentof) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    parentof[root] = nullptr;
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
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

vector<int> distanceK_BFS(TreeNode* root, TreeNode* target, int K) {
    unordered_map<TreeNode*, TreeNode*> parentof;
    buildParentMap(root, parentof);

    unordered_set<TreeNode*> visited;
    queue<TreeNode*> q;
    q.push(target);
    visited.insert(target);

    int dist = 0;
    while (!q.empty()) {
        int size = (int)q.size();
        if (dist == K) break;
        dist++;

        for (int i = 0; i < size; ++i) {
            TreeNode* curr = q.front();
            q.pop();

            if (curr->left && !visited.count(curr->left)) {
                visited.insert(curr->left);
                q.push(curr->left);
            }
            if (curr->right && !visited.count(curr->right)) {
                visited.insert(curr->right);
                q.push(curr->right);
            }
            if (parentof[curr] && !visited.count(parentof[curr])) {
                visited.insert(parentof[curr]);
                q.push(parentof[curr]);
            }
        }
    }

    vector<int> result;
    while (!q.empty()) {
        result.push_back(q.front()->val);
        q.pop();
    }
    return result;
}

/* Helper function to create sample tree */
TreeNode* createSampleTree() {
    /*
           3
          / \
         5   1
        / \  / \
       6  2 0  8
         / \
        7   4
    */
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    return root;
}

/* Helper function to delete tree */
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Nodes at Distance K in Binary Tree ===\n\n";
    TreeNode* root = createSampleTree();

    function<TreeNode*(TreeNode*, int)> findNode = [&](TreeNode* node, int val) -> TreeNode* {
        if (!node) return nullptr;
        if (node->val == val) return node;
        TreeNode* leftRes = findNode(node->left, val);
        if (leftRes) return leftRes;
        return findNode(node->right, val);
    };

    TreeNode* target = findNode(root, 5);
    int K = 2;

    vector<int> ansDFS = distanceK_DFS(root, target, K);
    cout << "Distance K (DFS): ";
    for (int v : ansDFS) cout << v << " ";
    cout << "\n";

    vector<int> ansBFS = distanceK_BFS(root, target, K);
    cout << "Distance K (BFS): ";
    for (int v : ansBFS) cout << v << " ";
    cout << "\n";

    deleteTree(root);
    return 0;
}

/*
✅ Approach Overview:
- DFS with parent map is elegant and recursive.
- BFS with parent map and level order is intuitive and optimal.
- Both run in O(N) time and O(N) space.
*/
