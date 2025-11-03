#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Implement Queue using Stacks
Link: (LeetCode #232)

Problem Statement:
Implement a queue using two stacks.  
The queue must support the following operations:
- enQueue(x): Insert element at the end
- deQueue(): Remove element from the front
- peek(): Get the front element
- isEmpty(): Check if queue is empty

Constraints:
All operations should run efficiently using stack operations (push/top/pop).

---------------------------------------------------------------
Examples:

Example 1:
Input:
enQueue(1), enQueue(2), peek(), deQueue(), isEmpty(), peek()
Output:
Front=1, Dequeued=1, Empty=No, Front=2

Example 2:
Input: deQueue() on empty queue
Output: -1 or error message
---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Approach 1: Push Costly (Move all elements during enQueue)
------------------------------------------------------------
💡 Idea:
- Always keep the "front" element accessible at top of one stack.
- For enQueue:
  1. Move all elements from output → input
  2. Push new element into input
  3. Move all back from input → output
- For deQueue/peek: Directly read/pop from output.

⏱ Time Complexity:
- enQueue: O(N)
- deQueue & peek: O(1)
📦 Space: O(N)
------------------------------------------------------------ */
class QueuePushCostly {
    stack<int> input, output;
public:
    void enQueue(int val) {
        // Step 1: move output to input
        while(!output.empty()) {
            input.push(output.top());
            output.pop();
        }
        // Step 2: push new element
        input.push(val);
        // Step 3: move back all to output
        while(!input.empty()) {
            output.push(input.top());
            input.pop();
        }
    }

    int deQueue() {
        if(output.empty()) return -1;
        int val = output.top();
        output.pop();
        return val;
    }

    int peek() {
        if(output.empty()) return -1;
        return output.top();
    }

    bool isEmpty() {
        return output.empty();
    }
};


/* -----------------------------------------------------------
   Approach 2: Pop Costly (Efficient enQueue)
------------------------------------------------------------
💡 Idea:
- Enqueue directly into input stack.
- For deQueue:
  - If output empty → transfer all elements input→output (reverses order).
  - Pop from output.
- This way enQueue is O(1).

⏱ Time Complexity:
- enQueue: O(1)
- deQueue, peek: Amortized O(1) (each element moved once)
📦 Space: O(N)
✅ Better for frequent enQueue operations
------------------------------------------------------------ */
class QueuePopCostly {
    stack<int> input, output;
public:
    void enQueue(int val) {
        input.push(val);
    }

    int deQueue() {
        if(output.empty()) {
            if(input.empty()) return -1;
            while(!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        int val = output.top();
        output.pop();
        return val;
    }

    int peek() {
        if(output.empty()) {
            if(input.empty()) return -1;
            while(!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        return output.top();
    }

    bool isEmpty() {
        return (input.empty() && output.empty());
    }
};


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    cout << "=== Using Push Costly Queue ===" << endl;
    QueuePushCostly q1;
    q1.enQueue(1);
    q1.enQueue(2);
    cout << "Front: " << q1.peek() << endl;          // 1
    cout << "Dequeued: " << q1.deQueue() << endl;   // 1
    cout << "Is Empty? " << (q1.isEmpty()?"Yes":"No") << endl;
    cout << "Front After Dequeue: " << q1.peek() << endl; // 2

    cout << "\n=== Using Pop Costly Queue ===" << endl;
    QueuePopCostly q2;
    q2.enQueue(10);
    q2.enQueue(20);
    q2.enQueue(30);
    cout << "Front: " << q2.peek() << endl;          // 10
    cout << "Dequeued: " << q2.deQueue() << endl;   // 10
    cout << "Dequeued: " << q2.deQueue() << endl;   // 20
    cout << "Is Empty? " << (q2.isEmpty()?"Yes":"No") << endl;
    cout << "Front After Dequeue: " << q2.peek() << endl; // 30

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Push Costly:
         + enQueue O(N), deQueue O(1).
         + Good if deQueue is much more frequent.
       - Pop Costly (Better):
         + enQueue O(1), deQueue amortized O(1).
         + Preferred in interviews.
    ------------------------------------------------------- */
    return 0;
}
