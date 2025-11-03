#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Sort Colors (0s, 1s, and 2s)

Problem Statement:
Given an integer array nums consisting only of 0s, 1s, and 2s, sort the array in-place so that all 0s come first, followed by 1s, then 2s.

Example:
Input:
  nums = [2,0,2,1,1,0]
Output:
  [0,0,1,1,2,2]

Approach Overview:
- Approach 1: Counting Sort (Two-pass) — count frequencies of 0,1,2 and overwrite the array accordingly.
- Approach 2: Dutch National Flag (One-pass, in-place) — maintain three regions using low, mid, high pointers.
*/

/*
Approach: Counting Sort (Two-pass)
Approach Idea:
- Count the number of 0s, 1s, and 2s in a single scan.
- Overwrite the array: first c0 zeros, then c1 ones, then c2 twos.

Algorithm:
1) c0=c1=c2=0
2) For each x in nums:
     - if x==0: c0++
     - else if x==1: c1++
     - else: c2++
3) i=0
4) While c0-->0: nums[i++]=0
5) While c1-->0: nums[i++]=1
6) While c2-->0: nums[i++]=2

Time Complexity: O(n)
Space Complexity: O(1)
*/
void sortColors(vector<int>& nums) {
    int c0 = 0, c1 = 0, c2 = 0;
    for (int x : nums) {
        if (x == 0) c0++;
        else if (x == 1) c1++;
        else c2++;
    }
    int i = 0;
    while (c0--) nums[i++] = 0;
    while (c1--) nums[i++] = 1;
    while (c2--) nums[i++] = 2;
}

/*
Approach: Dutch National Flag (Single-pass, in-place)
Approach Idea:
- Partition array into four regions:
  - [0..low-1] -> 0s
  - [low..mid-1] -> 1s
  - [mid..high] -> unknown
  - [high+1..n-1] -> 2s
- Inspect nums[mid]:
  - If 0: swap with nums[low], advance low and mid.
  - If 1: advance mid.
  - If 2: swap with nums[high], decrement high (do not advance mid yet).

Algorithm:
1) low=0, mid=0, high=n-1
2) While mid <= high:
   - if nums[mid]==0: swap(nums[low], nums[mid]); low++; mid++;
   - else if nums[mid]==1: mid++;
   - else: swap(nums[mid], nums[high]); high--;
3) Done

Time Complexity: O(n)
Space Complexity: O(1)
*/
void sortColorsDutchFlag(vector<int>& nums) {
    int n = nums.size();
    int low = 0, mid = 0, high = n - 1;
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low++], nums[mid++]);
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high--]);
        }
    }
}

int main() {
    vector<int> nums = {2,0,2,1,1,0,2,2,0,1,0,0,2,1,2,0,1,0};

    // Choose approach:
    // sortColors(nums);               // Counting Sort
    sortColorsDutchFlag(nums);         // Dutch National Flag

    for (int i = 0; i < (int)nums.size(); i++) {
        cout << nums[i] << " ";
    }
    return 0;
}
