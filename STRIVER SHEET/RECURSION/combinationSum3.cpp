#include <bits/stdc++.h>
using namespace std;

/*
==================================================
Problem Title: Combination Sum III (LeetCode 216)
Problem Link: https://leetcode.com/problems/combination-sum-iii/

Problem Statement:
Find all valid combinations of k numbers that sum up to n such that:
- Only numbers 1 through 9 are used.
- Each number is used at most once.

Return a list of all possible valid combinations. The list must not contain the same combination twice.
Combinations may be returned in any order.

Examples:

1) 
Input:
k = 3, n = 7

Output:
[
  [1,2,4]
]

Explanation:
Only one combination of 3 numbers from 1..9 sums to 7: 1 + 2 + 4 = 7.

2)
Input:
k = 3, n = 9

Output:
[
  [1,2,6],
  [1,3,5],
  [2,3,4]
]

Explanation:
All unique triplets of numbers in 1..9 that sum to 9.

Constraints:
- 2 <= k <= 9
- 1 <= n <= 60
==================================================
*/

/*
---------------------------------------------
Approach 1: Brute Force (Generate All Subsets of 1..9)
💡 Idea
- Consider every subset of numbers from 1..9 (there are 2^9 = 512 subsets).
- Keep only those with exactly k elements and sum equal to n.

🧩 Algorithm
1) Enumerate mask from 0 to (1<<9)-1.
2) Build subset using numbers where the bit is set (i+1).
3) If subset size == k and sum == n, add to result.

⏱ Time Complexity: O(2^9 * 9) ≈ O(1) in practice, but conceptually O(2^n * n).
📦 Space Complexity: O(k) for current subset (excluding result).
---------------------------------------------
*/
vector<vector<int>> combinationSum3_BruteForce(int k, int n) {
    vector<vector<int>> result;
    for (int mask = 0; mask < (1 << 9); ++mask) {
        vector<int> cur;
        int sum = 0;
        for (int i = 0; i < 9; ++i) {
            if (mask & (1 << i)) {
                cur.push_back(i + 1);
                sum += (i + 1);
            }
        }
        if ((int)cur.size() == k && sum == n) {
            result.push_back(cur);
        }
    }
    return result;
}

/*
---------------------------------------------
Approach 2: Backtracking (Simple DFS)
💡 Idea
- Build combinations incrementally using numbers from 1..9.
- At each step, choose a next number > last chosen, ensuring uniqueness.
- Stop when we pick k numbers; if the remaining sum is zero, record the combination.

🧩 Algorithm
1) Define dfs(start, remain, k, path):
   - If path.size() == k:
       - If remain == 0: add path to result.
       - Return.
   - For i from start to 9:
       - Push i to path
       - dfs(i+1, remain - i, k, path)
       - Pop i from path

⏱ Time Complexity: O(C(9, k)) in practice; worst-case O(2^9).
📦 Space Complexity: O(k) recursion depth.
---------------------------------------------
*/
void dfsSimple(vector<vector<int>>& result, vector<int>& path, int remain, int k, int start) {
    if ((int)path.size() == k) {
        if (remain == 0) result.push_back(path);
        return;
    }
    for (int i = start; i <= 9; ++i) {
        path.push_back(i);
        dfsSimple(result, path, remain - i, k, i + 1);
        path.pop_back();
    }
}

vector<vector<int>> combinationSum3_Backtracking(int k, int n) {
    vector<vector<int>> result;
    vector<int> path;
    dfsSimple(result, path, n, k, 1);
    return result;
}

/*
---------------------------------------------
Approach 3: Optimized Backtracking (Pruning + Bounds)
💡 Idea
- Use pruning to avoid exploring impossible branches:
  - If remain < 0, stop (sum exceeded).
  - If remaining picks * minimal possible values > remain, stop.
  - If remaining picks * maximal possible values < remain, stop.
- Early bound checks significantly reduce search space.

🧩 Algorithm
1) dfs(start, remain, k, path):
   - If path.size() == k:
       - If remain == 0: store path
       - Return
   - Let picks_left = k - path.size()
   - Compute minimal_sum = i + (i+1) + ... for next picks_left numbers starting at 'start'
   - Compute maximal_sum = 9 + 8 + ... for picks_left numbers
   - If remain < minimal_sum or remain > maximal_sum: return (prune)
   - For i from start to 9:
       - If i > remain: break (prune)
       - Push i, recurse with i+1, remain - i
       - Pop i

⏱ Time Complexity: Better than plain backtracking due to pruning; still exponential in worst case.
📦 Space Complexity: O(k).
---------------------------------------------
*/
static inline int sumArithmetic(int a1, int d, int terms) {
    // sum of AP: terms/2 * (2*a1 + (terms-1)*d)
    return terms <= 0 ? 0 : (terms * (2 * a1 + (terms - 1) * d)) / 2;
}

