#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Serialize and Deserialize Binary Tree
 Problem Link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

 Problem Statement:
 -----------------
 Design an algorithm to serialize and deserialize a binary tree. Serialization is converting a tree to a string, and deserialization is converting the string back to the original tree.

 Example:
 Input:        1
              / \
             2   3
                / \
               4   5

 serialize(root) => "1,2,3,#,#,4,5,#,#,#,#,"
 deserialize("1,2,3,#,#,4,5,#,#,#,#,") => reconstructs the same tree

 Constraints:
 - Number of nodes in the tree is in the range [0, 10^4]
 - Node values are integers
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
 Algorithm: Level-Order Serialization/Deserialization

 1. **Serialization**:
    - Use BFS (level order traversal).
    - For each node, add its value as a string to the result. If null, add a "#" as a marker.
    - Move through the tree by queue and include left/right children (nulls as "#").
    - String is comma-separated.

 2. **Deserialization**:
    - Use a stringstream to break the serialized string by commas.
    - Reconstruct the root from the first token.
    - Use BFS: for each node, retrieve tokens for left/right children, attach as children if not "#".
    - Push non-null children to the queue for further expansion.
 
 ⏱ Time Complexity: O(N) for both serialization and deserialization
 📦 Space Complexity: O(N) for the queue and resultant string

==========================================
*/

// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    string data = "";
    if (!root) return data;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            TreeNode* temp = q.front();
            q.pop();
            string add = (temp) ? to_string(temp->val) : "#";
            data += add + ",";
            if (!temp) continue;
            q.push(temp->left);
            q.push(temp->right);
        }
    }
    return data;
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    if (data.size() == 0) return nullptr;
    stringstream s(data);
    string str;
    getline(s, str, ',');
    TreeNode* root = new TreeNode(stoi(str));
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            TreeNode* temp = q.front(); q.pop();

            getline(s, str, ',');
            if (str != "#") {
                TreeNode* leftNode = new TreeNode(stoi(str));
                temp->left = leftNode;
                q.push(leftNode);
            }

            getline(s, str, ',');
            if (str != "#") {
                TreeNode* rightNode = new TreeNode(stoi(str));
                temp->right = rightNode;
                q.push(rightNode);
            }
        }
    }
    return root;
}

/* Helper: Inorder traversal to verify deserialization */
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

/* ========= MAIN FUNCTION ========= */
int main() {
    // Construct test tree:   1
    //                       / \
    //                      2   3
    //                         / \
    //                        4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    string data = serialize(root);
    cout << "Serialized: " << data << "\n";

    TreeNode* newRoot = deserialize(data);
    cout << "Deserialized inorder: ";
    printInorder(newRoot); // Should print 2 1 4 3 5
    cout << "\n";

    // Memory cleanup omitted for brevity
    return 0;
}

/*
✅ Approach Overview:
- Serializes the tree with level-order and '#' for nulls.
- Deserializes by reconstructing the tree in level-order.
- Both processes are O(N) time and space.
- Industry-standard and interview-approved method.
*/
