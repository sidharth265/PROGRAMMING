#include<bits/stdc++.h>
using namespace std;

/*
Problem: Maximum Subarray Sum (with variants and subarray retrieval)

Problem Statement:
Given an integer array nums, find:
1) The maximum possible sum of a contiguous subarray (at least one element).
2) Optionally, retrieve one subarray that achieves this maximum sum.

Example:
Input:
  nums = [-2, 1, -3, 4, -1, -2, 1, 5, -5, 4]
Output:
  Maximum Sum: 7
  One Maximum Subarray: [4, -1, -2, 1, 5]
Explanation:
- The subarray [4, -1, -2, 1, 5] has sum 7, which is maximal.

Approach Overview:
- Brute Force O(n^3): Check all subarrays and compute sums three nested loops.
- Improved O(n^2): Fix start, extend end while maintaining a running sum.
- Kadane’s Algorithm O(n): Single pass tracking running sum and best sum.
- Subarray Retrieval: Kadane variant tracking start/end indices to return the actual subarray.

Complexity Overview:
- Brute Force: Time O(n^3), Space O(1).
- Improved: Time O(n^2), Space O(1).
- Kadane: Time O(n), Space O(1).
- Retrieval variant: Time O(n), Space O(1) auxiliary (excluding returned subarray).
*/

/*
Approach 1: Brute Force (O(n^3))

Idea:
- Enumerate all (i, j) and compute the sum by iterating k from i..j.

Algorithm:
1) max_sum = -inf
2) For i in [0..n-1]:
     For j in [i..n-1]:
        sum = 0
        For k in [i..j]: sum += nums[k]
        max_sum = max(max_sum, sum)
3) Return max_sum
*/
int maxSubArray(vector<int> nums)
{
    int n = nums.size();
    int max_sum = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int sum = 0;
            for (int k = i; k <= j; k++)
            {
                sum += nums[k];
            }
            max_sum = max(max_sum, sum);
        }
    }
    return max_sum;
}

/*
Approach 2: Improved O(n^2) with running sum

Idea:
- Fix start i; extend j and accumulate sum incrementally without inner-most loop.

Algorithm:
1) max_sum = -inf
2) For i in [0..n-1]:
     sum = 0
     For j in [i..n-1]:
        sum += nums[j]
        max_sum = max(max_sum, sum)
3) Return max_sum
*/
int maxSubArray2(vector<int> nums)
{
    int n = nums.size();
    int max_sum = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += nums[j];
            max_sum = max(max_sum, sum);
        }
    }
    return max_sum;
}

/*
Approach 3: Kadane’s Algorithm (O(n)) — Maximum Sum

Idea:
- Maintain a running sum; if it drops below 0, reset to 0.
- Track the best maximum sum encountered.

Algorithm:
1) max_sum = -inf, sum = 0
2) For each x in nums:
     sum += x
     max_sum = max(max_sum, sum)
     if sum < 0: sum = 0
3) Return max_sum
*/
int maxSubArray3(vector<int> nums)
{
    int n = nums.size();
    int max_sum = INT_MIN;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
        max_sum = max(max_sum, sum);
        if (sum < 0)
        {
            sum = 0;
        }
    }
    return max_sum;
}

/*
Approach 4: Kadane’s Algorithm with Subarray Retrieval (O(n))

Idea:
- Track current window start, and when sum becomes better than max_sum, record bestStart/bestEnd.
- Reset sum and move tentative start when sum < 0.

Algorithm:
1) max_sum = -inf, sum = 0
   start = -1, end = -1, tempStart = 0
2) For i in [0..n-1]:
     sum += nums[i]
     if sum > max_sum: max_sum = sum, start = tempStart, end = i
     if sum < 0: sum = 0, tempStart = i+1
3) Return nums[start..end]
Note:
- Handles all-negative arrays correctly as max_sum starts at -inf and we update before reset.
*/
vector<int> SubArray(vector<int> nums)
{
    int n = nums.size();
    int max_sum = INT_MIN;
    int sum = 0;
    int start = -1;
    int end = -1;
    int tempStart = 0;

    for (int i = 0; i < n; i++)
    {
        sum += nums[i];
        if (max_sum < sum)
        {
            max_sum = sum;
            start = tempStart;
            end = i;
        }
        if (sum < 0)
        {
            sum = 0;
            tempStart = i + 1;
        }
    }
    // In degenerate case where all negatives and start could remain -1 (unlikely here),
    // the loop above still sets start/end when sum surpasses max_sum before reset.
    return vector<int>(nums.begin() + start, nums.begin() + end + 1);
}

int main()
{
    vector<int> nums = {-2, 1, -3, 4, -1, -2, 1, 5, -5, 4};

    int result = maxSubArray3(nums);
    cout << "Maximum Subarray Sum: " << result << endl;

    vector<int> subArray = SubArray(nums);
    cout << "Subarray: ";
    for (int i = 0; i < (int)subArray.size(); i++)
    {
        cout << subArray[i] << " ";
    }
    return 0;
}
