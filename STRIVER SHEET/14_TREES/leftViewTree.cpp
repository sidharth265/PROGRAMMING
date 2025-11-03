#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Binary Tree Left View
 Problem Link: https://practice.geeksforgeeks.org/problems/left-view-of-binary-tree/

 Problem Statement:
 -----------------
 Given a binary tree, return the values of the nodes visible 
 when the tree is viewed from the left side ordered from top to bottom.

 Example:
 Input:
        1
       /  \
      2    3
       \    \
        4    5

 Output: 1 2 4
 Explanation: Nodes visible from the left side are 1, 2, and 4.

 Constraints:
 - Number of nodes in the tree: 1 to 10^5
 - Node values range: 1 to 10^5
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
 Approach 1: Brute Force - Use Height + Levelwise DFS with Tracking Visited Levels
-----------------------------------------
💡 Idea:
First calculate tree height, then for each level, traverse tree to find the first node encountered at that level.

🧩 Algorithm:
1. Calculate height of tree.
2. For each level from 1 to height:
   - Perform DFS, passing current level.
   - If first node found at level, record and stop searching deeper for that level.
3. Continue for all levels.
4. Collect recorded nodes in a vector.

⏱ Time Complexity: O(N^2) in worst case (for skewed trees).
📦 Space Complexity: O(H) recursion + O(H) result.
*/
int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

bool dfsFirstNodeAtLevel(Node* root, int level, int& value, bool& found) {
    if (!root) return false;
    if (level == 1 && !found) {
        value = root->data;
        found = true;
        return true;
    }
    if (level > 1) {
        if (dfsFirstNodeAtLevel(root->left, level - 1, value, found)) return true;
        if (dfsFirstNodeAtLevel(root->right, level - 1, value, found)) return true;
    }
    return false;
}

vector<int> leftViewBruteForce(Node* root) {
    vector<int> result;
    int h = height(root);
    for (int level = 1; level <= h; ++level) {
        int val = -1;
        bool found = false;
        dfsFirstNodeAtLevel(root, level, val, found);
        if (found) result.push_back(val);
    }
    return result;
}

/* 
==========================================
 Approach 2: Better - DFS with Depth Tracking and Result Vector
-----------------------------------------
💡 Idea:
DFS traversal prefers left child first, passes current depth. 
If current depth equals the size of result vector, it means first node at that depth, append its value.

🧩 Algorithm:
1. Initialize empty vector for result.
2. DFS traverse tree passing depth starting at 0.
3. If depth == result.size(), it’s first node at that depth to visit, add to result.
4. Traverse left child first, then right child.
5. return result.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(H) recursion + O(H) result.
*/
void dfsLeftView(Node* root, int depth, vector<int>& result) {
    if (!root) return;
    if (depth == (int)result.size()) 
        result.push_back(root->data);
    dfsLeftView(root->left, depth + 1, result);
    dfsLeftView(root->right, depth + 1, result);
}

vector<int> leftViewBetter(Node* root) {
    vector<int> result;
    dfsLeftView(root, 0, result);
    return result;
}

/* 
==========================================
 Approach 3: Optimal - Iterative Level Order (BFS) Traversal
-----------------------------------------
💡 Idea:
Perform BFS level order traversal. For each level, add the first node's value to result.

🧩 Algorithm:
1. Initialize queue with root.
2. While queue not empty:
   - Track number of nodes at current level.
   - Pop nodes one by one.
   - Add first popped node value of level to result.
   - Enqueue left and right children.
3. Return result.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
vector<int> leftViewOptimal(Node* root) {
    vector<int> result;
    if (!root) return result;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int n = (int)q.size();
        for (int i = 0; i < n; ++i) {
            Node* temp = q.front();
            q.pop();
            if (i == 0) result.push_back(temp->data);

            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }
    return result;
}

/* Helper function to create a sample tree */
Node* createSampleTree() {
    /*
           1
          /  \
         2    3
          \    \
           4    5
    */
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->right->right = new Node(5);
    return root;
}

/* Helper function to delete tree */
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Binary Tree Left View Problem ===\n\n";

    Node* tree = createSampleTree();

    vector<int> res1 = leftViewBruteForce(tree);
    cout << "Brute Force Result: ";
    for (int v : res1) cout << v << " ";
    cout << "\n";

    vector<int> res2 = leftViewBetter(tree);
    cout << "Better DFS Result: ";
    for (int v : res2) cout << v << " ";
    cout << "\n";

    vector<int> res3 = leftViewOptimal(tree);
    cout << "Optimal BFS Result: ";
    for (int v : res3) cout << v << " ";
    cout << "\n";

    deleteTree(tree);
    return 0;
}

/*
✅ Approach Overview:
- Brute Force: Level-wise DFS searching first node per level (O(N^2)) worst case.
- Better DFS: Preorder traversal with depth tracking to capture first visited node per depth.
- Optimal BFS: Level order traversal, adding first node at each level (O(N)) straightforward and efficient.
Recommend Approach 3 for optimal clarity and performance.
*/
