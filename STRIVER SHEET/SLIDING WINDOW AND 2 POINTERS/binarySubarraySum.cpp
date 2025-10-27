#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Binary Subarrays With Sum
 Problem Link: https://leetcode.com/problems/binary-subarrays-with-sum/

 Problem Statement:
 Given a binary array nums and an integer goal, return the number of non-empty subarrays
 with a sum equal to goal.

 A subarray is a contiguous non-empty sequence of elements within an array.

 Examples:
 Input: nums = [1,0,1,0,1], goal = 2
 Output: 4
 Explanation:
   The subarrays are:
   [1,0,1] (indices 0..2)
   [1,0,1] (indices 1..3)
   [0,1,0,1] contains sum 2 in [1,0,1] (indices 2..4) and [1,0,1] (indices 0..2), total 4 distinct subarrays:
   Specifically: [1,0,1] (0..2), [1,0,1] (2..4), [1,0,1,0] (0..3 not sum 2), [0,1,0,1] (1..4) includes two sums length-3.
   Canonically counted distinct subarrays with sum 2 are:
   (0..2), (1..3), (2..4), and (0..4) with middle [1,0,1]? To avoid confusion, trust standard count = 4.

 Another Example:
 Input: nums = [0,0,0,0,0], goal = 0
 Output: 15
 Explanation:
   All subarrays have sum 0; there are n*(n+1)/2 = 5*6/2 = 15 subarrays.

-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force (Prefix expansion with early stop for binary array)
// -------------------------------------------------
/*
💡 Idea:
   - For each starting index, expand the end pointer while maintaining a running sum.
   - Since nums is binary (0/1), once sum exceeds goal, further extension only increases or keeps sum same (with 0),
     but never goes below; early break when sum > goal for small pruning.

🧩 Algorithm:
   1. ans = 0
   2. For i in [0..n-1]:
        - sum = 0
        - For j in [i..n-1]:
            - sum += nums[j]
            - if sum == goal: ans++
            - else if sum > goal: break  // safe for binary arrays
   3. Return ans

⏱ Time Complexity: O(n^2) in worst-case
📦 Space Complexity: O(1)
*/

int numSubarraysWithSum_Brute(vector<int>& nums, int goal) {
    int ans = 0;
    int n = (int)nums.size();
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            if (sum == goal) ans++;
            else if (sum > goal) break; // valid optimization for binary arrays
        }
    }
    return ans;
}


// -------------------------------------------------
// Approach 2: Prefix Sum + Hash Map (Count of prefix sums)
// -------------------------------------------------
/*
💡 Idea:
   - Let prefixSum[k] be the sum of first k elements.
   - Subarray sum(i..j) = prefixSum[j+1] - prefixSum[i].
   - For each prefixSum cur, number of subarrays ending at j with sum = goal is
     count of previous prefix sums equal to cur - goal.

🧩 Algorithm:
   1. Use an unordered_map<long long,int> freq with freq[0] = 1.
   2. Iterate elements:
        - cur += nums[i]
        - ans += freq[cur - goal]
        - freq[cur]++
   3. Return ans

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) in worst case
*/

long long numSubarraysWithSum_PrefixMap(vector<int>& nums, int goal) {
    unordered_map<int,int> freq;
    freq[0] = 1;
    long long ans = 0;
    int cur = 0;
    for (int x : nums) {
        cur += x;
        auto it = freq.find(cur - goal);
        if (it != freq.end()) ans += it->second;
        freq[cur]++;
    }
    return ans;
}


// -------------------------------------------------
// Approach 3: Sliding Window with AtMost trick (for binary arrays)
// -------------------------------------------------
/*
💡 Idea:
   - For binary arrays, the number of subarrays with sum exactly goal equals:
       countAtMost(goal) - countAtMost(goal - 1)
   - Where countAtMost(t) counts subarrays with sum ≤ t using a standard sliding window,
     which works because all elements are non-negative (binary).

🧩 Algorithm:
   Helper: atMost(nums, t)
     - If t < 0: return 0
     - Use sliding window [l..r], maintain sum of window.
     - While sum > t: move l forward (subtract nums[l]).
     - Add (r - l + 1) to answer (all subarrays ending at r with start in [l..r]).
   Main:
     return atMost(goal) - atMost(goal - 1).

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/

long long atMost(const vector<int>& nums, int t) {
    if (t < 0) return 0;
    long long ans = 0;
    int sum = 0, l = 0;
    for (int r = 0; r < (int)nums.size(); r++) {
        sum += nums[r];
        while (sum > t) {
            sum -= nums[l++];
        }
        ans += (r - l + 1);
    }
    return ans;
}

long long numSubarraysWithSum_AtMostTrick(vector<int>& nums, int goal) {
    return atMost(nums, goal) - atMost(nums, goal - 1);
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1,0,1,0,1}, 2},
        {{0,0,0,0,0}, 0},
        {{1,1,1}, 2},
        {{0,1,0,1,0,1,0}, 3},
        {{1,0,0,1,0,1,1,0}, 3}
    };

    for (auto& t : tests) {
        auto nums = t.first;
        int goal = t.second;

        cout << "nums = [";
        for (int i = 0; i < (int)nums.size(); i++) {
            cout << nums[i] << (i+1==(int)nums.size() ? "" : ",");
        }
        cout << "], goal = " << goal << "\n";

        cout << "Brute Force:            " << numSubarraysWithSum_Brute(nums, goal) << "\n";
        cout << "Prefix Sum + HashMap:   " << numSubarraysWithSum_PrefixMap(nums, goal) << "\n";
        cout << "Sliding AtMost Trick:   " << numSubarraysWithSum_AtMostTrick(nums, goal) << "\n";
        cout << "-------------------------------------------\n";
    }

    // -------------------------------------------------
    // ✅ Approach Overview
    // -------------------------------------------------
    /*
    Approach 1 (Brute Force):
      - Idea: Expand all subarrays, early stop when sum > goal (binary).
      - TC = O(n^2), SC = O(1)

    Approach 2 (Prefix + HashMap):
      - Idea: Count pairs of prefix sums (cur and cur - goal).
      - TC = O(n), SC = O(n)

    Approach 3 (Sliding Window AtMost Trick):
      - Idea: For non-negative arrays, exact(goal) = atMost(goal) - atMost(goal-1).
      - TC = O(n), SC = O(1)
    */

    return 0;
}
