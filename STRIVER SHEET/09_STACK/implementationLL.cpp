#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Custom Stack Implementation Using Linked List

 Problem Statement:
 Implement a stack data structure using a singly linked list, supporting standard operations:
 - push(x): add an element to the top of the stack
 - pop(): remove the top element and return its value
 - peek(): print the top element
 - isEmpty(): check if the stack is empty
 - printStack(): print all stack elements

 Handle empty stack cases gracefully in pop() and peek().

 Example:
 Input/Output:
   Push 1, Push 2, Push 3, Peek, Pop, Push 4, Print, Multiple Pops
   Output Sequence:
     3
     4 2 1
     Stack is Empty
-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Linked List-Based Stack
// -------------------------------------------------
/*
💡 Idea:
   - The stack is represented as a singly linked list, top pointing to the start.
   - Each push creates a new node and places it at the head.
   - Pop removes the node from the head and returns its value.
   - PrintStack traverses and prints all elements from top down.

⏱ Time Complexity:
   - Every operation runs in O(1) except printStack (O(n))
📦 Space Complexity: O(n) for n stack nodes
*/

class Node {
public:
    int data;
    Node *next;
    Node(int x) {
        data = x;
        next = nullptr;
    }
};

class Stack {
public:
    Node *top = nullptr;
    void peek() {
        if (isEmpty()) {
            cout << "Stack is Empty\n";
            return;
        }
        cout << top->data << endl;
    }
    void push(int x) {
        Node *newnode = new Node(x);
        newnode->next = top;
        top = newnode;
    }
    int pop() {
        if (isEmpty()) {
            cout << "Stack is Empty\n";
            return -1;
        }
        Node *temp = top;
        top = top->next;
        int ret = temp->data;
        delete temp;
        return ret;
    }
    void printStack() {
        Node *temp = top;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    bool isEmpty() {
        return top == nullptr;
    }
};


// -------------------------------------------------
// Main Function (Demo / Test Cases)
// -------------------------------------------------
int main() {
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << "Peek (should be 3): ";
    s.peek();
    cout << "Pop (should remove top): " << s.pop() << endl;
    s.push(4);
    cout << "Print Stack: ";
    s.printStack();

    cout << "Pop: " << s.pop() << endl;
    cout << "Pop: " << s.pop() << endl;
    cout << "Pop: " << s.pop() << endl;
    cout << "Pop (empty): " << s.pop() << endl;
    cout << "Print Stack (should be empty): ";
    s.printStack();

    // ✅ Approach Overview
    /*
    - All standard stack operations supported in O(1) time.
    - Linked-list implementation works for any number of pushes.
    - Operations safe when stack is empty.
    */
    return 0;
}
