#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Reverse a Stack using Recursion
 Problem Link: (Custom / Common Interview Question)
====================================================

📝 Problem Statement:
Given a stack of integers, reverse the stack using recursion.
You are not allowed to use any additional data structures 
(like arrays, queues, or other stacks). You can only use 
the call stack for extra memory.

📌 Input:
- A stack of integers

📌 Output:
- The stack should be reversed in place

----------------------------------------------------
🔹 Example 1:
Input:  Stack(top → bottom) = [5, 4, 3, 2, 1]  
Output: Stack(top → bottom) = [1, 2, 3, 4, 5]  

Explanation:
We used recursion to remove items one by one until
the stack was empty, then inserted them back at the
bottom to maintain reversed order.

🔹 Example 2:
Input:  [10, 20, 30]  
Output: [30, 20, 10]  

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Brute Force (Using extra vector/array)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Pop all elements from the stack into an array
- Push them back into the stack in reverse order

🧩 Algorithm:
1. Create a temporary vector.
2. Pop all elements from stack into vector.
3. Push elements from vector back into stack in reverse order.
4. Stack will be reversed.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) (extra vector)
*/

void reverseStackBrute(stack<int> &st) {
    vector<int> temp;
    while(!st.empty()) {
        temp.push_back(st.top());
        st.pop();
    }
    for(int x : temp)
        st.push(x);
}

//////////////////////////////////////////////////////
// Approach 2: Better (Using an auxiliary stack)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Use another stack as helper.
- Pop elements from original stack and push into helper.
- The helper stack will have reversed order.

🧩 Algorithm:
1. Create another empty stack helper.
2. While original stack not empty -> pop and push into helper.
3. Assign helper back to original.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) (extra stack)
*/

void reverseStackAuxiliary(stack<int> &st) {
    stack<int> helper;
    while(!st.empty()) {
        helper.push(st.top());
        st.pop();
    }
    st = helper;
}

//////////////////////////////////////////////////////
// Approach 3: Optimal (Recursion - No extra DS)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Use recursion (call stack as implicit storage).
- First pop all items recursively.
- Insert each popped element at the bottom of stack.

🧩 Algorithm:
1. Define helper insertAtBottom(stack, element):
   - If stack empty → push element.
   - Else pop top element, recursively insert element 
     at bottom, then push back popped element.
2. Define Reverse(stack):
   - If stack empty → return.
   - Pop top element, reverse remaining stack.
   - Insert popped element at bottom.

⏱ Time Complexity: O(n^2) worst case (inserting at bottom repeatedly costs O(n))
📦 Space Complexity: O(n) (recursion call stack)
*/

void insertAtBottom(stack<int> &st, int ele) {
    if(st.empty()) {
        st.push(ele);
        return;
    }
    int topEle = st.top(); st.pop();
    insertAtBottom(st, ele);
    st.push(topEle);
}

void reverseStackRecursion(stack<int> &st) {
    if(st.empty()) return;
    int ele = st.top(); st.pop();
    reverseStackRecursion(st);
    insertAtBottom(st, ele);
}

//////////////////////////////////////////////////////
// Utility: Print stack top → bottom
//////////////////////////////////////////////////////
void printStack(stack<int> st) {
    while(!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

//////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////
int main() {
    // Test Case 1
    stack<int> st1;
    for(int i=1;i<=5;i++) st1.push(i);  // 1..5

    cout << "Original Stack (Test 1): ";
    printStack(st1);

    reverseStackRecursion(st1);
    cout << "Reversed (Recursion): ";
    printStack(st1);

    // Test Case 2
    stack<int> st2;
    st2.push(10); st2.push(20); st2.push(30);

    cout << "\nOriginal Stack (Test 2): ";
    printStack(st2);

    reverseStackAuxiliary(st2);
    cout << "Reversed (Auxiliary Stack): ";
    printStack(st2);

    // Test Case 3
    stack<int> st3;
    st3.push(100); st3.push(200);

    cout << "\nOriginal Stack (Test 3): ";
    printStack(st3);

    reverseStackBrute(st3);
    cout << "Reversed (Brute Force w/ Vector): ";
    printStack(st3);

    ////////////////////////////////////////////////
    // ✅ Approach Overview
    ////////////////////////////////////////////////
    cout << "\n========== Approach Overview ==========\n";
    cout << "1. Brute Force (Vector)      -> O(n), Extra O(n)\n";
    cout << "2. Auxiliary Stack           -> O(n), Extra O(n)\n";
    cout << "3. Recursion (Optimal DS)    -> O(n^2), Extra O(n) [call stack only]\n";
    cout << "=======================================\n";

    return 0;
}
