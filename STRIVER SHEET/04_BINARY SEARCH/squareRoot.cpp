#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Sqrt(x) (LeetCode 69)
---------------------------------------------------------------
Link: https://leetcode.com/problems/sqrtx/

📌 Problem Statement:
Given a non-negative integer `x`, compute and return the square root of `x`,  
where only the **integer part** of the result is returned (decimal digits truncated).

⚠️ Important:
- You must not use any built-in exponent or sqrt functions.

---------------------------------------------------------------
Example 1:
Input: x = 4
Output: 2
Explanation: sqrt(4) = 2 exactly.

Example 2:
Input: x = 8
Output: 2
Explanation: sqrt(8) ≈ 2.828...
Truncated result = 2

Constraints:
- 0 <= x <= 2^31 - 1
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Start from 0 and keep checking i*i until it exceeds x.
- The answer is the largest i such that i*i <= x.

🧩 Algorithm:
1. Initialize i = 0.
2. While i*i <= x: keep incrementing i.
3. Once it exceeds, return i-1.

⏱ Time Complexity: O(sqrt(x))
📦 Space Complexity: O(1)
===============================================================
*/
int mySqrtBrute(int x) {
    long long i = 0; // use long long to prevent overflow in i*i
    while (i * i <= x) {
        i++;
    }
    return (int)(i - 1);
}


/*
===============================================================
Approach 2: Binary Search (Optimal)
---------------------------------------------------------------
💡 Idea:
- The function f(i) = i*i has a monotonic property.
- We can binary search in the range [0, x].

🧩 Algorithm:
1. Initialize low = 0, high = x.
2. While low <= high:
   a) mid = (low + high)/2
   b) If mid*mid == x → return mid
   c) If mid*mid < x → move low = mid+1
   d) Else → high = mid-1
3. Return high (since at exit, high will be floor(sqrt(x))).

⏱ Time Complexity: O(log x)
📦 Space Complexity: O(1)
===============================================================
*/
int mySqrtBinary(int x) {
    if (x < 2) return x; // quick handle for 0/1

    long long low = 0, high = x, ans = 0;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long sq = mid * mid;

        if (sq == x) return (int)mid;
        else if (sq < x) {
            ans = mid;       // mid is a candidate (floor sqrt)
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return (int)ans;
}


/*
===============================================================
Approach 3: Newton’s Method (Math based, very fast)
---------------------------------------------------------------
💡 Idea:
- Newton's method converges fast to sqrt(x).
- Apply iterative formula: guess = (guess + x/guess)/2 until stable.

🧩 Algorithm:
1. Start with guess = x (or x/2 for speed).
2. While guess*guess > x:
   - guess = (guess + x/guess)/2
3. Return guess.

⏱ Time Complexity: O(log x) (fast convergence)
📦 Space Complexity: O(1)
===============================================================
*/
int mySqrtNewton(int x) {
    if (x < 2) return x;
    
    long long guess = x;
    while (guess * guess > x) {
        guess = (guess + x / guess) / 2;
    }
    return (int)guess;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> testCases = {0, 1, 4, 8, 15, 100, 2147395599}; // large edge case

    for (int x : testCases) {
        cout << "Input: " << x << "\n";
        cout << "➡ Brute Force sqrt: " << mySqrtBrute(x) << "\n";
        cout << "➡ Binary Search sqrt: " << mySqrtBinary(x) << "\n";
        cout << "➡ Newton’s Method sqrt: " << mySqrtNewton(x) << "\n";
        cout << "------------------------------\n";
    }

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Check sequential squares until > x
       - ❌ Slow when x is very large (up to 2^31-1)
       - Time: O(sqrt(x))

    2. Binary Search (Optimal Practical Solution):
       - Uses monotonic property of squares.
       - ✅ Efficient for huge numbers.
       - Time: O(log x), Space: O(1)

    3. Newton’s Method:
       - Mathematical approximation that converges very quickly.
       - ✅ Extremely fast, also O(log x) but fewer iterations.
       - Slightly trickier but elegant.

    🔑 Conclusion:
    - Use Binary Search in interviews (clear + optimal).
    - Newton’s Method is great to mention for optimization.
    ===========================================================
    */
    return 0;
}
