#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Find Length of the Loop in a Linked List
Link: (GFG / Amazon Interview Problem)

Problem Statement:
Given the head of a singly linked list, 
determine the **length of the cycle** (if any) present in the list.

Return:
- 0 if there is no cycle.
- Length of cycle if a cycle exists.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5
              ↑              |
              └──────────────┘
Output: 4
Explanation: Cycle starts at node 2, loop has 4 nodes.

Example 2:
Input: 1 -> 2 -> 3 -> NULL
Output: 0
Explanation: No cycle present.

Example 3:
Input: Empty list
Output: 0
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


/* -----------------------------------------------------------
   Approach 1: Using Hash Map
------------------------------------------------------------
💡 Idea:
- Use a hash map to store nodes and their index when first visited.
- If a node repeats, then cycle length = current_index - stored_index.

🧩 Algorithm:
1. Initialize unordered_map<Node*, index>.
2. Traverse the list.
3. If node already in map → return difference of indices.
4. Else insert node into map.
5. If end reached → return 0.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
------------------------------------------------------------ */
int lengthOfLoopHashing(ListNode* head) {
    unordered_map<ListNode*, int> nodeMap;
    int index = 0;

    while (head) {
        if (nodeMap.find(head) != nodeMap.end()) {
            return index - nodeMap[head];
        }
        nodeMap[head] = index++;
        head = head->next;
    }

    return 0; // No loop
}


/* -----------------------------------------------------------
   Approach 2: Floyd’s Cycle Detection (Optimal)
------------------------------------------------------------
💡 Idea:
- First use **slow and fast pointers** (Tortoise & Hare) to detect loop.
- If no loop, return 0.
- Once loop detected, keep one pointer fixed and move another till they meet again, counting steps.

🧩 Algorithm:
1. Use slow=head, fast=head.
2. Move fast=fast->next->next and slow=slow->next.
3. If they meet → loop detected, break.
4. If fast=nullptr → no loop → return 0.
5. Else keep slow fixed, move fast until it meets slow again, count steps.
6. Return count.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Best Solution
------------------------------------------------------------ */
int lengthOfLoopFloyd(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // Loop detected, now count its length
            int count = 1;
            fast = fast->next;
            while (fast != slow) {
                count++;
                fast = fast->next;
            }
            return count;
        }
    }
    return 0; // No loop
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<int> values = {1, 2, 3, 4, 5};
    ListNode* head = createLinkedList(values);

    // Creating a loop manually for testing:
    // Last node (5) points back to node (2), forming loop length = 4
    head->next->next->next->next->next = head->next;

    cout << "Length of Loop (Hashing): " 
         << lengthOfLoopHashing(head) << endl;  // Expected: 4

    cout << "Length of Loop (Floyd’s Cycle Detection): " 
         << lengthOfLoopFloyd(head) << endl;   // Expected: 4

    // ⚠️ Do not call delete head since it has a loop; memory leak left intentionally for demo
    // (in practice, break loop first then delete nodes)

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Hashing:
         + Simple but O(N) space.
         + Easy to implement.
       - Floyd’s Cycle Detection:
         + O(1) extra space.
         + Elegant, interview favorite.
         + Best and most efficient in practice.
    ------------------------------------------------------- */

    return 0;
}
