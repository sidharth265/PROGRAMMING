#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Find the Middle of a Linked List
Link: (LeetCode #876)

Problem Statement:
Given the head of a singly linked list, return the middle node of the linked list.  
If there are two middle nodes, return the **second** middle node.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5
Output: 3
Explanation: Middle node is 3.

Example 2:
Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6
Output: 4
Explanation: There are two middle nodes (3 and 4).  
By problem definition, return the second middle → 4.

Example 3:
Input: 1
Output: 1
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
        if (this->next != NULL) {
            delete next;
            this->next = NULL;
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
   Approach 1: Count Nodes (Brute Force)
------------------------------------------------------------
💡 Idea:
- Traverse once to count total nodes.
- Traverse again to (n/2)-th index.
- Return that node.

🧩 Algorithm:
1. Traverse list and count total nodes (n).
2. Middle index = n/2 (integer division).
   (Handles even-length case → picks second middle).
3. Traverse again to middle index and return that node.

⏱ Time Complexity: O(N) + O(N) = O(N)
📦 Space Complexity: O(1)
------------------------------------------------------------ */
ListNode* middleNodeBrute(ListNode* head) {
    int count = 0;
    ListNode* curr = head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    int mid = count / 2;
    curr = head;
    for (int i = 0; i < mid; i++) {
        curr = curr->next;
    }
    return curr;
}


/* -----------------------------------------------------------
   Approach 2: Fast & Slow Pointers (Optimal)
------------------------------------------------------------
💡 Idea:
- Use two pointers: slow and fast.
- Move slow 1 step, fast 2 steps at a time.
- When fast reaches end, slow is at middle.
- Naturally handles even case (returning second middle).

🧩 Algorithm:
1. Initialize slow=head, fast=head.
2. While fast and fast->next exist:
   - slow = slow->next
   - fast = fast->next->next
3. When loop ends, slow will be at middle.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Best
------------------------------------------------------------ */
ListNode* middleNodeOptimal(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {1,2,3,4,5},      // Odd length
        {1,2,3,4,5,6},    // Even length
        {1}               // Single node
    };

    for (auto& values : testCases) {
        cout << "-------------------------------------\n";
        cout << "Original List: ";
        ListNode* head1 = createLinkedList(values);
        ListNode* head2 = createLinkedList(values);
        printList(head1);

        // Brute Force
        ListNode* mid1 = middleNodeBrute(head1);
        cout << "Middle (Brute Force): " << mid1->data << endl;

        // Optimal
        ListNode* mid2 = middleNodeOptimal(head2);
        cout << "Middle (Optimal Fast-Slow): " << mid2->data << endl;

        // Cleanup
        delete head1;
        delete head2;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force:
         + Two passes (count + traverse).
         + Easy to understand.
       - Fast & Slow Pointers:
         + One pass only.
         + O(1) extra space.
         + Recommended for interviews.
    ------------------------------------------------------- */
    return 0;
}
