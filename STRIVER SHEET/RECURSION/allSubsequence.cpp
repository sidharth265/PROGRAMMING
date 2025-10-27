#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------------
Problem Title: Generate All Subsequences (Subsets) of a Set
Problem Link: Classic Backtracking / Power Set problem (LeetCode 78 - Subsets)

Problem Statement:
Given a set (array of distinct integers) `nums`, return all possible subsets 
(power set). The solution set must not contain duplicate subsets.

Example:
Input:
nums = [1, 2, 3]

Output:
[
  [], 
  [1], 
  , 
  , 
  [1, 2], 
  [1, 3], 
  [2, 3], 
  [1, 2, 3]
]

Explanation:
All possible subsets (2^3 = 8) are included, starting from empty subset.
--------------------------------------------------
*/

/* 
---------------------------------------------
Approach 1: Brute Force Using Bitmasking
💡 Idea:
- Each element can either be INCLUDED or EXCLUDED in a subset.
- Represent selection as a binary string of length n (0 = exclude, 1 = include).
- There are 2^n subsets in total.

🧩 Algorithm:
1. For integer mask = 0 to (2^n - 1):
   - For each bit in mask, decide if element belongs in subset.
2. Collect and return all subsets.

⏱ Time Complexity: O(n * 2^n)
📦 Space Complexity: O(n * 2^n) for results
---------------------------------------------
*/
vector<vector<int>> subsetsBitmask(vector<int>& nums) {
    int n = nums.size();
    int total = 1 << n; // 2^n
    vector<vector<int>> result;

    for (int mask = 0; mask < total; mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) subset.push_back(nums[i]);
        }
        result.push_back(subset);
    }
    return result;
}

/* 
---------------------------------------------
Approach 2: Recursive Backtracking
💡 Idea:
- At each index, we make 2 choices:
   1. Exclude the current element.
   2. Include the current element.
- Use recursion to explore both paths.
- Base case: when we’ve processed all elements, store the subset.

🧩 Algorithm:
1. Recursively explore decision tree (include or exclude each item).
2. At end, add constructed subset to results.

⏱ Time Complexity: O(2^n)
📦 Space Complexity: O(n * 2^n)
---------------------------------------------
*/
void generateBacktracking(vector<int>& arr, vector<vector<int>>& result, vector<int>& nums, int idx) {
    if (idx == nums.size()) {
        result.push_back(arr);
        return;
    }
    // Exclude
    generateBacktracking(arr, result, nums, idx+1);

    // Include
    arr.push_back(nums[idx]);
    generateBacktracking(arr, result, nums, idx+1);
    arr.pop_back();
}

vector<vector<int>> subsetsBacktracking(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> arr;
    generateBacktracking(arr, result, nums, 0);
    return result;
}

/* 
---------------------------------------------
Approach 3: Iterative Approach (Optimal for Memory)
💡 Idea:
- Start with empty set [[]].
- For each element in nums:
   - Take all existing subsets.
   - Create new subsets by adding current element to each.
   - Append new subsets to result.

🧩 Algorithm:
1. Initialize result = [[]]
2. For each num in nums:
   - For each existing subset in result, copy it and add `num`.
   - Append new subsets to result.
3. Return result.

⏱ Time Complexity: O(n * 2^n)
📦 Space Complexity: O(n * 2^n) 
---------------------------------------------
*/
vector<vector<int>> subsetsIterative(vector<int>& nums) {
    vector<vector<int>> result = {{}};
    for (int num : nums) {
        vector<vector<int>> newSubsets;
        for (auto subset : result) {
            subset.push_back(num);
            newSubsets.push_back(subset);
        }
        for (auto s : newSubsets) result.push_back(s);
    }
    return result;
}

/*
--------------------------------------------------
MAIN FUNCTION to demonstrate all approaches
--------------------------------------------------
*/
int main() {
    vector<vector<int>> testCases = {
        {1, 2, 3},
        {0, 1},
        {5}
    };

    for (auto nums : testCases) {
        cout << "\n=== Test Case: { ";
        for (int x : nums) cout << x << " ";
        cout << "} ===\n";

        // Brute Force (Bitmasking)
        auto res1 = subsetsBitmask(nums);
        cout << "[Bitmasking] Subsets:\n";
        for (auto &subset : res1) {
            cout << "{ ";
            for (int val : subset) cout << val << " ";
            cout << "}\n";
        }

        // Backtracking
        auto res2 = subsetsBacktracking(nums);
        cout << "[Backtracking] Subsets:\n";
        for (auto &subset : res2) {
            cout << "{ ";
            for (int val : subset) cout << val << " ";
            cout << "}\n";
        }

        // Iterative
        auto res3 = subsetsIterative(nums);
        cout << "[Iterative] Subsets:\n";
        for (auto &subset : res3) {
            cout << "{ ";
            for (int val : subset) cout << val << " ";
            cout << "}\n";
        }
    }

    /*
    ✅ Approach Overview:
    - Bitmasking:
        🔴 Simple but explicitly scans all 2^n binary masks.
        Time: O(n * 2^n), Space: O(n * 2^n)
    - Backtracking:
        🟡 Elegant recursion, direct subsets exploration, easy to extend.
        Time: O(2^n), Space: O(n*2^n)
    - Iterative:
        🟢 Easy to reason iteratively, clean memory usage.
        Time: O(n * 2^n)
    */
    return 0;
}
