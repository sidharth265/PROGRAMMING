#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Count Set Bits of an Integer
---------------------------------------------------------------
Link: Classic bit manipulation problem.

📌 Problem Statement:
Given a non-negative integer `n`, return the number of set bits (1s) in its binary representation.

---------------------------------------------------------------
Example 1:
Input: n = 29
Binary: 11101
Output: 4

Example 2:
Input: n = 15
Binary: 1111
Output: 4

Constraints:
- 0 <= n <= 10^9
===============================================================
*/


/*
===============================================================
Approach 1: Bit by Bit (Right Shift)
---------------------------------------------------------------
💡 Idea:
- Repeatedly check the least significant bit (LSB).
- Increment count if `n & 1 == 1`
- Then shift `n` to the right.

🧩 Algorithm:
1. Initialize count = 0
2. While n > 0:
   - If (n & 1) → increment count
   - Right shift n by 1
3. Return count

⏱ Time Complexity: O(log n)
📦 Space Complexity: O(1)
===============================================================
*/
int countSetBitsSimple(int n) {
    int count = 0;
    while (n) {
        count += (n & 1);
        n >>= 1;
    }
    return count;
}


/*
===============================================================
Approach 2: Brian Kernighan’s Algorithm (Optimized)
---------------------------------------------------------------
💡 Idea:
- Instead of checking each bit, repeatedly remove the **lowest set bit** until n == 0.
- Operation: n = n & (n - 1) removes the rightmost set bit.

🧩 Algorithm:
1. Initialize count = 0
2. While n > 0:
   - Do n = n & (n-1)
   - Increment count
3. Return count

⏱ Time Complexity: O(#set bits in n)
📦 Space Complexity: O(1)
===============================================================
*/
int countSetBitsKernighan(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}


/*
===============================================================
Approach 3: Built-in Popcount
---------------------------------------------------------------
💡 Idea:
- Modern compilers (GCC/Clang) provide built-in functions for set bits.
- `__builtin_popcount(n)` → 32-bit integers
- `__builtin_popcountll(n)` → 64-bit integers

🧩 Algorithm:
1. Return __builtin_popcount(n)

⏱ Time Complexity: O(1) (hardware level)
📦 Space Complexity: O(1)
===============================================================
*/
int countSetBitsBuiltin(int n) {
    return __builtin_popcount(n);  // works for int
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> testCases = {0, 1, 15, 29, 1023}; 

    for (int n : testCases) {
        cout << "Number: " << n << " (Binary: " << bitset<16>(n) << ")\n";
        cout << "➡ Simple (Right shift): " << countSetBitsSimple(n) << "\n";
        cout << "➡ Kernighan’s Algo: " << countSetBitsKernighan(n) << "\n";
        cout << "➡ Built-in popcount: " << countSetBitsBuiltin(n) << "\n";
        cout << "-------------------------------\n";
    }

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Simple Right Shift:
       - Check each bit by shifting and counting.
       - Time: O(log n), works universally.
    
    2. Brian Kernighan’s Algorithm:
       - Removes set bits one by one.
       - Time: O(#set bits), faster if n has few set bits.
    
    3. Built-in Popcount:
       - Compiler intrinsic, extremely fast.
       - Best for production / competitive coding.
    
    🔑 Conclusion:
    - In interviews → explain Approach 1 (clear), mention Kernighan (optimized),
      and Built-in (real-world usage).
    ===========================================================
    */
    return 0;
}
