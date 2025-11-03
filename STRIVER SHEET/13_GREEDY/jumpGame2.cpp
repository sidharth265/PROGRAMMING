#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Jump Game II
 LeetCode Link: https://leetcode.com/problems/jump-game-ii/

 Problem Statement:
 -----------------
 You are given a 0-indexed array of integers nums of length n. You are 
 initially positioned at nums[0]. Each element nums[i] represents the 
 maximum length of a forward jump from index i. In other words, if you 
 are at nums[i], you can jump to any nums[i + j] where:
 - 0 <= j <= nums[i]
 - i + j < n

 Return the minimum number of jumps to reach nums[n - 1].

 Example 1:
 Input: nums = [2,3,1,1,4]
 Output: 2
 Explanation: The minimum number of jumps to reach the last index is 2. 
 Jump 1 step from index 0 to 1, then 3 steps to the last index.

 Example 2:
 Input: nums = [2,3,0,1,4]
 Output: 2
 Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

 Example 3:
 Input: nums = [1,2,3]
 Output: 2
 Explanation: Jump 1 step from index 0 to 1, then 2 steps to the last index.

 Constraints:
 - 1 <= nums.length <= 10^4
 - 0 <= nums[i] <= 1000
 - It's guaranteed that you can reach nums[n - 1]
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Recursive with All Paths
 -----------------------------------------
 💡 Idea:
 Try all possible jumps from each position recursively and find the path
 that requires minimum number of jumps to reach the end.

 🧩 Algorithm:
 1. Start from index 0 with 0 jumps.
 2. At position i, try all possible jumps from 1 to nums[i].
 3. For each jump, recursively calculate minimum jumps from new position.
 4. Return minimum jumps across all possible paths.
 5. Base case: if we reach last index, return 0.

 ⏱ Time Complexity: O(N^N) - exponential combinations
 📦 Space Complexity: O(N) - recursion stack depth
*/
int jumpBruteForceHelper(vector<int>& nums, int pos) {
    if (pos >= nums.size() - 1) return 0; // Reached or overshot the end
    
    int minJumps = INT_MAX;
    
    // Try all possible jumps from current position
    for (int jump = 1; jump <= nums[pos]; jump++) {
        int result = jumpBruteForceHelper(nums, pos + jump);
        if (result != INT_MAX) {
            minJumps = min(minJumps, 1 + result);
        }
    }
    
    return minJumps;
}

int jumpBruteForce(vector<int>& nums) {
    if (nums.size() <= 1) return 0;
    return jumpBruteForceHelper(nums, 0);
}


/* 
==========================================
 Approach 2: Better - Dynamic Programming
 -----------------------------------------
 💡 Idea:
 Use bottom-up DP where dp[i] represents minimum jumps needed to reach
 the end from position i. Build solution from right to left.

 🧩 Algorithm:
 1. Create dp array where dp[i] = min jumps to reach end from position i.
 2. Initialize dp[n-1] = 0 (already at end).
 3. For each position from n-2 to 0:
    - Try all possible jumps from current position
    - dp[i] = min(dp[i], 1 + dp[i + jump])
 4. Return dp[0].

 ⏱ Time Complexity: O(N^2) - for each position, try all possible jumps
 📦 Space Complexity: O(N) - DP array
*/
int jumpDP(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;
    
    vector<int> dp(n, INT_MAX);
    dp[n - 1] = 0; // No jumps needed from last position
    
    // Fill DP table from right to left
    for (int i = n - 2; i >= 0; i--) {
        // Try all possible jumps from position i
        for (int jump = 1; jump <= nums[i] && i + jump < n; jump++) {
            if (dp[i + jump] != INT_MAX) {
                dp[i] = min(dp[i], 1 + dp[i + jump]);
            }
        }
    }
    
    return dp[0];
}


