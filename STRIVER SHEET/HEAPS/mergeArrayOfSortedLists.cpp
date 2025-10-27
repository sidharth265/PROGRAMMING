#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Merge K Sorted Lists
 Problem Link: https://leetcode.com/problems/merge-k-sorted-lists/

 Problem Statement:
 -----------------
 Given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 Merge all the linked-lists into one sorted linked-list and return it.

 Example:
 Input: lists = [[1,4,5],[1,3,4],[2,6]]
 Output: [1,1,2,3,4,4,5,6]

 Constraints:
 - k == lists.length
 - 0 <= k <= 10^4
 - 0 <= lists[i].length <= 500
 - -10^4 <= lists[i][j] <= 10^4
 - lists[i] is sorted in ascending order.
 - Total number of nodes <= 10^4
====================================================
*/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
==========================================
 Approach 1: Brute Force - Iterative Merging by Pairs
-----------------------------------------
💡 Idea:
Iteratively merge lists one by one using a merge function for two sorted lists.

🧩 Algorithm:
1. Initialize mergedHead with first list.
2. Iterate through lists from second to last:
   - Merge mergedHead with current list.
3. Return mergedHead.

⏱ Time Complexity: O(kN), where k is number of lists, N is total nodes.
📦 Space Complexity: O(1)
*/
ListNode* merge(ListNode* head1, ListNode* head2) {
    ListNode dummy(-1);
    ListNode* curr = &dummy;
    while (head1 && head2) {
        if (head1->val < head2->val) {
            curr->next = head1;
            head1 = head1->next;
        } else {
            curr->next = head2;
            head2 = head2->next;
        }
        curr = curr->next;
    }
    curr->next = head1 ? head1 : head2;
    return dummy.next;
}

ListNode* mergeKListsBrute(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    ListNode* mergedHead = lists[0];
    for (int i = 1; i < (int)lists.size(); ++i) {
        mergedHead = merge(mergedHead, lists[i]);
    }
    return mergedHead;
}

/*
==========================================
 Approach 2: Better - Divide and Conquer Merging
-----------------------------------------
💡 Idea:
Merge lists in pairs, reducing number of lists by half each time, similar to merge sort.

🧩 Algorithm:
1. Recursively divide lists into two halves.
2. Merge each half.
3. Merge two halves together.

⏱ Time Complexity: O(N log k), more efficient than Approach 1.
📦 Space Complexity: O(log k) recursion stack.
*/
ListNode* mergeKListsDivideAndConquer(vector<ListNode*>& lists, int left, int right) {
    if (left > right) return nullptr;
    if (left == right) return lists[left];

    int mid = left + (right - left) / 2;
    ListNode* l1 = mergeKListsDivideAndConquer(lists, left, mid);
    ListNode* l2 = mergeKListsDivideAndConquer(lists, mid + 1, right);
    return merge(l1, l2);
}

ListNode* mergeKListsBetter(vector<ListNode*>& lists) {
    return mergeKListsDivideAndConquer(lists, 0, (int)lists.size() - 1);
}

/*
==========================================
 Approach 3: Optimal - Min-Heap (Priority Queue)
-----------------------------------------
💡 Idea:
Use a min-heap / priority queue to always extract the smallest element among the heads of all lists.

🧩 Algorithm:
1. Push heads of all non-empty lists into min-heap (value, ListNode*).
2. Pop the smallest node, add to merged list.
3. If popped node has next, push next node to heap.
4. Repeat until heap is empty.

⏱ Time Complexity: O(N log k), where N is total nodes.
📦 Space Complexity: O(k)
*/
struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val; // Min-heap based on node value
    }
};

ListNode* mergeKListsOptimal(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
    for (auto node : lists) {
        if (node) pq.push(node);
    }

    ListNode dummy(-1);
    ListNode* tail = &dummy;

    while (!pq.empty()) {
        ListNode* curr = pq.top();
        pq.pop();
        tail->next = curr;
        tail = tail->next;
        if (curr->next) pq.push(curr->next);
    }

    return dummy.next;
}

/* Helper function to print linked list */
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Merge K Sorted Lists ===\n\n";

    // Example: lists = [[1->4->5], [1->3->4], [2->6]]
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    ListNode* l3 = new ListNode(2);
    l3->next = new ListNode(6);

    vector<ListNode*> lists = {l1, l2, l3};

    ListNode* resBrute = mergeKListsBrute(lists);
    cout << "Brute Force Merge: ";
    printList(resBrute);

    // Recreate lists (since merged above)
    l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    l3 = new ListNode(2);
    l3->next = new ListNode(6);
    lists = {l1, l2, l3};

    ListNode* resBetter = mergeKListsBetter(lists);
    cout << "Better Divide & Conquer Merge: ";
    printList(resBetter);

    // Recreate lists again
    l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    l3 = new ListNode(2);
    l3->next = new ListNode(6);
    lists = {l1, l2, l3};

    ListNode* resOptimal = mergeKListsOptimal(lists);
    cout << "Optimal Min-Heap Merge: ";
    printList(resOptimal);

    // Memory cleanup omitted for brevity

    return 0;
}

/*
✅ Approach Overview:
- Brute Force: merge lists one by one, O(kN) time.
- Better: divide and conquer merging, O(N log k) time.
- Optimal: Min-heap based merging, O(N log k) time, best for largest k and N.
*/
