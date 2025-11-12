#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Check if a Number is Odd or Even
🔗 Problem Link: (Classic Problem - asked in basic coding interviews)

📌 Problem Statement:
Given an integer `n`, determine if the number is odd or even.

👉 Return true (or print message) if the number is odd, otherwise false/even.

----------------------------------------------------------
🧩 Example 1:
Input:
    n = 5
Output:
    "5 is odd."
Explanation:
    Binary of 5 = 101 → Least Significant Bit (LSB) = 1 → odd.

🧩 Example 2:
Input:
    n = 8
Output:
    "8 is even."
Explanation:
    Binary of 8 = 1000 → LSB = 0 → even.
----------------------------------------------------------
*/


//////////////////////////////////////////////////////////////
// Approach 1: Using Modulo Operator
// 💡 Idea:
//   - A number is odd if `n % 2 != 0`; otherwise even.
//
// 🧩 Algorithm:
//   1. If (n % 2 == 0) → even
//   2. Else → odd
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
bool isOdd_Modulo(int n) {
    return (n % 2 != 0);
}


//////////////////////////////////////////////////////////////
// Approach 2: Using Bitwise AND
// 💡 Idea:
//   - Odd numbers always have their least significant bit = 1.
//   - So check if (n & 1) == 1.
//   - Faster than `%` because it's pure bit operation.
//
// 🧩 Algorithm:
//   1. Compute `n & 1`.
//   2. If result = 1 → odd, otherwise even.
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
bool isOdd_Bitwise(int n) {
    return (n & 1);
}


//////////////////////////////////////////////////////////////
// Approach 3: Using Right Shift & Left Shift Trick
// 💡 Idea:
//   - Shift right by 1 (n >> 1 removes LSB).
//   - Then shift it back left (<< 1).
//   - If result == original number → even, else odd.
//
// 🧩 Algorithm:
//   1. Compute `((n >> 1) << 1)`.
//   2. Compare with original number:
//      - If equal → even
//      - Else → odd
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
bool isOdd_ShiftTrick(int n) {
    return (((n >> 1) << 1) != n);
}


//////////////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////////////
int main() {
    vector<int> testCases = {5, 8, -3, 0, 17, 1024};

    for (int n : testCases) {
        cout << "Checking number: " << n << "\n";

        // Using Modulo
        cout << "   Approach 1 (Modulo): "
             << (isOdd_Modulo(n) ? "Odd" : "Even") << endl;

        // Using Bitwise AND
        cout << "   Approach 2 (Bitwise AND): "
             << (isOdd_Bitwise(n) ? "Odd" : "Even") << endl;

        // Using Shift Trick
        cout << "   Approach 3 (Shift Trick): "
             << (isOdd_ShiftTrick(n) ? "Odd" : "Even") << endl;

        cout << "-------------------------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1 (Modulo): Very simple & intuitive, but slightly slower.
    // - Approach 2 (Bitwise AND): Fastest and most commonly used.
    // - Approach 3 (Shift Trick): More of a clever approach, not practical.
    ////////////////////////////////////////////////////////////

    return 0;
}
