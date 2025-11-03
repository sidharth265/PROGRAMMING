#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Find the Starting Node of Cycle in a Linked List
Link: (LeetCode #142)

Problem Statement:
Given the head of a singly linked list, return the node 
where the cycle begins. If there is no cycle, return NULL.

- A cycle occurs if a node’s next pointer points to one of the previous nodes.
- We want to detect **where the cycle starts** (not just if it exists).

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5
                   ^         |
                   |_________|
Output: Node with value 2
Explanation: cycle starts at value 2.

Example 2:
Input: 1 -> 2 -> 3 -> NULL
Output: NULL
Explanation: No loop present.

Example 3:
Input: Empty List
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
    if(values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* curr = head;
    for(int i=1; i<values.size(); i++) {
        curr->next = new ListNode(values[i]);
        curr = curr->next;
    }
    return head;
}

void printListSafe(ListNode* head, int limit=15) {
    int cnt=0;
    while(head && cnt<limit) {
        cout << head->data << " ";
        head=head->next;
        cnt++;
    }
    if(head) cout << "...(possible cycle)";
    cout << endl;
}


/* -----------------------------------------------------------
   Approach 1: Using Hashing (Brute Force)
------------------------------------------------------------
💡 Idea:
- Use unordered_set to store visited node addresses.
- If we find a node already visited, that's the starting node of the cycle.

🧩 Algorithm:
1. Traverse the list.
2. If node already in set → return that node.
3. If traversal ends normally → return NULL.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
------------------------------------------------------------ */
ListNode* detectCycleHashing(ListNode* head) {
    unordered_set<ListNode*> seen;
    while(head) {
        if(seen.find(head)!=seen.end()) return head;
        seen.insert(head);
        head=head->next;
    }
    return nullptr;
}


/* -----------------------------------------------------------
   Approach 2: Floyd’s Cycle Detection Algorithm (Optimal)
------------------------------------------------------------
💡 Idea:
- First detect if a cycle exists using fast/slow pointers.
- If no cycle → return NULL.
- If cycle found, reset one pointer to head.
- Move both one step at a time → first meeting point is cycle start.

🧩 Algorithm:
1. Initialize slow=head, fast=head.
2. Loop until fast or fast->next is NULL:
   - slow = slow->next
   - fast = fast->next->next
   - If slow == fast → break
3. If no meeting → return NULL.
4. Reset slow=head.
5. Move slow & fast one step until they meet.
6. Return meeting node (start of loop).

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Best for Interviews
------------------------------------------------------------ */
ListNode* detectCycleFloyd(ListNode* head) {
    if(!head || !head->next) return nullptr;

    ListNode* slow=head;
    ListNode* fast=head;
    bool hasCycle=false;

    // Step 1: Detect cycle
    while(fast && fast->next) {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast) { hasCycle=true; break; }
    }
    if(!hasCycle) return nullptr;

    // Step 2: Find cycle start
    slow=head;
    while(slow!=fast) {
        slow=slow->next;
        fast=fast->next;
    }
    return slow;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    // Case 1: List with cycle
    vector<int> values = {1,2,3,4,5};
    ListNode* head = createLinkedList(values);

    // create cycle: node 5 -> node 2
    ListNode* tail=head;
    while(tail->next) tail=tail->next;
    tail->next=head->next; 

    ListNode* cycleStart1 = detectCycleHashing(head);
    cout << "Cycle starts at (Hashing): " 
         << (cycleStart1 ? to_string(cycleStart1->data) : "NULL") << endl;

    ListNode* cycleStart2 = detectCycleFloyd(head);
    cout << "Cycle starts at (Floyd's): " 
         << (cycleStart2 ? to_string(cycleStart2->data) : "NULL") << endl;


    // Case 2: No Cycle
    vector<int> values2={10,20,30};
    ListNode* head2=createLinkedList(values2);
    ListNode* cycleStart3=detectCycleFloyd(head2);
    cout << "\nNo-cycle Case: "
         << (cycleStart3 ? to_string(cycleStart3->data) : "NULL") << endl;

    // ⚠️ Cannot safely delete head with loop still present (would infinite delete)
    delete head2;

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Hashing:
         + Simple, O(N) space.
         + Okay but not memory optimal.
       - Floyd’s Cycle Detection:
         + O(1) extra space, runs in O(N).
         + Standard, elegant, interview-preferred.
    ------------------------------------------------------- */
    return 0;
}
