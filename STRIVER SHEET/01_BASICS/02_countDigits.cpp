#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Count Digits That Evenly Divide a Number

Problem Statement:
Given an integer n, count how many digits in n evenly divide n.
A digit d evenly divides n if d != 0 and n % d == 0.

-----------------------------------------------------------
Example 1:
Input: n = 12
Output: 2
Explanation: Digits are 1 and 2. Both divide 12 evenly.

Example 2:
Input: n = 1012
Output: 3
Explanation: Digits are 1, 0, 1, 2. 1,1 and 2 divide 1012 evenly (0 is ignored).

===========================================================
*/

/*-----------------------------------------------------------
Approach: Extract digits and check divisibility
💡 Idea:
- Extract digits by repeatedly taking modulo 10.
- Increment count if digit divides n evenly and digit != 0.

🧩 Algorithm:
1. Initialize count to 0.
2. Make a copy of n to iterate over its digits.
3. While copy > 0:
   a) Get last digit = copy % 10.
   b) If digit != 0 and n % digit == 0, increment count.
   c) Reduce copy by dividing by 10.
4. Return count.

⏱ Time Complexity: O(log n) (number of digits)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
int evenlyDivides(int n) {
    int count = 0;
    int num = n;
    while (num > 0) {
        int digit = num % 10;
        if (digit != 0 && n % digit == 0) {
            count++;
        }
        num /= 10;
    }
    return count;
}

/*-----------------------------------------------------------
Main function: Test cases for counting digits that divide number
-----------------------------------------------------------*/
int main() {
    vector<int> testCases = {12, 1012, 123456, 111, 0, 100};

    for (int n : testCases) {
        cout << "Number: " << n << ", Count of digits that evenly divide it: "
             << evenlyDivides(n) << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach: Extract digits and check divisible condition.
       Time Complexity: O(log n)
       Space Complexity: O(1)

    Efficiently processes each digit once.
    -----------------------------------------------------------
    */
    return 0;
}
