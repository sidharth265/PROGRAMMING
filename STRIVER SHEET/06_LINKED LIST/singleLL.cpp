#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Implementation of Singly Linked List (SLL)
Link: (Classic Data Structure Implementation)

Problem Statement:
Implement a **Singly Linked List** with the following operations:
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
   - Find length of list

---------------------------------------------------------------
Examples (Operations on List):

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
   Definition for Singly Linked List Node
------------------------------------------------------------ */
class Node {
public:
    int val;
    Node* next;
    Node(int val) {
        this->val = val;
        this->next = NULL;
    }
    ~Node() {
        if (this->next != NULL) {
            delete next;
            this->next = NULL;
        }
    }
};


/* -----------------------------------------------------------
   Utility Functions
------------------------------------------------------------ */
void printList(Node* head) {
    Node* curr = head;
    while(curr != NULL) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
}

int length(Node* head) {
    int len = 0;
    Node* curr = head;
    while(curr != NULL) {
        len++;
        curr = curr->next;
    }
    return len;
}

bool search(Node* head, int val) {
    Node* curr = head;
    while(curr != NULL) {
        if(curr->val == val) return true;
        curr = curr->next;
    }
    return false;
}


/* -----------------------------------------------------------
   Insertion Operations
------------------------------------------------------------
All Insertions:
⏱ Time Complexity: O(1) for head; O(N) for tail/pos
📦 Space Complexity: O(1)
------------------------------------------------------------ */

// Insert at Head
void insertAtHead(Node** head, int val) {
    Node* newNode = new Node(val);
    newNode->next = *head;
    *head = newNode;
}

// Insert at Tail
void insertAtTail(Node** head, int val) {
    Node* newNode = new Node(val);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* curr = *head;
    while(curr->next) curr = curr->next;
    curr->next = newNode;
}

// Insert at Position (1-based index)
void insertAtPos(Node** head, int val, int pos) {
    Node* newNode = new Node(val);
    if(pos == 1) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    Node* curr = *head;
    while(pos > 2 && curr != NULL) {
        curr = curr->next;
        pos--;
    }
    if(curr == NULL) return; // invalid position
    newNode->next = curr->next;
    curr->next = newNode;
}


/* -----------------------------------------------------------
   Deletion Operations
------------------------------------------------------------
All Deletions:
⏱ Time Complexity: O(1) for head; O(N) for tail/pos
📦 Space Complexity: O(1)
------------------------------------------------------------ */

// Delete Head
void deleteHeadNode(Node** head) {
    if(*head == NULL) return;
    Node* temp = *head;
    *head = (*head)->next;
    temp->next = NULL;
    delete temp;
}

// Delete Tail
void deleteTailNode(Node** head) {
    if (*head == NULL) return;
    if((*head)->next == NULL) {
        delete *head;
        *head = NULL;
        return;
    }
    Node* curr = *head;
    while(curr->next->next) curr = curr->next;
    delete curr->next;
    curr->next = NULL;
}

// Delete Node by Value
void deleteNode(Node** head, int val) {
    if(*head == NULL) return;
    if((*head)->val == val) {
        deleteHeadNode(head);
        return;
    }
    Node* curr = *head;
    while(curr->next && curr->next->val != val) {
        curr = curr->next;
    }
    if(curr->next == NULL) return; // Not found
    Node* temp = curr->next;
    curr->next = temp->next;
    temp->next = NULL;
    delete temp;
}

// Delete Node at Position (1-based index)
void deleteAtPos(Node** head, int pos) {
    if (*head == NULL) return;
    if (pos == 1) {
        deleteHeadNode(head);
        return;
    }
    Node* curr = *head;
    while(curr && pos > 2) {
        curr = curr->next;
        pos--;
    }
    if(curr == NULL || curr->next == NULL) return; // out of bounds
    Node* temp = curr->next;
    curr->next = temp->next;
    temp->next = NULL;
    delete temp;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
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

    // Clean up memory
    delete head;

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Insert: Head O(1), Tail/Pos O(N)
       - Delete: Head O(1), Tail/Pos O(N)
       - Utilities: Search O(N), Length O(N)
       - Mastering SLL pointer ops is a foundation for advanced LL problems.
    ------------------------------------------------------- */
    return 0;
}
