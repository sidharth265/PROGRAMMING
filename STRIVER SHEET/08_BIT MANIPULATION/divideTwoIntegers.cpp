#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Divide Two Integers (without using *, /, or %)
---------------------------------------------------------------
LeetCode 29: https://leetcode.com/problems/divide-two-integers/

📌 Problem Statement:
Given two integers `dividend` and `divisor`, divide them without using
the multiplication, division, or mod operators.

Return the **quotient** after dividing `dividend` by `divisor`.  

⚠️ Notes:
- The result should truncate toward zero (i.e., remove fractional part).
- If division overflows (e.g., dividend = INT_MIN, divisor = -1),
  return INT_MAX.

---------------------------------------------------------------
Example 1:
Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = 3.333 → truncated to 3

Example 2:
Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7 / -3 = -2.333 → truncated to -2

Constraints:
- -2^31 <= dividend, divisor <= 2^31 - 1
- divisor != 0
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force (Repeated Subtraction)
---------------------------------------------------------------
💡 Idea:
- Keep subtracting divisor from dividend until dividend < divisor.
- Count how many times we subtract.
- Handle sign separately.

🧩 Algorithm:
1. Handle overflow case (dividend = INT_MIN, divisor = -1).
2. Determine sign based on dividend and divisor.
3. Convert dividend and divisor to positive `long long`.
4. Subtract divisor from dividend repeatedly until remainder < divisor.
5. Return quotient with sign.

⏱ Time Complexity: O(|quotient|) → too slow for large inputs.
📦 Space Complexity: O(1)
===============================================================
*/
int divideBruteForce(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX; // overflow case

    bool sign = (dividend < 0) == (divisor < 0); // true if same sign
    long long n = abs((long long)dividend);
    long long d = abs((long long)divisor);
    long long ans = 0;

    while (n >= d) {
        n -= d;
        ans++;
    }

    return sign ? ans : -ans;
}


/*
===============================================================
Approach 2: Optimized Bit Manipulation (Doubling)
---------------------------------------------------------------
💡 Idea:
- Use bit shifting to speed up repeated subtraction.
- Instead of subtracting divisor once, subtract powers of two multiples.
- Example: if dividend = 43, divisor = 3,
  subtract (3 << 3 = 24), then (3 << 2 = 12), etc.

🧩 Algorithm:
1. Handle overflow (dividend = INT_MIN, divisor = -1).
2. Determine sign.
3. Convert dividend, divisor to positive long long.
4. While dividend >= divisor:
   a) Find largest `count` such that (divisor << count) <= dividend
   b) Subtract (divisor << count) from dividend
   c) Add (1 << count) to quotient
5. Return quotient with sign.

⏱ Time Complexity: O(log n) — since divisor doubles each time.
📦 Space Complexity: O(1)
===============================================================
*/
int divideBitManipulation(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;

    bool sign = (dividend < 0) == (divisor < 0);
    long long n = abs((long long)dividend);
    long long d = abs((long long)divisor);
    long long ans = 0;

    while (n >= d) {
        long long temp = d, multiple = 1;
        while (n >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }
        n -= temp;
        ans += multiple;
    }

    return sign ? ans : -ans;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<pair<int,int>> testCases = {
        {10, 3},   // expected 3
        {7, -3},   // expected -2
        {1, 1},    // expected 1
        {-15, 2},  // expected -7
        {INT_MIN, -1}, // expected INT_MAX (overflow case)
        {INT_MIN, 1},  // expected INT_MIN
    };

    for (auto [dividend, divisor] : testCases) {
        cout << "Dividend=" << dividend << ", Divisor=" << divisor << "\n";
        cout << "➡ Brute Force Result: " << divideBruteForce(dividend, divisor) << "\n";
        cout << "➡ Bit Manipulation Result: " << divideBitManipulation(dividend, divisor) << "\n";
        cout << "-------------------------------\n";
    }

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Repeatedly subtract divisor from dividend.
       - ❌ Too slow when |dividend| is large (up to 2^31).
       - Time: O(|quotient|)

    2. Bit Manipulation (Optimal):
       - Uses subtraction by powers of 2.
       - ✅ Efficient, accepted in interviews and coding platforms.
       - Time: O(log n), Space: O(1)

    🔑 Conclusion:
    - Explain Brute Force for intuition.
    - Use Bit Manipulation solution in production/interviews.
    ===========================================================
    */
    return 0;
}
