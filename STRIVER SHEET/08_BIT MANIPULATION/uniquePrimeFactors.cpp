#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Unique Prime Factors of a Number
🔗 Problem Link: (Classic Number Theory / Prime Factorization)

📌 Problem Statement:
Given a positive integer n, return the list of its unique prime factors
(i.e., each prime factor appears at most once in the output, regardless of multiplicity).

Constraints:
- 1 <= n

----------------------------------------------------------
🧩 Example 1:
Input:
    n = 28
Output:
    [2, 7]
Explanation:
    28 = 2^2 * 7 → unique prime factors are 2 and 7.

🧩 Example 2:
Input:
    n = 60
Output:
    [2, 3, 5]
Explanation:
    60 = 2^2 * 3 * 5 → unique prime factors are 2, 3, 5.

🧩 Example 3:
Input:
    n = 1
Output:
    []
Explanation:
    1 has no prime factors.
----------------------------------------------------------
*/

//////////////////////////////////////////////////////////////
// Approach 1: Trial Division up to sqrt(n)
// 💡 Idea:
//   Repeatedly divide out each prime factor. First handle 2,
//   then try odd candidates up to sqrt(n). If leftover n > 1,
//   it is a prime factor itself.
//
// 🧩 Algorithm:
//   1) If n <= 1, return empty list.
//   2) If n divisible by 2, push 2 and divide n by 2 while divisible.
//   3) For i from 3 to i*i <= n, step 2:
//        - If n % i == 0: push i, and divide n by i while divisible.
//   4) If n > 1, push n (it's a prime).
//
// ⏱ Time Complexity: O(sqrt(n))
// 📦 Space Complexity: O(k) for k unique primes
//////////////////////////////////////////////////////////////
vector<int> uniquePrimeFactors_TrialDivision(long long n) {
    vector<int> ans;
    if (n <= 1) return ans;

    if (n % 2 == 0) {
        ans.push_back(2);
        while (n % 2 == 0) n /= 2;
    }
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            ans.push_back((int)i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ans.push_back((int)n);
    return ans;
}

//////////////////////////////////////////////////////////////
// Approach 2: Precompute primes up to sqrt(n) (Sieve) then divide
// 💡 Idea:
//   Generate all primes up to sqrt(n) using sieve, then divide n by those primes.
//   More cache-friendly and faster when factoring multiple numbers.
//
// 🧩 Algorithm:
//   1) If n <= 1, return empty.
//   2) Limit = floor(sqrt(n)). Build sieve to get primes up to Limit.
//   3) For each prime p:
//        - If n % p == 0: push p, divide n by p while divisible.
//   4) If n > 1, push n (prime).
//
// ⏱ Time Complexity: O(L log log L) + O(#primes * divisions), where L ≈ sqrt(n)
// 📦 Space Complexity: O(L)
//////////////////////////////////////////////////////////////
vector<int> uniquePrimeFactors_Sieve(long long n) {
    vector<int> ans;
    if (n <= 1) return ans;

    long long L = sqrt((long double)n);
    if (L < 2) L = 2;
    vector<bool> isPrime(L + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (long long p = 2; p * p <= L; ++p) {
        if (isPrime[p]) {
            for (long long j = p * p; j <= L; j += p) isPrime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= L; ++i) if (isPrime[i]) primes.push_back(i);

    for (int p : primes) {
        if ((long long)p * p > n) break;
        if (n % p == 0) {
            ans.push_back(p);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) ans.push_back((int)n);
    return ans;
}

//////////////////////////////////////////////////////////////
// Approach 3: Optimized Trial Division with 6k ± 1 skipping
// 💡 Idea:
//   After removing factors 2 and 3, all primes are of the form 6k±1.
//   Check i = 5, 11, 17, ... and i+2 = 7, 13, 19, ...
//
// 🧩 Algorithm:
//   1) Handle n<=1; remove factor 2; remove factor 3.
//   2) For i from 5 while i*i <= n step 6:
//        - Check i; if divides, push i and divide fully.
//        - Check i+2; if divides, push i+2 and divide fully.
//   3) If n>1, push n.
//
// ⏱ Time Complexity: O(sqrt(n)) but fewer iterations than plain odd loop
// 📦 Space Complexity: O(k)
//////////////////////////////////////////////////////////////
vector<int> uniquePrimeFactors_6k1(long long n) {
    vector<int> ans;
    if (n <= 1) return ans;

    if (n % 2 == 0) {
        ans.push_back(2);
        while (n % 2 == 0) n /= 2;
    }
    if (n % 3 == 0) {
        ans.push_back(3);
        while (n % 3 == 0) n /= 3;
    }
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0) {
            ans.push_back((int)i);
            while (n % i == 0) n /= i;
        }
        long long j = i + 2;
        if (n % j == 0) {
            ans.push_back((int)j);
            while (n % j == 0) n /= j;
        }
    }
    if (n > 1) ans.push_back((int)n);
    return ans;
}

//////////////////////////////////////////////////////////////
// Helper: Pretty print a vector
//////////////////////////////////////////////////////////////
void printVector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << (i + 1 < v.size() ? ", " : "");
    }
    cout << "]";
}

//////////////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////////////
int main() {
    vector<long long> testCases = {28, 60, 1, 2, 3, 999, 1024, 99991};

    for (long long n : testCases) {
        cout << "n = " << n << "\n";

        auto a1 = uniquePrimeFactors_TrialDivision(n);
        cout << "   Approach 1 (Trial Division):      ";
        printVector(a1); cout << "\n";

        auto a2 = uniquePrimeFactors_Sieve(n);
        cout << "   Approach 2 (Sieve + Divide):      ";
        printVector(a2); cout << "\n";

        auto a3 = uniquePrimeFactors_6k1(n);
        cout << "   Approach 3 (6k ± 1 Optimization): ";
        printVector(a3); cout << "\n";

        cout << "-------------------------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1 (Trial Division):
    //     → Simple, reliable for single inputs; O(sqrt(n)) time, O(k) space.
    // - Approach 2 (Sieve + Divide):
    //     → Better when factoring many numbers; precompute primes up to sqrt(n).
    // - Approach 3 (6k ± 1):
    //     → Fewer iterations than checking all odds; still O(sqrt(n)).
    //
    // Recommendation:
    //   - Single query: Approach 1 or 3.
    //   - Multiple queries with large n: Approach 2.
    ////////////////////////////////////////////////////////////

    return 0;
}
