#include<bits/stdc++.h>
using namespace std;

/*
Problem: Maximum Subarray (Kadane's Algorithm variant with subarray retrieval)

Problem Statement:
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return that subarray itself.

Example:
Input:
  nums = [-2, 1, -3, 4, -1, -2, 1, 5, -5, 4]
Output:
  [4, -1, -2, 1, 5]
Explanation:
- The maximum sum is 7, obtained by the subarray [4, -1, -2, 1, 5].

Approach:
- Kadane’s Algorithm (tracking subarray boundaries):
  - Maintain a running sum; if it drops below 0, reset it and move the tentative start forward.
  - Track the best (maximum) sum seen so far and the corresponding end index.
  - After the pass, the subarray is from bestStart to bestEnd.

Algorithm:
1) Initialize:
   - max_sum = -inf, sum = 0
   - start = 0 (current tentative start)
   - bestStart = 0, bestEnd = 0
2) For i from 0 to n-1:
   - sum += nums[i]
   - If sum > max_sum: update max_sum = sum; bestStart = start; bestEnd = i
   - If sum < 0: sum = 0; start = i+1
3) Return nums[bestStart..bestEnd] as the maximum-sum subarray.

Time Complexity:
- O(n) single pass

Space Complexity:
- O(1) auxiliary (excluding returned subarray)
*/
vector<int> maxSubArray(vector<int> nums)
{
    int n = nums.size();
    long long max_sum = LLONG_MIN;
    long long sum = 0;
    int start = 0;
    int bestStart = 0, bestEnd = 0;

    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
        if (sum > max_sum) {
            max_sum = sum;
            bestStart = start;
            bestEnd = i;
        }
        if (sum < 0)
        {
            sum = 0;
            start = i+1;
        }
    }
    return vector<int>(nums.begin() + bestStart, nums.begin() + bestEnd + 1);
}

int main()
{
    vector<int> nums = {-2, 1, -3, 4, -1, -2, 1, 5, -5, 4};
    vector<int> result = maxSubArray(nums);
    cout << "Maximum Subarray: ";
    for (int i = 0; i < (int)result.size(); i++)
    {
        cout << result[i] << " ";
    }
    return 0;
}
