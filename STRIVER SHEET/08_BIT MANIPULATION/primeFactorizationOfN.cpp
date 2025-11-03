#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Prime Factorization of a Number
🔗 Problem Link: (Classic Problem - asked in interviews & CP)

📌 Problem Statement:
Given an integer `N`, find its prime factorization.  
That is, express `N` as a product of prime numbers.

----------------------------------------------------------
🧩 Example 1:
Input:
    N = 100
Output:
    [2, 2, 5, 5]
Explanation:
    100 = 2 × 2 × 5 × 5

🧩 Example 2:
Input:
    N = 37
Output:
    [37]
Explanation:
    37 is already prime.

🧩 Example 3:
Input:
    N = 84
Output:
    [2, 2, 3, 7]
Explanation:
    84 = 2 × 2 × 3 × 7
----------------------------------------------------------
*/


//////////////////////////////////////////////////////////////
// Approach 1: Trial Division
// 💡 Idea:
//   - Keep dividing by smallest possible prime factors.
//   - Start with 2, then go through odd numbers until sqrt(N).
//   - If N > 1 at the end, push N (itself prime).
//
// 🧩 Algorithm:
//   1. Divide N by 2 repeatedly while divisible.
//   2. For i from 3 to sqrt(N), step = 2:
//      - Keep dividing while divisible, collect factors.
//   3. If N > 1 → push N (remaining prime).
//
// ⏱ Time Complexity: O(sqrt(N))
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
vector<int> primeFactors_TrialDivision(int N) {
    vector<int> ans;
    while (N % 2 == 0) {
        ans.push_back(2);
        N /= 2;
    }
    for (int i = 3; i * i <= N; i += 2) {
        while (N % i == 0) {
            ans.push_back(i);
            N /= i;
        }
    }
    if (N > 1) ans.push_back(N);
    return ans;
}


//////////////////////////////////////////////////////////////
// Approach 2: Sieve of Eratosthenes (Smallest Prime Factor)
// 💡 Idea:
//   - Precompute the smallest prime factor (SPF) for each number.
//   - For given N, repeatedly divide by SPF to extract factors.
//
// 🧩 Algorithm:
//   1. Create spf[] array where spf[x] = smallest prime factor of x.
//   2. Initialize spf[i] = i.
//   3. Run modified sieve to fill SPF values.
//   4. While N > 1:
//        - ans.push_back(spf[N])
//        - N = N / spf[N]
//
// ⏱ Time Complexity: O(N log log N) preprocessing, O(log N) factorization
// 📦 Space Complexity: O(N)
//////////////////////////////////////////////////////////////
vector<int> primeFactors_Sieve(int N) {
    vector<int> spf(N + 1);
    for (int i = 2; i <= N; i++) spf[i] = i;

    for (int i = 2; i * i <= N; i++) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j <= N; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }

    vector<int> ans;
    while (N != 1) {
        ans.push_back(spf[N]);
        N /= spf[N];
    }
    return ans;
}


//////////////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////////////
int main() {
    vector<int> testCases = {100, 37, 84, 56, 999, 1};

    for (int N : testCases) {
        cout << "Prime factors of " << N << " (Trial Division): ";
        vector<int> factors1 = primeFactors_TrialDivision(N);
        for (int f : factors1) cout << f << " ";
        cout << "\n";

        if (N > 1) { // sieve method fails for N=1
            cout << "Prime factors of " << N << " (Sieve SPF):    ";
            vector<int> factors2 = primeFactors_Sieve(N);
            for (int f : factors2) cout << f << " ";
            cout << "\n";
        }

        cout << "-------------------------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1 (Trial Division):
    //     → Simple, works well for single queries.
    //     → Time: O(sqrt(N)), Space: O(1).
    //
    // - Approach 2 (Sieve with SPF):
    //     → Efficient if multiple queries for many values of N.
    //     → Time: O(N log log N) preprocessing + O(log N) per query
    //     → Space: O(N).
    //
    // 🔑 Recommendation:
    //   - Use Trial Division for small/one-off inputs.
    //   - Use SPF Sieve for multiple factorization queries.
    ////////////////////////////////////////////////////////////

    return 0;
}
