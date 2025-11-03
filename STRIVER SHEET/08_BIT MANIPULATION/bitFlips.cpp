#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Minimum Bit Flips to Convert Number
---------------------------------------------------------------
Link: (Similar to LeetCode 2220 - Minimum Bit Flips to Convert Number)

📌 Problem Statement:
Given two integers `start` and `goal`, return the **minimum number of bit flips** required to convert `start` into `goal`.

- In one bit flip, you can change a `0` to `1` or a `1` to `0`.

---------------------------------------------------------------
Example 1:
Input: start = 10, goal = 7
Output: 3
Explanation:
    Binary of start = 1010
    Binary of goal  = 0111
    Bits differ at 3 positions → Answer = 3

Example 2:
Input: start = 3, goal = 4
Output: 3
Explanation:
    Binary of start = 011
    Binary of goal  = 100
    Bits differ at 3 positions → Answer = 3

Constraints:
- 0 <= start, goal <= 10^9
===============================================================
*/


/*
===============================================================
Approach 1: Bitwise Comparison
---------------------------------------------------------------
💡 Idea:
- Compare each bit of `start` and `goal` one by one.
- Count how many positions differ.

🧩 Algorithm:
1. Initialize count = 0
2. While either `start` or `goal` is nonzero:
   a) Compare least significant bit (LSB) of both.
   b) If they differ → increment count.
   c) Right shift both numbers.
3. Return count.

⏱ Time Complexity: O(log(max(start, goal)))
📦 Space Complexity: O(1)
===============================================================
*/
int minBitFlipsCompare(int start, int goal) {
    int count = 0;
    while (start || goal) {
        if ((start & 1) != (goal & 1)) count++;
        start >>= 1;
        goal >>= 1;
    }
    return count;
}


/*
===============================================================
Approach 2: XOR Method (Optimal)
---------------------------------------------------------------
💡 Idea:
- XOR highlights differing bits: 
    - If start[i] != goal[i] ⇒ XOR[i] = 1
    - Else XOR[i] = 0
- So the number of set bits in (start ^ goal) = #bit flips.

🧩 Algorithm:
1. Perform Xor = start ^ goal
2. Count no. of 1s in Xor (set bits).
3. That count = answer.

⏱ Time Complexity: O(log(max(start, goal)))
📦 Space Complexity: O(1)
===============================================================
*/
int minBitFlipsXOR(int start, int goal) {
    int x = start ^ goal;
    int count = 0;
    while (x) {
        count += (x & 1);
        x >>= 1;
    }
    return count;
}


/*
===============================================================
Approach 3: Built-in Popcount (Very Concise)
---------------------------------------------------------------
💡 Idea:
- Modern C++ has `__builtin_popcount(x)` which counts set bits efficiently.
- Simply compute `__builtin_popcount(start ^ goal)`.

🧩 Algorithm:
1. Compute XOR = start ^ goal.
2. Return number of set bits = __builtin_popcount(XOR).

⏱ Time Complexity: O(1) (hardware instruction usually)
📦 Space Complexity: O(1)
===============================================================
*/
int minBitFlipsPopcount(int start, int goal) {
    return __builtin_popcount(start ^ goal);
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<pair<int,int>> testCases = {
        {10, 7},  // Expected 3
        {3, 4},   // Expected 3
        {0, 0},   // Expected 0
        {1, 15},  // Expected 3 (0001 -> 1111)
    };

    for (auto [start, goal] : testCases) {
        cout << "Start=" << start << ", Goal=" << goal << "\n";
        cout << "➡ Compare Approach: " << minBitFlipsCompare(start, goal) << "\n";
        cout << "➡ XOR Approach: " << minBitFlipsXOR(start, goal) << "\n";
        cout << "➡ Built-in Popcount: " << minBitFlipsPopcount(start, goal) << "\n";
        cout << "-------------------------------\n";
    }

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Bitwise Comparison:
       - Compare individual bits by shifting.
       - Clear and simple.
       - Time: O(log n), Space: O(1)

    2. XOR Approach:
       - Faster and elegant: count differing bits with XOR.
       - Time: O(log n), Space: O(1)

    3. Built-in Popcount:
       - One-liner using hardware supported popcount.
       - Time: O(1), Space: O(1)

    🔑 Conclusion:
    - XOR method is the best to explain in interviews.
    - Built-in popcount is the concise competitive programming solution.
    ===========================================================
    */
    return 0;
}
