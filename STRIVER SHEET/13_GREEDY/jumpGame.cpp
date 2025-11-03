#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Jump Game
 LeetCode Link: https://leetcode.com/problems/jump-game/

 Problem Statement:
 -----------------
 You are given an integer array nums. You are initially positioned at the 
 array's first index, and each element in the array represents your maximum 
 jump length at that position. Return true if you can reach the last index, 
 or false otherwise.

 Example 1:
 Input: nums = [2,3,1,1,4]
 Output: true
 Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

 Example 2:
 Input: nums = [3,2,1,0,4]
 Output: false
 Explanation: You will always arrive at index 3. Its maximum jump length is 0, 
 which makes it impossible to reach the last index.

 Example 3:
 Input: nums = [0]
 Output: true
 Explanation: We are already at the last index.

 Constraints:
 - 1 <= nums.length <= 10^4
 - 0 <= nums[i] <= 10^5
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Recursive Backtracking
 -----------------------------------------
 💡 Idea:
 From each position, try all possible jumps (1 to nums[i]) and recursively
 check if any path leads to the last index.

 🧩 Algorithm:
 1. Start from index 0.
 2. At position i, if i == last index, return true.
 3. If nums[i] == 0, cannot jump further, return false.
 4. Try all jumps from 1 to nums[i], recurse for each.
 5. If any recursive call returns true, return true.
 6. If no jump works, return false.

 ⏱ Time Complexity: O(2^N) - each position may try multiple jumps
 📦 Space Complexity: O(N) - recursion stack depth
*/
bool generateBruteForce(vector<int>& nums, int i) {
    if (i == nums.size() - 1) return true;  // Reached last index
    if (i > nums.size() - 1) return false;  // Overshot the array
    
    if (nums[i] == 0) return false; // Cannot jump from here
    
    // Try all possible jumps from current position
    for (int j = 1; j <= nums[i]; j++) {
        if (generateBruteForce(nums, i + j)) {
            return true;
        }
    }
    
    return false; // No jump worked
}

bool canJumpBruteForce(vector<int>& nums) {
    return generateBruteForce(nums, 0);
}


/* 
==========================================
 Approach 2: Better - Top-Down DP with Memoization
 -----------------------------------------
 💡 Idea:
 Same recursive approach but memoize results to avoid recomputation.
 Use DP array where dp[i] indicates if we can reach end from position i.

 🧩 Algorithm:
 1. Use memoization array: dp[i] = can we reach end from index i?
 2. Initialize all positions as "unknown" (use enum GOOD/BAD/UNKNOWN).
 3. Same recursive logic as brute force.
 4. Store result for each position to avoid recalculation.
 5. Return cached result if already computed.

 ⏱ Time Complexity: O(N^2) - each position computed once, tries all jumps
 📦 Space Complexity: O(N) - DP array + recursion stack
*/
bool generateMemoized(vector<int>& nums, int i, vector<int>& dp) {
    if (i == nums.size() - 1) return true;
    if (i > nums.size() - 1) return false;
    
    // If we already know this position leads to failure
    if (dp[i] == 0) return false; // 0 = BAD, 1 = GOOD, -1 = UNKNOWN
    
    if (nums[i] == 0) return false;
    
    // Try all possible jumps
    for (int j = 1; j <= nums[i]; j++) {
        if (generateMemoized(nums, i + j, dp)) {
            return true;
        }
    }
    
    dp[i] = 0; // Mark this position as BAD
    return false;
}

bool canJumpMemoized(vector<int>& nums) {
    vector<int> dp(nums.size(), -1); // -1 = UNKNOWN, 0 = BAD, 1 = GOOD
    return generateMemoized(nums, 0, dp);
}


/* 
==========================================
 Approach 3: Optimal - Greedy Algorithm
 -----------------------------------------
 💡 Idea:
 Track the maximum reachable position as we iterate through array.
 If current position is beyond max reachable, return false.

 🧩 Algorithm:
 1. Initialize maxReach = 0.
 2. For each position i from 0 to n-1:
    - If i > maxReach, return false (unreachable)
    - Update maxReach = max(maxReach, i + nums[i])
    - If maxReach >= n-1, we can reach end
 3. Return true if we complete iteration.

 ⏱ Time Complexity: O(N) - single pass through array
 📦 Space Complexity: O(1) - only using one variable
*/
bool canJumpOptimal(vector<int>& nums) {
    int maxReach = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        // If current position is unreachable
        if (i > maxReach) return false;
        
        // Update maximum reachable position
        maxReach = max(maxReach, i + nums[i]);
        
        // Early termination: if we can already reach the end
        if (maxReach >= nums.size() - 1) return true;
    }
    
    return true;
}


/* Helper function to trace the path (for demonstration) */
void tracePath(vector<int>& nums) {
    cout << "Optimal path demonstration:\n";
    int maxReach = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        if (i > maxReach) {
            cout << "Position " << i << " is unreachable!\n";
            return;
        }
        
        int oldMaxReach = maxReach;
        maxReach = max(maxReach, i + nums[i]);
        
        cout << "At position " << i << " (value=" << nums[i] << "): ";
        cout << "can reach up to " << maxReach;
        if (maxReach > oldMaxReach) {
            cout << " (improved from " << oldMaxReach << ")";
        }
        cout << "\n";
        
        if (maxReach >= nums.size() - 1) {
            cout << "Can reach the end from position " << i << "!\n";
            break;
        }
    }
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<vector<int>> testCases = {
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4},
        {0},
        {1},
        {1, 2},
        {2, 0},
        {1, 0, 1, 0},
        {2, 5, 0, 0},
        {1, 1, 1, 1, 1},
        {5, 9, 3, 2, 1, 0, 2, 3, 3, 1, 0, 0}
    };

    cout << "=== Testing Jump Game Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> nums1 = testCases[t];
        vector<int> nums2 = testCases[t];
        vector<int> nums3 = testCases[t];
        
        cout << "Test Case " << t + 1 << ":\n";
        cout << "Input: [";
        for (int i = 0; i < nums1.size(); i++) {
            cout << nums1[i];
            if (i < nums1.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        bool ans1 = (nums1.size() <= 10) ? canJumpBruteForce(nums1) : false; // Skip for large inputs
        bool ans2 = canJumpMemoized(nums2);
        bool ans3 = canJumpOptimal(nums3);
        
        if (nums1.size() <= 10) {
            cout << " Brute Force:       " << (ans1 ? "true" : "false") << "\n";
        } else {
            cout << " Brute Force:       [Skipped - too slow]\n";
        }
        cout << " Memoized DP:       " << (ans2 ? "true" : "false") << "\n";
        cout << " Optimal Greedy:    " << (ans3 ? "true" : "false") << "\n";
        
        tracePath(nums3);
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(2^N) time, tries all possible jump combinations.\n";
    cout << "2. Memoized DP -> O(N^2) time, optimizes recursion with caching.\n";
    cout << "3. Optimal Greedy -> O(N) time, tracks maximum reachable position.\n";
    cout << "\nRecommendation: Your optimal greedy approach is brilliant! ✅\n";
    cout << "Key Insight: We don't need to find the actual path, just whether end is reachable.\n";
    cout << "             Track the farthest position reachable so far.\n";
    cout << "\nGreedy Choice: At each position, we know the maximum distance we can reach.\n";
    cout << "If current position is within reach, we can potentially extend our reach.\n";
    cout << "\nYour provided solutions showcase the perfect evolution from recursive\n";
    cout << "to memoized DP to optimal greedy - excellent problem-solving progression! 🎯\n";

    return 0;
}
