#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Reverse a Linked List
Link: (LeetCode #206)

Problem Statement:
Given the head of a singly linked list, reverse the list, 
and return the new head.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5
Output: 5 -> 4 -> 3 -> 2 -> 1

Example 2:
Input: 1
Output: 1

Example 3:
Input: NULL
Output: NULL
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
    ListNode* curr = head;
    for (int i = 1; i < values.size(); i++) {
        curr->next = new ListNode(values[i]);
        curr = curr->next;
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
   Approach 1: Iterative (Loop)
------------------------------------------------------------
💡 Idea:
- Keep track of three pointers: prev, curr, next.
- Iteratively reverse each link by redirecting next pointer.
- Finally return prev as new head.

🧩 Algorithm:
1. Initialize prev = NULL, curr = head.
2. While curr != NULL:
   - Save next = curr->next
   - Set curr->next = prev
   - Move prev = curr, curr = next
3. Return prev (new head).

⏱ Time Complexity: O(N)  
📦 Space Complexity: O(1)
------------------------------------------------------------ */
ListNode* reverseListIterative(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;

    while (curr) {
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}


/* -----------------------------------------------------------
   Approach 2: Recursive
------------------------------------------------------------
💡 Idea:
- Reverse the rest of the list recursively.
- Once reversed, fix the current node’s next pointer.

🧩 Algorithm:
1. Base case: if head == NULL or only one node → return head.
2. Recursively reverse the rest of the list.
3. Update head->next->next = head.
4. Set head->next = NULL.
5. Return new head of reversed list.

⏱ Time Complexity: O(N)  
📦 Space Complexity: O(N) (recursion stack)
------------------------------------------------------------ */
ListNode* reverseListRecursive(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* newHead = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {1, 2, 3, 4, 5}, // full list
        {1},             // single node
        {}               // empty list
    };

    for (auto& values : testCases) {
        cout << "----------------------------------------\n";
        cout << "Original List: ";
        ListNode* head1 = createLinkedList(values);
        ListNode* head2 = createLinkedList(values);
        printList(head1);

        ListNode* rev1 = reverseListIterative(head1);
        cout << "Reversed (Iterative): ";
        printList(rev1);

        ListNode* rev2 = reverseListRecursive(head2);
        cout << "Reversed (Recursive): ";
        printList(rev2);

        delete rev1;
        delete rev2;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Iterative (Preferred for Interviews):
         + One-pass O(N), O(1) extra space.
       - Recursive:
         + Shorter/elegant.
         + Uses O(N) recursion stack.
    ------------------------------------------------------- */
    return 0;
}
