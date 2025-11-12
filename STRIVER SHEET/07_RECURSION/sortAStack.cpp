#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Sort a Stack using Recursion
 Problem Link: (Common Interview Question)
====================================================

📝 Problem Statement:
Given a stack of integers, sort the stack in ascending order (smallest element at the bottom, largest at the top) 
using recursion. You are not allowed to use any extra data structures such as arrays, queues, or other stacks.
You can only utilize the call stack as auxiliary space.

📌 Input:
- A stack of integers

📌 Output:
- The stack sorted in ascending order

----------------------------------------------------
🔹 Example 1:
Input:  Stack(top → bottom) = [2, 4, 1, 3]  
Output: Stack(top → bottom) = [4, 3, 2, 1]  

Explanation:
The smallest element (1) remains at the bottom, followed by (2), then (3), and the largest (4) on top.

🔹 Example 2:
Input:  [34, 3, 31, 98, 92, 23]  
Output: [98, 92, 34, 31, 23, 3]  

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Brute Force (Using Extra Vector)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Pop elements into a vector/array.
- Sort the vector using built-in sorting.
- Push back into stack.

🧩 Algorithm:
1. Pop all stack elements into a vector.
2. Sort vector in ascending order.
3. Push elements back into the stack.

⏱ Time Complexity: O(n log n)  
📦 Space Complexity: O(n) (extra array)
*/

void sortStackBrute(stack<int> &st) {
    vector<int> temp;
    while(!st.empty()){
        temp.push_back(st.top());
        st.pop();
    }
    sort(temp.begin(), temp.end());
    for(int x : temp){
        st.push(x);
    }
}


//////////////////////////////////////////////////////
// Approach 2: Optimal (Recursion - No extra DS)
//////////////////////////////////////////////////////
/*
💡 Idea:
- Use recursion to pop every element.
- Recursively sort the smaller stack.
- Insert the popped element back in correct sorted position.

🧩 Algorithm:
1. Define helper insert(stack, ele):
   - If stack empty → push ele.
   - Else compare with stack top.
   - If top < ele → push ele on top.
   - Else pop top, recursively insert(ele), push top back.
2. Define Sort(stack):
   - If stack empty → return.
   - Pop top element, recursively Sort(stack).
   - Insert popped element in correct position.

⏱ Time Complexity: O(n^2) worst case (every insert may take O(n))
📦 Space Complexity: O(n) (recursion call stack)
*/

void insertAtRightPosition(stack<int> &s, int ele) {
    if(s.empty() || s.top() < ele) {
        s.push(ele);
        return;
    }
    int topEle = s.top(); s.pop();
    insertAtRightPosition(s, ele);
    s.push(topEle);
}

void sortStackRecursion(stack<int> &s) {
    if(s.empty()) return;
    int ele = s.top(); s.pop();
    sortStackRecursion(s);
    insertAtRightPosition(s, ele);
}


//////////////////////////////////////////////////////
// Utility: Print Stack (top → bottom)
//////////////////////////////////////////////////////
void printStack(stack<int> s) {
    while(!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}


//////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////
int main() {
    // Test Case 1
    stack<int> s1;
    s1.push(3);
    s1.push(1);
    s1.push(4);
    s1.push(2);

    cout << "Original Stack (Test 1): ";
    printStack(s1);
    sortStackRecursion(s1);
    cout << "Sorted (Recursion): ";
    printStack(s1);

    // Test Case 2
    stack<int> s2;
    s2.push(34); s2.push(3); s2.push(31);
    s2.push(98); s2.push(92); s2.push(23);

    cout << "\nOriginal Stack (Test 2): ";
    printStack(s2);
    sortStackRecursion(s2);
    cout << "Sorted (Recursion): ";
    printStack(s2);

    // Test Case 3 (Brute Force)
    stack<int> s3;
    s3.push(7); s3.push(1); s3.push(5); s3.push(3);

    cout << "\nOriginal Stack (Test 3): ";
    printStack(s3);
    sortStackBrute(s3);
    cout << "Sorted (Brute Force): ";
    printStack(s3);

    ////////////////////////////////////////////////
    // ✅ Approach Overview
    ////////////////////////////////////////////////
    cout << "\n========== Approach Overview ==========\n";
    cout << "1. Brute Force (Vector Sort)   -> O(n log n), Extra O(n)\n";
    cout << "2. Recursion (Optimal DS)      -> O(n^2), Extra O(n) [call stack only]\n";
    cout << "=======================================\n";

    return 0;
}
