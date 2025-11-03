#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Flatten a Linked List with Next and Bottom Pointers
Link: (GFG / Common Interview Problem)

Problem Statement:
You are given a linked list where every node has two pointers:
- `next`: points to the next node in the main list
- `bottom`: points to a sorted linked list

The task is to flatten the entire list so that all nodes appear
in a **single sorted linked list**, using the `bottom` pointers.  
The `next` pointers of all nodes should be set to NULL.

---------------------------------------------------------------
Examples:

Example:
Input:
5 -> 10 -> 19 -> 28
|    |     |     |
7    20    22    35
|          |     |
8          50    40
|                |
30               45

Output:
5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 30 -> 35 -> 40 -> 45 -> 50

Explanation:
All sub-lists are merged into one single sorted list.
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Definition for Node
------------------------------------------------------------ */
class Node {
public:
    int data;
    Node* next;
    Node* bottom;

    Node(int val) : data(val), next(nullptr), bottom(nullptr) {}
    ~Node() {
        if (this->next != NULL) {
            delete next;
            this->next = NULL;
            this->bottom = NULL;
        }
    }
};


/* -----------------------------------------------------------
   Utility Functions
------------------------------------------------------------ */
void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->bottom;
    }
    cout << endl;
}


/* -----------------------------------------------------------
   Approach 1: Using Extra Array
------------------------------------------------------------
💡 Idea:
- Traverse all nodes in main and bottom lists.
- Push them into an array.
- Sort the array.
- Create a new flattened list.

🧩 Algorithm:
1. Traverse list using next and bottom.
2. Store values in array.
3. Sort array.
4. Build new flattened linked list.

⏱ Time Complexity: O(N log N)
📦 Space Complexity: O(N)
------------------------------------------------------------ */
Node* flattenArray(Node* root) {
    vector<int> arr;
    Node* head = root;

    while (head) {
        Node* curr = head;
        while (curr) {
            arr.push_back(curr->data);
            curr = curr->bottom;
        }
        head = head->next;
    }

    sort(arr.begin(), arr.end());

    Node* dummy = new Node(-1);
    Node* curr = dummy;
    for (int val : arr) {
        curr->bottom = new Node(val);
        curr = curr->bottom;
    }
    return dummy->bottom;
}


/* -----------------------------------------------------------
   Approach 2: Recursive Merge (Optimal)
------------------------------------------------------------
💡 Idea:
- Flatten the list recursively by merging sublists.
- At each step, merge `root` and `flatten(root->next)`.

🧩 Algorithm:
1. Base Case: if root==NULL or root->next==NULL return root.
2. Recursively flatten the rest: head2 = flatten(root->next).
3. Merge two sorted lists (root and head2) by bottom pointers.
4. Return merged head.

⏱ Time Complexity: O(N) [since merging all nodes]
📦 Space Complexity: O(N) recursion stack
------------------------------------------------------------ */
Node* mergeTwoList(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;

    Node* result;

    if (a->data < b->data) {
        result = a;
        result->bottom = mergeTwoList(a->bottom, b);
    } else {
        result = b;
        result->bottom = mergeTwoList(a, b->bottom);
    }
    result->next = NULL;  // ensure next=NULL in final list
    return result;
}

Node* flattenMerge(Node* root) {
    if (!root || !root->next) return root;
    root->next = flattenMerge(root->next);
    return mergeTwoList(root, root->next);
}


/* -----------------------------------------------------------
   Approach 3: Using Min-Heap (Priority Queue)
------------------------------------------------------------
💡 Idea:
- Use a min-heap to always pick the smallest among all heads.
- Insert bottom nodes step by step into heap.

🧩 Algorithm:
1. Create min-heap of nodes (data, pointer).
2. Insert all top-level nodes into heap.
3. While heap not empty:
   - Pop smallest node.
   - Append to result list.
   - If node->bottom exists, push into heap.
4. Return flattened list.

⏱ Time Complexity: O(N log K)
📦 Space Complexity: O(K) (where K = no. of sub-lists)
------------------------------------------------------------ */
struct Comp {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data;
    }
};

Node* flattenHeap(Node* root) {
    if (!root) return nullptr;

    priority_queue<Node*, vector<Node*>, Comp> pq;

    // Step 1: Push all top nodes into heap
    Node* head = root;
    while (head) {
        pq.push(head);
        head = head->next;
    }

    Node dummy(-1);
    Node* tail = &dummy;

    // Step 2: Process heap
    while (!pq.empty()) {
        Node* curr = pq.top();
        pq.pop();

        tail->bottom = curr;
        tail = tail->bottom;

        if (curr->bottom) pq.push(curr->bottom);

        // Ensure next=NULL for safety
        curr->next = NULL;
    }

    return dummy.bottom;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    /*
        Building the following structure:
        5 -> 10 -> 19 -> 28
        |    |     |     |
        7    20    22    35
        |          |     |
        8          50    40
        |                |
        30               45
    */
    Node* head = new Node(5);
    head->next = new Node(10);
    head->next->next = new Node(19);
    head->next->next->next = new Node(28);

    head->bottom = new Node(7);
    head->bottom->bottom = new Node(8);
    head->bottom->bottom->bottom = new Node(30);

    head->next->bottom = new Node(20);

    head->next->next->bottom = new Node(22);
    head->next->next->bottom->bottom = new Node(50);

    head->next->next->next->bottom = new Node(35);
    head->next->next->next->bottom->bottom = new Node(40);
    head->next->next->next->bottom->bottom->bottom = new Node(45);


    cout << "Flatten using Array: ";
    Node* flat1 = flattenArray(head);
    printList(flat1);

    cout << "Flatten using Recursive Merge: ";
    Node* flat2 = flattenMerge(head);
    printList(flat2);

    cout << "Flatten using Min-Heap: ";
    Node* flat3 = flattenHeap(head);
    printList(flat3);

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Array Method: Easy to implement, O(N log N) time, O(N) space.
       - Recursive Merge: Clean, O(N), recursion stack O(N).
       - Min-Heap: Best for large K (no. of sublists), O(N log K). 
         Popular interview solution.
    ------------------------------------------------------- */

    return 0;
}
