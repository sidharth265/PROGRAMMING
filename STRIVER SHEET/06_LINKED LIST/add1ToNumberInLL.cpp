#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Add 1 to a Number Represented by Linked List
Link: (Can be found on GeeksforGeeks/LeetCode-style problems)

Problem Statement:
You are given a non-empty singly linked list representing a non-negative integer. 
The digits are stored in forward order, and each node contains a single digit. 
Add one to the integer and return the head of the resulting linked list.

The most significant digit is at the head of the linked list.

---------------------------------------------------------------
Examples:

Example 1:
Input: 9 -> 9 -> 9
Output: 1 -> 0 -> 0 -> 0
Explanation: 999 + 1 = 1000

Example 2:
Input: 1 -> 2 -> 3
Output: 1 -> 2 -> 4
Explanation: 123 + 1 = 124

Example 3:
Input: (empty list)
Output: (empty list)

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
   Approach 1: Brute Force
------------------------------------------------------------
💡 Idea:
- Traverse the linked list, store the number in an integer.
- Increment integer by 1.
- Construct a new linked list from the incremented number.

🧩 Algorithm:
1. Traverse list and append each digit to form a string.
2. Convert string to number (may cause overflow for large LL).
3. Add one to that number.
4. Convert back into linked list.

⏱ Time Complexity: O(N) 
📦 Space Complexity: O(N) due to string/number storage
------------------------------------------------------------ */
ListNode* addOneBruteForce(ListNode* head) {
    if (!head) return nullptr;
    string num = "";
    while (head) {
        num += to_string(head->data);
        head = head->next;
    }
    // Convert string to BigInteger-like structure
    // Use reverse addition to avoid overflow
    int carry = 1;
    for (int i = num.size() - 1; i >= 0 && carry; i--) {
        int sum = (num[i] - '0') + carry;
        num[i] = (sum % 10) + '0';
        carry = sum / 10;
    }
    if (carry) num.insert(num.begin(), '1');

    // Convert back to Linked List
    ListNode* newHead = new ListNode(num[0] - '0');
    ListNode* curr = newHead;
    for (int i = 1; i < num.size(); i++) {
        curr->next = new ListNode(num[i] - '0');
        curr = curr->next;
    }
    return newHead;
}

/* -----------------------------------------------------------
   Approach 2: Recursive (Better)
------------------------------------------------------------
💡 Idea:
- Use recursion to add +1 starting from last digit (like hand addition).
- Carry is bubbled up through recursive calls.

🧩 Algorithm:
1. Recursively traverse to the last node.
2. At the last node, add 1 and propagate carry backward.
3. If a carry is returned at head, insert new node at front.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N) due to recursive stack
------------------------------------------------------------ */
int addWithCarry(ListNode* head) {
    if (!head) return 1; // Base: "carry of 1" for last node addition
    int carry = addWithCarry(head->next);
    if (!carry) return 0;
    int sum = head->data + carry;
    head->data = sum % 10;
    return sum / 10; // carry for previous
}

ListNode* addOneRecursive(ListNode* head) {
    if (!head) return nullptr;
    int carry = addWithCarry(head);
    if (carry) {
        ListNode* newNode = new ListNode(carry);
        newNode->next = head;
        head = newNode;
    }
    return head;
}

/* -----------------------------------------------------------
   Approach 3: Iterative Reverse (Optimal)
------------------------------------------------------------
💡 Idea:
- Reverse the linked list, add one iteratively, handle carry.
- Finally reverse again to retain order.

🧩 Algorithm:
1. Reverse linked list.
2. Traverse with a carry=1, update node values.
3. If carry still remains, add a new node.
4. Reverse the linked list back.
5. Return the new head.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1)
------------------------------------------------------------ */
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* nextNode = head->next;
        head->next = prev;
        prev = head;
        head = nextNode;
    }
    return prev;
}

ListNode* addOneOptimal(ListNode* head) {
    if (!head) return nullptr;
    head = reverseList(head);
    ListNode* curr = head;
    int carry = 1;
    while (curr && carry) {
        curr->data += carry;
        if (curr->data == 10) {
            curr->data = 0;
            carry = 1;
        } else {
            carry = 0;
        }
        curr = curr->next;
    }
    head = reverseList(head);
    if (carry) {
        ListNode* newHead = new ListNode(1);
        newHead->next = head;
        head = newHead;
    }
    return head;
}

/* -----------------------------------------------------------
   Driver Code (Testing Main)
------------------------------------------------------------ */
int main() {
    vector<vector<int>> testCases = {
        {9, 9, 9},
        {1, 2, 3},
        {0},
        {9}
    };

    for (auto& values : testCases) {
        cout << "----------------------------------------\n";
        ListNode* head = createLinkedList(values);

        cout << "Original Number: ";
        printList(head);

        // Brute Force
        ListNode* brute = addOneBruteForce(createLinkedList(values));
        cout << "Brute Force Result: ";
        printList(brute);

        // Recursive
        ListNode* rec = addOneRecursive(createLinkedList(values));
        cout << "Recursive Result: ";
        printList(rec);

        // Optimal
        ListNode* opt = addOneOptimal(createLinkedList(values));
        cout << "Optimal Result: ";
        printList(opt);

        delete head; delete brute; delete rec; delete opt;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force: Easy, but uses string/extra space.
       - Recursive: Elegant, uses recursion → O(N) space.
       - Optimal: Iterative, O(1) space. BEST for interviews.
    ------------------------------------------------------- */
    return 0;
}
