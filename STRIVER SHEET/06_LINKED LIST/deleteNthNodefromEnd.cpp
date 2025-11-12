#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Remove N-th Node from End of Linked List
Link: (LeetCode #19)

Problem Statement:
Given the head of a singly linked list, remove the n-th node 
from the end of the list and return its head.

Constraints:
- 1 <= length of list <= 10^5
- 1 <= n <= length of list

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5, n = 2
Output: 1 -> 2 -> 3 -> 5
Explanation: The second node from the end is 4, which is removed.

Example 2:
Input: 1, n = 1
Output: NULL
Explanation: Only one node, it gets deleted.

Example 3:
Input: 1 -> 2, n = 1
Output: 1
Explanation: Delete the last node.
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
   Approach 1: Length-Based (Brute Force)
------------------------------------------------------------
💡 Idea:
- First traverse list to calculate length.
- Index of node to delete = length - n.
- Do a second traversal to that index and delete it.

🧩 Algorithm:
1. Count total nodes (len).
2. Position to delete = len - n.
3. Special case: if deleting head, return head->next.
4. Otherwise, traverse to (pos-1) and remove next node.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1)
------------------------------------------------------------ */
ListNode* removeNthFromEndBrute(ListNode* head, int n) {
    if (!head) return nullptr;

    // Step 1: Count length
    int len = 0;
    ListNode* curr = head;
    while (curr) {
        len++;
        curr = curr->next;
    }

    int pos = len - n; // 0-based index from front
    if (pos == 0) { // delete head
        ListNode* temp = head;
        head = head->next;
        temp->next = nullptr;
        delete temp;
        return head;
    }

    // Step 2: Traverse to (pos-1) and delete
    curr = head;
    for (int i = 0; i < pos - 1; i++) {
        curr = curr->next;
    }
    ListNode* temp = curr->next;
    curr->next = temp->next;
    temp->next = nullptr;
    delete temp;

    return head;
}


/* -----------------------------------------------------------
   Approach 2: Two-Pointer Technique (Optimal)
------------------------------------------------------------
💡 Idea:
- Use “fast” and “slow” pointers.
- Move fast n steps ahead.
- Then move fast and slow together until fast reaches end.
- Slow->next is the node to delete.

🧩 Algorithm:
1. Create dummy node before head (to handle edge cases cleanly).
2. Move fast pointer n+1 steps ahead from dummy.
3. Move fast and slow pointers until fast == NULL.
4. Delete slow->next.
5. Return dummy->next as new head.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Best
------------------------------------------------------------ */
ListNode* removeNthFromEndOptimal(ListNode* head, int n) {
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;

    ListNode* fast = dummy;
    ListNode* slow = dummy;

    // Move fast n+1 steps ahead (so slow lands on prev node of deletion)
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }

    // Move both until fast reaches end
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }

    // Delete slow->next
    ListNode* temp = slow->next;
    slow->next = temp->next;
    temp->next = nullptr;
    delete temp;

    head = dummy->next;
    dummy->next = nullptr;
    delete dummy;

    return head;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{1,2,3,4,5}, 2}, // remove 2nd from end → remove 4
        {{1}, 1},         // remove 1st from end → delete head
        {{1,2}, 1},       // remove 1st from end → [1]
        {{1,2}, 2}        // remove 2nd from end → 
    };

    for (auto& test : testCases) {
        cout << "\n----------------------------------------\n";
        vector<int> vals = test.first;
        int n = test.second;

        cout << "Original List: ";
        ListNode* head1 = createLinkedList(vals);
        ListNode* head2 = createLinkedList(vals);
        printList(head1);

        // Brute Force
        ListNode* ans1 = removeNthFromEndBrute(head1, n);
        cout << "After Removing " << n << "th from End (Brute): ";
        printList(ans1);

        // Optimal
        ListNode* ans2 = removeNthFromEndOptimal(head2, n);
        cout << "After Removing " << n << "th from End (Optimal): ";
        printList(ans2);

        delete ans1;
        delete ans2;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force: Two-pass, simpler logic but less elegant.
       - Two-Pointer Technique: One-pass, O(1) space, clean code.
         → Recommended for interviews.
    ------------------------------------------------------- */
    return 0;
}
