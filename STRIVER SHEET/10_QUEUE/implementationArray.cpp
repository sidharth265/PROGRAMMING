#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Queue Implementation using Array (Circular Queue)
Link: (Standard DS implementation)

Problem Statement:
Implement a queue using arrays with the following operations:
- push(x): enqueue an element into the queue
- pop(): dequeue an element from the queue
- front(): get the front element of the queue

Your queue should:
- Work in O(1) time per operation
- Handle overflow and underflow properly
- Use circular array logic

---------------------------------------------------------------
Examples:

Example 1:
Input:
push(10), push(20), front(), pop(), front()
Output:
Front = 10, Front = 20

Example 2:
Input:
pop() on empty queue
Output:
Queue is empty
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Queue Class Implementation
------------------------------------------------------------ */
class Queue {
    int *arr;
    int start, end, size, capacity;

public:
    // Constructor
    Queue(int cap = 1000) {
        arr = new int[cap];
        start = 0;
        end = 0;
        size = 0;
        capacity = cap;
    }

    // Destructor
    ~Queue() {
        delete[] arr;
    }

    // Check if empty
    bool isEmpty() {
        return size == 0;
    }

    // Check if full
    bool isFull() {
        return size == capacity;
    }

    // Enqueue
    void push(int x) {
        if (isFull()) {
            cout << "Queue is full" << endl;
            return;
        }
        arr[end] = x;
        end = (end + 1) % capacity;
        size++;
    }

    // Dequeue
    void pop() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        start = (start + 1) % capacity;
        size--;
    }

    // Get front element
    int front() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1; // or throw an exception
        }
        return arr[start];
    }

    // Get current size
    int getSize() {
        return size;
    }
};


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    Queue q(5);  // Small capacity for testing

    cout << "-----------------------------------" << endl;
    q.push(10);
    q.push(20);
    q.push(30);

    cout << "Front element: " << q.front() << endl; // 10
    cout << "Size: " << q.getSize() << endl;        // 3

    q.pop();
    cout << "Front after pop: " << q.front() << endl; // 20
    cout << "Size: " << q.getSize() << endl;          // 2

    q.push(40);
    q.push(50);
    q.push(60);
    q.push(70);   // Should show "Queue is full"

    cout << "Front element: " << q.front() << endl; // 20

    q.pop(); q.pop(); q.pop(); q.pop(); q.pop();    // Pop until empty
    q.pop();  // Should show "Queue is empty"

    cout << "-----------------------------------" << endl;

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Queue implemented using a **circular array**.
       - All operations run in O(1).
       - Handles overflow (full) and underflow (empty).
       - Compared with STL `queue<int>`:
         + Similar function but explicit memory management.
    ------------------------------------------------------- */
    return 0;
}
