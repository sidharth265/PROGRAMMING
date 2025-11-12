#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Queue Implementation using Linked List
Link: (Standard DS Implementation)

Problem Statement:
Implement a queue using a singly linked list with the following operations:
- enqueue(x): Insert element at rear of queue
- dequeue(): Remove element from front of queue
- getFront(): Get the front element
- getSize(): Get the size of queue
- isEmpty(): Check if queue is empty

Key Property:
- Unlike array-based implementation, linked list implementation 
  has no fixed size limit (dynamic memory).

---------------------------------------------------------------
Examples:

Example 1:
Input: enqueue(10), enqueue(20), enqueue(30)
Output: Front = 10, Size = 3

After dequeue → Front = 20, Size = 2

Example 2:
Input: dequeue() on empty queue
Output: Does nothing (safe handling)
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Node Definition for Linked List
------------------------------------------------------------ */
class Node {
public:
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = NULL;
    }
};


/* -----------------------------------------------------------
   Queue Implementation using Linked List
------------------------------------------------------------ */
class Queue {
    Node* front;
    Node* rear;
    int size;

public:
    // Constructor
    Queue() {
        front = NULL;
        rear = NULL;
        size = 0;
    }

    // Enqueue operation (add at rear)
    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (rear == NULL) {   // First node
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // Dequeue operation (remove from front)
    void dequeue() {
        if (front == NULL) {
            cout << "Queue is empty" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL;  // Queue became empty
        delete temp;
        size--;
    }

    // Get front element
    int getFront() {
        if (front != NULL) return front->data;
        cout << "Queue is empty" << endl;
        return -1; // Or throw exception
    }

    // Get size
    int getSize() {
        return size;
    }

    // Check if empty
    bool isEmpty() {
        return size == 0;
    }
};


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    Queue q;

    cout << "-----------------------------------" << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Front element: " << q.getFront() << endl; // 10
    cout << "Queue size: " << q.getSize() << endl;     // 3

    q.dequeue();
    cout << "Front after dequeue: " << q.getFront() << endl; // 20
    cout << "Size: " << q.getSize() << endl;                 // 2

    q.dequeue();
    q.dequeue();
    q.dequeue(); // extra dequeue (queue empty)

    cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl;

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Array-based Queue: Fixed size, uses circular indexing.
       - Linked List Queue (this):
         + Dynamic size.
         + Both enqueue & dequeue in O(1).
         + No shifting or wrap-around issues.
       - Tradeoff: Requires extra memory for next pointers.
    ------------------------------------------------------- */
    return 0;
}
