#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Count & Generate Prime Numbers Less Than N
🔗 Problem Link: (Classic Problem - LeetCode 204, GFG "Count Primes")

📌 Problem Statement:
Given a number `N`, find all prime numbers strictly less than `N`.  
Additionally, return the **count of primes** below `N`.

----------------------------------------------------------
🧩 Example 1:
Input:
    N = 10
Output:
    Primes: [2, 3, 5, 7]
    Count: 4
Explanation:
    Prime numbers less than 10 are 2, 3, 5, 7.

🧩 Example 2:
Input:
    N = 30
Output:
    Primes: [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
    Count: 10
----------------------------------------------------------
*/


//////////////////////////////////////////////////////////////
// Approach 1: Brute Force Prime Check
// 💡 Idea:
//   - For each number i in [2, N), check if i is prime by trial division.
//   - Count them or store them in a list.
//
// 🧩 Algorithm (Prime Check):
//   1. Edge case: return false for n < 2.
//   2. If n % 2 == 0, check if n == 2.
//   3. Loop over odd numbers till sqrt(n).
//   4. If divisible → not prime, else prime.
//
// ⏱ Time Complexity: O(N * sqrt(N))
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
bool isPrime_Brute(int n) {
    if (n < 2) return false;
    if (n % 2 == 0) return (n == 2);
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<int> primes_BruteForce(int N) {
    vector<int> primes;
    for (int i = 2; i < N; i++) {
        if (isPrime_Brute(i)) primes.push_back(i);
    }
    return primes;
}


//////////////////////////////////////////////////////////////
// Approach 2: Sieve of Eratosthenes
// 💡 Idea:
//   - Use a boolean array to mark multiples of primes as non-prime.
//   - Remaining unmarked numbers are primes.
//
// 🧩 Algorithm:
//   1. Initialize an array `isPrime[N] = true` for i in [2..N).
//   2. Start from p = 2:
//        - If isPrime[p] is true, mark all multiples of p starting from p*p.
//   3. Collect all numbers still marked true as primes.
//
// ⏱ Time Complexity: O(N log log N)
// 📦 Space Complexity: O(N)
//////////////////////////////////////////////////////////////
vector<int> primes_Sieve(int N) {
    if (N <= 2) return {};
    vector<bool> isPrime(N, true);
    isPrime[0] = isPrime = false;

    for (int p = 2; p * p < N; p++) {
        if (isPrime[p]) {
            for (int j = p * p; j < N; j += p) {
                isPrime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i < N; i++) {
        if (isPrime[i]) primes.push_back(i);
    }
    return primes;
}


//////////////////////////////////////////////////////////////
// Approach 3: Optimized Sieve (Skip Evens)
// 💡 Idea:
//   - Handle 2 separately, then mark only odd multiples.
//   - Saves time & memory for large N.
//
// ⏱ Time Complexity: O(N log log N)
// 📦 Space Complexity: O(N/2) ~ O(N)
//////////////////////////////////////////////////////////////
vector<int> primes_OptimizedSieve(int N) {
    if (N <= 2) return {};
    vector<bool> isPrime(N, true);
    isPrime[0] = isPrime = false;

    for (int p = 3; p * p < N; p += 2) {
        if (isPrime[p]) {
            for (int j = p * p; j < N; j += 2 * p) {
                isPrime[j] = false;
            }
        }
    }

    vector<int> primes = {2};
    for (int i = 3; i < N; i += 2) {
        if (isPrime[i]) primes.push_back(i);
    }
    return primes;
}


//////////////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////////////
int main() {
    vector<int> testCases = {10, 30, 1, 2, 50};

    for (int N : testCases) {
        cout << "N = " << N << "\n";

        // Brute Force
        vector<int> brute = primes_BruteForce(N);
        cout << "   Approach 1 (Brute Force): Count=" << brute.size() << " → ";
        for (int p : brute) cout << p << " ";
        cout << "\n";

        // Sieve
        vector<int> sieve = primes_Sieve(N);
        cout << "   Approach 2 (Sieve): Count=" << sieve.size() << " → ";
        for (int p : sieve) cout << p << " ";
        cout << "\n";

        // Optimized Sieve
        vector<int> opt = primes_OptimizedSieve(N);
        cout << "   Approach 3 (Optimized Sieve): Count=" << opt.size() << " → ";
        for (int p : opt) cout << p << " ";
        cout << "\n";

        cout << "-------------------------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1 (Brute Force):
    //     → Simple but too slow for N > 1e5.
    //     → O(N√N).
    //
    // - Approach 2 (Sieve of Eratosthenes):
    //     → Fast, efficient for N up to 1e7.
    //     → O(N log log N), Space O(N).
    //
    // - Approach 3 (Optimized Sieve):
    //     → Further optimizes by skipping evens.
    //     → Slightly faster in practice.
    //
    // Recommendation:
    //   - Use Brute Force for small N (< 5000).
    //   - Use Sieve/Optimized Sieve for large N.
    ////////////////////////////////////////////////////////////

    return 0;
}
