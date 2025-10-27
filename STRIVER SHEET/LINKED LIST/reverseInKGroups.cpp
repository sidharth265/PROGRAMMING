#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Reverse Nodes in k-Group
Link: (LeetCode #25)

Problem Statement:
Given the head of a singly linked list, reverse the nodes of the list 
`k` at a time, and return its modified list.  
If the number of nodes is not a multiple of `k`, leave the last nodes as-is.

You must not alter the values in the list; only the nodes themselves may be changed.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5, k = 2
Output: 2 -> 1 -> 4 -> 3 -> 5

Example 2:
Input: 1 -> 2 -> 3 -> 4 -> 5, k = 3
Output: 3 -> 2 -> 1 -> 4 -> 5

Example 3:
Input: 1, k = 1
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
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}


/* -----------------------------------------------------------
   Approach 1: Recursive (Clean but uses stack)
------------------------------------------------------------
💡 Idea:
- First check if k nodes are available.
- If not, return head.
- Else reverse first k nodes, recursively call on rest.

🧩 Algorithm:
1. Check if there are ≥ k nodes.
2. Reverse first k nodes.
3. Recurse for the rest, attach result.
4. Return new head.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N/k) stack frames
------------------------------------------------------------ */
ListNode* reverseKGroupRecursive(ListNode* head, int k) {
    if (!head) return head;

    // check if we have at least k nodes
    ListNode* node = head;
    for (int i = 0; i < k; i++) {
        if (!node) return head;  // fewer than k nodes → return as is
        node = node->next;
    }

    // reverse k nodes
    ListNode* curr = head;
    ListNode* prev = NULL;
    ListNode* next = NULL;
    int count = k;
    while (count-- && curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // recurse on rest
    head->next = reverseKGroupRecursive(curr, k);
    return prev;
}


/* -----------------------------------------------------------
   Helper: Reverse sublist (iterative)
------------------------------------------------------------ */
pair<ListNode*, ListNode*> reverseSublist(ListNode* head, ListNode* tail) {
    ListNode* prev = tail->next;
    ListNode* curr = head;
    while (prev != tail) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return {tail, head};
}


/* -----------------------------------------------------------
   Approach 2: Iterative (Optimal - No recursion)
------------------------------------------------------------
💡 Idea:
- Count length of list.
- For every group of size k, reverse it using helper.
- Attach groups while iterating.

🧩 Algorithm:
1. Compute total length.
2. Use dummy node to simplify handling.
3. While len >= k:
   - Identify sublist [first..last] of size k.
   - Reverse sublist.
   - Update connections.
   - Reduce len by k.
4. Return dummy->next.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Best Solution
------------------------------------------------------------ */
ListNode* reverseKGroupIterative(ListNode* head, int k) {
    if (!head || k == 1) return head;

    // Count length
    int n = 0;
    for (ListNode* temp = head; temp; temp=temp->next) n++;

    ListNode dummy(-1);
    dummy.next = head;
    ListNode* prevGroup = &dummy;

    while (n >= k) {
        // locate tail of this group
        ListNode* tail = prevGroup;
        for (int i = 0; i < k; i++) tail = tail->next;

        ListNode* nextGroup = tail->next;
        ListNode* first = prevGroup->next;

        // reverse this sublist [first..tail]
        auto reversed = reverseSublist(first, tail);
        ListNode* newHead = reversed.first;
        ListNode* newTail = reversed.second;

        // connect groups
        prevGroup->next = newHead;
        newTail->next = nextGroup;

        // move prevGroup
        prevGroup = newTail;
        n -= k;
    }

    return dummy.next;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{1,2,3,4,5}, 2}, // simple k=2
        {{1,2,3,4,5}, 3}, // k=3
        {{1,2}, 2},       // exact length = k
        {{1}, 1},         // single node
        {{}, 2}           // empty
    };

    for (auto& [values, k] : testCases) {
        cout << "-----------------------------------------\n";
        cout << "Original: ";
        ListNode* head1 = createLinkedList(values);
        ListNode* head2 = createLinkedList(values);
        printList(head1);

        ListNode* res1 = reverseKGroupRecursive(head1, k);
        cout << "Reversed in Groups (Recursive): ";
        printList(res1);

        ListNode* res2 = reverseKGroupIterative(head2, k);
        cout << "Reversed in Groups (Iterative Optimal): ";
        printList(res2);

        delete res1;
        delete res2;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Recursive:
         + Cleaner but uses recursion space.
         + O(N) time, O(N/k) stack memory.
       - Iterative:
         + O(N) time, O(1) space.
         + Efficient pointer manipulation.
         + Best for interviews.
    ------------------------------------------------------- */
    return 0;
}
