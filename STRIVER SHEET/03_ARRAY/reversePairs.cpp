#include<bits/stdc++.h>
using namespace std;

/*
Problem: Reverse Pairs (Count pairs (i, j) with i < j and nums[i] > 2*nums[j])

Problem Statement:
Given an integer array nums, return the number of reverse pairs, where a reverse pair is a pair of indices (i, j) such that i < j and nums[i] > 2*nums[j].

Example:
Input:
  nums = [1, 3, 2, 3, 1]
Output:
  2
Explanation:
- Reverse pairs at (i, j): (1,4) -> 3 > 2*1 and (3,4) -> 3 > 2*1.

Approach Overview:
- Brute Force: Check all pairs (i, j) with i<j and count when nums[i] > 2*nums[j].
- Optimized (Merge Sort Counting): During merge sort, count cross pairs where left[i] > 2*right[j] using two pointers, then merge the halves.

Complexity Overview:
- Brute Force: Time O(n^2), Space O(1).
- Merge Sort Count: Time O(n log n), Space O(n).
*/

/*
Approach 1: Brute Force

Idea:
- Double loop over all pairs (i, j) with i<j and test the inequality.

Algorithm:
1) count = 0
2) For i from 0..n-1:
     For j from i+1..n-1:
        if nums[i] > 2*nums[j]: count++
3) Return count

Time Complexity: O(n^2)
Space Complexity: O(1)
Note:
- Use integer-safe comparison; avoid float division. Compare as (long long)nums[i] > 2LL*nums[j].
*/
int reversePairs(vector<int>& nums) {
    int count = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((long long)nums[i] > 2LL * nums[j]) count++;
        }
    }
    return count;
}

/*
Approach 2: Optimized using Merge Sort with Counting

Idea:
- Sort array via merge sort.
- Before merging two sorted halves [low..mid] and [mid+1..high], count how many pairs satisfy left[i] > 2*right[j].
  Because both halves are sorted, use a pointer j over the right half for each i in left half to count how many right elements work.

Algorithm:
1) Recursively sort left and right halves.
2) Count cross reverse pairs:
   - For i in left:
       while j in right and left[i] > 2*right[j]: j++
       add j (relative to right half start) to count
3) Merge the two halves into the original array.
4) Sum counts from all levels and return.

Time Complexity: O(n log n)
Space Complexity: O(n) for temporary arrays
*/
void mergeAndCount(vector<int> &nums, int low, int mid, int high, long long &count) {
    vector<int> left(nums.begin()+low, nums.begin()+mid+1);
    vector<int> right(nums.begin()+mid+1, nums.begin()+high+1);
    int n1 = (int)left.size(), n2 = (int)right.size();

    // Count reverse pairs across halves
    int j = 0;
    for (int i = 0; i < n1; i++) {
        while (j < n2 && (long long)left[i] > 2LL * right[j]) j++;
        count += j;
    }

    // Standard merge
    int i = 0; j = 0; int k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) nums[k++] = left[i++];
        else nums[k++] = right[j++];
    }
    while (i < n1) nums[k++] = left[i++];
    while (j < n2) nums[k++] = right[j++];
}

void ms(vector<int> &nums, int low, int high, long long &count) {
    if (low >= high) return;
    int mid = low + (high - low)/2;
    ms(nums, low, mid, count);
    ms(nums, mid+1, high, count);
    mergeAndCount(nums, low, mid, high, count);
}

int reversePairs2(vector<int>& nums) {
    int n = nums.size();
    long long count = 0;
    ms(nums, 0, n-1, count);
    return (int)count;
}

// Example usage:
int main() {
    vector<int> nums = {1, 3, 2, 3, 1};
    cout << "Brute Force Approach: " << reversePairs(nums) << "\n";
    cout << "Optimized Approach: " << reversePairs2(nums) << "\n";
    return 0;
}
