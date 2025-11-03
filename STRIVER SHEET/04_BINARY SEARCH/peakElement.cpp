#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


// Problem Link: https://leetcode.com/problems/find-peak-element/
// Problem Statement: A peak element in an array is an element which is greater than or equal to its neighbours.
// Given an input array nums, where nums[i] != nums[i+1], find a peak element and return its index.
// A peak element is an element that is greater than or equal to its neighbours.


// Approach: Binary Search
// 1. Check if the first or last element is a peak.
// 2. If the middle element is greater than both its neighbours, return its index.
// 3. If the middle element is less than its left neighbour, search in the left half.
// 4. If the middle element is less than its right neighbour, search in the right half.
// 5. Repeat the process until a peak is found.
// Time Complexity: O(log n)
// Space Complexity: O(1)
int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return 0; // If there is only one element, it is the peak
    if (nums[0] > nums[1]) return 0; // If the first element is greater than the second, it is the peak
    if (nums[n - 1] > nums[n - 2]) return n - 1; // If the last element is greater than the second last, it is the peak

    int left = 1, right = n - 2; // We start searching in the range [1, n-2]
    while (left <= right) {
        int mid = left + (right - left) / 2; // Calculate the middle index
        if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) return mid; // If the middle element is greater than its neighbours, return it
        else if (nums[mid] < nums[mid - 1]) right = mid - 1; // Search in the left half
        else left = mid + 1; // Search in the right half
    }
    return -1; // This line should never be reached
}


// Example usage
int main() {
    vector<int> arr = {1, 2, 3, 1};
    int peakIndex = findPeakElement(arr);
    cout << "Peak element index: " << peakIndex << endl; // Output: Peak element index: 2
    return 0;
}