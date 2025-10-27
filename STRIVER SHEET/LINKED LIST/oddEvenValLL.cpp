#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Rearrange Linked List by Odd/Even Node Values
Link: (GFG / Amazon Interview Variant)

Problem Statement:
Given the head of a singly linked list, rearrange the list so that:
- All nodes with **even values** appear first
- Followed by all nodes with **odd values**,
while preserving their **original relative order**.

➤ NOTE: This is NOT based on index parity (like Odd-Even Linked List on LeetCode),
but based on the actual numeric value of the nodes.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6
Output: 2 -> 4 -> 6 -> 1 -> 3 -> 5
Explanation: Even values first, then odd values, maintaining relative order.

Example 2:
Input: 7 -> 9 -> 2 -> 4 -> 5
Output: 2 -> 4 -> 7 -> 9 -> 5

Example 3:
Input: 1 -> 3 -> 5
Output: 1 -> 3 -> 5
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Definition for ListNode
------------------------------------------------------------ */
class ListNode {
public:
    int data;
    ListNode* next;
    ListNode(int val) : data(val), next(nullptr) {}
    ~ListNode() {
        if (this->next) {
            delete next;
            this->next = nullptr;
        }
    }
};


/* -----------------------------------------------------------
   Utility Functions
------------------------------------------------------------ */
ListNode* createLinkedList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}


/* -----------------------------------------------------------
   Approach 1: Using Two Dummy Lists (Optimal)
------------------------------------------------------------
💡 Idea:
- Maintain two separate lists: one for even values, one for odd values.
- Traverse the original list once:
   - If value is even → append to evenTail
   - Else → append to oddTail
- Connect even list tail → odd list head.
- Return even list head.

🧩 Algorithm:
1. Create dummy nodes evenHead, oddHead.
2. For each node:
   - Detach it and append to even/odd list accordingly.
3. Connect evenTail->next = oddHead->next.
4. Return evenHead->next as new head.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1)
------------------------------------------------------------ */
ListNode* rearrangeByValue(ListNode* head) {
    if (!head) return nullptr;

    ListNode* evenHead = new ListNode(-1);
    ListNode* oddHead = new ListNode(-1);
    ListNode* evenTail = evenHead;
    ListNode* oddTail = oddHead;

    ListNode* curr = head;
    while (curr) {
        ListNode* temp = curr;
        curr = curr->next;
        temp->next = nullptr;

        if (temp->data % 2 == 0) {
            evenTail->next = temp;
            evenTail = temp;
        } else {
            oddTail->next = temp;
            oddTail = temp;
        }
    }

    // Attach odd list after even list
    evenTail->next = oddHead->next;

    ListNode* newHead = evenHead->next;

    // Delete dummy nodes
    delete evenHead;
    delete oddHead;

    return newHead;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {1, 2, 3, 4, 5, 6},   // mix of odd and even
        {7, 9, 2, 4, 5},      // evens in middle
        {1, 3, 5},            // all odd
        {2, 4, 6},            // all even
        {}                    // empty list
    };

    for (auto& values : testCases) {
        cout << "--------------------------------------\n";
        cout << "Original List: ";
        ListNode* head = createLinkedList(values);
        printList(head);

        ListNode* rearranged = rearrangeByValue(head);
        cout << "Rearranged (Even first, then Odd): ";
        printList(rearranged);

        delete rearranged;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Dummy two-list approach:
         + Traverse once.
         + Maintain stability (order preserved).
         + O(1) extra space.
       - This is the standard and most optimal solution asked in interviews.
    ------------------------------------------------------- */
    return 0;
}
