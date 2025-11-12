#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Detect Loop in Linked List
Link: (LeetCode #141 / GFG variant)

Problem Statement:
Given the head of a singly linked list, determine whether 
the linked list has a cycle/loop inside it.

A cycle exists if there is some node in the list that can 
be reached again by continuously following the `next` pointer.  
Return true if cycle exists, else false.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5
                 ↑         |
                 └─────────┘
Output: true
Explanation: The linked list contains a cycle at node 2.

Example 2:
Input: 1 -> 2 -> 3 -> NULL
Output: false
Explanation: No cycle, as list terminates properly.

Example 3:
Input: Empty list
Output: false
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

void printListSafe(ListNode* head, int limit = 15) {
    // Print limited nodes to avoid infinite loop printing
    int count = 0;
    while (head && count < limit) {
        cout << head->data << " ";
        head = head->next;
        count++;
    }
    if (head != nullptr) cout << "...(loop detected while printing)";
    cout << endl;
}


/* -----------------------------------------------------------
   Approach 1: Hashing / Set Method
------------------------------------------------------------
💡 Idea:
- Traverse the list while storing node addresses in a hash set.
- If a node repeats, then a cycle exists.

🧩 Algorithm:
1. Create an unordered_set of ListNode*.
2. Traverse list node by node.
3. If node already in set, return true.
4. Else insert node into set.
5. If traversal ends, return false.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
------------------------------------------------------------ */
bool detectLoopHashing(ListNode* head) {
    unordered_set<ListNode*> visited;
    while (head) {
        if (visited.find(head) != visited.end())
            return true;
        visited.insert(head);
        head = head->next;
    }
    return false;
}


/* -----------------------------------------------------------
   Approach 2: Floyd’s Cycle Detection (Optimal)
------------------------------------------------------------
💡 Idea:
- Use two pointers `slow` and `fast`.
- `slow` moves 1 step, `fast` moves 2 steps.
- If they meet → cycle exists.
- If `fast` reaches NULL → no cycle.

🧩 Algorithm:
1. Initialize slow=head, fast=head.
2. While fast != NULL and fast->next != NULL:
   - slow = slow->next
   - fast = fast->next->next
   - If slow == fast → cycle detected
3. If loop finishes, return false.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Most Optimal
------------------------------------------------------------ */
bool detectLoopFloyd(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }
    return false;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    // Case 1: List with a loop
    vector<int> values = {1, 2, 3, 4, 5};
    ListNode* head1 = createLinkedList(values);
    head1->next->next->next->next->next = head1->next; // creates loop: 5 -> 2

    cout << "Case 1 (Loop present):" << endl;
    cout << "Hashing: " << (detectLoopHashing(head1) ? "Loop detected" : "No loop") << endl;
    cout << "Floyd’s Algo: " << (detectLoopFloyd(head1) ? "Loop detected" : "No loop") << endl;

    // Case 2: List without a loop
    vector<int> values2 = {10, 20, 30};
    ListNode* head2 = createLinkedList(values2);

    cout << "\nCase 2 (No loop):" << endl;
    cout << "Hashing: " << (detectLoopHashing(head2) ? "Loop detected" : "No loop") << endl;
    cout << "Floyd’s Algo: " << (detectLoopFloyd(head2) ? "Loop detected" : "No loop") << endl;

    delete head2; // Cannot safely delete head1 due to loop, so skip.

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Hashing: Easy, but uses O(N) extra space.
       - Floyd’s Cycle Detection:
         + Uses constant space O(1).
         + Elegant, widely preferred in interviews.
    ------------------------------------------------------- */
    return 0;
}
