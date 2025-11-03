#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------------
Problem Title: Combination Sum II (LeetCode 40)
Problem Link: https://leetcode.com/problems/combination-sum-ii/

Problem Statement:
Given a collection of candidate numbers (candidates) and a target number (target),
find all unique combinations in candidates where the candidate numbers sum to target.

- Each number in candidates may only be used once in the combination.
- The solution set must not contain duplicate combinations.

Example:
Input:
candidates = [10,1,2,7,6,1,5], target = 8

Output:
[
  [1,1,6],
  [1,2,5],
  [1,7],
  [2,6]
]

Explanation:
- We must ensure each candidate is used at most once.
- Must also handle duplicates in the input carefully to avoid duplicate combinations.
--------------------------------------------------
*/

/* 
---------------------------------------------
Approach 1: Brute Force (Generate All Subsets)
💡 Idea:
- Generate ALL possible subsets using recursion or bitmasking.
- For each subset, check if the sum == target.
- Store subsets in a set (or hash) to ensure uniqueness.

🧩 Algorithm:
1. Generate all subsets of candidates (2^n possibilities).
2. For each subset:
   - If sum == target, add it to result set.
3. Return all unique subsets.

⏱ Time Complexity: O(2^n * n)
📦 Space Complexity: O(n * 2^n)
❌ Not practical for large n, but builds the foundation.
---------------------------------------------
*/
// Skipped here due to inefficiency, we’ll focus on backtracking.

/* 
---------------------------------------------
Approach 2: Recursive Backtracking (DFS)
💡 Idea:
- Sort candidates to easily skip duplicates.
- Use recursion with index `i`.
- At each step:
   - Either skip the element.
   - Or include it (move to next index, since only once allowed).
- If sum == target → store combination.

🧩 Algorithm:
1. Sort candidates.
2. Recursive function (i, target):
   - If target == 0 → store combination.
   - Else loop j from i..n-1:
       - Skip duplicate elements (if candidates[j] == candidates[j-1] and j > i).
       - If candidates[j] > target → break (pruning).
       - Include candidates[j], recurse with target - candidates[j] and next index (j+1).
       - Backtrack (remove last element).
3. Return all stored results.

⏱ Time Complexity: O(2^n) (each element either taken or not).
📦 Space Complexity: O(n) stack depth.
---------------------------------------------
*/
void dfsCombinationSumII(vector<vector<int>> &result, vector<int> &curr,
                         vector<int>& candidates, int target, int start) {
    if (target == 0) {
        result.push_back(curr);
        return;
    }

    for (int j = start; j < candidates.size(); j++) {
        // skip duplicates in same level
        if (j > start && candidates[j] == candidates[j-1]) continue;

        if (candidates[j] > target) break; // pruning

        curr.push_back(candidates[j]);
        dfsCombinationSumII(result, curr, candidates, target - candidates[j], j+1);
        curr.pop_back();
    }
}

vector<vector<int>> combinationSum2_Backtracking(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> result;
    vector<int> curr;
    dfsCombinationSumII(result, curr, candidates, target, 0);
    return result;
}

/* 
---------------------------------------------
Approach 3: Iterative + Set (Alternative)
💡 Idea:
- Simulate subsequence generation iteratively with power set.
- Collect subsets, filter sum, and insert into a set for uniqueness.
- Very inefficient compared to Backtracking.

⏱ Time Complexity: O(2^n * n logM), where M is number of unique subsets.
📦 Space Complexity: O(n * 2^n).
---------------------------------------------
*/
vector<vector<int>> combinationSum2_Iterative(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> result;
    set<vector<int>> uniqueRes;
    int n = candidates.size();
    int total = 1 << n; // power set size

    for (int mask = 0; mask < total; mask++) {
        vector<int> subset;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += candidates[i];
                subset.push_back(candidates[i]);
            }
        }
        if (sum == target) {
            sort(subset.begin(), subset.end()); // ensure order
            uniqueRes.insert(subset);
        }
    }
    for (auto &s : uniqueRes) result.push_back(s);
    return result;
}

/*
--------------------------------------------------
MAIN FUNCTION to demonstrate approaches
--------------------------------------------------
*/
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{10,1,2,7,6,1,5}, 8},
        {{2,5,2,1,2}, 5},
        {{3,1,3,5,1}, 8}
    };

    for (auto &tc : testCases) {
        vector<int> candidates = tc.first;
        int target = tc.second;

        cout << "\n=== Test Case: candidates = { ";
        for (int x : candidates) cout << x << " ";
        cout << "}, target = " << target << " ===\n";

        // Backtracking solution
        auto res2 = combinationSum2_Backtracking(candidates, target);
        cout << "[Backtracking] Unique Combinations:\n";
        for (auto &comb : res2) {
            cout << "[ ";
            for (int num : comb) cout << num << " ";
            cout << "]\n";
        }

        // Iterative + Set (for comparison, less efficient)
        auto res3 = combinationSum2_Iterative(candidates, target);
        cout << "[Iterative+Set] Unique Combinations:\n";
        for (auto &comb : res3) {
            cout << "[ ";
            for (int num : comb) cout << num << " ";
            cout << "]\n";
        }
    }

    /*
    ✅ Approach Overview:
    - Brute Force w/ subsets:
        🔴 Generates all subsets blindly, inefficient. O(2^n * n).
    - Backtracking (DFS):
        🟡 Efficient, avoids duplicates via sorting + skipping.
        Time: O(2^n), Space: O(n).
    - Iterative + Set:
        🟢 Alternative using power set + set for uniqueness.
        Much slower and heavier in memory.
    Best Choice = Backtracking (Approach 2) ✅
    */

    return 0;
}
