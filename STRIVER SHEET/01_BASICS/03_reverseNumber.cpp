#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Reverse an Integer

Problem Statement:
Given an integer x, reverse its digits. If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1],
return 0.

Handle negative integers as well.

-----------------------------------------------------------
Example 1:
Input: x = 123
Output: 321

Example 2:
Input: x = -123
Output: -321

Example 3:
Input: x = 120
Output: 21

Example 4:
Input: x = 1534236469
Output: 0 (because reversed integer overflows 32-bit range)

===========================================================
*/

/*-----------------------------------------------------------
Approach: Iterative digit extraction and reversal with overflow check
💡 Idea:
- Extract digits from x from right to left.
- Build reversed number by multiplying accumulated number by 10 and adding digit.
- Check for overflow before multiplying or adding.
- Return 0 if overflow occurs; else return reversed number after processing.

🧩 Algorithm:
1. Initialize ans = 0.
2. While x != 0:
   a. Extract last digit: digit = x % 10.
   b. Check if ans will overflow:
      - If ans > INT_MAX / 10 or ans < INT_MIN / 10, return 0.
   c. ans = ans * 10 + digit.
   d. x /= 10.
3. Return ans.

⏱ Time Complexity: O(log n) (number of digits)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
int reverseNumber(int x) {
    int ans = 0;
    while (x != 0) {
        int digit = x % 10;
        if (ans > INT_MAX / 10 || ans < INT_MIN / 10) {
            return 0;
        }
        ans = ans * 10 + digit;
        x /= 10;
    }
    return ans;
}

/*-----------------------------------------------------------
Main function: Tests reverseNumber with sample inputs
-----------------------------------------------------------*/
int main() {
    vector<int> testCases = {123, -123, 120, 1534236469};

    for (int num : testCases) {
        cout << "Input: " << num << ", Reversed: " << reverseNumber(num) << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach:
       - Extract digits and construct reversed number iteratively.
       - Check for overflow before each multiplication and addition.
    Time Complexity: O(log n)
    Space Complexity: O(1)
    -----------------------------------------------------------
    */
    return 0;
}
