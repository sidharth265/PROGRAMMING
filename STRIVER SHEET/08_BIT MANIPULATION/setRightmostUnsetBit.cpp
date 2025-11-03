#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Set the Rightmost Unset Bit
🔗 Problem Link: (Classic Bit Manipulation Interview Question)

📌 Problem Statement:
Given an integer `n`, set (turn into 1) the **rightmost unset (0) bit** in its binary representation, and return the modified number.

⚠️ Important:
- Assume we are only considering standard integer bits (not infinite bit-length).
- If all bits up to the most significant bit are already set (like 7 = 111), `n` remains unchanged.

----------------------------------------------------------
🧩 Example 1:
Input:
    n = 18
Output:
    19
Explanation:
    Binary(18) = 10010
    Set rightmost 0 → becomes 10011 (19).

🧩 Example 2:
Input:
    n = 7
Output:
    7
Explanation:
    Binary(7) = 111, all bits already set → remains unchanged.
----------------------------------------------------------
*/


//////////////////////////////////////////////////////////////
// Approach 1: Brute Force (Bit Check)
// 💡 Idea:
//   - Traverse bits from right to left.
//   - Find the first 0-bit and set it using OR (|).
//
// 🧩 Algorithm:
//   1. For position i = 0,1,2,... until 31 (assuming 32-bit integer):
//      - If ( (n >> i) & 1 ) == 0 → set this bit: n |= (1 << i),
//        and break.
//   2. Return n.
//
// ⏱ Time Complexity: O(log n) (in number of bits)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
int setRightmostUnsetBit_Brute(int n) {
    for (int i = 0; i < 32; i++) {
        if (((n >> i) & 1) == 0) {
            n |= (1 << i);
            break;
        }
    }
    return n;
}


//////////////////////////////////////////////////////////////
// Approach 2: Bit Trick using (n | (n+1))
// 💡 Idea:
//   - Adding 1 to n flips the rightmost sequence of 1's into 0's
//     and sets the first 0-bit to 1.
//   - OR with n sets that 0-bit in n.
//
// 🧩 Algorithm:
//   1. Return (n | (n + 1)).
//   2. Special case: if n already has all bits set up to MSB → it remains unchanged.
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
int setRightmostUnsetBit_BitTrick(int n) {
    return (n | (n + 1));
}


//////////////////////////////////////////////////////////////
// Example usage with test cases
//////////////////////////////////////////////////////////////
int main() {
    vector<int> testCases = {18, 7, 0, 8, 15, 32};

    for (int n : testCases) {
        cout << "n = " << n << " (Binary = " << bitset<8>(n) << ")\n";

        int bruteAns = setRightmostUnsetBit_Brute(n);
        cout << "   Approach 1 (Brute Force Bit Scan): " << bruteAns
             << " (Binary = " << bitset<8>(bruteAns) << ")\n";

        int trickAns = setRightmostUnsetBit_BitTrick(n);
        cout << "   Approach 2 (Bit Trick):             " << trickAns
             << " (Binary = " << bitset<8>(trickAns) << ")\n";

        cout << "-------------------------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1 (Brute Force Scanning):
    //     → Works by checking each bit manually.
    //     → O(log n) but still fast for integers.
    //
    // - Approach 2 (Bit Trick with n | (n+1)):
    //     → Extremely concise, O(1).
    //     → Best approach for interviews & CP.
    ////////////////////////////////////////////////////////////

    return 0;
}
