#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Odd Even Linked List (Rearrange by Index)
Link: (LeetCode #328)

Problem Statement:
Given the head of a singly linked list, group all the nodes 
with **odd indices** together followed by the nodes with **even indices**, 
and return the reordered list.

- Indexing is based on **1-based position** in the list.
- The relative order among odd nodes and even nodes should remain the same.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5
Output: 1 -> 3 -> 5 -> 2 -> 4
Explanation: Odd indices: 1,3,5 | Even indices: 2,4

Example 2:
Input: 2 -> 1 -> 3 -> 5 -> 6 -> 4 -> 7
Output: 2 -> 3 -> 6 -> 7 -> 1 -> 5 -> 4
Explanation: Odd indices: 2,3,6,7 | Even indices: 1,5,4

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
   Approach 1: Brute Force (using extra space)
------------------------------------------------------------
💡 Idea:
- Traverse list once, store odd nodes and even nodes separately.
- Concatenate odd list + even list.
- Requires extra storage (vectors).

🧩 Algorithm:
1. Traverse list, split data into odd/even vectors.
2. Create a new linked list for odd elements.
3. Append list for even elements.
4. Return new head.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
------------------------------------------------------------ */
ListNode* oddEvenBrute(ListNode* head) {
    if (!head || !head->next) return head;
    vector<int> oddVals, evenVals;

    int index = 1;
    for (ListNode* curr = head; curr; curr = curr->next, index++) {
        if (index % 2 == 1) oddVals.push_back(curr->data);
        else evenVals.push_back(curr->data);
    }

    // Build new list
    ListNode* dummy = new ListNode(-1);
    ListNode* curr = dummy;
    for (int val : oddVals) {
        curr->next = new ListNode(val);
        curr = curr->next;
    }
    for (int val : evenVals) {
        curr->next = new ListNode(val);
        curr = curr->next;
    }
    return dummy->next;
}


/* -----------------------------------------------------------
   Approach 2: In-place (Optimal)
------------------------------------------------------------
💡 Idea:
- Maintain two lists: odd nodes and even nodes.
- Rearrange by pointers without creating new nodes.
- Finally connect end of odd list with start of even list.

🧩 Algorithm:
1. Handle base case (list with 0 or 1 node).
2. Initialize:
   odd = head, even = head->next, evenHead = even.
3. While even and even->next:
   - odd->next = even->next, move odd forward.
   - even->next = odd->next, move even forward.
4. Connect odd->next = evenHead.
5. Return head.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Best
------------------------------------------------------------ */
ListNode* oddEvenOptimal(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* evenHead = even;

    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;

        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead;
    return head;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {1, 2, 3, 4, 5},             // odd count
        {2, 1, 3, 5, 6, 4, 7},       // mixed order
        {1},                         // single node
        {1, 2}                       // two nodes
    };

    for (auto& values : testCases) {
        cout << "--------------------------------------\n";
        cout << "Original List: ";
        ListNode* head1 = createLinkedList(values);
        ListNode* head2 = createLinkedList(values);
        printList(head1);

        // Brute Force
        ListNode* res1 = oddEvenBrute(head1);
        cout << "Rearranged (Brute Force): ";
        printList(res1);

        // Optimal
        ListNode* res2 = oddEvenOptimal(head2);
        cout << "Rearranged (Optimal In-place): ";
        printList(res2);

        delete res1;
        delete res2;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force:
         + Uses vectors and extra memory.
         + Simple to code but not memory efficient.
       - Optimal In-place:
         + Rearranges nodes with pointer changes.
         + O(1) extra space.
         + Preferred for interviews.
    ------------------------------------------------------- */
    return 0;
}
