#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Longest Consecutive Ones after flipping at most k zeros

Problem Statement:
Given a binary array (or a binary string), return the length of the longest contiguous subarray
containing only 1s after flipping at most k zeros to 1s.

Example:
Input:  nums = [1,1,0,0,1,1,1,0,1,1], k = 2
Output: 8
Explanation: Flip two zeros in the window [1,1,0,0,1,1,1,0] (e.g., positions 2 and 3), window length becomes 8.

Approach Overview:
- Brute Force: For each start index, expand the subarray counting zeros; stop when zeros exceed k.
- Sliding Window (Two-pointer): Maintain a window with at most k zeros; expand right, shrink left when zeros > k.
- Optimal Sliding Window: Same as the optimized approach; O(n) with constant extra space.
*/

/*
Approach: Brute Force
Approach Idea:
- Try every starting point i and extend j while counting zeros.
- Stop extension when zero count exceeds k; track the maximum length valid window.

Algorithm:
1) maxLen = 0
2) For i in [0..n-1]:
   - zero = 0
   - For j in [i..n-1]:
       - if nums[j]==0: zero++
       - if zero > k: break
       - maxLen = max(maxLen, j-i+1)
3) Return maxLen

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
// Variant that accepts a string of '0'/'1'
int longestOnes(string s, int k) {
    int n = (int)s.size();
    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        int zeroCount = 0;
        for (int j = i; j < n; j++) {
            if (s[j] == '0') zeroCount++;
            if (zeroCount > k) break;
            maxLength = max(maxLength, j - i + 1);
        }
    }
    return maxLength;
}

/*
Approach: Optimized Sliding Window (Two-pointer)
Approach Idea:
- Maintain a window [l..r] that contains at most k zeros.
- Expand r and count zeros; while zeros > k, move l right and decrement zero count when passing a zero.
- Track the maximum window length.

Algorithm:
1) l=0, zeros=0, ans=0
2) For r in [0..n-1]:
   - if nums[r]==0: zeros++
   - while zeros > k:
       - if nums[l]==0: zeros--
       - l++
   - ans = max(ans, r-l+1)
3) Return ans

Time Complexity: O(n)
Space Complexity: O(1)
*/
int longestOnes2(vector<int>& nums, int k) {
    int n = nums.size();
    int l = 0, zeros = 0, ans = 0;
    for (int r = 0; r < n; r++) {
        if (nums[r] == 0) zeros++;
        while (zeros > k) {
            if (nums[l] == 0) zeros--;
            l++;
        }
        ans = max(ans, r - l + 1);
    }
    return ans;
}

/*
Approach: Optimal Sliding Window (clean O(n))
Approach Idea:
- Same as the optimized approach; slight variation on updating the answer.

Algorithm:
1) left=0, zeros=0, best=0
2) For right in [0..n-1]:
   - if nums[right]==0: zeros++
   - while zeros > k:
       - if nums[left]==0: zeros--
       - left++
   - best = max(best, right-left+1)
3) Return best

Time Complexity: O(n)
Space Complexity: O(1)
*/
int longestOnes3(vector<int>& nums, int k) {
    int left = 0, zeros = 0, best = 0;
    for (int right = 0; right < nums.size(); right++) {
        if (nums[right] == 0) zeros++;
        while (zeros > k) {
            if (nums[left] == 0) zeros--;
            left++;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

int main() {
    vector<int> nums = {1,1,0,0,1,1,1,0,1,1};
    int k = 2;
    cout << "Brute force (string variant): "
         << longestOnes(string("1100111011"), k) << "\n";
    cout << "Sliding Window: " << longestOnes2(nums, k) << "\n";
    cout << "Optimal Sliding Window: " << longestOnes3(nums, k) << "\n";
    return 0;
}
