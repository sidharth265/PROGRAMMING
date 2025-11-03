#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Implement Stack using Queues
 Problem Link: (Common interview question)

 Problem Statement:
 Implement a stack using two queues. The stack should provide:
 - push(x): add element x to top of stack
 - pop(): remove and return top element
 - top(): return top element without removing
 - getSize(): return number of elements
 - isEmpty(): check if the stack is empty

 Use two queues and mimick stack behavior (LIFO) with FIFO queues.

-------------------------------------------------
 Example:
 Input:
   push(1), push(2), top(), pop(), getSize(), isEmpty()
 Output:
   Top element: 2
   Popped element: 2
   Size of stack: 1
   Is stack empty? No
-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Using Two Queues (Push costlier)
// -------------------------------------------------
/*
💡 Idea:
   - On push, enqueue new element to empty queue (q2).
   - Move all elements from q1 to q2 to reorder.
   - Swap q1 and q2; now q1's front is the new top.
   - pop and top operate on q1 directly.

⏱ Time Complexity:
   - push: O(n) due to moving elements
   - pop, top, size, isEmpty: O(1)
📦 Space Complexity: O(n)
*/

class Stack {
    queue<int> q1;
    queue<int> q2;

public:
    Stack() {
        // Constructor does not need initialization beyond queue defaults
    }

    int getSize() {
        return (int)q1.size();
    }

    bool isEmpty() {
        return q1.empty();
    }

    void push(int element) {
        // Push element onto q2
        q2.push(element);

        // Push all elements of q1 to q2 to maintain order
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        // Swap q1 and q2
        swap(q1, q2);
    }

    int pop() {
        if (q1.empty()) return -1;
        int front = q1.front();
        q1.pop();
        return front;
    }

    int top() {
        if (q1.empty()) return -1;
        return q1.front();
    }
};


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    Stack s;
    s.push(1);
    s.push(2);

    cout << "Top element: " << s.top() << endl;          // Should print 2
    cout << "Popped element: " << s.pop() << endl;       // Should print 2
    cout << "Size of stack: " << s.getSize() << endl;    // Should print 1
    cout << "Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl; // Should print No

    s.pop();  // Pop last element

    cout << "Is stack empty after popping all? " << (s.isEmpty() ? "Yes" : "No") << endl; // Should print Yes

    return 0;
}
