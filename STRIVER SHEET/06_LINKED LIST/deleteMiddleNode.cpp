#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Delete the Middle Node of a Linked List
Link: (LeetCode #2095)

Problem Statement:
You are given the head of a singly linked list.  
Delete the middle node of the linked list and return the head.  

- If the linked list has only one node, return NULL.  
- The middle node is at position ⌊n/2⌋ (0-based index).  

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5
Output: 1 -> 2 -> 4 -> 5
Explanation: Middle node is 3 (at index 2), so it is removed.

Example 2:
Input: 1 -> 2 -> 3 -> 4
Output: 1 -> 2 -> 4
Explanation: Middle node is 3 (at index 2 using floor division).

Example 3:
Input: 1
Output: NULL
Explanation: Only one node, so deletion removes it entirely.
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
        if (this->next != nullptr) {
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
   Approach 1: Count + Delete (Brute Force)
------------------------------------------------------------
💡 Idea:
- First, count total nodes.
- Find index of middle = count/2.
- Traverse again to (middle-1) node, delete middle.

🧩 Algorithm:
1. Traverse list to count nodes (n).
2. If n == 1, return NULL.
3. Find middle index = n/2.
4. Traverse to node before middle.
5. Delete middle node, relink.

⏱ Time Complexity: O(N) + O(N) ≈ O(N)
📦 Space Complexity: O(1)
------------------------------------------------------------ */
ListNode* deleteMiddleBrute(ListNode* head) {
    if (!head || !head->next) return nullptr;
    
    int n = 0;
    ListNode* curr = head;
    while (curr) {
        n++;
        curr = curr->next;
    }
    int mid = n / 2;

    curr = head;
    for (int i = 0; i < mid - 1; i++) {
        curr = curr->next;
    }
    ListNode* temp = curr->next;
    curr->next = temp->next;
    temp->next = nullptr;
    delete temp;

    return head;
}


/* -----------------------------------------------------------
   Approach 2: Slow-Fast Pointers (Optimal)
------------------------------------------------------------
💡 Idea:
- Use slow and fast pointers.
- Move `fast` two steps, `slow` one step.
- When `fast` reaches end, `slow` will be before middle node.
- Delete node after `slow`.

🧩 Algorithm:
1. Initialize `slow=head`, `fast=head->next->next`.
2. Iterate until fast null:
    - Move fast → fast->next->next
    - Move slow → slow->next
3. Remove slow->next (middle).
4. Return head.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Best
------------------------------------------------------------ */
ListNode* deleteMiddleOptimal(ListNode* head) {
    if (!head || !head->next) return nullptr;

    ListNode* slow = head;
    ListNode* fast = head->next->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            fast = fast->next;
            slow = slow->next;
        }
    }
    
    // Delete middle node
    ListNode* temp = slow->next;
    slow->next = temp->next;
    temp->next = nullptr;
    delete temp;

    return head;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4},
        {1}
    };

    for (auto& values : testCases) {
        cout << "-------------------------------------\n";
        cout << "Original List: ";
        ListNode* head1 = createLinkedList(values);
        ListNode* head2 = createLinkedList(values);
        printList(head1);

        // Brute Force
        head1 = deleteMiddleBrute(head1);
        cout << "After Deleting Middle (Brute): ";
        printList(head1);

        // Optimal Slow-Fast
        head2 = deleteMiddleOptimal(head2);
        cout << "After Deleting Middle (Optimal): ";
        printList(head2);

        delete head1;
        delete head2;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force: Requires two passes, simpler to think about.
       - Optimal Two-pointer: Single pass, O(1) space. Best choice.
    ------------------------------------------------------- */
    return 0;
}
