#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Binary Tree Right Side View
 Problem Link: https://leetcode.com/problems/binary-tree-right-side-view/

 Problem Statement:
 -----------------
 Given the root of a binary tree, imagine yourself standing on the right side
 of it, return the values of the nodes you can see ordered from top to bottom.

 Example:
 Input: root = [1,2,3,null,5,null,4]
        1
       / \
      2   3
       \    \
        5    4
 Output: [1,3,4]
 Explanation: From the right side, nodes visible are 1, then 3, then 4.

 Constraints:
 - The number of nodes in the tree is in the range [0, 100]
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
 Approach 1: Brute Force - Height Calculation + Recursive State Tracking
-----------------------------------------
💡 Idea:
Calculate the height of the tree, then create a vector of that size initialized 
with sentinel values. Perform a DFS starting from the root, traversing right subtree 
before left subtree to prefer right side nodes. Whenever the first node at a depth
(i.e., level) is visited, record its value.

🧩 Algorithm:
1. Calculate tree height.
2. Initialize a vector 'result' sized to the height with sentinel value (-101).
3. Traverse tree in preorder with right subtree first.
4. For each node at depth i, if result[i] is still sentinel, assign node’s value.
5. After traversal, 'result' contains right side view nodes.

⏱ Time Complexity: O(N), where N is number of nodes.
📦 Space Complexity: O(H) recursion stack + O(H) result vector.
*/
int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

void generate(TreeNode* root, vector<int>& result, int i) {
    if (!root) return;
    if (result[i] == -101) result[i] = root->val;
    generate(root->right, result, i + 1);
    generate(root->left, result, i + 1);
}

vector<int> rightSideView(TreeNode* root) {
    int n = height(root);
    vector<int> result(n, -101);
    generate(root, result, 0);
    return result;
}

/* 
==========================================
 Approach 2: Better - DFS with Depth Tracking Without Height Calculation
-----------------------------------------
💡 Idea:
Traverse the tree root-first, right subtree before left, and keep track of depth.
If the current depth equals the size of the result vector, this is the first node seen
at this depth, so add it to the result.

🧩 Algorithm:
1. Initialize empty vector 'result'.
2. Traverse recursively, passing current depth.
3. If depth equals size of 'result', append node value.
4. Traverse right subtree then left subtree to prioritize right side nodes.
5. Return 'result'.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(H) recursion + O(H) result
*/
void dfs(TreeNode* root, int depth, vector<int>& result) {
    if (!root) return;
    if (depth == (int)result.size())
        result.push_back(root->val);
    dfs(root->right, depth + 1, result);
    dfs(root->left, depth + 1, result);
}

vector<int> rightSideViewBetter(TreeNode* root) {
    vector<int> result;
    dfs(root, 0, result);
    return result;
}

/* 
==========================================
 Approach 3: Optimal - Iterative Level Order (BFS) Traversal
-----------------------------------------
💡 Idea:
Use BFS level order traversal. At each level, add the last node's value in that level 
to the result (the rightmost node).

🧩 Algorithm:
1. Use a queue and enqueue the root.
2. For each level:
   - Traverse all nodes in the level.
   - Add the value of the last node to 'result'.
   - Enqueue the left and right children of all nodes.
3. Return 'result'.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
vector<int> rightSideViewOptimal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = (int)q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            if (i == size - 1)
                result.push_back(node->val);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}


/* Helper function to create sample trees */
TreeNode* createSampleTree() {
    /*
        1
       / \
      2   3
       \    \
        5    4
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->right = new TreeNode(5);
    root->right = new TreeNode(3);
    root->right->right = new TreeNode(4);
    return root;
}

/* Helper function to delete tree and free memory */
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Binary Tree Right Side View Problem ===\n\n";

    TreeNode* tree = createSampleTree();

    vector<int> res1 = rightSideView(tree);
    cout << "Approach 1 (Brute Force) result: ";
    for (int v : res1) cout << v << " ";
    cout << "\n";

    vector<int> res2 = rightSideViewBetter(tree);
    cout << "Approach 2 (Better DFS) result: ";
    for (int v : res2) cout << v << " ";
    cout << "\n";

    vector<int> res3 = rightSideViewOptimal(tree);
    cout << "Approach 3 (Optimal BFS) result: ";
    for (int v : res3) cout << v << " ";
    cout << "\n";

    deleteTree(tree);
    return 0;
}

/*
✅ Approach Overview:
- Approach 1: Uses height calculation then stores first visible node at each level via DFS (O(N)).
- Approach 2: DFS without explicit height, appends first node at each depth with right subtree priority.
- Approach 3: BFS level order traversal taking last element at each level, simplest and optimal for iterative implementation.
All three have O(N) time and O(H) space complexity, but BFS is often most intuitive.
*/
