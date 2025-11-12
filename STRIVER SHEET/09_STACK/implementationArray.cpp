#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Custom Stack Implementation Using Array

 Problem Statement:
 Implement a stack data structure using a fixed-size array, supporting standard operations:
 - push(x): add an element to the top of the stack
 - pop(): remove the top element
 - top(): return the top element
 - isEmpty(): check if the stack is empty

 Handle stack overflow and underflow properly with meaningful messages.

 Example:
 Input/Output:
   Push 1, Push 2, Push 3, Pop, Top
   Output: 2
 Explanation:
   After pushing 1,2,3 and popping, top is 2.
-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Array-Based Stack
// -------------------------------------------------
/*
💡 Idea:
   - Use an integer array for storage.
   - Track the index of the top element.
   - Support common operations with error handling.

🧩 Algorithm:
   1. push(x): If not full, increment top and insert, else error.
   2. pop(): If not empty, decrement top, else error.
   3. top(): Return arr[top] if not empty, else error.
   4. isEmpty(): Return true if top == -1

⏱ Time Complexity: Each operation is O(1)
📦 Space Complexity: O(capacity)
*/

class Stack {
private:
    int *arr;
    int Top;
    int capacity;
public:
    Stack() {
        arr = new int[1000];
        Top = -1;
        capacity = 1000;
    }
    Stack(int size) {
        arr = new int[size];
        Top = -1;
        capacity = size;
    }
    ~Stack() {
        delete[] arr;
    }
    void push(int x) {
        if (Top + 1 >= capacity) {
            cout << "Stack overflow" << endl;
            return;
        }
        arr[++Top] = x;
    }
    void pop() {
        if (isEmpty()) {
            cout << "Stack underflow" << endl;
            return;
        }
        Top--;
    }
    int top() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return arr[Top];
    }
    bool isEmpty() {
        return Top == -1;
    }
};


// -------------------------------------------------
// Main Function (Demo / Test Cases)
// -------------------------------------------------
int main() {
    Stack s(5);

    cout << "Push 1\n"; s.push(1);
    cout << "Push 2\n"; s.push(2);
    cout << "Push 3\n"; s.push(3);
    cout << "Pop\n"; s.pop();
    cout << "Top: " << s.top() << endl; // Should print 2

    cout << "Pop\n"; s.pop();
    cout << "Pop\n"; s.pop();
    cout << "Pop (should cause underflow):\n"; s.pop();

    cout << "Push 4\n"; s.push(4);
    cout << "Push 5\n"; s.push(5);
    cout << "Push 6\n"; s.push(6);
    cout << "Push 7\n"; s.push(7); // Should cause overflow

    cout << "Top: " << s.top() << endl; // Should print 6

    // ✅ Approach Overview
    /*
    - All operations (push, pop, top, isEmpty) run in O(1).
    - Stack overflow/underflow handled gracefully.
    - Self-contained class.
    */

    return 0;
}
