#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Unset the Rightmost Set Bit
🔗 Problem Link: (Classic Bit Manipulation Interview Question)

📌 Problem Statement:
Given an integer n, unset (turn to 0) the rightmost set bit (the least significant 1-bit) in its binary representation and return the resulting number.

Notes:
- If n is 0, there is no set bit; the result should remain 0.
- Consider standard integer bit width.

----------------------------------------------------------
🧩 Example 1:
Input:
    n = 18
Output:
    16
Explanation:
    18 in binary = 10010. Unsetting the rightmost set bit (the bit at position 1) yields 10000 = 16.

🧩 Example 2:
Input:
    n = 12
Output:
    8
Explanation:
    12 in binary = 01100. Unsetting the rightmost set bit (position 2) yields 01000 = 8.

🧩 Example 3:
Input:
    n = 0
Output:
    0
Explanation:
    No set bits to unset; remains 0.
----------------------------------------------------------
*/

//////////////////////////////////////////////////////////////
// Approach 1: Bit Trick with (n & (n - 1))
// 💡 Idea:
//   - The expression (n - 1) flips all bits from the rightmost set bit to the end
//     (including turning that rightmost 1 to 0).
//   - ANDing n with (n - 1) clears the rightmost set bit while leaving other bits unchanged.
//
// 🧩 Algorithm:
//   1) If n == 0 → return 0 (nothing to clear).
//   2) Return n & (n - 1).
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
int unsetRightmostBit_BitTrick(int n) {
    return n & (n - 1);
}

//////////////////////////////////////////////////////////////
// Approach 2: Scan Bits Right-to-Left
// 💡 Idea:
//   - Iterate over bit positions from LSB to MSB.
//   - On finding the first set bit, clear it using n &= ~(1 << i).
//
// 🧩 Algorithm:
//   1) For i from 0 to 31 (assuming 32-bit int):
//        - If ((n >> i) & 1) == 1 → n &= ~(1 << i); break.
//   2) Return n.
//
// ⏱ Time Complexity: O(log n) in number of bits (constant 32 in practice)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
int unsetRightmostBit_Scan(int n) {
    for (int i = 0; i < 32; i++) {
        if ((n >> i) & 1) {
            n &= ~(1 << i);
            break;
        }
    }
    return n;
}

//////////////////////////////////////////////////////////////
// Approach 3: Isolate Rightmost Set Bit then Subtract
// 💡 Idea:
//   - Isolate the rightmost set bit as r = n & -n.
//   - Clear it using n - r (equivalent effect to n & (n-1)).
//
// 🧩 Algorithm:
//   1) If n == 0 → return 0.
//   2) r = n & -n.
//   3) Return n - r.
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
int unsetRightmostBit_Isolate(int n) {
    if (n == 0) return 0;
    int r = n & -n;
    return n - r;
}

//////////////////////////////////////////////////////////////
// Helper: print in binary with fixed width
//////////////////////////////////////////////////////////////
string bin(int x, int width = 8) {
    return bitset<32>(x).to_string().substr(32 - width);
}

//////////////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////////////
int main() {
    vector<int> testCases = {18, 12, 1, 0, 7, 32, 1023};

    cout << "Unset the rightmost set bit of n\n";
    cout << "--------------------------------\n";
    for (int n : testCases) {
        int a1 = unsetRightmostBit_BitTrick(n);
        int a2 = unsetRightmostBit_Scan(n);
        int a3 = unsetRightmostBit_Isolate(n);

        cout << "n = " << setw(5) << n
             << " | bin: " << bin(n, 12) << "\n";
        cout << "  Approach 1 (n & (n-1)): " << setw(5) << a1
             << " | bin: " << bin(a1, 12) << "\n";
        cout << "  Approach 2 (Scan bits):  " << setw(5) << a2
             << " | bin: " << bin(a2, 12) << "\n";
        cout << "  Approach 3 (Isolate r):  " << setw(5) << a3
             << " | bin: " << bin(a3, 12) << "\n";
        cout << "--------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1: Bit Trick n & (n - 1)
    //     • Cleanest and fastest. Recommended.
    // - Approach 2: Scan Bits
    //     • Educational, works in constant 32 iterations max.
    // - Approach 3: Isolate Rightmost Set Bit (r = n & -n), then n - r
    //     • Equivalent effect, also O(1); shows another common bit trick.
    ////////////////////////////////////////////////////////////

    return 0;
}
