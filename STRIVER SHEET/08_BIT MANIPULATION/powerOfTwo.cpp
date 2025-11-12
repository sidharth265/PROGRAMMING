#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Check if a Number is Power of Two
🔗 Problem Link: (Classic Interview Problem / LeetCode 231 - Power of Two)

📌 Problem Statement:
Given an integer `n`, check whether it is a power of two or not.  
That means determine if there exists an integer `k` such that:
    n = 2^k   (k >= 0)

----------------------------------------------------------
🧩 Example 1:
Input:
    n = 16
Output:
    true
Explanation:
    16 = 2^4. Hence, it is a power of two.

🧩 Example 2:
Input:
    n = 18
Output:
    false
Explanation:
    18 cannot be expressed as 2^k for any integer k.

🧩 Example 3:
Input:
    n = 1
Output:
    true
Explanation:
    1 = 2^0 → valid power of two.
----------------------------------------------------------
*/


//////////////////////////////////////////////////////////////
// Approach 1: Brute Force (Repeated Division by 2)
// 💡 Idea:
//   Keep dividing the number by 2 until it becomes 1.
//   - If at any stage it is not divisible by 2, return false.
//   - If it becomes 1, return true.
//
// 🧩 Algorithm:
//   1. If n <= 0 → return false.
//   2. While n % 2 == 0, divide by 2.
//   3. After the loop, if n == 1 → return true, else false.
//
// ⏱ Time Complexity: O(log n)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
bool isPowerOfTwo_BruteForce(int n) {
    if (n <= 0) return false;
    while (n % 2 == 0) n /= 2;
    return (n == 1);
}


//////////////////////////////////////////////////////////////
// Approach 2: Bit Manipulation Trick (n & (n-1))
// 💡 Idea:
//   - A power of two has exactly one bit set in binary representation.
//   - Example: 1 (0001), 2 (0010), 4 (0100), 8 (1000).
//   - Property: n & (n-1) == 0 only when n is power of two.
//
// 🧩 Algorithm:
//   1. If n <= 0 → return false.
//   2. Return (n & (n - 1)) == 0.
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
bool isPowerOfTwo_Bitwise(int n) {
    if (n <= 0) return false;
    return (n & (n - 1)) == 0;
}


//////////////////////////////////////////////////////////////
// Approach 3: Using Math Logarithm
// 💡 Idea:
//   A number n is power of two if log2(n) is an integer.
//   - Compute log2(n) and check if it equals floor(log2(n)).
//
// 🧩 Algorithm:
//   1. If n <= 0 → return false.
//   2. Compute logValue = log2(n).
//   3. If floor(logValue) == ceil(logValue) → return true.
//   4. Else false.
//
// ⏱ Time Complexity: O(1) (depends on system math library)
// 📦 Space Complexity: O(1)
// ⚠️ Note: May suffer from floating-point precision issues.
//////////////////////////////////////////////////////////////
bool isPowerOfTwo_Log(int n) {
    if (n <= 0) return false;
    double logValue = log2(n);
    return floor(logValue) == ceil(logValue);
}


//////////////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////////////
int main() {
    vector<int> testCases = {16, 18, 1, 2, 3, 64, 1023, 1024, 0, -8};

    for (int n : testCases) {
        cout << "Checking n = " << n << "\n";

        // Approach 1 (Brute Force)
        cout << "   Approach 1 (Brute Force): "
             << (isPowerOfTwo_BruteForce(n) ? "Power of Two" : "Not Power of Two") << endl;

        // Approach 2 (Bitwise)
        cout << "   Approach 2 (Bitwise): "
             << (isPowerOfTwo_Bitwise(n) ? "Power of Two" : "Not Power of Two") << endl;

        // Approach 3 (Logarithm)
        cout << "   Approach 3 (Logarithm): "
             << (isPowerOfTwo_Log(n) ? "Power of Two" : "Not Power of Two") << endl;

        cout << "-------------------------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1 (Brute Force / Division): Works fine, O(log n).
    // - Approach 2 (Bit Manipulation): Best (clean & efficient), O(1).
    // - Approach 3 (Logarithm): Elegant but risky due to floating point precision.
    ////////////////////////////////////////////////////////////

    return 0;
}
