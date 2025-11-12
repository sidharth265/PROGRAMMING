#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Kth Largest Element in an Array
 LeetCode Link: https://leetcode.com/problems/kth-largest-element-in-an-array/

 Problem Statement:
 -----------------
 Given an integer array `nums` and an integer `k`, return the kth 
 largest element in the array. Note that it is the kth largest 
 element in the sorted order, not the kth distinct element.

 Example 1:
 Input: nums = [3,2,1,5,6,4], k = 2
 Output: 5
 Explanation: The array sorted in descending order is [6,5,4,3,2,1]. 
 The 2nd largest element is 5.

 Example 2:
 Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 Output: 4
 Explanation: The array sorted in descending order is [6,5,5,4,3,3,2,2,1]. 
 The 4th largest element is 4.

 Constraints:
 - 1 <= k <= nums.length <= 10^5
 - -10^4 <= nums[i] <= 10^4
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Sorting
 -----------------------------------------
 💡 Idea:
 Sort the entire array in descending order, then return the element at index k-1.

 🧩 Algorithm:
 1. Sort the array in descending order using built-in sort function.
 2. Return the element at index k-1 (0-based indexing).

 ⏱ Time Complexity: O(N log N) - sorting dominates
 📦 Space Complexity: O(1) - in-place sorting
*/
int kthLargestSorting(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end(), greater<int>());
    return nums[k-1];
}


/* 
==========================================
 Approach 2: Better - Min Heap of Size K
 -----------------------------------------
 💡 Idea:
 Maintain a min-heap of size k. The root will always be the kth largest element.
 When heap size exceeds k, remove the smallest element.

 🧩 Algorithm:
 1. Create a min-heap (priority queue).
 2. For each element in array:
    - Add element to heap
    - If heap size > k, remove the smallest element
 3. The root of heap is the kth largest element.

 ⏱ Time Complexity: O(N log K) - N insertions, each taking log K time
 📦 Space Complexity: O(K) - heap stores at most K elements
*/
int kthLargestMinHeap(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap
    
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    return minHeap.top();
}


/* 
==========================================
 Approach 3: Optimal - QuickSelect Algorithm
 -----------------------------------------
 💡 Idea:
 Use the partition logic from QuickSort. Instead of sorting entire array,
 we only recurse on the side that contains our target kth largest element.

 🧩 Algorithm:
 1. Choose a pivot and partition array around it.
 2. If pivot position == k-1, we found our answer.
 3. If pivot position > k-1, search left half.
 4. If pivot position < k-1, search right half.
 5. Repeat until we find the kth largest.

 ⏱ Time Complexity: O(N) average, O(N²) worst case
 📦 Space Complexity: O(1) - in-place partitioning
*/

// Helper function for partitioning
int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[right];
    int i = left;
    
    for (int j = left; j < right; j++) {
        // For kth largest, we want larger elements on the left
        if (nums[j] >= pivot) {
            swap(nums[i], nums[j]);
            i++;
        }
    }
    swap(nums[i], nums[right]);
    return i;
}

// QuickSelect helper function
int quickSelect(vector<int>& nums, int left, int right, int k) {
    if (left == right) {
        return nums[left];
    }
    
    int pivotIndex = partition(nums, left, right);
    
    if (pivotIndex == k - 1) {
        return nums[pivotIndex];
    } else if (pivotIndex > k - 1) {
        return quickSelect(nums, left, pivotIndex - 1, k);
    } else {
        return quickSelect(nums, pivotIndex + 1, right, k);
    }
}

int kthLargestQuickSelect(vector<int>& nums, int k) {
    return quickSelect(nums, 0, nums.size() - 1, k);
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{3,2,1,5,6,4}, 2},
        {{3,2,3,1,2,4,5,5,6}, 4},
        {{1}, 1},
        {{1,2}, 1},
        {{2,1}, 1},
        {{7,10,4,3,20,15}, 3}
    };

    cout << "=== Testing Kth Largest Element Problem ===\n\n";
    
    for (auto &tc : testCases) {
        vector<int> nums1 = tc.first, nums2 = tc.first, nums3 = tc.first;
        int k = tc.second;
        
        cout << "Input: nums = [";
        for (int i = 0; i < nums1.size(); i++) {
            cout << nums1[i];
            if (i < nums1.size() - 1) cout << ",";
        }
        cout << "], k = " << k << "\n";
        
        int ans1 = kthLargestSorting(nums1, k);
        int ans2 = kthLargestMinHeap(nums2, k);
        int ans3 = kthLargestQuickSelect(nums3, k);
        
        cout << " Sorting:          " << ans1 << "\n";
        cout << " Min Heap:         " << ans2 << "\n";
        cout << " QuickSelect:      " << ans3 << "\n";
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Sorting -> O(N log N) time, simple but not optimal for this specific problem.\n";
    cout << "2. Min Heap -> O(N log K) time, great when K is small compared to N.\n";
    cout << "3. QuickSelect -> O(N) average time, optimal solution used in interviews.\n";
    cout << "\nRecommendation: Use MinHeap for small K, QuickSelect for general case.\n";

    return 0;
}
