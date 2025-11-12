#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Sort Linked List of 0s, 1s, and 2s
Link: (GFG / Common Interview Problem)

Problem Statement:
Given the head of a singly linked list where each node contains 
only values 0, 1, or 2, sort the list in non-decreasing order.

You must rearrange node connections, not just copy values.

---------------------------------------------------------------
Examples:

Example 1:
Input: 2 -> 1 -> 0 -> 2 -> 1 -> 0
Output: 0 -> 0 -> 1 -> 1 -> 2 -> 2

Example 2:
Input: 0 -> 2 -> 1
Output: 0 -> 1 -> 2

Example 3:
Input: 1 -> 1 -> 1
Output: 1 -> 1 -> 1
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
    ListNode* curr = head;
    for (int i=1; i<values.size(); i++) {
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
   Approach 1: Counting (Brute Force)
------------------------------------------------------------
💡 Idea:
- Traverse list and count 0s, 1s, and 2s.
- Traverse again rewriting node values in sorted order.

🧩 Algorithm:
1. Count number of 0s, 1s, and 2s.
2. Traverse list again, overwrite node values accordingly.
3. Return head.

⏱ Time Complexity: O(N)  
📦 Space Complexity: O(1)  
⚠️ Modifies node data (Not always allowed in real interviews).
------------------------------------------------------------ */
ListNode* sort012Count(ListNode* head) {
    int cnt0=0, cnt1=0, cnt2=0;
    ListNode* curr = head;

    while(curr) {
        if(curr->data==0) cnt0++;
        else if(curr->data==1) cnt1++;
        else cnt2++;
        curr = curr->next;
    }

    curr = head;
    while(curr) {
        if(cnt0) { curr->data=0; cnt0--; }
        else if(cnt1) { curr->data=1; cnt1--; }
        else { curr->data=2; cnt2--; }
        curr = curr->next;
    }
    return head;
}


/* -----------------------------------------------------------
   Approach 2: Dummy Node Buckets (Optimal - Rearrange Links)
------------------------------------------------------------
💡 Idea:
- Use 3 dummy heads for 0s, 1s, and 2s.
- Traverse original list, append each node to correct dummy list.
- Merge lists: 0-list → 1-list → 2-list.
- Return new head.

🧩 Algorithm:
1. Create dummy heads for zero/one/two lists.
2. Traverse main list, segregate nodes into respective lists.
3. Merge dummy lists.
4. Return start of merged list.

⏱ Time Complexity: O(N)  
📦 Space Complexity: O(1) ✅ Best Solution
------------------------------------------------------------ */
ListNode* sort012Buckets(ListNode* head) {
    if(!head || !head->next) return head;

    ListNode* zeroHead = new ListNode(-1);
    ListNode* oneHead  = new ListNode(-1);
    ListNode* twoHead  = new ListNode(-1);
    ListNode* zeroTail = zeroHead, *oneTail=oneHead, *twoTail=twoHead;

    ListNode* curr = head;
    while(curr) {
        if(curr->data == 0) {
            zeroTail->next = curr;
            zeroTail = curr;
        }
        else if(curr->data == 1) {
            oneTail->next = curr;
            oneTail = curr;
        }
        else {
            twoTail->next = curr;
            twoTail = curr;
        }
        curr = curr->next;
    }

    // Merge parts
    zeroTail->next = (oneHead->next) ? oneHead->next : twoHead->next;
    oneTail->next = twoHead->next;
    twoTail->next = nullptr;

    ListNode* newHead = zeroHead->next;

    // Delete dummy headers
    delete zeroHead; delete oneHead; delete twoHead;

    return newHead;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {2,1,0,2,1,0},  // mixed unsorted
        {0,2,1},        // small case
        {1,1,1},        // all identical
        {0,0,2,2,1,1},  // already grouped
        {}              // empty case
    };

    for(auto& values : testCases) {
        cout << "-----------------------------------\n";
        ListNode* head1 = createLinkedList(values);
        ListNode* head2 = createLinkedList(values);

        cout << "Original List: ";
        printList(head1);

        ListNode* sorted1 = sort012Count(head1);
        cout << "Sorted (Counting - Change Data): ";
        printList(sorted1);

        ListNode* sorted2 = sort012Buckets(head2);
        cout << "Sorted (Buckets - Rearrange Links): ";
        printList(sorted2);

        delete sorted1;
        delete sorted2;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Counting:
         + Simpler but rewrites node values.
         + Not always acceptable (nodes may store objects).
       - Buckets (Dummy Nodes):
         + Adjusts only links.
         + Preserves node integrity.
         + Interview-preferred solution.
    ------------------------------------------------------- */
    return 0;
}
