#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Delete All Occurrences of a Key in a Doubly Linked List
Link: (Similar problem on GFG)

Problem Statement:
Given a head reference of a doubly linked list and a key `k`, 
delete all nodes from the list whose data is equal to `k`.  
Return the updated head of the list.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 <-> 2 <-> 3 <-> 4 <-> 2 <-> 5 <-> 2 , key = 2
Output: 1 <-> 3 <-> 4 <-> 5
Explanation: All `2`s are removed from DLL.

Example 2:
Input: 2 <-> 2 <-> 2 , key = 2
Output: (empty list)
Explanation: All nodes deleted.

Example 3:
Input: 7 <-> 1 <-> 9 , key = 3
Output: 7 <-> 1 <-> 9
Explanation: Key not found, list unchanged.
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Definition for DLL Node
------------------------------------------------------------ */
class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }

    ~Node() {
        if (this->next) {
            delete next;
            this->next = nullptr;
        }
    }
};


/* -----------------------------------------------------------
   Utility Functions
------------------------------------------------------------ */
Node* createLinkedList(vector<int> values) {
    if (values.empty()) return nullptr;
    Node* head = new Node(values[0]);
    Node* curr = head;
    for (int i = 1; i < values.size(); i++) {
        Node* newNode = new Node(values[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }
    return head;
}

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}


/* -----------------------------------------------------------
   Approach 1: Brute Force (Rebuild New List)
------------------------------------------------------------
💡 Idea:
- Traverse the DLL, copy only nodes whose value != k.
- Build a new DLL excluding nodes equal to k.

🧩 Algorithm:
1. Initialize dummy node for new list.
2. Traverse original list.
3. For every node != k, append it to new list.
4. Delete original list to free memory.
5. Return head of new list.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N) (new list created)
------------------------------------------------------------ */
Node* deleteOccurrencesBrute(Node* head, int k) {
    if (!head) return nullptr;
    Node* newHead = nullptr;
    Node* tail = nullptr;

    Node* curr = head;
    while (curr) {
        if (curr->data != k) {
            Node* newNode = new Node(curr->data);
            if (!newHead) {
                newHead = newNode;
                tail = newHead;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
        curr = curr->next;
    }
    return newHead;
}


/* -----------------------------------------------------------
   Approach 2: In-place Deletion (Optimal)
------------------------------------------------------------
💡 Idea:
- Directly traverse and delete all nodes with data == k.
- Handle head separately if head contains the key.

🧩 Algorithm:
1. While head and head->data == k, shift head forward and delete old head.
2. Traverse rest of list:
   - If current->data == k, delete it and adjust prev/next pointers.
   - Else move forward.
3. Return updated head.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Best Solution
------------------------------------------------------------ */
Node* deleteOccurrencesOptimal(Node* head, int k) {
    if (!head) return head;

    // Step 1: Delete occurrences at head
    while (head && head->data == k) {
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        temp->next = nullptr;
        delete temp;
    }

    // Step 2: Traverse and delete from middle/end
    Node* curr = head;
    while (curr) {
        if (curr->data == k) {
            Node* temp = curr;
            curr = curr->next;
            if (curr) curr->prev = temp->prev;
            if (temp->prev) temp->prev->next = curr;
            temp->next = nullptr;
            temp->prev = nullptr;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
    return head;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<int> values = {1, 2, 3, 4, 2, 5, 2};
    int k = 2;

    Node* head1 = createLinkedList(values);
    Node* head2 = createLinkedList(values);

    cout << "Original List: ";
    printList(head1);

    // Brute Force
    Node* result1 = deleteOccurrencesBrute(head1, k);
    cout << "After deleting " << k << " (Brute Force): ";
    printList(result1);

    // Optimal
    Node* result2 = deleteOccurrencesOptimal(head2, k);
    cout << "After deleting " << k << " (Optimal in-place): ";
    printList(result2);

    // Cleanup
    delete result1;
    delete result2;

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force: Easy, ideal for beginners, but uses O(N) space.
       - Optimal In-place: No extra space, efficient, 
         recommended for interviews.
    ------------------------------------------------------- */
    return 0;
}