void dfsPruned(vector<vector<int>>& result, vector<int>& path, int remain, int k, int start) {
    int picked = (int)path.size();
    if (picked == k) {
        if (remain == 0) result.push_back(path);
        return;
    }

    int picks_left = k - picked;

    // minimal possible sum if we pick the next 'picks_left' smallest numbers starting at 'start'
    // e.g., start + (start+1) + ... for picks_left terms
    int minimal_sum = sumArithmetic(start, 1, picks_left);

    // maximal possible sum if we pick the next 'picks_left' largest numbers up to 9
    // e.g., 9 + 8 + ... for picks_left terms
    int maximal_sum = sumArithmetic(9, -1, picks_left);

    if (remain < minimal_sum) return;  // can't reach remain with smallest choices
    if (remain > maximal_sum) return;  // even picking largest isn't enough

    for (int i = start; i <= 9; ++i) {
        if (i > remain) break; // further numbers only larger
        path.push_back(i);
        dfsPruned(result, path, remain - i, k, i + 1);
        path.pop_back();
    }
}

vector<vector<int>> combinationSum3_Optimized(int k, int n) {
    vector<vector<int>> result;
    vector<int> path;
    dfsPruned(result, path, n, k, 1);
    return result;
}

/*
--------------------------------------------------
MAIN FUNCTION: Example inputs and outputs with multiple test cases
--------------------------------------------------
*/
int main() {
    vector<pair<int,int>> tests = {
        {3, 7},   // [[1,2,4]]
        {3, 9},   // [[1,2,6],[1,3,5],[2,3,4]]
        {2, 5},   // [[1,4],[2,3]]
        {4, 1},   // []
        {3, 24}   // e.g., [[7,8,9]]
    };

    for (auto &tc : tests) {
        int k = tc.first, n = tc.second;

        cout << "\n=== Test Case: k = " << k << ", n = " << n << " ===\n";

        // Approach 1: Brute Force
        auto res1 = combinationSum3_BruteForce(k, n);
        cout << "[Brute Force] Combinations:\n";
        for (auto &comb : res1) {
            cout << "[ ";
            for (int x : comb) cout << x << " ";
            cout << "]\n";
        }

        // Approach 2: Backtracking
        auto res2 = combinationSum3_Backtracking(k, n);
        cout << "[Backtracking] Combinations:\n";
        for (auto &comb : res2) {
            cout << "[ ";
            for (int x : comb) cout << x << " ";
            cout << "]\n";
        }

        // Approach 3: Optimized Backtracking (Pruning)
        auto res3 = combinationSum3_Optimized(k, n);
        cout << "[Optimized Backtracking] Combinations:\n";
        for (auto &comb : res3) {
            cout << "[ ";
            for (int x : comb) cout << x << " ";
            cout << "]\n";
        }
    }

    /*
    ✅ Approach Overview
    - Approach 1: Brute Force
      - Idea: Enumerate all subsets of 1..9 and filter by size and sum.
      - Time: O(2^9 * 9) | Space: O(k) + output
      - Pros: Simple to implement.
      - Cons: Blind search; not scalable (still okay here due to small domain).

    - Approach 2: Backtracking (Simple DFS)
      - Idea: Choose numbers in increasing order, stop at k picks.
      - Time: Exponential in worst-case, small constants due to domain.
      - Space: O(k)
      - Pros: Clean, direct, avoids duplicates naturally.

    - Approach 3: Optimized Backtracking (Pruning)
      - Idea: Add bound checks (minimal/maximal possible sums) and early-stopping.
      - Time: Fastest in practice due to strong pruning.
      - Space: O(k)
      - Pros: Most efficient and interview-ready; scales best within problem limits.
    */

    return 0;
}
