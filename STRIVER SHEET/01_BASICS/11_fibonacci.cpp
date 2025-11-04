#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Nth Fibonacci Number

Problem Statement:
Given a number n, find the nth term of the Fibonacci sequence.

The Fibonacci sequence starts with 0 and 1, and each subsequent term is the sum of the two preceding ones.

-----------------------------------------------------------
Example 1:
Input: n = 1
Output: 0

Example 2:
Input: n = 5
Output: 3
Explanation: Sequence: 0, 1, 1, 2, 3...

Example 3:
Input: n = 10
Output: 34

===========================================================
*/

/*-----------------------------------------------------------
Approach: Iterative calculation of Fibonacci number
💡 Idea:
- Use two variables to track last two fibonacci numbers.
- Iterate from 3rd term to nth, summing last two numbers.
- Return the nth number.

🧩 Algorithm:
1. Initialize a = 0 (F1), b = 1 (F2).
2. If n == 1, return a.
3. Use loop from 3 to n:
   - c = a + b
   - update a = b, b = c
4. Return c after loop.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
int fibonacci(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;

    int a = 0, b = 1, c;
    for (int i = 3; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

/*-----------------------------------------------------------
Main function: Reads n, prints nth fibonacci number
-----------------------------------------------------------*/
int main() {
    int n;
    cout << "Enter the number of terms: ";
    cin >> n;
    cout << fibonacci(n) << endl;

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Iterative approach to find Nth Fibonacci number in O(n) time and O(1) space.
    -----------------------------------------------------------
    */
    return 0;
}
