#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Fibonacci Sequence Using Dynamic Programming
Problem Link: General concept of DP, demonstrative only

Problem Statement:
Compute the n-th Fibonacci number, where
F(0) = 0,
F(1) = 1,
and F(n) = F(n-1) + F(n-2) for n ≥ 2.

Naive recursion repeats calculations exponentially. Dynamic Programming optimizes by storing intermediate results to avoid recomputation.
*/


// Approach 1: Top-Down Memoization (Recursion + DP)
// 💡 Idea:
// Use recursion and save (memoize) results in a dp array to avoid recomputation.
// Recursive formula: fib(n) = fib(n-1) + fib(n-2)
// Base cases: fib(0) = 0, fib(1) = 1
//
// ⏱ Time Complexity: O(n)
// 📦 Space Complexity: O(n) for dp + recursion stack

int fib(int n, vector<int>& dp) {
    if (n <= 1) return dp[n] = n;
    if (dp[n] != -1) return dp[n];
    return dp[n] = fib(n-1, dp) + fib(n-2, dp);
}

int nthFibonacciTopDown(int n) {
    vector<int> dp(n+1, -1);
    return fib(n, dp);
}


// Approach 2: Bottom-Up Tabulation (Iterative DP)
// 💡 Idea:
// Iteratively compute from the base cases upwards, filling dp array.
// Avoid recursive overhead.
//
// ⏱ Time Complexity: O(n)
// 📦 Space Complexity: O(n)

int nthFibonacciBottomUp(int n) {
    if (n <= 1) return n;
    vector<int> dp(n+1);
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}


// Approach 3: Space Optimized Iterative DP
// 💡 Idea:
// Only keep track of last two Fibonacci numbers to save space.
//
// ⏱ Time Complexity: O(n)
// 📦 Space Complexity: O(1)

int nthFibonacciSpaceOpt(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1, curr;
    for (int i = 2; i <= n; i++) {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}


int main() {
    int n = 10;

    cout << "Top-Down Memoization: " << nthFibonacciTopDown(n) << "\n";
    cout << "Bottom-Up Tabulation: " << nthFibonacciBottomUp(n) << "\n";
    cout << "Space Optimized Iterative: " << nthFibonacciSpaceOpt(n) << "\n";

    return 0;
}

/*
✅ Approach Overview:
| Approach               | Time Complexity | Space Complexity | Notes                              |
|------------------------|-----------------|------------------|----------------------------------|
| Top-Down Memoization   | O(n)            | O(n)             | Recursion + Memoization           |
| Bottom-Up Tabulation   | O(n)            | O(n)             | Iterative DP                     |
| Space Optimized Iterative | O(n)         | O(1)             | Uses constant extra space         |

Dynamic Programming eliminates redundant computations characteristic of naive recursion by caching intermediate subproblem solutions.
*/
