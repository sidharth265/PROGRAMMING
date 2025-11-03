#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Sum of Divisors of All Numbers from 1 to n

Problem Statement:
Calculate the sum of divisors of all integers from 1 to n.

For example, if n = 4:
- Divisors of 1: 1
- Divisors of 2: 1, 2  (sum = 3)
- Divisors of 3: 1, 3  (sum = 4)
- Divisors of 4: 1, 2, 4 (sum = 7)
Total sum = 1 + 3 + 4 + 7 = 15

-----------------------------------------------------------
Example:
Input: n = 4
Output: 15

===========================================================
*/

/*-----------------------------------------------------------
Approach 1: Naive approach - check divisors for each number
💡 Idea:
- For each number i from 1 to n, iterate from 1 to i/2 to find divisors.
- Sum divisors for each number and accumulate overall sum.

🧩 Algorithm:
1. Initialize ans = 0.
2. For i in [1..n]:
   a) For j in [1..i/2]:
      - If j divides i, add j to ans.
   b) Add i itself to ans.
3. Return ans.

⏱ Time Complexity: O(n^2)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
int sumOfDivisors(int n) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= (i / 2); j++) {
            if (i % j == 0) {
                ans += j;
            }
        }
        ans += i;
    }
    return ans;
}

/*-----------------------------------------------------------
Approach 2: Optimized divisor counting using sqrt(i)
💡 Idea:
- Divisors come in pairs d and i/d.
- Iterate only till sqrt(i) to save time.
- Add both divisors if distinct.

🧩 Algorithm:
1. Initialize ans = 0.
2. For i in [1..n]:
   a) Let l = sqrt(i).
   b) For j in [1..l]:
      - If j divides i:
          * Add j.
          * If j != i/j, add i/j.
3. Return ans.

⏱ Time Complexity: O(n * sqrt(n))  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
int sumOfDivisors2(int n) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = sqrt(i);
        for (int j = 1; j <= l; j++) {
            if (i % j == 0) {
                ans += j;
                if (j != i / j) {
                    ans += i / j;
                }
            }
        }
    }
    return ans;
}

/*-----------------------------------------------------------
Approach 3: Mathematical optimized formula using divisor summation
💡 Idea:
- Use the fact that each number i appears as a divisor floor(n / i) times.
- Sum all i * floor(n / i) for i in [1..n].

🧩 Algorithm:
1. Initialize ans = 0.
2. For i in [1..n]:
   - Add i * (n / i) to ans.
3. Return ans.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
int sumOfDivisorsOptimized(int n) {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += i * (n / i);
    }
    return ans;
}

/*-----------------------------------------------------------
Main function: Test all approaches on sample input
-----------------------------------------------------------*/
int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    cout << "Sum of divisors (Naive): " << sumOfDivisors(n) << endl;
    cout << "Sum of divisors (Optimized sqrt): " << sumOfDivisors2(n) << endl;
    cout << "Sum of divisors (Mathematical): " << sumOfDivisorsOptimized(n) << endl;

    cout << "Time Complexity of naive: O(n^2)" << endl;
    cout << "Time Complexity of optimized sqrt: O(n * sqrt(n))" << endl;
    cout << "Time Complexity of mathematical: O(n)" << endl;
    cout << "Space Complexity: O(1)" << endl;

    /* ✅ Approach Overview
    -----------------------------------------------------------
    1. Naive approach: O(n^2) - check divisors for each number.
    2. Optimized approach: O(n * sqrt(n)) - check divisors up to sqrt.
    3. Mathematical formula approach: O(n) - sum frequency of divisors.
    -----------------------------------------------------------
    */
    return 0;
}
