#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Find Pairs with Given Sum in a Doubly Linked List
Link: (GFG Interview Problem)

Problem Statement:
Given a sorted doubly linked list of distinct integers, 
and a target sum `k`, return all pairs of nodes whose sum = k.

---------------------------------------------------------------
Examples:

Example 1:
Input: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6, k = 7
Output: (1,6) (2,5) (3,4)

Example 2:
Input: 1 <-> 2 <-> 3 <-> 4, k = 8
Output: (2,6)

Example 3:
Input: 1 <-> 2 <-> 3, k = 10
Output: No pairs found
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Definition for DLL Node
------------------------------------------------------------ */
class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int data) {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};


/* -----------------------------------------------------------
   Utility Functions
------------------------------------------------------------ */
Node* createLinkedList(vector<int> values) {
    if(values.empty()) return NULL;
    Node* head = new Node(values[0]);
    Node* curr = head;
    for(int i = 1; i < values.size(); i++) {
        Node* newNode = new Node(values[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while(curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}


/* -----------------------------------------------------------
   Approach 1: Brute Force
------------------------------------------------------------
💡 Idea:
- For every node, traverse rest of list and check if sum=k.
- Collect all valid pairs.

🧩 Algorithm:
1. Traverse list with two nested loops.
2. If (node1->data + node2->data == k) → store pair.
3. Output all valid pairs.

⏱ Time Complexity: O(N^2)
📦 Space Complexity: O(1)
⚠️ Not efficient for interviews.
------------------------------------------------------------ */
vector<pair<int,int>> findPairsBrute(Node* head, int k) {
    vector<pair<int,int>> result;
    for(Node* p = head; p; p=p->next) {
        for(Node* q=p->next; q; q=q->next) {
            if(p->data + q->data == k) {
                result.push_back({p->data, q->data});
            }
        }
    }
    return result;
}


/* -----------------------------------------------------------
   Approach 2: Two-Pointer Technique (Optimal)
------------------------------------------------------------
💡 Idea:
- Since DLL is sorted, we can use two-pointer approach 
  (like in two-sum on sorted array).
- Start: first=head, last=tail.
- If sum==k → store and move both pointers inward.
- If sum>k → move last backwards.
- If sum<k → move first forward.

🧩 Algorithm:
1. Let first=head, last=tail (rightmost node).
2. While(first < last):
   - Check sum=first->data + last->data.
   - If sum==k → store pair, move both.
   - Else adjust pointers.
3. Return list of pairs.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(1) ✅ Interview Favorite
------------------------------------------------------------ */
vector<pair<int,int>> findPairsTwoPointer(Node* head, int k) {
    vector<pair<int,int>> result;

    if(!head) return result;
    Node* first = head;
    Node* last = head;
    while(last->next) last = last->next; // move to tail

    while(first && last && first != last && last->next != first) {
        int sum = first->data + last->data;
        if(sum == k) {
            result.push_back({first->data, last->data});
            first = first->next;
            last = last->prev;
        } 
        else if(sum > k) {
            last = last->prev;
        }
        else {
            first = first->next;
        }
    }

    return result;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<int> values = {1, 2, 3, 4, 5, 6};
    Node* head = createLinkedList(values);

    cout << "Original Doubly Linked List: ";
    printList(head);

    int k = 7;

    // Brute Force
    vector<pair<int,int>> pairs1 = findPairsBrute(head, k);
    cout << "\nPairs (Brute Force): ";
    if(pairs1.empty()) cout << "No pairs found";
    else for(auto &p : pairs1) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    // Optimal Two-Pointer
    vector<pair<int,int>> pairs2 = findPairsTwoPointer(head, k);
    cout << "Pairs (Two Pointer Optimal): ";
    if(pairs2.empty()) cout << "No pairs found";
    else for(auto &p : pairs2) cout << "(" << p.first << "," << p.second << ") ";
    cout << endl;

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Brute Force: O(N^2), easy but inefficient.
       - Two-Pointer:
         + Uses DLL property + sorted order.
         + O(N) time, O(1) space.
         + Best and preferred in interviews.
    ------------------------------------------------------- */
    return 0;
}
