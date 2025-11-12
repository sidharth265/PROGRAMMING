#include<bits/stdc++.h>
using namespace std;

/*
Problem: Merge Sorted Array (In-place merge into nums1)

Problem Statement:
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
- nums1 has length m+n, with the first m elements initialized.
- nums2 has length n, with all n elements initialized.
- After merging, nums1 should contain the sorted result.

Example:
Input:
  nums1 = [1, 2, 3, 0, 0, 0], m = 3
  nums2 = [2, 5, 6], n = 3
Output:
  [1, 2, 2, 3, 5, 6]

Approach Overview:
- Brute Force: Concatenate first m of nums1 with nums2, sort, and copy back.
- Better (Merge with temp copy of nums1): Standard two-way merge using extra O(m) space.
- Optimized (In-place from the end): Use three pointers from the back to avoid extra space.

Complexity Overview:
- Brute Force: Time O((m+n) log(m+n)), Space O(m+n).
- Better Merge: Time O(m+n), Space O(m).
- Optimized In-place: Time O(m+n), Space O(1).
*/

/*
Approach 1: Brute Force

Idea:
- Copy first m of nums1 and all of nums2 into a temp vector, sort it, then write back.

Algorithm:
1) Create nums1Temp size m+n.
2) Copy nums1[0..m-1] and nums2[0..n-1] into nums1Temp.
3) Sort nums1Temp.
4) Copy back to nums1.

Time Complexity: O((m+n) log(m+n))
Space Complexity: O(m+n)
*/
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> nums1Temp(m+n);
    for (int i=0; i<m; i++) nums1Temp[i] = nums1[i];
    for (int i=0; i<n; i++) nums1Temp[m+i] = nums2[i];
    sort(nums1Temp.begin(), nums1Temp.end());
    for (int i=0; i<m+n; i++) nums1[i] = nums1Temp[i];
}

/*
Approach 2: Better Merge with Temporary Copy of nums1

Idea:
- Copy the first m elements of nums1 into a temp array, then merge it with nums2 into nums1 using three pointers.

Algorithm:
1) Copy nums1[0..m-1] into nums1Temp size m.
2) Use pointers i (nums1Temp), j (nums2), k (nums1) to merge:
   - Compare nums1Temp[i] and nums2[j], place smaller into nums1[k++].
3) Copy remaining elements.

Time Complexity: O(m+n)
Space Complexity: O(m)
*/
void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    vector<int> nums1Temp(m);
    for (int i=0; i<m; i++) nums1Temp[i] = nums1[i];
    int i = 0, j = 0, k = 0;
    while (i<m && j<n) {
        if (nums1Temp[i] > nums2[j]) nums1[k++] = nums2[j++];
        else nums1[k++] = nums1Temp[i++];
    }
    while (i<m) nums1[k++] = nums1Temp[i++];
    while (j<n) nums1[k++] = nums2[j++];
}

/*
Approach 3: Optimized In-place Merge from the End (Recommended)

Idea:
- Since nums1 has trailing space, fill from the back using three indices:
  i = m-1 (last valid in nums1), j = n-1 (last in nums2), k = m+n-1 (fill position).
- Place the larger of nums1[i] and nums2[j] at nums1[k], then decrement pointers.

Algorithm:
1) i = m-1, j = n-1, k = m+n-1
2) While i>=0 and j>=0:
     - If nums1[i] > nums2[j]: nums1[k--] = nums1[i--]
     - Else: nums1[k--] = nums2[j--]
3) While j>=0: nums1[k--] = nums2[j--]  // if any remain in nums2
4) Done (remaining nums1 are already in place)

Time Complexity: O(m+n)
Space Complexity: O(1)
*/
void merge3(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m-1, j = n-1, k = m+n-1;
    while (i>=0 && j>=0) {
        if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
    while (j>=0) nums1[k--] = nums2[j--];
}

// Test the function
int main() {
    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};
    int m = 3;
    int n = 3;
    
    // Choose approach to run:
    // merge(nums1, m, nums2, n);   // Brute Force
    // merge2(nums1, m, nums2, n);  // Better Merge
    merge3(nums1, m, nums2, n);     // Optimized In-place

    for (int i=0; i<m+n; i++) cout << nums1[i] << " ";
    cout << "\n";
    return 0;
}
