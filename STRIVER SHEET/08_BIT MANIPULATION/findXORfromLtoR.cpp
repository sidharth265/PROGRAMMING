#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: XOR of Numbers in a Range [L, R]
---------------------------------------------------------------
Link: Classic Bit Manipulation Problem (range XOR trick)

📌 Problem Statement:
Given two integers L and R (L ≤ R), compute the XOR of all integers
from L to R inclusive, i.e., L ⊕ (L+1) ⊕ ... ⊕ R.

Return the result in O(1) time.

---------------------------------------------------------------
Example 1:
Input:
    L = 5, R = 10
Output:
    15
Explanation:
    5 ^ 6 ^ 7 ^ 8 ^ 9 ^ 10
    = 0101 ^ 0110 ^ 0111 ^ 1000 ^ 1001 ^ 1010
    = 1111 (decimal 15)

Example 2:
Input:
    L = 0, R = 0
Output:
    0
Explanation:
    XOR of single element 0 is 0.

Constraints:
- 0 <= L <= R <= 10^18
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Iterate from L to R and accumulate XOR.
- Works only for very small ranges due to O(R-L+1) time.

🧩 Algorithm:
1. Initialize ans = 0.
2. For x from L to R:
   - ans ^= x
3. Return ans.

⏱ Time Complexity: O(R - L + 1)
📦 Space Complexity: O(1)
===============================================================
*/
long long rangeXorBrute(long long L, long long R) {
    long long ans = 0;
    for (long long x = L; x <= R; x++) ans ^= x;
    return ans;
}


/*
===============================================================
Approach 2: XOR Prefix Trick (Optimal)
---------------------------------------------------------------
💡 Idea:
- Use the known pattern for XOR from 0 to n:
    f(n) = n, 1, n+1, 0  depending on n % 4 = 0,1,2,3 respectively.
- Then XOR(L..R) = f(R) ^ f(L-1).

🧩 Algorithm:
1. Define a helper f(n) that returns XOR of [0..n] using n%4 pattern.
2. Return f(R) ^ f(L-1).

⏱ Time Complexity: O(1)
📦 Space Complexity: O(1)
===============================================================
*/
long long xorPrefix(long long n) {
    switch (n & 3) { // n % 4
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        default: return 0; // case 3
    }
}

long long rangeXorFast(long long L, long long R) {
    if (L == 0) return xorPrefix(R);
    return xorPrefix(R) ^ xorPrefix(L - 1);
}


/*
===============================================================
Approach 3: Bitwise Insight (Explanation-focused)
---------------------------------------------------------------
💡 Idea:
- For each bit position independently, count how many numbers in [L, R]
  have that bit set. If the count is odd, that bit contributes 1 in result.
- While educational, implementing per-bit counting is more involved and
  not necessary since the prefix trick gives O(1).

🧩 Algorithm:
1. For each bit b from 0..60:
   - Count set bits at position b in [0..R] and [0..L-1] using periodicity.
   - Take difference; if odd, set bit b in answer.
2. Return answer.

⏱ Time Complexity: O(log(max(R, L)))
📦 Space Complexity: O(1)
===============================================================
*/
long long rangeXorPerBit(long long L, long long R) {
    auto countSetAtBitUpTo = [](long long n, int b)->long long {
        if (n < 0) return 0;
        long long period = 1LL << (b + 1);
        long long full = (n + 1) / period;
        long long rem = (n + 1) % period;
        long long onesInPeriod = 1LL << b;
        long long ones = full * onesInPeriod + max(0LL, rem - onesInPeriod);
        return ones;
    };
    long long ans = 0;
    for (int b = 0; b < 61; b++) {
        long long onesR = countSetAtBitUpTo(R, b);
        long long onesL_1 = countSetAtBitUpTo(L - 1, b);
        long long cnt = onesR - onesL_1;
        if (cnt & 1) ans |= (1LL << b);
    }
    return ans;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<pair<long long, long long>> tests = {
        {5, 10},     // Expected 15
        {0, 0},      // Expected 0
        {0, 7},      // 0^1^2^3^4^5^6^7 = 0 (since f(7)=0)
        {8, 8},      // 8
        {1, 1},      // 1
        {2, 4},      // 2^3^4 = 5
        {1234567890123LL, 1234567890999LL} // large range
    };

    for (auto [L, R] : tests) {
        cout << "L=" << L << ", R=" << R << "\n";
        cout << "➡ Brute (small ranges): ";
        if (R - L <= 100000) { // avoid huge loops
            cout << rangeXorBrute(L, R) << "\n";
        } else {
            cout << "(skipped; large range)\n";
        }
        cout << "➡ Prefix Trick (O(1)): " << rangeXorFast(L, R) << "\n";
        cout << "➡ Per-bit method:      " << rangeXorPerBit(L, R) << "\n";
        cout << "-------------------------------\n";
    }

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Iterative XOR from L to R.
       - ❌ O(R-L+1), impractical for large ranges.

    2. Prefix Trick (Optimal):
       - Uses pattern of XOR(0..n) based on n % 4.
       - ✅ O(1) time, O(1) space, simplest and fastest.

    3. Per-bit Counting:
        - Counts parity of set bits per position over [L, R].
        - ✅ O(log max(R,L)), educational but more complex than needed.

    🔑 Conclusion:
    - Use the Prefix Trick in interviews and contests for clean O(1) solution.
    ===========================================================
    */
    return 0;
}
