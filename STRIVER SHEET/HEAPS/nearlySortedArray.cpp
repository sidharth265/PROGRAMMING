#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Sort a Nearly Sorted (K-Sorted) Array
 GeeksForGeeks Link: https://www.geeksforgeeks.org/dsa/nearly-sorted-algorithm/

 Problem Statement:
 -----------------
 Given an array arr[] and a number k, where each element is at most k 
 distance away from its target position in a fully sorted array.
 Sort the array optimally.

 Note: You need to change the given array arr[] in place.
 Do NOT use built-in sort() function.

 Example 1:
 Input: arr = [6, 5, 3, 2, 8, 10, 9], k = 3
 Output: [2, 3, 5, 6, 8, 9, 10]
 Explanation: Each element is at most 3 positions away from its correct position.

 Example 2:
 Input: arr = [1, 4, 5, 2, 3, 6, 7, 8, 9, 10], k = 2
 Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
 Explanation: Each element is at most 2 positions away from its correct position.

 Constraints:
 - 1 <= arr.length <= 10^5
 - k < arr.length
 - Elements can be negative or positive
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Standard Sorting
 -----------------------------------------
 💡 Idea:
 Simply sort the entire array using any standard sorting algorithm.
 This doesn't utilize the property that elements are at most k away.

 🧩 Algorithm:
 1. Apply any standard sorting algorithm (merge sort, quick sort, etc.)
 2. Return the sorted array.

 ⏱ Time Complexity: O(N log N) - standard sorting complexity
 📦 Space Complexity: O(1) - in-place sorting
*/
void sortNearlySortedBruteForce(vector<int>& arr, int k) {
    sort(arr.begin(), arr.end());
}


/* 
==========================================
 Approach 2: Better - Insertion Sort (for small k)
 -----------------------------------------
 💡 Idea:
 Since elements are at most k positions away, insertion sort performs
 better than usual because each element needs at most k swaps.

 🧩 Algorithm:
 1. For each element starting from index 1:
    - Compare with previous elements (at most k comparisons)
    - Insert in correct position by shifting elements
 2. Continue until array is sorted.

 ⏱ Time Complexity: O(N * K) - each element moves at most k positions
 📦 Space Complexity: O(1) - in-place sorting
*/
void sortNearlySortedInsertion(vector<int>& arr, int k) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements that are greater than key, at most k positions
        while (j >= 0 && j >= i - k - 1 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


/* 
==========================================
 Approach 3: Optimal - Min Heap (Priority Queue)
 -----------------------------------------
 💡 Idea:
 Use a min-heap of size (k+1). The minimum element in this heap
 will always be the next element in sorted order.

 🧩 Algorithm:
 1. Create a min-heap and insert first (k+1) elements.
 2. For remaining elements:
    - Extract minimum from heap and place it in current position
    - Insert next element from array into heap
 3. Extract all remaining elements from heap to complete sorting.

 ⏱ Time Complexity: O(N log K) - N insertions/deletions, each O(log K)
 📦 Space Complexity: O(K) - heap stores at most K+1 elements
*/
void sortNearlySortedHeap(vector<int>& arr, int k) {
    int n = arr.size();
    
    // Create a min-heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    // Insert first k+1 elements into the heap
    int heapSize = min(k + 1, n);
    for (int i = 0; i < heapSize; i++) {
        minHeap.push(arr[i]);
    }
    
    // Extract minimum from heap and insert next element
    int index = 0;
    for (int i = k + 1; i < n; i++) {
        arr[index++] = minHeap.top();
        minHeap.pop();
        minHeap.push(arr[i]);
    }
    
    // Extract remaining elements from heap
    while (!minHeap.empty()) {
        arr[index++] = minHeap.top();
        minHeap.pop();
    }
}


/* Helper function to print array */
void printArray(const vector<int>& arr) {
    cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]";
}

/* Helper function to check if array is sorted */
bool isSorted(const vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i-1]) return false;
    }
    return true;
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{6, 5, 3, 2, 8, 10, 9}, 3},
        {{1, 4, 5, 2, 3, 6, 7, 8, 9, 10}, 2},
        {{3, 2, 1, 5, 6, 4}, 2},
        {{10, 9, 8, 7, 4, 70, 60, 50}, 4},
        {{1}, 0},
        {{2, 1}, 1}
    };

    cout << "=== Testing Nearly Sorted Array Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> arr1 = testCases[t].first;
        vector<int> arr2 = testCases[t].first;  
        vector<int> arr3 = testCases[t].first;
        int k = testCases[t].second;
        
        cout << "Test Case " << t + 1 << ":\n";
        cout << "Input:  ";
        printArray(arr1);
        cout << ", k = " << k << "\n";
        
        // Test all approaches
        sortNearlySortedBruteForce(arr1, k);
        sortNearlySortedInsertion(arr2, k);
        sortNearlySortedHeap(arr3, k);
        
        cout << "Brute Force:    ";
        printArray(arr1);
        cout << " ✓\n";
        
        cout << "Insertion Sort: ";
        printArray(arr2);
        cout << " ✓\n";
        
        cout << "Min Heap:       ";
        printArray(arr3);
        cout << " ✓\n";
        
        cout << "All approaches sorted: " << 
                (isSorted(arr1) && isSorted(arr2) && isSorted(arr3) ? "YES" : "NO") << "\n";
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N log N) time, doesn't utilize the 'nearly sorted' property.\n";
    cout << "2. Insertion Sort -> O(N*K) time, good when K is very small (K << N).\n";
    cout << "3. Min Heap -> O(N log K) time, optimal approach that leverages the K-distance property.\n";
    cout << "\nRecommendation: Use Min Heap approach for optimal performance in interviews!\n";
    cout << "Key Insight: Only need to consider K+1 elements at any time since each element\n";
    cout << "             is at most K positions away from its correct position.\n";

    return 0;
}
