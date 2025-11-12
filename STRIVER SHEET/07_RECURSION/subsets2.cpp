#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Subsets II (All Unique Subsets)
 Problem Link: (LeetCode 90 or similar)
====================================================

📝 Problem Statement:
Given an integer array that may contain duplicates, return all possible subsets (the power set) without duplicate subsets.
The solution set must not contain duplicate subsets. The subsets can be returned in any order.

📌 Input:
- An array of integers `nums` (may contain duplicates)

📌 Output:
- A vector of vectors containing all unique subsets.

----------------------------------------------------
🔹 Example 1:
Input: nums = [1, 2, 2]
Output:
[
  [],
  [1],
  [2],
  [1,2],
  [2,2],
  [1,2,2]
]

🔹 Explanation:
Although 2 appears twice, subsets do not repeat and duplicates are avoided.

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Brute Force using Set to Avoid Duplicates
//////////////////////////////////////////////////////
/*
💡 Idea:
- Generate all subsequences recursively.
- Sort each subsequence to treat duplicates as identical.
- Insert into a set to ensure uniqueness.

🧩 Algorithm:
1. Recursively include or exclude each element.
2. At base case, sort the current subset and insert into a set.
3. Convert the set to vector before returning.

⏱ Time Complexity: O(2^n * n log n) due to subset sorting and insertion in set.  
📦 Space Complexity: O(n * 2^n) for storing all subsets in set.
*/

void generate(set<vector<int>> &result, vector<int> arr, const vector<int> &nums, int i) {
    if (i == nums.size()) {
        sort(arr.begin(), arr.end());
        result.insert(arr);
        return;
    }
    // Not pick nums[i]
    generate(result, arr, nums, i + 1);

    // Pick nums[i]
    arr.push_back(nums[i]);
    generate(result, arr, nums, i + 1);
}

vector<vector<int>> subsetsWithDupBrute(vector<int> &nums) {
    set<vector<int>> result;
    vector<int> arr;
    generate(result, arr, nums, 0);
    return vector<vector<int>>(result.begin(), result.end());
}


//////////////////////////////////////////////////////
// Approach 2: Optimized Backtracking with Sorting & Skipping Duplicates
//////////////////////////////////////////////////////
/*
💡 Idea:
- Sort array to bring duplicates together.
- Use backtracking while skipping duplicates in recursive calls.

🧩 Algorithm:
1. Sort nums.
2. Recursively build subsets from index i.
3. At each level, iterate j from i to end:
   - If nums[j] == nums[j-1] and j > i, skip to avoid duplicates.
   - Include nums[j] and recurse for j+1.
4. Add each subset formed to result.

⏱ Time Complexity: O(2^n * n) generating subsets and copying subsets.  
📦 Space Complexity: O(n * 2^n) for storing subsets.
*/

void generate2(vector<vector<int>> &result, vector<int> &arr, const vector<int> &nums, int i) {
    result.push_back(arr);
    for (int j = i; j < nums.size(); j++) {
        if (j > i && nums[j] == nums[j - 1]) 
            continue; // skip duplicates
        arr.push_back(nums[j]);
        generate2(result, arr, nums, j + 1);
        arr.pop_back();
    }
}

vector<vector<int>> subsetsWithDupOptimized(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> arr;
    generate2(result, arr, nums, 0);
    return result;
}


//////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////
int main() {
    vector<int> nums = {1, 2, 2};

    cout << "Brute Force Unique Subsets:\n";
    vector<vector<int>> resBrute = subsetsWithDupBrute(nums);
    for (const auto &subset : resBrute) {
        for (int num : subset) cout << num << " ";
        cout << "\n";
    }

    cout << "\nOptimized Unique Subsets:\n";
    vector<vector<int>> resOpt = subsetsWithDupOptimized(nums);
    for (const auto &subset : resOpt) {
        for (int num : subset) cout << num << " ";
        cout << "\n";
    }

    return 0;
}


//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// 1. Brute Force: Generates all subsets with duplicates,
//    sorts them and uses a set for uniqueness - costly due to sorting and set insertion.
// 2. Optimized: Sorts input upfront and uses backtracking with
//    duplicate skipping - more efficient and preferred in interviews.
