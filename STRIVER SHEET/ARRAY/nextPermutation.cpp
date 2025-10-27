#include<bits/stdc++.h>
using namespace std;

/*
Problem: Next Permutation

Problem Statement:
Given an array of integers nums representing a permutation, transform it into the next lexicographically greater permutation. If no such permutation exists (i.e., the array is in descending order), rearrange it into the lowest possible order (ascending). The transformation must be done in-place.

Example:
Input:
  nums = [1, 2, 3, 4, 5]
Output:
  [1, 2, 3, 5, 4]
Explanation:
- The next lexicographic permutation after [1,2,3,4,5] is [1,2,3,5,4].

Approach:
- Standard Next Permutation Algorithm:
  1) Scan from right to left to find the first index i where nums[i] < nums[i+1] (the pivot).
  2) If such i exists, scan from the right to find the first index j where nums[j] > nums[i], then swap nums[i] and nums[j].
  3) Reverse the suffix starting at i+1 to the end to get the minimal arrangement for that suffix.
  4) If no pivot is found (array in non-increasing order), reversing the entire array yields the smallest permutation.

Algorithm:
1) i = n-2; while i>=0 and nums[i] >= nums[i+1]: i--
2) If i>=0:
     - j = n-1; while nums[j] <= nums[i]: j--
     - swap(nums[i], nums[j])
3) reverse(nums.begin()+i+1, nums.end())

Time Complexity:
- O(n) for a single pass plus reverse.

Space Complexity:
- O(1) in-place.
*/
void nextPermutation(vector<int> &nums){
    int n = nums.size();
    int i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }
    if (i >= 0) {
        int j = n - 1;
        while (j >= 0 && nums[j] <= nums[i]) {
            j--;
        }
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    nextPermutation(nums);
    for (int i=0; i<nums.size(); i++) {
        cout << nums[i] << " ";
    }
    return 0;
}
