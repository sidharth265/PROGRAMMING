#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Nth Root of M
---------------------------------------------------------------
Link: https://www.geeksforgeeks.org/problems/find-nth-root-of-m5843/1

Given two integers `n` and `m`, find the **nth root of m**.  
- If nth root exists as an integer → return it.  
- If not an exact integer → return -1.  

---------------------------------------------------------------
Example 1:
Input: n = 3, m = 27
Output: 3
Explanation: 3^3 = 27

Example 2:
Input: n = 4, m = 16
Output: 2
Explanation: 2^4 = 16

Example 3:
Input: n = 2, m = 8
Output: -1
Explanation: sqrt(8) ≠ integer
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Test every integer i from 1 → m.
- Compute i^n each time, check if equals m.

🧩 Algorithm:
1. Loop i = 1 to m.
2. Compute i^n (multiplying n times).
3. If i^n == m, return i.
4. If no match found, return -1.

⏱ Time Complexity: O(m^(1/n)) ~ O(m * n) worst
📦 Space Complexity: O(1)
===============================================================
*/
int nthRoot(int n, int m) {
    for (int i = 1; i <= m; i++) {
        long long power = 1;
        for (int j = 0; j < n; j++) power *= i;
        if (power == m) return i;
        if (power > m) break; // optimization
    }
    return -1;
}


/*
===============================================================
Approach 2: Binary Search (manual power multiplication)
---------------------------------------------------------------
💡 Idea:
- Nth root search space is [1, m].
- Use binary search:
  - Check mid^n.
  - If equals m → return mid.
  - If too small → low = mid+1.
  - If too big → high = mid-1.

🧩 Algorithm:
1. Initialize low=1, high=m.
2. While low <= high:
   - mid = (low+high)/2
   - Compute mid^n (stop early if >m).
   - Compare with m.
3. Return ans or -1.

⏱ Time Complexity: O(n * log m)
📦 Space Complexity: O(1)
===============================================================
*/
int nthRoot2(int n, int m) {
    int low = 1, high = m;
    while(low <= high) {
        int mid = low + (high - low)/2;
        long long p = 1;
        for(int i=1; i<=n; i++) {
            p *= mid;
            if(p > m) break; // no need to continue
        }
        if(p < m) low = mid+1;
        else if(p > m) high = mid-1;
        else return mid;
    }
    return -1;
}


/*
===============================================================
Approach 3: Binary Search + Fast Exponentiation (power function)
---------------------------------------------------------------
💡 Idea:
- Use exponentiation by squaring (fast power) for efficiency.
- Rest identical to Approach 2.

🧩 Algorithm:
1. Write fast power function → computes x^y in O(log y).
2. In binary search, compute mid^n using fast power.
3. Same comparisons as before.

⏱ Time Complexity: O(log n * log m)
📦 Space Complexity: O(1)
===============================================================
*/
long long power(int x, int y) {
    long long res = 1;
    long long base = x;
    while (y > 0) {
        if (y & 1) res *= base;
        base *= base;
        y >>= 1;
    }
    return res;
}

int nthRoot3(int n, int m) {
    int low = 1, high = m;
    while(low <= high) {
        int mid = low + (high - low)/2;
        long long p = power(mid, n);
        if(p < m) low = mid+1;
        else if(p > m) high = mid-1;
        else return mid;
    }
    return -1;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    int n, m;
    
    n = 3; m = 27;
    cout << "n=" << n << ", m=" << m << endl;
    cout << "Brute: " << nthRoot(n, m) << endl;
    cout << "Binary Search: " << nthRoot2(n, m) << endl;
    cout << "Binary Search + Fast Power: " << nthRoot3(n, m) << endl;
    cout << "-----------------------------" << endl;

    n = 4; m = 16;
    cout << "n=" << n << ", m=" << m << endl;
    cout << "Brute: " << nthRoot(n, m) << endl;
    cout << "Binary Search: " << nthRoot2(n, m) << endl;
    cout << "Binary Search + Fast Power: " << nthRoot3(n, m) << endl;
    cout << "-----------------------------" << endl;

    n = 2; m = 8;
    cout << "n=" << n << ", m=" << m << endl;
    cout << "Brute: " << nthRoot(n, m) << endl;
    cout << "Binary Search: " << nthRoot2(n, m) << endl;
    cout << "Binary Search + Fast Power: " << nthRoot3(n, m) << endl;
    cout << "-----------------------------" << endl;

    /*
    ===========================================================
    ✅ Approach Overview (Comparison)
    -----------------------------------------------------------
    1. Brute Force:
       - Check all numbers 1...m.
       - Time: O(m*n), Space: O(1)

    2. Binary Search:
       - Divide search space, compute power manually.
       - Time: O(n log m), Space: O(1)

    3. Binary Search + Fast Power:
       - Use exponentiation by squaring for mid^n.
       - Time: O(log n * log m), Space: O(1)

    🔑 Conclusion:
    - Brute force only works for very small values.
    - Binary search is efficient and practical for large inputs.
    ===========================================================
    */

    return 0;
}
