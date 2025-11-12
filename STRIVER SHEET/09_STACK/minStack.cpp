#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Min Stack
 Problem Link: (LeetCode 155 or similar)
====================================================

📝 Problem Statement:
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

📌 Input:
- Sequence of stack operations (push, pop, top, getMin)

📌 Output:
- Results of top and getMin operations

----------------------------------------------------
🔹 Example:
push(5), push(3), push(7), top() -> 7, getMin() -> 3,
pop(), top() -> 3, getMin() -> 3
====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Using a single stack to store pairs (value, current min)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Store each element with the minimum element seen so far in the stack.
- This allows O(1) retrieval of min while pushing and popping.

🧩 Operations:
- push(val): push {val, min(val, currentMin)} pair.
- pop(): pop top
- top(): return top().first
- getMin(): return top().second

⏱ Time Complexity: O(1) for all operations  
📦 Space Complexity: O(n)
*/

class MinStack {
    stack<pair<int, int>> s;
public:
    MinStack() {}

    void push(int val) {
        int minimum = val;
        if (!s.empty()) minimum = min(val, s.top().second);
        s.push({val, minimum});
    }

    void pop() {
        if (!s.empty()) s.pop();
    }

    int top() {
        if (s.empty()) return -1;
        return s.top().first;
    }

    int getMin() {
        if (s.empty()) return -1;
        return s.top().second;
    }
};

//////////////////////////////////////////////////////
// Approach 2: Using modified stack values and a minimum variable
//////////////////////////////////////////////////////
/*
💡 Idea:
- Keep track of the minimum in a variable.
- When a new minimum is pushed, push a "coded" value (2 * val - minimum) to encode previous minimum.
- On pop, if top is less than current minimum, decode previous minimum.

⏱ Time Complexity: O(1) for all operations  
📦 Space Complexity: O(n)
*/

class MinStack2 {
    stack<int> s;
    int minimum;
public:
    MinStack2() : minimum(INT_MAX) {}

    void push(int val) {
        if (s.empty()) {
            s.push(val);
            minimum = val;
        } else {
            if (val < minimum) {
                s.push(2 * val - minimum);
                minimum = val;
            } else {
                s.push(val);
            }
        }
    }

    void pop() {
        if (s.empty()) return;
        int top = s.top(); s.pop();
        if (top < minimum) {
            minimum = 2 * minimum - top;
        }
    }

    int top() {
        if (s.empty()) return -1;
        int top = s.top();
        return (top < minimum) ? minimum : top;
    }

    int getMin() {
        return s.empty() ? -1 : minimum;
    }
};

//////////////////////////////////////////////////////
// Main function with example test case
//////////////////////////////////////////////////////
int main() {
    MinStack minStack;
    minStack.push(5);
    minStack.push(3);
    minStack.push(7);
    cout << "Top element: " << minStack.top() << endl;         // Should print 7
    cout << "Minimum element: " << minStack.getMin() << endl;  // Should print 3
    minStack.pop();
    cout << "Top element after pop: " << minStack.top() << endl;        // Should print 3
    cout << "Minimum element after pop: " << minStack.getMin() << endl; // Should print 3
    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Both approaches achieve O(1) time for push, pop, top, and getMin.
// Approach 1 uses extra space per element for min tracking.
// Approach 2 uses encoding with a single stack and minimum variable.
