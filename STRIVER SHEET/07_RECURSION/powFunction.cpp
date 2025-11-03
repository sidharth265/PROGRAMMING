#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Implement Pow(x, n)
 Problem Link: https://leetcode.com/problems/powx-n/

 Problem Statement:
 Implement `myPow(x, n)`, which calculates x raised to the power n (x^n).
 Handle negative exponents and integer edge cases correctly.

-------------------------------------------------
 Example:
 Input: x = 2, n = 10
 Output: 1024

 Input: x = 2, n = -2
 Output: 0.25
 Explanation: 2^-2 = 1/2^2 = 0.25
-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Fast Recursion (Divide and Conquer)
// -------------------------------------------------
/*
💡 Idea:
   - Use recursion with dividing exponent by 2.
   - For even n, myPow(x, n) = myPow(x*x, n/2)
   - For odd n, myPow(x, n) = x * myPow(x, n-1)
   - Handle negative exponent by reciprocal technique.
   - Handle INT_MIN carefully to avoid overflow.

🧩 Algorithm:
   1. If n < 0:
       - If n == INT_MIN (abs overflow), do: 
         1 / (x * myPow(x, -(n+1)))
       - Else: return 1 / myPow(x, -n)
   2. Base case: if n == 0, return 1
   3. If n is odd: return x * myPow(x, n-1)
   4. Else: return myPow(x * x, n/2)

⏱ Time Complexity: O(log n)
📦 Space Complexity: O(log n) recursion stack
*/

double myPow(double x, int n) {
    if (n < 0) {
        if (n == INT_MIN)  // handle overflow in -n
            return 1 / (x * myPow(x, -(n + 1)));
        return 1 / myPow(x, -n);
    } 
    else if (n == 0) {
        return 1.0;
    } 
    else if (n & 1) {
        return x * myPow(x, n - 1);
    } 
    else {
        double half = myPow(x, n / 2);
        return half * half;
    }
}


// -------------------------------------------------
// Main Function (Demo)
// -------------------------------------------------
int main() {
    double x;
    int n;
    cout << "Enter base (x) and exponent (n): ";
    cin >> x >> n;

    double result = myPow(x, n);
    cout << "Result of " << x << "^" << n << " is: " << result << endl;

    // Additional tests
    vector<pair<double,int>> tests = {
        {2.0, 10},
        {2.0, -2},
        {3.0, 0},
        {5.0, 3},
        {2.0, INT_MIN},
        {1.00001, 123456}
    };

    for (auto &test : tests) {
        cout << test.first << "^" << test.second << " = " << myPow(test.first, test.second) << endl;
    }

    return 0;
}
