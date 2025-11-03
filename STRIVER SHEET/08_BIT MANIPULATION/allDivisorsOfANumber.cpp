#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Print All Divisors of a Number
---------------------------------------------------------------
Link: (Classic Math Problem) - Not platform specific.

📌 Problem Statement:
Given a positive integer `n`, print all of its divisors in **increasing order**.

A divisor of a number `n` is any integer `d` such that `n % d == 0`.

---------------------------------------------------------------
Example 1:
Input: n = 28
Output: 1 2 4 7 14 28

Explanation: 
28 is divisible by 1, 2, 4, 7, 14 and 28.

Example 2:
Input: n = 12
Output: 1 2 3 4 6 12

Constraints:
- 1 <= n <= 10^9 (large numbers possible)
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- A divisor must lie in the range [1, n].
- Check all numbers i = 1 to n, if n % i == 0 → i is a divisor.

🧩 Algorithm:
1. Initialize result list.
2. Loop i = 1 to n:
   - If n % i == 0 → add i to result.
3. Print result in sorted order (already sorted naturally).

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1) extra
===============================================================
*/
void printDivisorsBrute(int n) {
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) cout << i << " ";
    }
    cout << "\n";
}


/*
===============================================================
Approach 2: Optimized using sqrt(n)
---------------------------------------------------------------
💡 Idea:
- Divisors come in pairs: (i, n/i).
- If `i` divides `n`, then both `i` and `n/i` are divisors.
- We only need to check up to sqrt(n).

🧩 Algorithm:
1. Initialize result list.
2. Loop i = 1 to sqrt(n):
   - If n % i == 0:
     • Add i
     • If i != n/i, add n/i as well
3. Sort the collected divisors.
4. Print them.

⏱ Time Complexity: O(sqrt(n))
📦 Space Complexity: O(#divisors) for storing
===============================================================
*/
void printDivisorsOptimized(int n) {
    vector<int> divisors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) divisors.push_back(n / i);
        }
    }
    sort(divisors.begin(), divisors.end());
    for (int d : divisors) cout << d << " ";
    cout << "\n";
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    int n1 = 28;
    cout << "Divisors of " << n1 << " (Brute): ";
    printDivisorsBrute(n1); // Expected: 1 2 4 7 14 28

    cout << "Divisors of " << n1 << " (Optimized): ";
    printDivisorsOptimized(n1); // Expected: 1 2 4 7 14 28

    cout << "-------------------------------\n";

    int n2 = 36;
    cout << "Divisors of " << n2 << " (Brute): ";
    printDivisorsBrute(n2); // Expected: 1 2 3 4 6 9 12 18 36

    cout << "Divisors of " << n2 << " (Optimized): ";
    printDivisorsOptimized(n2); // Expected: 1 2 3 4 6 9 12 18 36

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Check all numbers from 1 to n.
       - ❌ Very slow for large n (up to 1e9).
       - Time: O(n)

    2. Optimized sqrt(n) approach:
       - Divisors come in pairs.
       - ✅ Much faster, only O(sqrt(n)) iterations.
       - Standard and accepted solution.

    🔑 Conclusion:
    - Use Brute Force only for small inputs.
    - Optimized sqrt(n) is the standard method.
    ===========================================================
    */
    return 0;
}
