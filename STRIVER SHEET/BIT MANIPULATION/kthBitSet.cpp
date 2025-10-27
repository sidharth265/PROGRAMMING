#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Check if K-th Bit is Set
🔗 Problem Link: (e.g., GeeksforGeeks - https://www.geeksforgeeks.org/problems/check-whether-k-th-bit-is-set-or-not)

📌 Problem Statement:
Given an integer `n` and a position `k`, check whether the k-th bit of `n` 
is set (i.e., equal to 1) in its binary representation.

👉 The bit positions are **0-indexed** from the rightmost side.

----------------------------------------------------------
🧩 Example 1:
Input:
    n = 5
    k = 2
Output:
    true
Explanation:
    Binary representation of 5 is (101).
    The 2nd bit (from right, 0-indexed) is 1 → hence set.

🧩 Example 2:
Input:
    n = 4
    k = 0
Output:
    false
Explanation:
    Binary representation of 4 is (100).
    The 0th bit is 0 → not set.
----------------------------------------------------------
*/

//////////////////////////////////////////////////////////////
// Approach 1: Brute Force (Divide by 2 until kth bit)
// 💡 Idea:
//   - Convert number to binary manually by dividing by 2.
//   - At each step, reduce `k`.
//   - When k reaches 0, check the remainder (n % 2).
//
// 🧩 Algorithm:
//   1. Loop while `n > 0`.
//   2. If k = 0 → check whether `n % 2 == 1`.
//   3. Else, divide n by 2 and decrement k.
//   4. If loop ends, return false.
//
// ⏱ Time Complexity: O(log n)   (due to repeated division by 2)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
bool checkKthBit_BruteForce(int n, int k) {
    while (n > 0) {
        if (k == 0) {
            return (n % 2 == 1);
        }
        n /= 2;
        k--;
    }
    return false;
}

//////////////////////////////////////////////////////////////
// Approach 2: Efficient Bitwise AND
// 💡 Idea:
//   - Left shift 1 by `k` positions to create mask (1 << k).
//   - Perform bitwise AND with n.
//   - If result != 0 → kth bit is set.
//
// 🧩 Algorithm:
//   1. Compute mask = (1 << k).
//   2. Return (n & mask) != 0.
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
bool checkKthBit_Bitwise(int n, int k) {
    return (n & (1 << k)) != 0;
}

//////////////////////////////////////////////////////////////
// Approach 3: Using Right Shift
// 💡 Idea:
//   - Instead of creating a mask, right shift `n` by `k` bits.
//   - Then check the least significant bit (n >> k) & 1.
//
// 🧩 Algorithm:
//   1. Compute shifted = n >> k.
//   2. Return (shifted & 1).
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
bool checkKthBit_RightShift(int n, int k) {
    return ((n >> k) & 1) == 1;
}

//////////////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////////////
int main() {
    vector<pair<int,int>> testCases = {
        {5, 2},   // Binary: 101 → 2nd bit set
        {5, 0},   // Binary: 101 → 0th bit set
        {4, 0},   // Binary: 100 → 0th bit not set
        {8, 3},   // Binary: 1000 → 3rd bit set
        {8, 1}    // Binary: 1000 → 1st bit not set
    };

    for (auto [n, k] : testCases) {
        cout << "n = " << n << ", k = " << k << endl;

        // Using Brute Force
        cout << "   Approach 1 (Brute Force): "
             << (checkKthBit_BruteForce(n, k) ? "Set" : "Not Set") << endl;

        // Using Bitwise AND
        cout << "   Approach 2 (Bitwise AND): "
             << (checkKthBit_Bitwise(n, k) ? "Set" : "Not Set") << endl;

        // Using Right Shift
        cout << "   Approach 3 (Right Shift): "
             << (checkKthBit_RightShift(n, k) ? "Set" : "Not Set") << endl;

        cout << "-------------------------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1 (Brute Force): Easy to understand, O(log n)
    // - Approach 2 (Bitwise AND): Efficient, O(1)
    // - Approach 3 (Right Shift): Efficient, O(1), slightly simpler
    ////////////////////////////////////////////////////////////

    return 0;
}
