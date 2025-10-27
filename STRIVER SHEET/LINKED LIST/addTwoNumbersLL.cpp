#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Add Two Numbers Represented by Linked Lists
Link: (Typical LeetCode #2 / GFG variant)

Problem Statement:
You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in forward order, and each node contains a single digit. 
Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zeros, 
except for the number 0 itself.

---------------------------------------------------------------
Examples:

Example 1:
Input: 
List1 = 9 -> 4 -> 3 -> 8   (9438)
List2 = 5 -> 6 -> 4        (564)
Output: 1 -> 0 -> 0 -> 0 -> 2  (10002)
Explanation: 9438 + 564 = 10002

Example 2:
Input:
List1 = 2 -> 4 -> 3   (243)
List2 = 5 -> 6 -> 4   (564)
Output: 8 -> 0 -> 7   (807)
Explanation: 243 + 564 = 807

Example 3:
Input:
List1 = 0
List2 = 0
Output: 0
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
        if (this->next) {
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
    ListNode* current = head;
    for (int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

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


/* -----------------------------------------------------------
   Approach 1: Brute Force (Convert to Number, Add, Convert Back)
------------------------------------------------------------
💡 Idea:
- Traverse both linked lists, convert to strings/ numbers.
- Convert them to large numbers, add together.
- Construct new linked list from sum.

🧩 Algorithm:
1. Traverse each list and create strings for numbers.
2. Convert both to integers (or use string-based addition).
3. Add them up.
4. Convert result back into linked list digits.

⚠️ Can fail for very large numbers due to integer overflow.

⏱ Time Complexity: O(N + M)
📦 Space Complexity: O(N + M) (uses strings/arrays)
------------------------------------------------------------ */
ListNode* addTwoNumbersBruteForce(ListNode* l1, ListNode* l2) {
    string num1 = "", num2 = "";
    while (l1) { num1.push_back(l1->val + '0'); l1 = l1->next; }
    while (l2) { num2.push_back(l2->val + '0'); l2 = l2->next; }

    // Perform string-based addition (like grade-school)
    int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
    string sumRev = "";
    while (i >= 0 || j >= 0 || carry) {
        int n1 = (i >= 0 ? num1[i--] - '0' : 0);
        int n2 = (j >= 0 ? num2[j--] - '0' : 0);
        int s = n1 + n2 + carry;
        sumRev.push_back((s % 10) + '0');
        carry = s / 10;
    }
    reverse(sumRev.begin(), sumRev.end());

    // Build linked list from sum string
    ListNode* dummy = new ListNode(-1);
    ListNode* curr = dummy;
    for (char c : sumRev) {
        curr->next = new ListNode(c - '0');
        curr = curr->next;
    }
    return dummy->next;
}


/* -----------------------------------------------------------
   Approach 2: Using Stacks (Better)
------------------------------------------------------------
💡 Idea:
- Push digits of both lists into stacks.
- Pop from both stacks (which gives access from least significant digit).
- Add digits with carry, push into a result stack.
- Build the result list in forward order.

🧩 Algorithm:
1. Push all digits of l1, l2 into two stacks.
2. Initialize carry=0.
3. While either stack non-empty or carry > 0:
   - Pop from stacks (if available).
   - Sum digits + carry.
   - Create new node with sum%10 and insert at front.
4. Return head.

⏱ Time Complexity: O(N + M)
📦 Space Complexity: O(N + M) stacks
------------------------------------------------------------ */
ListNode* addTwoNumbersStacks(ListNode* l1, ListNode* l2) {
    stack<int> s1, s2;
    while (l1) { s1.push(l1->val); l1 = l1->next; }
    while (l2) { s2.push(l2->val); l2 = l2->next; }

    int carry = 0;
    ListNode* head = nullptr;
    while (!s1.empty() || !s2.empty() || carry) {
        int n1 = (!s1.empty() ? s1.top() : 0);
        int n2 = (!s2.empty() ? s2.top() : 0);
        if (!s1.empty()) s1.pop();
        if (!s2.empty()) s2.pop();
        int sum = n1 + n2 + carry;
        carry = sum / 10;
        ListNode* newNode = new ListNode(sum % 10);
        newNode->next = head; // insert at front
        head = newNode;
    }
    return head;
}


/* -----------------------------------------------------------
   Approach 3: Reverse List (Optimal)
------------------------------------------------------------
💡 Idea:
- Reverse both lists so that least significant digit comes first.
- Add forward as a normal addition with carry.
- Reverse final result to restore forward order.

🧩 Algorithm:
1. Reverse l1 and l2.
2. Traverse both lists adding digits + carry.
3. Create new nodes for sum%10.
4. Reverse the result and return.

⏱ Time Complexity: O(N + M)
📦 Space Complexity: O(1)
------------------------------------------------------------ */
ListNode* addTwoNumbersOptimal(ListNode* l1, ListNode* l2) {
    l1 = reverseList(l1);
    l2 = reverseList(l2);

    int carry = 0;
    ListNode* dummy = new ListNode(-1);
    ListNode* curr = dummy;

    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }
        carry = sum / 10;
        curr->next = new ListNode(sum % 10);
        curr = curr->next;
    }
    return reverseList(dummy->next);
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<pair<vector<int>, vector<int>>> testCases = {
        {{9,4,3,8}, {5,6,4}},   // 9438 + 564
        {{2,4,3}, {5,6,4}},     // 243 + 564
        {{9,9,9}, {1}},         // 999 + 1
        {{0}, {0}}              // 0 + 0
    };

    for (auto& test : testCases) {
        cout << "----------------------------------------\n";
        ListNode* l1 = createLinkedList(test.first);
        ListNode* l2 = createLinkedList(test.second);

        cout << "List 1: "; printList(l1);
        cout << "List 2: "; printList(l2);

        ListNode* brute = addTwoNumbersBruteForce(createLinkedList(test.first), createLinkedList(test.second));
        cout << "Brute Force Result: "; printList(brute);

        ListNode* stackRes = addTwoNumbersStacks(createLinkedList(test.first), createLinkedList(test.second));
        cout << "Stacks Result: "; printList(stackRes);

        ListNode* optimal = addTwoNumbersOptimal(createLinkedList(test.first), createLinkedList(test.second));
        cout << "Optimal Result: "; printList(optimal);

        delete l1; delete l2;
        delete brute; delete stackRes; delete optimal;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force: Simple but not feasible for big numbers (overflow risk).
       - Stacks: Elegant, avoids reversing but uses O(N+M) extra space.
       - Optimal Reverse: In-place, O(1) extra space. BEST for interviews.
    ------------------------------------------------------- */

    return 0;
}
