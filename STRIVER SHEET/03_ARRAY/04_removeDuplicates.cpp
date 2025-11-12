#include<bits/stdc++.h>
using namespace std;

/*
Problem: Remove Duplicates from Array (Sorted and Unsorted Variants)

Problem Statement:
- Given an integer array:
  1) If the array is sorted non-decreasingly, remove duplicates in-place so that each unique element appears once and return the new length k. The first k elements of nums should hold the unique values in order.
  2) If the array is unsorted, remove duplicates and return the new length. Order is not guaranteed unless explicitly maintained with an ordered structure.

Example:
Input:
  nums(sorted) = [1, 2, 3, 4, 5, 5, 6, 7, 8, 8]
Output:
  k = 8, nums = [1,2,3,4,5,6,7,8, ...]
Explanation:
- Unique elements compacted to the front; elements beyond k can be ignored.

Approach Overview:
- Sorted Array (Two-pointer write-in-place): Track last written unique value and write forward when a new value is found.
- Unsorted Array (Hashing to filter uniques): Use a hash set/map to deduplicate, then write back unique keys.

Complexity Overview:
- Sorted in-place: Time O(n), Space O(1).
- Unsorted hashing: Time O(n), Space O(n).
*/

/*
Approach 1: Sorted Array — Two-Pointer In-Place

Idea:
- Since nums is sorted, duplicates are adjacent.
- Keep a write index k and the last unique value. When nums[i] > last, write it at nums[k] and advance k.

Algorithm:
1) If n==0: return 0
2) k=1, last=nums[0]
3) For i in [1..n-1]:
     if nums[i] > last:
        last = nums[i]
        nums[k++] = last
4) Return k

Time Complexity: O(n)
Space Complexity: O(1)
Notes:
- Start loop at i=1 to avoid re-reading the first element.
*/
int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    int k = 1;
    int last = nums[0];
    for (int i = 1; i < n; i++) {
        if (nums[i] > last) {
            last = nums[i];
            nums[k] = last;
            k++;
        }
    }
    return k;
}

/*
Approach 2: Unsorted Array — Hashing

Idea:
- Insert all elements into an unordered_set/map to deduplicate.
- Write unique elements back into nums. Order is arbitrary when iterating a hash container.

Algorithm:
1) Build unordered_set<int> seen from nums.
2) Write back each value from seen into nums[k++].
3) Return k.

Time Complexity: O(n) average
Space Complexity: O(n)
Note:
- If stable order is desired for unsorted input, use an ordered approach:
  - Keep an unordered_set for membership and build a separate output vector by scanning nums and inserting unseen values in encounter order.
*/
int removeDuplicates2(vector<int>& nums) {
    unordered_set<int> seen(nums.begin(), nums.end());
    int k = 0;
    for (int x : seen) {
        nums[k++] = x;
    }
    return k;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 5, 6, 7, 8, 8};
    int newLength = removeDuplicates(nums);
    cout << "New length of the array after removing duplicates (sorted): " << newLength << "\n";
    cout << "Array after removing duplicates (sorted): ";
    for (int i = 0; i < newLength; i++) cout << nums[i] << " ";
    cout << "\n";

    vector<int> nums2 = {1, 2, 3, 4, 5, 5, 6, 7, 8, 8};
    int newLength2 = removeDuplicates2(nums2);
    cout << "New length of the array after removing duplicates (unsorted hashing): " << newLength2 << "\n";
    cout << "Array after removing duplicates (unsorted hashing): ";
    for (int i = 0; i < newLength2; i++) cout << nums2[i] << " ";
    cout << "\n";

    return 0;
}
