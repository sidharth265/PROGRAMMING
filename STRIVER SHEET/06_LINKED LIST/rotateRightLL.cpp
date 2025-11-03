#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Rotate List (Right Rotation by k)
Link: (LeetCode #61)

Problem Statement:
Given the head of a singly linked list, rotate the list to the right by `k` places.

- Right rotation means: the last k nodes become the first k nodes in the list.
- If k >= length of list, only perform (k % length) rotations.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5, k = 2
Output: 4 -> 5 -> 1 -> 2 -> 3
Explanation: Rotated right 2 times.

Example 2:
Input: 0 -> 1 -> 2, k = 4
Output: 2 -> 0 -> 1
Explanation: Length=3, k%3=1 → rotate once.

Example 3:
Input: 1, k = 0
Output: 1 (no rotation needed).
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
    for (int i = 1; i < values.size(); i++) {
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
   Approach 1: Brute Force (Rotate One Step k Times)
------------------------------------------------------------
💡 Idea:
- Rotate list by 1 → Move last node to front.
- Repeat k times.

🧩 Algorithm:
1. For i=1→k:
   - Traverse to last node.
   - Detach last node and make it new head.
2. Return head.

⏱ Time Complexity: O(k*N) (bad when k large)
📦 Space Complexity: O(1)
⚠️ Not practical for big inputs.
------------------------------------------------------------ */
ListNode* rotateRightBrute(ListNode* head, int k) {
    if (!head || !head->next) return head;

    for (int i=0; i<k; i++) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr->next) {
            prev = curr;
            curr = curr->next;
        }
        curr->next = head;
        head = curr;
        prev->next = nullptr;
    }
    return head;
}


/* -----------------------------------------------------------
   Approach 2: Optimal O(N)
------------------------------------------------------------
💡 Idea:
- Compute length of list (n).
- Make it circular by connecting tail → head.
- Find newHead at position (n-k%n).
- Break the circle at that position.

🧩 Algorithm:
1. Count length n, connect last node → head (circular).
2. Adjust k = k%n (no extra rotations).
3. Find (n-k)th node → that will become new tail.
4. Next node → new head.
5. Break circle and return newHead.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Interview Favorite
------------------------------------------------------------ */
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k==0) return head;

    // Step 1: Count length
    int n = 1;
    ListNode* tail = head;
    while (tail->next) {
        tail = tail->next;
        n++;
    }

    // Step 2: Connect tail to head (circular list)
    tail->next = head;

    // Step 3: New head = (n - k%n)th node
    k = k % n;
    int stepsToNewHead = n - k;
    ListNode* newTail = tail;
    while (stepsToNewHead--) {
        newTail = newTail->next;
    }

    ListNode* newHead = newTail->next;
    newTail->next = nullptr;

    return newHead;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{1,2,3,4,5}, 2},   // Rotate by 2 → 4 5 1 2 3
        {{0,1,2}, 4},       // Rotate by 4 (same as rotate by 1)
        {{1}, 0},           // No rotation
        {{1,2}, 2},         // k == length → no change
        {{}, 5}             // Empty list
    };

    for (auto& [values, k] : testCases) {
        cout << "----------------------------------------\n";
        cout << "Original: ";
        ListNode* head1 = createLinkedList(values);
        ListNode* head2 = createLinkedList(values);
        printList(head1);

        ListNode* res1 = rotateRightBrute(head1, k);
        cout << "Brute Rotated by " << k << ": ";
        printList(res1);

        ListNode* res2 = rotateRight(head2, k);
        cout << "Optimal Rotated by " << k << ": ";
        printList(res2);

        delete res1; 
        delete res2;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force:
         + Rotate 1-by-1, O(k*N).
         + Simplest but inefficient for large k.
       - Optimal (O(N)):
         + Uses circular link trick.
         + O(N) time, O(1) space.
         + Preferred for interviews.
    ------------------------------------------------------- */
    return 0;
}
