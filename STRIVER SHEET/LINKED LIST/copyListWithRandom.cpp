#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Clone a Linked List with Next and Random Pointers
Link: (LeetCode #138 / GFG variant)

Problem Statement:
You are given a linked list where each node has two pointers:
- next: points to the next node in the list
- random: points to a random node in the list (may be NULL)

Your task is to create a **deep copy** of the linked list.  
Return the head of the cloned linked list.  

The new list should be a completely independent copy, 
with both 'next' and 'random' links set correctly.

---------------------------------------------------------------
Examples:

Example 1:
Input:
Original List:
1 -> 2 -> 3 -> 4 -> 5
Random Links: (1->3), (2->1), (3->2), (4->3), (5->NULL)

Output:
Cloned List should have same structure with independent nodes.

---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Definition for Node
------------------------------------------------------------ */
struct Node {
    int data;
    Node *next;
    Node *random;

    Node(int x) {
        data = x;
        next = nullptr;
        random = nullptr;
    }
};


/* -----------------------------------------------------------
   Utility Functions
------------------------------------------------------------ */
void printList(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data;
        if (curr->random) cout << "(" << curr->random->data << ")";
        else cout << "(NULL)";
        cout << " -> ";
        curr = curr->next;
    }
    cout << "NULL\n";
}


/* -----------------------------------------------------------
   Approach 1: Using Hash Map (Brute Force)
------------------------------------------------------------
💡 Idea:
- Use a hash map to store mapping from original node → cloned node.
- Traverse list once to create cloned nodes.
- Traverse again to set up `next` and `random` pointers properly.

🧩 Algorithm:
1. Create empty hash map.
2. First pass: For each original node, create a new node and store mapping.
3. Second pass: For each original node, set:
   newNode->next = map[orig->next]
   newNode->random = map[orig->random]
4. Return map[head].

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
------------------------------------------------------------ */
Node* cloneLinkedListHashing(Node* head) {
    if (!head) return nullptr;
    unordered_map<Node*, Node*> mp;

    Node* curr = head;
    while (curr) {
        mp[curr] = new Node(curr->data);
        curr = curr->next;
    }

    curr = head;
    while (curr) {
        mp[curr]->next = mp[curr->next];
        mp[curr]->random = mp[curr->random];
        curr = curr->next;
    }
    return mp[head];
}


/* -----------------------------------------------------------
   Approach 2: Interleaving (Optimal, O(1) Space)
------------------------------------------------------------
💡 Idea:
- Copy each node and insert it right after the original node.
- Update the random pointers of the clones.
- Separate the original and copied lists.

🧩 Algorithm:
1. Traverse original list. For every node:
   Create a cloned node and insert immediately after it.
   (So list looks like orig1 -> clone1 -> orig2 -> clone2 ...)
2. Traverse again to fix random pointers: clone->random = orig->random->next
3. Traverse again to restore original and extract clone list separately.
4. Return head of cloned list.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1)  ✅ Best Approach
------------------------------------------------------------ */
Node* cloneLinkedListOptimal(Node* head) {
    if (!head) return nullptr;

    Node* curr = head;
    // Step 1: Interleave cloned nodes
    while (curr) {
        Node* newNode = new Node(curr->data);
        newNode->next = curr->next;
        curr->next = newNode;
        curr = newNode->next;
    }

    // Step 2: Setup random pointers
    curr = head;
    while (curr) {
        if (curr->random) curr->next->random = curr->random->next;
        curr = curr->next->next;
    }

    // Step 3: Separate cloned list
    Node* dummy = new Node(-1);
    Node* copyIter = dummy;
    curr = head;
    while (curr) {
        Node* clone = curr->next;
        curr->next = clone->next;
        copyIter->next = clone;
        copyIter = clone;
        curr = curr->next;
    }

    return dummy->next;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    // Creating original linked list
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    // Setting random pointers
    head->random = head->next->next;             // 1 -> 3
    head->next->random = head;                   // 2 -> 1
    head->next->next->random = head->next;       // 3 -> 2
    head->next->next->next->random = head->next->next;  // 4 -> 3
    head->next->next->next->next->random = nullptr;     // 5 -> NULL

    cout << "Original List (with randoms):\n";
    printList(head);

    // Hashmap Approach
    Node* clone1 = cloneLinkedListHashing(head);
    cout << "Cloned List (Hashing):\n";
    printList(clone1);

    // Optimal Approach
    Node* clone2 = cloneLinkedListOptimal(head);
    cout << "Cloned List (Optimal O(1) Space):\n";
    printList(clone2);


    /* -------------------------------------------------------
       ✅ Approach Overview
       - Hashing: Simple and clear logic, O(N) extra space.
       - Interleaving Optimal: No extra space, faster, best for interviews.
    ------------------------------------------------------- */

    return 0;
}
