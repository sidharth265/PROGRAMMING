#include<bits/stdc++.h>
using namespace std;

/*
Problem: Max Consecutive Ones

Problem Statement:
Given a binary array nums (containing only 0s and 1s), find the maximum number of consecutive 1s in the array.

Example:
Input:
  nums = [1, 1, 0, 1, 1, 1]
Output:
  3
Explanation:
- The longest run of consecutive 1s is the last three elements.

Approach:
- Single pass counter:
  - Maintain a running count of consecutive 1s.
  - Reset the running count to 0 when a 0 is encountered.
  - Track the maximum count seen so far.

Algorithm:
1) Initialize max_count = 0, count = 0.
2) For each element x in nums:
   - If x == 1: count++
   - Else: max_count = max(max_count, count); count = 0
3) Return max(max_count, count) to account for a trailing run of 1s.

Time Complexity:
- O(n), single pass over the array.

Space Complexity:
- O(1), constant extra space.
*/
int findMaxConsecutiveOnes(vector<int>& nums) {
    int n = nums.size();
    int max_count = 0;
    int count = 0;
    for(int i=0; i<n; i++) {
        if (nums[i] == 1) {
            count++;
        }
        else{
            max_count = max(max_count, count);
            count = 0;
        }
    }
    return max(max_count, count);
}

int main() {
    vector<int> nums = {1, 1, 0, 1, 1, 1};
    cout << "Maximum number of consecutive 1's: " << findMaxConsecutiveOnes(nums) << endl;
    return 0;
}
