#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Palindrome Linked List
Link: (LeetCode #234, GFG variant)

Problem Statement:
Given the head of a singly linked list, return true if it is a palindrome
or false otherwise.

A linked list is palindrome if:
- The sequence of values from head to tail is the same as from tail to head.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 -> 2 -> 2 -> 1
Output: true

Example 2:
Input: 1 -> 2 -> 3 -> 2 -> 1
Output: true

Example 3:
Input: 1 -> 2
Output: false
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Definition for ListNode
------------------------------------------------------------ */
class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int val) : val(val), next(nullptr) {}
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
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}


/* -----------------------------------------------------------
   Approach 1: Using Stack (Brute Force)
------------------------------------------------------------
💡 Idea:
- Push all node values onto a stack.
- Traverse list again, comparing values with stack top.

🧩 Algorithm:
1. Traverse list, push values into stack.
2. Traverse again while popping stack.
3. If mismatch found → not a palindrome.
4. Else return true.

⏱ Time Complexity: O(N)  
📦 Space Complexity: O(N)
------------------------------------------------------------ */
bool isPalindromeStack(ListNode* head) {
    stack<int> st;
    ListNode* curr = head;
    while (curr) {
        st.push(curr->val);
        curr = curr->next;
    }
    curr = head;
    while (curr) {
        if (st.top() != curr->val) return false;
        st.pop();
        curr = curr->next;
    }
    return true;
}


/* -----------------------------------------------------------
   Helper to Reverse a Linked List
------------------------------------------------------------ */
ListNode* reverseLL(ListNode* head) {
    ListNode* prev = NULL;
    while (head) {
        ListNode* nextNode = head->next;
        head->next = prev;
        prev = head;
        head = nextNode;
    }
    return prev;
}


/* -----------------------------------------------------------
   Approach 2: Fast & Slow Pointer (Optimal)
------------------------------------------------------------
💡 Idea:
- Use slow/fast pointer to find the mid node.
- Reverse the second half of the list.
- Compare first half and second half.
- Restore list structure (optional).

🧩 Algorithm:
1. Use slow & fast pointers to locate midpoint.
2. Reverse second half starting from slow.
3. Compare first half & second half.
4. Restore the reversed part for cleanup (optional).
5. Return true if same, else false.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Best choice
------------------------------------------------------------ */
bool isPalindromeTwoPointer(ListNode* head) {
    if (!head || !head->next) return true;

    // Find mid using fast/slow
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half
    ListNode* secondHalf = reverseLL(slow);

    // Compare halves
    ListNode* p1 = head;
    ListNode* p2 = secondHalf;
    bool result = true;
    while (p2) {
        if (p1->val != p2->val) {
            result = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    // Restore second half (optional, keeps input intact)
    reverseLL(secondHalf);

    return result;
}


/* -----------------------------------------------------------
   Approach 3: Recursion
------------------------------------------------------------
💡 Idea:
- Recursively traverse to last node.
- Compare values from end to start using recursion stack.

🧩 Algorithm:
1. Use recursion to go till last node.
2. Compare node value with a global pointer moving from left.
3. Return result at each stack unwind.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N) (recursion stack)
------------------------------------------------------------ */
bool isPalindromeRecUtil(ListNode* right, ListNode*& left) {
    if (!right) return true;
    bool res = isPalindromeRecUtil(right->next, left);
    if (!res || left->val != right->val) return false;
    left = left->next;
    return true;
}
bool isPalindromeRec(ListNode* head) {
    ListNode* left = head;
    return isPalindromeRecUtil(head, left);
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {1,2,3,2,1},     // palindrome
        {1,2,2,1},       // palindrome
        {1,2},           // not palindrome
        {1},             // single node (palindrome)
        {}               // empty list
    };

    for (auto& values : testCases) {
        cout << "\n-----------------------------------\n";
        cout << "List: ";
        ListNode* head = createLinkedList(values);
        printList(head);

        cout << "Palindrome (Stack): " 
             << (isPalindromeStack(head) ? "true" : "false") << endl;

        cout << "Palindrome (Two Pointer): " 
             << (isPalindromeTwoPointer(head) ? "true" : "false") << endl;

        cout << "Palindrome (Recursion): " 
             << (isPalindromeRec(head) ? "true" : "false") << endl;

        delete head;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Stack:
         + Simple but needs O(N) extra memory.
       - Two-Pointer + Reverse:
         + O(1) extra space, single traversal.
         + Preferred in interviews.
       - Recursion:
         + Elegant but O(N) recursion memory.
         + Good for academic explanation.
    ------------------------------------------------------- */
    return 0;
}
