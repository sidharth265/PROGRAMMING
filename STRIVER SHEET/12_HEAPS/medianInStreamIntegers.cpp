#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Find Median from Data Stream
Problem Link: https://leetcode.com/problems/find-median-from-data-stream

Problem Statement:
The median is the middle value in an ordered integer list. 
If the size of the list is even, the median is the average of the two middle values. 
Design a data structure that supports adding numbers from a data stream and finding the median efficiently.

Example 1:
Input:
addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2

Explanation:
After adding 1 and 2, the median is (1 + 2) / 2 = 1.5.
After adding 3, the median is 2 (middle of [1,2,3]).

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Balanced Two Heaps
   ------------------------------------------------------
   💡 Idea:
   Maintain two heaps:
   - Max-heap for the lower half of numbers.
   - Min-heap for the upper half.
   
   This allows O(log N) insertion and O(1) median retrieval.

   🧩 Algorithm:
   1. When adding a number:
       a. Add it to the max-heap if empty or <= maxHeap top.
       b. Else add to min-heap.
   2. Balance sizes:
       - If maxHeap has more than one element extra, move top to minHeap.
       - If minHeap has more elements, move top to maxHeap.
   3. To find median:
       - If maxHeap has more elements, median is maxHeap top.
       - Else average of maxHeap top and minHeap top.

   ⏱ Time Complexity:
   - addNum(): O(log N)
   - findMedian(): O(1)
   📦 Space Complexity: O(N)
------------------------------------------------------ */
class MedianFinder {
    priority_queue<int> maxHeap;  // lower half
    priority_queue<int, vector<int>, greater<int>> minHeap;  // upper half

public:
    MedianFinder() {
    }
    
    void addNum(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }

        // Balance sizes
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }
};

/* ===================== Main Function ===================== */
int main() {
    MedianFinder mf;
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << "Adding numbers and printing median:\n";

    for (int num : nums) {
        mf.addNum(num);
        cout << "Added " << num << ", current median: " << mf.findMedian() << "\n";
    }

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method              | Time Complexity       | Space Complexity | Notes                  |
       |---------------------|----------------------|------------------|------------------------|
       | Balanced Heaps      | add: O(log N)         | O(N)             | Efficient, standard    |
       |                     | findMedian: O(1)                                      |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
