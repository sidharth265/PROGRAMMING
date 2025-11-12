#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Sort a Linked List
Link: (LeetCode #148)

Problem Statement:
Sort a singly linked list in ascending order and return its head.

Constraints:
- The list could be very long.
- Sorting must ideally be done **in O(N log N)** time using 
  constant extra space if possible.

---------------------------------------------------------------
Examples:

Example 1:
Input: 4 -> 2 -> 1 -> 3
Output: 1 -> 2 -> 3 -> 4

Example 2:
Input: -1 -> 5 -> 3 -> 4 -> 0
Output: -1 -> 0 -> 3 -> 4 -> 5

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
   Approach 1: Array-based Sorting (Brute Force)
------------------------------------------------------------
💡 Idea:
- Extract all values into an array.
- Sort using STL.
- Rebuild linked list.

🧩 Algorithm:
1. Traverse list → store values in vector.
2. Sort array.
3. Rebuild new linked list.
4. Return new head.

⏱ Time Complexity: O(N log N)  
📦 Space Complexity: O(N)
------------------------------------------------------------ */
ListNode* sortListArray(ListNode* head) {
    if(!head || !head->next) return head;

    vector<int> arr;
    for(ListNode* curr=head; curr; curr=curr->next) {
        arr.push_back(curr->data);
    }

    sort(arr.begin(), arr.end());

    ListNode* dummy = new ListNode(-1);
    ListNode* tail = dummy;
    for(int val : arr) {
        tail->next = new ListNode(val);
        tail = tail->next;
    }
    return dummy->next;
}


/* -----------------------------------------------------------
   Approach 2: Merge Sort (Optimal)
------------------------------------------------------------
💡 Idea:
- Preferred for linked lists since random access isn't possible.
- Split list in halves, recursively sort, then merge.

🧩 Algorithm:
1. Use fast/slow pointers to find middle.
2. Recursively sort left & right halves.
3. Merge two sorted halves.
4. Return sorted head.

⏱ Time Complexity: O(N log N)  
📦 Space Complexity: O(log N) recursion stack
------------------------------------------------------------ */
ListNode* findMid(ListNode* head) {
    ListNode* slow=head, *fast=head->next;
    while(fast && fast->next) {
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}

ListNode* merge(ListNode* left, ListNode* right) {
    ListNode dummy(-1);
    ListNode* curr=&dummy;
    while(left && right) {
        if(left->data < right->data) {
            curr->next = left;
            left = left->next;
        } else {
            curr->next = right;
            right = right->next;
        }
        curr=curr->next;
    }
    if(left) curr->next=left;
    if(right) curr->next=right;
    return dummy.next;
}

ListNode* mergeSort(ListNode* head) {
    if(!head || !head->next) return head;

    ListNode* mid = findMid(head);
    ListNode* left=head;
    ListNode* right=mid->next;
    mid->next=nullptr;

    left = mergeSort(left);
    right = mergeSort(right);
    return merge(left, right);
}


/* -----------------------------------------------------------
   Approach 3: Insertion Sort
------------------------------------------------------------
💡 Idea:
- Build a new sorted list by inserting nodes one by one in correct position.

🧩 Algorithm:
1. Maintain dummy sorted list.
2. For each node, find position in sorted list.
3. Insert in correct spot.
4. Move to next node.

⏱ Time Complexity: O(N²)  
📦 Space Complexity: O(1)
------------------------------------------------------------ */
ListNode* insertionSortList(ListNode* head) {
    if(!head || !head->next) return head;

    ListNode dummy(-1);
    ListNode* curr = head;

    while(curr) {
        ListNode* nextNode = curr->next;
        ListNode* prev = &dummy;
        while(prev->next && prev->next->data < curr->data) prev=prev->next;
        curr->next = prev->next;
        prev->next = curr;
        curr=nextNode;
    }
    return dummy.next;
}


/* -----------------------------------------------------------
   Approach 4: Bubble Sort
------------------------------------------------------------
💡 Idea:
- Swap adjacent nodes until list becomes sorted.

🧩 Algorithm:
1. Repeat until no swaps:
   - Traverse list, swap values if curr > curr->next.
2. Continue until sorted.

⏱ Time Complexity: O(N²)  
📦 Space Complexity: O(1)
------------------------------------------------------------ */
ListNode* bubbleSortList(ListNode* head) {
    if(!head || !head->next) return head;

    bool swapped;
    do {
        swapped=false;
        ListNode* curr=head;
        while(curr && curr->next) {
            if(curr->data > curr->next->data) {
                swap(curr->data, curr->next->data);
                swapped=true;
            }
            curr=curr->next;
        }
    } while(swapped);

    return head;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {4,2,1,3},
        {-1,5,3,4,0},
        {1},
        {}
    };

    for(auto values : testCases) {
        cout << "-------------------------------------\n";
        ListNode* head1 = createLinkedList(values);
        ListNode* head2 = createLinkedList(values);
        ListNode* head3 = createLinkedList(values);
        ListNode* head4 = createLinkedList(values);

        cout << "Original List: ";
        printList(head1);

        ListNode* sorted1 = sortListArray(head1);
        cout << "Sorted (Array + Rebuild): ";
        printList(sorted1);

        ListNode* sorted2 = mergeSort(head2);
        cout << "Sorted (Merge Sort Optimal): ";
        printList(sorted2);

        ListNode* sorted3 = insertionSortList(head3);
        cout << "Sorted (Insertion Sort): ";
        printList(sorted3);

        ListNode* sorted4 = bubbleSortList(head4);
        cout << "Sorted (Bubble Sort): ";
        printList(sorted4);

        delete sorted1;
        delete sorted2;
        delete sorted3;
        delete sorted4;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Array Sort: O(N log N), easy but requires O(N) extra space.
       - Merge Sort: O(N log N), O(log N) recursion, **best choice for LL**.
       - Insertion Sort: O(N²), works well on nearly-sorted lists.
       - Bubble Sort: O(N²), simple but inefficient.
    ------------------------------------------------------- */
    return 0;
}
