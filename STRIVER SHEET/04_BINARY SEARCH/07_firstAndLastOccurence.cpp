#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Find First and Last Position of a Target in a Sorted Array

Problem Statement:
Given a sorted array nums (non-decreasing) and an integer target, return the starting and ending index of target in nums.
If target is not present, return {-1, -1}. The solution should run in O(log n) time.

Example:
Input:  nums = [1, 2, 3, 3, 3, 4, 5], target = 3
Output: [2, 4]

Approach Overview:
- Brute Force: Scan from left to find the first index, scan from right to find the last index. O(n).
- Optimized (Binary Search): Perform two binary searches:
  - Lower bound of target (first index with nums[i] >= target), check equality for existence.
  - Upper bound of target (first index with nums[i] > target) minus one gives last index.
  Both searches are O(log n), total O(log n).
*/

/*
Approach: Brute Force
Approach Idea:
- Linearly find the first occurrence by scanning from left.
- Linearly find the last occurrence by scanning from right.

Algorithm:
1) ans = {-1, -1}
2) For i from 0..n-1: if nums[i] == target: ans[0] = i; break
3) For i from n-1..0: if nums[i] == target: ans[1] = i; break
4) Return ans

Time Complexity: O(n)
Space Complexity: O(1)
*/
vector<int> searchRange(vector<int>& nums, int target) {
    int n = nums.size();
    vector<int> ans(2, -1);
    for (int i = 0; i < n; i++) {
        if (nums[i] == target) {
            ans[0] = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] == target) {
            ans[1] = i;
            break;
        }
    }
    return ans;
}

/*
Approach: Optimized Binary Search (Two passes)
Approach Idea:
- First pass: find first index where nums[i] >= target (lower bound).
  - If that index is out of bounds or nums[idx] != target, target doesn’t exist -> return {-1,-1}.
  - Else, this idx is the first occurrence.
- Second pass: find first index where nums[i] > target (upper bound), then last occurrence is idx - 1.

Algorithm:
1) lb = lower_bound_index(nums, target)
   - Binary search: while low <= high:
       mid = low + (high-low)/2
       if nums[mid] >= target: ans = mid, high = mid - 1
       else low = mid + 1
   - return ans (or n if not found)
2) If lb == n or nums[lb] != target: return {-1,-1}
3) ub = upper_bound_index(nums, target)
   - Binary search: while low <= high:
       mid = low + (high-low)/2
       if nums[mid] > target: ans = mid, high = mid - 1
       else low = mid + 1
   - return ans (or n if not found)
4) Return {lb, ub - 1}

Time Complexity: O(log n)
Space Complexity: O(1)
*/
static int lowerBoundIdx(const vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1, ans = n;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (nums[mid] >= target) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

static int upperBoundIdx(const vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1, ans = n;
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (nums[mid] > target) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

vector<int> searchRange2(vector<int>& nums, int target) {
    int n = nums.size();
    int lb = lowerBoundIdx(nums, target);
    if (lb == n || nums[lb] != target) return {-1, -1};
    int ub = upperBoundIdx(nums, target);
    return {lb, ub - 1};
}

// Example usage
int main() {
    vector<int> nums = {1, 2, 3, 3, 3, 4, 5};
    int target = 3;

    auto res1 = searchRange(nums, target);
    cout << "Brute Force -> First: " << res1[0] << ", Last: " << res1[1] << "\n";

    auto res2 = searchRange2(nums, target);
    cout << "Binary Search -> First: " << res2[0] << ", Last: " << res2[1] << "\n";

    return 0;
}
