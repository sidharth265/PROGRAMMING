#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Intersection of Two Linked Lists
Link: (LeetCode #160 / GFG variant)

Problem Statement:
Given the heads of two singly linked-lists headA and headB, 
return the node at which the two lists intersect. 
If the two linked lists have no intersection, return null.

Note that the linked lists must retain their original structure 
after the function returns.

The intersection is defined if there exists a node such that:
- It appears in both lists
- After this node, both lists share all next nodes

---------------------------------------------------------------
Examples:

Example 1:
ListA: 1 -> 2 -> 3 -> 4 -> 5 -> 9 -> 10
ListB: 6 -> 7 -> 8 --------┘
Output: Node with value 9
Explanation: Both lists merge at node 9.

Example 2:
ListA: 1 -> 2 -> 3
ListB: 4 -> 5
Output: NULL
Explanation: No intersection.

Example 3:
ListA: 2 -> 6 -> 4
ListB: 1 -> 5
Output: NULL
Explanation: No intersection.
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


/* -----------------------------------------------------------
   Approach 1: Using Hashing (Brute Force)
------------------------------------------------------------
💡 Idea:
- Store addresses of all nodes from ListA in a hash set.
- Traverse ListB, and for each node check if already in set.
- If found, that’s the intersection node.

🧩 Algorithm:
1. Create a hash set.
2. Traverse ListA, insert each node pointer into set.
3. Traverse ListB, check each node in set.
4. The first match = intersection node.

⏱ Time Complexity: O(N + M)
📦 Space Complexity: O(N) 
------------------------------------------------------------ */
ListNode* getIntersectionNodeHashing(ListNode* headA, ListNode* headB) {
    unordered_set<ListNode*> visited;
    while (headA) {
        visited.insert(headA);
        headA = headA->next;
    }
    while (headB) {
        if (visited.find(headB) != visited.end())
            return headB;
        headB = headB->next;
    }
    return nullptr;
}


/* -----------------------------------------------------------
   Approach 2: Length Difference Method (Better)
------------------------------------------------------------
💡 Idea:
- Find lengths of both lists.
- Move the pointer of the longer list ahead by the length difference.
- Traverse both lists together until they meet or end.

🧩 Algorithm:
1. Calculate lengths of ListA and ListB.
2. Advance the longer list’s pointer by |lenA - lenB|.
3. Traverse simultaneously until both pointers are equal or NULL.
4. Return the intersection node.

⏱ Time Complexity: O(N + M)
📦 Space Complexity: O(1)
------------------------------------------------------------ */
int length(ListNode* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

ListNode* getIntersectionNodeLengthDiff(ListNode* headA, ListNode* headB) {
    int n1 = length(headA), n2 = length(headB);
    ListNode* curr1 = headA;
    ListNode* curr2 = headB;

    if (n2 > n1) {
        for (int i = 0; i < n2 - n1; i++) curr2 = curr2->next;
    } else {
        for (int i = 0; i < n1 - n2; i++) curr1 = curr1->next;
    }
    while (curr1 && curr2) {
        if (curr1 == curr2) return curr1;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return nullptr;
}


/* -----------------------------------------------------------
   Approach 3: Two Pointer Switch-over (Optimal, Elegant)
------------------------------------------------------------
💡 Idea:
- Use two pointers that start at heads of A and B.
- When one reaches NULL → redirect it to other list’s head.
- Eventually, both will either meet at intersection or NULL.

🧩 Algorithm:
1. Initialize two pointers pA=headA, pB=headB.
2. While pA != pB:
   - Move pA to pA->next, if NULL → move to headB.
   - Move pB to pB->next, if NULL → move to headA.
3. Return pA (= pB), which will be intersection or NULL.

⏱ Time Complexity: O(N + M)
📦 Space Complexity: O(1)
🚀 Interview Favorite!
------------------------------------------------------------ */
ListNode* getIntersectionNodeTwoPointers(ListNode* headA, ListNode* headB) {
    ListNode* a = headA;
    ListNode* b = headB;
    while (a != b) {
        a = (a == nullptr) ? headB : a->next;
        b = (b == nullptr) ? headA : b->next;
    }
    return a;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    // Build example lists
    vector<int> values1 = {1, 2, 3, 4, 5};
    vector<int> values2 = {6, 7, 8};
    
    ListNode* list1 = createLinkedList(values1);
    ListNode* list2 = createLinkedList(values2);

    // Creating a shared collision node
    ListNode* collisionNode = new ListNode(9);
    list1->next->next->next->next->next = collisionNode; // connect at node 9
    list2->next->next = collisionNode;                   // connect at node 9
    collisionNode->next = new ListNode(10);

    cout << "List 1: "; printList(list1);
    cout << "List 2: "; printList(list2);

    // Hashing Method
    ListNode* inter1 = getIntersectionNodeHashing(list1, list2);
    cout << "Hashing Intersection: " 
         << (inter1 ? to_string(inter1->val) : "NULL") << endl;

    // Length Difference Method
    ListNode* inter2 = getIntersectionNodeLengthDiff(list1, list2);
    cout << "Length Difference Intersection: " 
         << (inter2 ? to_string(inter2->val) : "NULL") << endl;

    // Two Pointer Method (Optimal)
    ListNode* inter3 = getIntersectionNodeTwoPointers(list1, list2);
    cout << "Two Pointer Intersection: " 
         << (inter3 ? to_string(inter3->val) : "NULL") << endl;

    // Cleanup (avoid double free since lists share nodes)
    delete list1; 
    delete list2; // deletes collisionNode & next chain too

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Hashing: Simple to implement, O(N) extra space.
       - Length Diff: Requires O(1) space, slightly more logic.
       - Two Pointer: Most elegant, O(1) space, short code. 
         → Recommended for interviews.
    ------------------------------------------------------- */
    return 0;
}
