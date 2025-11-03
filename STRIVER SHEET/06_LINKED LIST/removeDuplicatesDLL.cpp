#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Remove Duplicates from a Sorted Doubly Linked List
Link: (GFG Problem / Common Interview Question)

Problem Statement:
Given the head of a **sorted doubly linked list (DLL)**, 
remove duplicate nodes such that each element appears only once.  
Return the head of the updated list.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 <-> 2 <-> 2 <-> 3 <-> 4 <-> 4 <-> 5
Output: 1 <-> 2 <-> 3 <-> 4 <-> 5

Example 2:
Input: 10 <-> 20 <-> 20 <-> 20 <-> 30
Output: 10 <-> 20 <-> 30

Example 3:
Input: 1
Output: 1
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Definition for Doubly Linked List Node
------------------------------------------------------------ */
class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};


/* -----------------------------------------------------------
   Utility Functions
------------------------------------------------------------ */
Node* createLinkedList(vector<int> values) {
    if(values.empty()) return NULL;
    Node* head = new Node(values[0]);
    Node* curr = head;
    for(int i = 1; i < values.size(); i++) {
        Node* newNode = new Node(values[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while(curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}


/* -----------------------------------------------------------
   Approach 1: Brute Force (Using Set + Rebuild DLL)
------------------------------------------------------------
💡 Idea:
- Insert unique values into a set.
- Rebuild a new DLL from set values.

🧩 Algorithm:
1. Traverse DLL, insert all node values into a set (since sorted, will restore order).
2. Iterate over set elements, construct new DLL.
3. Return new head.

⏱ Time Complexity: O(N log N)  
📦 Space Complexity: O(N)
⚠️ Not optimal. Just educational.
------------------------------------------------------------ */
Node* removeDuplicatesBrute(Node* head) {
    if(!head) return nullptr;

    set<int> s;
    Node* curr = head;
    while(curr) {
        s.insert(curr->data);
        curr = curr->next;
    }

    Node* newHead = nullptr;
    Node* tail = nullptr;
    for(int val : s) {
        Node* newNode = new Node(val);
        if(!newHead) {
            newHead = newNode;
            tail = newHead;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    return newHead;
}


/* -----------------------------------------------------------
   Approach 2: In-place Removal (Optimal)
------------------------------------------------------------
💡 Idea:
- Since DLL is sorted, duplicates always appear consecutively.
- Traverse list once, compare current node with next.
- If duplicate → delete next node and fix links.
- Otherwise → move to next node.

🧩 Algorithm:
1. Start at head.
2. While(curr != NULL):
   - If curr->next != NULL && curr->data == curr->next->data:
        → Delete curr->next
   - Else move curr forward.
3. Return head.

⏱ Time Complexity: O(N)  
📦 Space Complexity: O(1) ✅ Best Solution
------------------------------------------------------------ */
Node* removeDuplicatesOptimal(Node* head) {
    Node* curr = head;
    while(curr != NULL) {
        if(curr->next != NULL && curr->data == curr->next->data) {
            Node* toDelete = curr->next;
            curr->next = toDelete->next;
            if(curr->next) curr->next->prev = curr;
            delete toDelete;
        }
        else {
            curr = curr->next;
        }
    }
    return head;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {1, 2, 2, 3, 4, 4, 5},     // multiple duplicates
        {10, 20, 20, 20, 30},      // chain of duplicates
        {1},                       // single node
        {1,1,1,1,1},               // all values equal
        {}                         // empty list
    };

    for(auto& values : testCases) {
        cout << "----------------------------------------\n";
        cout << "Original DLL: ";
        Node* head1 = createLinkedList(values);
        Node* head2 = createLinkedList(values);
        printList(head1);

        Node* res1 = removeDuplicatesBrute(head1);
        cout << "After Removing Duplicates (Brute): ";
        printList(res1);

        Node* res2 = removeDuplicatesOptimal(head2);
        cout << "After Removing Duplicates (Optimal): ";
        printList(res2);

        // cleanup
        delete res1;
        delete res2;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force:
         + Use set, extra space, slower.
         + Not interview-preferred but easy to grasp.  
       - Optimal (In-place):
         + O(N) time, O(1) space. 
         + Preferred for interviews.
    ------------------------------------------------------- */

    return 0;
}