/* 
==========================================
 Approach 3: Optimal - BFS/Greedy Range-based
 -----------------------------------------
 💡 Idea:
 Think of it as BFS where each "level" represents positions reachable
 with same number of jumps. Use greedy approach to find farthest reach
 in current level, then move to next level.

 🧩 Algorithm:
 1. Use two pointers (l, r) to represent current reachable range.
 2. For each jump level:
    - Find farthest position reachable from current range [l, r]
    - If farthest >= n-1, we can reach end with current jumps
    - Update range to [r+1, farthest] for next level
    - Increment jump count
 3. Continue until we can reach the end.

 ⏱ Time Complexity: O(N) - each position visited at most twice
 📦 Space Complexity: O(1) - only using variables
*/
int jumpOptimal(vector<int>& nums) {
    if (nums.size() <= 1) return 0;
    
    int jumps = 0, l = 0, r = 0;
    
    while (r < nums.size() - 1) {
        int farthest = 0;
        
        // Find farthest position reachable from current range [l, r]
        for (int i = l; i <= r; i++) {
            farthest = max(farthest, i + nums[i]);
        }
        
        // Move to next level
        l = r + 1;
        r = farthest;
        jumps++;
    }
    
    return jumps;
}


/* Alternative cleaner version of the optimal approach */
int jumpOptimalV2(vector<int>& nums) {
    int jumps = 0, currentEnd = 0, farthest = 0;
    
    // Don't need to consider last element since we want to reach it
    for (int i = 0; i < nums.size() - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        
        // When we reach the end of current jump range
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
        }
    }
    
    return jumps;
}


/* Helper function to show the jumping process */
void demonstrateJumps(vector<int>& nums) {
    cout << "Jump demonstration:\n";
    int jumps = 0, l = 0, r = 0;
    
    cout << "Initial range: [" << l << ", " << r << "]\n";
    
    while (r < nums.size() - 1) {
        int farthest = 0;
        cout << "Jump " << (jumps + 1) << ": From range [" << l << ", " << r << "] ";
        
        for (int i = l; i <= r; i++) {
            int reach = i + nums[i];
            farthest = max(farthest, reach);
            cout << "pos" << i << "(+" << nums[i] << "→" << reach << ") ";
        }
        
        l = r + 1;
        r = farthest;
        jumps++;
        
        cout << "→ new range [" << l << ", " << r << "]\n";
        
        if (r >= nums.size() - 1) {
            cout << "Can reach end with " << jumps << " jumps!\n";
            break;
        }
    }
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<vector<int>> testCases = {
        {2, 3, 1, 1, 4},
        {2, 3, 0, 1, 4},
        {1, 2, 3},
        {1},
        {1, 2},
        {2, 1},
        {1, 1, 1, 1},
        {3, 2, 1},
        {5, 6, 4, 4, 6, 9, 4, 4, 7, 4, 4, 8, 2, 6, 8, 1, 5, 9, 6, 5, 2, 7, 9, 8, 3, 2, 3, 6, 6, 1, 3, 5, 3, 8, 2, 4, 6, 6, 0, 3, 2, 8, 2, 6, 5, 3, 6}
    };

    cout << "=== Testing Jump Game II Problem ===\n\n";
    
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
        
        int ans1 = (nums1.size() <= 8) ? jumpBruteForce(nums1) : -1; // Skip for large inputs
        int ans2 = jumpDP(nums2);
        int ans3 = jumpOptimal(nums3);
        
        if (ans1 != -1) {
            cout << " Brute Force:       " << ans1 << "\n";
        } else {
            cout << " Brute Force:       [Skipped - too slow]\n";
        }
        cout << " Dynamic Programming: " << ans2 << "\n";
        cout << " Optimal BFS/Greedy:  " << ans3 << "\n";
        
        if (nums1.size() <= 10) {
            demonstrateJumps(nums3);
        }
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N^N) time, tries all possible jump combinations.\n";
    cout << "2. Dynamic Programming -> O(N^2) time, builds solution bottom-up.\n";
    cout << "3. Optimal BFS/Greedy -> O(N) time, treats problem as level-wise BFS.\n";
    cout << "\nRecommendation: Your optimal BFS/Greedy approach is exceptional! ✅\n";
    cout << "Key Insight: Think of it as BFS where each level represents positions\n";
    cout << "             reachable with the same number of jumps.\n";
    cout << "\nRange-based Greedy:\n";
    cout << "- [l, r] represents current reachable positions with 'jumps' steps\n";
    cout << "- Find farthest position reachable from this range\n";
    cout << "- Move to next level: [r+1, farthest] with 'jumps+1' steps\n";
    cout << "\nYour provided solution is the optimal BFS/Greedy approach - brilliantly implemented! 🎯\n";
    cout << "The range-based thinking (l, r pointers) makes this problem elegant and efficient.\n";

    return 0;
}
