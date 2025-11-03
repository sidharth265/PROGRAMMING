#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Kth Smallest Element in an Array
 GeeksForGeeks Link: https://www.geeksforgeeks.org/kth-smallest-largest-element-in-unsorted-array/

 Problem Statement:
 -----------------
 Given an array arr[] of N distinct elements and a number K, 
 where K is smaller than the size of the array. Find the Kth 
 smallest element in the given array.

 Example 1:
 Input: arr[] = [7, 10, 4, 3, 20, 15], K = 3
 Output: 7
 Explanation: The array sorted is [3, 4, 7, 10, 15, 20]. 
 The 3rd smallest element is 7.

 Example 2:
 Input: arr[] = [7, 10, 4, 3, 20, 15], K = 4
 Output: 10
 Explanation: The array sorted is [3, 4, 7, 10, 15, 20]. 
 The 4th smallest element is 10.

 Example 3:
 Input: arr[] = [1, 5, 7, 6, 4, 3, 2], K = 3
 Output: 3
 Explanation: The array sorted is [1, 2, 3, 4, 5, 6, 7]. 
 The 3rd smallest element is 3.

 Constraints:
 - 1 <= K <= arr.length <= 10^5
 - -10^4 <= arr[i] <= 10^4
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Sorting
 -----------------------------------------
 💡 Idea:
 Sort the entire array in ascending order, then return the element at index k-1.

 🧩 Algorithm:
 1. Sort the array in ascending order using built-in sort function.
 2. Return the element at index k-1 (0-based indexing).

 ⏱ Time Complexity: O(N log N) - sorting dominates
 📦 Space Complexity: O(1) - in-place sorting
*/
int kthSmallestSorting(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    return nums[k-1];
}


/* 
==========================================
 Approach 2: Better - Max Heap of Size K
 -----------------------------------------
 💡 Idea:
 Maintain a max-heap of size k. The root will always be the kth smallest element.
 When heap size exceeds k, remove the largest element.

 🧩 Algorithm:
 1. Create a max-heap (priority queue).
 2. For each element in array:
    - Add element to heap
    - If heap size > k, remove the largest element
 3. The root of heap is the kth smallest element.

 ⏱ Time Complexity: O(N log K) - N insertions, each taking log K time
 📦 Space Complexity: O(K) - heap stores at most K elements
*/
int kthSmallestMaxHeap(vector<int>& nums, int k) {
    priority_queue<int> maxHeap; // max-heap by default
    
    for (int num : nums) {
        maxHeap.push(num);
        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
    }
    
    return maxHeap.top();
}


/* 
==========================================
 Approach 3: Optimal - QuickSelect Algorithm
 -----------------------------------------
 💡 Idea:
 Use the partition logic from QuickSort. Instead of sorting entire array,
 we only recurse on the side that contains our target kth smallest element.

 🧩 Algorithm:
 1. Choose a pivot and partition array around it.
 2. If pivot position == k-1, we found our answer.
 3. If pivot position > k-1, search left half.
 4. If pivot position < k-1, search right half.
 5. Repeat until we find the kth smallest.

 ⏱ Time Complexity: O(N) average, O(N²) worst case
 📦 Space Complexity: O(1) - in-place partitioning
*/

// Helper function for partitioning
int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[right];
    int i = left;
    
    for (int j = left; j < right; j++) {
        // For kth smallest, we want smaller elements on the left
        if (nums[j] <= pivot) {
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

int kthSmallestQuickSelect(vector<int>& nums, int k) {
    return quickSelect(nums, 0, nums.size() - 1, k);
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{7, 10, 4, 3, 20, 15}, 3},
        {{7, 10, 4, 3, 20, 15}, 4},
        {{1, 5, 7, 6, 4, 3, 2}, 3},
        {{12, 3, 5, 7, 19}, 2},
        {{1}, 1},
        {{3, 1}, 1},
        {{3, 1}, 2}
    };

    cout << "=== Testing Kth Smallest Element Problem ===\n\n";
    
    for (auto &tc : testCases) {
        vector<int> nums1 = tc.first, nums2 = tc.first, nums3 = tc.first;
        int k = tc.second;
        
        cout << "Input: nums = [";
        for (int i = 0; i < nums1.size(); i++) {
            cout << nums1[i];
            if (i < nums1.size() - 1) cout << ",";
        }
        cout << "], k = " << k << "\n";
        
        int ans1 = kthSmallestSorting(nums1, k);
        int ans2 = kthSmallestMaxHeap(nums2, k);
        int ans3 = kthSmallestQuickSelect(nums3, k);
        
        cout << " Sorting:          " << ans1 << "\n";
        cout << " Max Heap:         " << ans2 << "\n";
        cout << " QuickSelect:      " << ans3 << "\n";
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Sorting -> O(N log N) time, simple but not optimal for this specific problem.\n";
    cout << "2. Max Heap -> O(N log K) time, great when K is small compared to N.\n";
    cout << "3. QuickSelect -> O(N) average time, optimal solution used in interviews.\n";
    cout << "\nRecommendation: Use MaxHeap for small K, QuickSelect for general case.\n";
    cout << "Key Difference from Kth Largest: Use MaxHeap instead of MinHeap to track smallest elements!\n";

    return 0;
}
