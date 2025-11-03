#include<bits/stdc++.h>
using namespace std;

/*
Problem: Two Sum

Problem Statement:
Given an array of integers nums and an integer target, return the indices of the two numbers such that they add up to target.
- Exactly one valid solution exists.
- The same element cannot be used twice.
- Return the answer in any order.

Example:
Input:
  nums = [2, 7, 11, 15], target = 9
Output:
  [0, 1]
Explanation:
- nums[0] + nums[1] = 2 + 7 = 9.

Approach Overview:
- Brute Force: Check all pairs with two loops.
- Slightly Better Pair Scan: Same O(n^2), but only checks j>i.
- Optimized Hashing: One-pass hash map to find complements in O(n).

Complexity Overview:
- Brute Force: Time O(n^2), Space O(1).
- Better Pair Scan: Time O(n^2), Space O(1).
- Hashing (recommended): Time O(n), Space O(n).
*/

/*
Approach 1: Brute Force

Idea:
- Try every pair (i, j) with i != j and check if nums[i] + nums[j] == target.

Algorithm:
1) For i from 0..n-1:
   - For j from 0..n-1, j != i:
       * If nums[i] + nums[j] == target, return {i, j}.
2) If no pair found, return empty.

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (j!=i && nums[j] == target-nums[i]) {
                return {i, j};
            }
        }
    }
    return {};
}

/*
Approach 2: Better Double Loop (avoid duplicate checks)

Idea:
- Check only pairs where j>i to avoid redundant comparisons.

Algorithm:
1) For i from 0..n-2:
   - For j from i+1..n-1:
       * If nums[i] + nums[j] == target, return {i, j}.
2) If no pair found, return empty.

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
vector<int> twoSum2(vector<int>& nums, int target) {
    int n = nums.size();
    for(int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            if ( nums[j] == target-nums[i]) {
                return {i, j};
            }
        }
    }
    return {};
}

/*
Approach 3: Optimized One-Pass Hashing (Recommended)

Idea:
- While iterating, check if the complement (target - nums[i]) has been seen.
- If seen, return its index and current i; otherwise store nums[i] -> i.

Algorithm:
1) Initialize an empty hash map m (value -> index).
2) For i from 0..n-1:
   - s = target - nums[i]
   - If s exists in m: return {m[s], i}
   - Else, store m[nums[i]] = i
3) If no pair found, return empty.

Time Complexity: O(n)
Space Complexity: O(n)
*/
vector<int> twoSum3(vector<int>& nums, int target) {
    int n = nums.size();
    unordered_map<int,int> m;
    for (int i=0; i<n; i++) {
        int s = target-nums[i];
        if (m.find(s) != m.end()) {
            return {m[s], i};
        }
        m[nums[i]] = i;
    }
    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    // Choose the desired approach:
    // vector<int> result = twoSum(nums, target);   // Brute Force
    vector<int> result = twoSum2(nums, target);     // Better Double Loop
    // vector<int> result = twoSum3(nums, target);  // Optimized Hashing

    if (result.size() == 2) {
        cout << "Indices: " << result[0] << ", " << result[1] << endl;
    } else {
        cout << "No solution found." << endl;
    }
    return 0;
}
