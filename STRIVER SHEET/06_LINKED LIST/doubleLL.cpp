#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Implementation of Doubly Linked List (DLL)
Link: (Classic DS Problem)

Problem Statement:
Implement a **Doubly Linked List** with the following operations:
1. Insertion:
   - At head
   - At tail
   - At a given position
2. Deletion:
   - Head node
   - Tail node
   - Node by value
   - Node by position
3. Utility:
   - Print list
   - Search element
   - Find length of DLL

---------------------------------------------------------------
Examples:

Example:
Operations on DLL:
Start: 4
InsertAtHead(2): 2 4
InsertAtTail(1): 2 4 1
InsertAtPos(3, 3): 2 4 3 1
InsertAtPos(0, 1): 0 2 4 3 1
InsertAtPos(5, 6): 0 2 4 3 1 5
DeleteHead(): 2 4 3 1 5
DeleteTail(): 2 4 3 1
DeleteNode(3): 2 4 1
DeleteAtPos(2): 2 1
Length: 2
Search(1): Found
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Definition for Doubly Linked List Node
------------------------------------------------------------ */
class Node {
public:
    int val;
    Node* prev;
    Node* next;

    Node(int val) {
        this->val = val;
        this->next = nullptr;
        this->prev = nullptr;
    }
};


/* -----------------------------------------------------------
   Utility Functions
------------------------------------------------------------ */
void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
}

int length(Node* head) {
    int len = 0;
    Node* curr = head;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }
    return len;
}

bool search(Node* head, int val) {
    Node* curr = head;
    while (curr != NULL) {
        if (curr->val == val) return true;
        curr = curr->next;
    }
    return false;
}


/* -----------------------------------------------------------
   Insertion Operations
------------------------------------------------------------
All insertions take:
⏱ Time Complexity: O(1) for head, O(N) for tail/pos
📦 Space Complexity: O(1)
------------------------------------------------------------ */

// Insert at Head
void insertAtHead(Node** head, int val) {
    Node* newNode = new Node(val);
    if (*head) {
        newNode->next = *head;
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Insert at Tail
void insertAtTail(Node** head, int val) {
    Node* newNode = new Node(val);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* curr = (*head);
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
    newNode->prev = curr;
}

// Insert at Position (1-based index)
void insertAtPos(Node** head, int val, int pos) {
    Node* newNode = new Node(val);
    if (pos <= 1 || !*head) {
        insertAtHead(head, val);
        return;
    }

    Node* curr = *head;
    while (pos > 2 && curr->next != NULL) {
        curr = curr->next;
        pos--;
    }
    newNode->next = curr->next;
    newNode->prev = curr;
    if (curr->next != NULL) curr->next->prev = newNode;
    curr->next = newNode;
}


/* -----------------------------------------------------------
   Deletion Operations
------------------------------------------------------------
All deletions take:
⏱ Time Complexity: O(1) for head/tail, O(N) by value/pos
📦 Space Complexity: O(1)
------------------------------------------------------------ */

// Delete Head
void deleteHeadNode(Node** head) {
    if (!*head) return;
    Node* temp = *head;
    *head = (*head)->next;
    if (*head) (*head)->prev = NULL;
    temp->next = NULL;
    delete temp;
}

// Delete Tail
void deleteTailNode(Node** head) {
    if (!*head) return;
    if (!(*head)->next) {
        deleteHeadNode(head);
        return;
    }

    Node* curr = *head;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }
    Node* temp = curr->next;
    curr->next = NULL;
    temp->prev = NULL;
    delete temp;
}

// Delete by Value
void deleteNode(Node** head, int val) {
    if (!*head) return;
    if ((*head)->val == val) {
        deleteHeadNode(head);
        return;
    }

    Node* curr = *head;
    while (curr->next != NULL && curr->next->val != val) {
        curr = curr->next;
    }
    if (curr->next == NULL) return; // not found

    Node* temp = curr->next;
    curr->next = temp->next;
    if (temp->next != NULL) temp->next->prev = curr;
    temp->next = NULL;
    temp->prev = NULL;
    delete temp;
}

// Delete at Position
void deleteAtPos(Node** head, int pos) {
    if (!*head) return;
    if (pos == 1) {
        deleteHeadNode(head);
        return;
    }

    Node* curr = *head;
    while (curr != NULL && pos > 2) {
        curr = curr->next;
        pos--;
    }
    if (curr == NULL || curr->next == NULL) return; // out of bounds

    Node* temp = curr->next;
    curr->next = temp->next;
    if (temp->next != NULL) temp->next->prev = curr;
    temp->next = NULL;
    temp->prev = NULL;
    delete temp;
}


/* -----------------------------------------------------------
   Driver Code (Testing All Operations)
------------------------------------------------------------ */
int main() {
    Node* head = new Node(4);
    printList(head);

    insertAtHead(&head, 2);
    printList(head);

    insertAtTail(&head, 1);
    printList(head);

    insertAtPos(&head, 3, 3);
    printList(head);

    insertAtPos(&head, 0, 1);
    printList(head);

    insertAtPos(&head, 5, 6);
    printList(head);

    deleteHeadNode(&head);
    printList(head);

    deleteTailNode(&head);
    printList(head);

    deleteNode(&head, 3);
    printList(head);

    deleteAtPos(&head, 2);
    printList(head);

    cout << "Length of the list: " << length(head) << endl;
    cout << "Searching for 1: " << (search(head, 1) ? "Found" : "Not Found") << endl;

    // Cleanup
    Node* curr = head;
    while (curr != NULL) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Insertion: At head (O(1)), tail/pos (O(N))
       - Deletion: Head/Tail (O(1)), by value/pos (O(N))
       - Utilities: Search O(N), Length O(N)

       This problem is mostly **LL fundamentals**: mastering 
       pointer manipulation in DLL is crucial.
    ------------------------------------------------------- */

    return 0;
}
