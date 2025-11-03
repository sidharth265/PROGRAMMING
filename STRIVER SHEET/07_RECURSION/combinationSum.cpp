#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------------
Problem Title: Combination Sum (LeetCode 39)
Problem Link: https://leetcode.com/problems/combination-sum/

Problem Statement:
Given an array of distinct integers `candidates` and a target integer `target`, 
return all unique combinations of candidates where the chosen numbers sum to `target`. 
You may use the same number from candidates an unlimited number of times. 
The order of combinations does not matter.

Example:
Input:
candidates = [2,3,6,7], target = 7

Output:
[
    [2,2,3],
    [7]
]

Explanation:
- Using 2s and 3 → (2 + 2 + 3) = 7
- Using a single 7 → (7) = 7
Other combinations do not sum up to 7.
--------------------------------------------------
*/

/* 
---------------------------------------------
Approach 1: Brute Force (Generate all subsets + check sum)
💡 Idea:
- Generate all subsets of candidates (using recursion or bitmask).
- For each subset, check if sum == target.

🧩 Algorithm:
1. Generate power set of candidates with possible repetitions.
2. Check sum of each subset.
3. Keep subsets with sum = target.

⏱ Time Complexity: O(2^n * n), inefficient.
📦 Space Complexity: O(n*2^n)
❌ Not practical for interviews, but useful starting idea.
---------------------------------------------
*/
// (Skipping full brute force implementation here for focus on better approaches)

/* 
---------------------------------------------
Approach 2: Recursive Backtracking (DFS) ✅
💡 Idea:
- At each index, decide:
   1. Pick: include candidates[i] if ≤ target, reduce target, recurse (i remains same).
   2. Skip: move to next index.

🧩 Algorithm:
1. Sort candidates (optional for better pruning).
2. Use recursion:
   - If target == 0 → push current combination.
   - If target < 0 or index == n → return.
   - Else → try including candidates[i] OR skipping it.
3. Ensure duplicates are avoided as input already distinct.

⏱ Time Complexity: O(2^t) where t = target/candidates_min (each path considered).
📦 Space Complexity: O(target) recursion stack.
---------------------------------------------
*/
void backtrackCombination(vector<vector<int>> &result, vector<int> &curr,
                          vector<int> &candidates, int target, int i) {
    // base cases
    if (target == 0) {
        result.push_back(curr);
        return;
    }
    if (i == candidates.size()) return;

    // pick current element (if allowed)
    if (candidates[i] <= target) {
        curr.push_back(candidates[i]);
        backtrackCombination(result, curr, candidates, target - candidates[i], i); // same index, unlimited usage
        curr.pop_back();
    }

    // skip current element
    backtrackCombination(result, curr, candidates, target, i+1);
}

vector<vector<int>> combinationSum_Backtracking(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> curr;
    backtrackCombination(result, curr, candidates, target, 0);
    return result;
}

/* 
---------------------------------------------
Approach 3: Optimized Backtracking with Pruning
💡 Idea:
- Sort candidates.
- If candidates[i] > target, break loop early (pruning).
- Avoid exploring impossible branches.

🧩 Algorithm:
1. Sort candidates to enable early pruning.
2. In recursive function:
   - For every candidate >= start index:
       - If candidate > target → break
       - Else pick candidate and recurse with reduced target.
3. This avoids useless recursive calls.

⏱ Time Complexity: Better than Approach 2 (due to pruning).
📦 Space Complexity: O(target).
---------------------------------------------
*/
void dfsPruned(vector<vector<int>> &result, vector<int> &curr,
               vector<int>& candidates, int target, int start) {
    if (target == 0) {
        result.push_back(curr);
        return;
    }

    for (int i = start; i < candidates.size(); i++) {
        if (candidates[i] > target) break; // pruning step
        curr.push_back(candidates[i]);
        dfsPruned(result, curr, candidates, target - candidates[i], i); // reuse allowed
        curr.pop_back();
    }
}

vector<vector<int>> combinationSum_Pruned(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> result;
    vector<int> curr;
    dfsPruned(result, curr, candidates, target, 0);
    return result;
}

/*
--------------------------------------------------
MAIN FUNCTION to demonstrate all approaches
--------------------------------------------------
*/
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{2,3,6,7}, 7},
        {{2,3,5}, 8},
        {{2}, 1}
    };

    for (auto &tc : testCases) {
        vector<int> candidates = tc.first;
        int target = tc.second;

        cout << "\n=== Test Case: candidates = { ";
        for (int x : candidates) cout << x << " ";
        cout << "}, target = " << target << " ===\n";

        // Backtracking solution
        auto res2 = combinationSum_Backtracking(candidates, target);
        cout << "[Backtracking] Combinations:\n";
        for (auto &comb : res2) {
            cout << "[ ";
            for (int num : comb) cout << num << " ";
            cout << "]\n";
        }

        // Optimized Backtracking with Pruning
        auto res3 = combinationSum_Pruned(candidates, target);
        cout << "[Pruned Backtracking] Combinations:\n";
        for (auto &comb : res3) {
            cout << "[ ";
            for (int num : comb) cout << num << " ";
            cout << "]\n";
        }
    }

    /*
    ✅ Approach Overview:
    - Brute Force (subset generation):
        🔴 Inefficient, checks too many invalid subsets.
    - Backtracking (DFS):
        🟡 Neat recursion approach. Time: O(2^t), Space: O(target).
    - Pruned Backtracking:
        🟢 Most efficient for this problem.
        Sorting + pruning avoids useless recursion.
    */

    return 0;
}
