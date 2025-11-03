#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Kth Largest Element in a Stream
 Problem Link: https://leetcode.com/problems/kth-largest-element-in-a-stream/

 Problem Statement:
 -----------------
 Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, 
 not the kth distinct element.

 Example:
 int k = 3;
 vector<int> nums = [4, 5, 8, 2];
 
 KthLargest kthLargest(k, nums);
 kthLargest.add(3);   // returns 4
 kthLargest.add(5);   // returns 5
 kthLargest.add(10);  // returns 5
 kthLargest.add(9);   // returns 8
 kthLargest.add(4);   // returns 8

 Constraints:
 - 1 <= k <= 10^4
 - 0 <= nums.length <= 10^4
 - -10^4 <= val <= 10^4
 - At most 10^4 calls will be made to add.
====================================================
*/

class KthLargest {
    priority_queue<int, vector<int>, greater<int>> pq; // min-heap
    int k;
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        // Add elements to min-heap
        for(int x : nums) {
            pq.push(x);
            if(pq.size() > k) pq.pop(); // Keep size of heap <= k
        }
    }

    int add(int val) {
        pq.push(val);
        if(pq.size() > k) pq.pop(); // Remove smallest if heap exceeds size k
        return pq.top();
    }
};

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Kth Largest Element in a Stream ===\n";

    int k = 3;
    vector<int> nums = {4, 5, 8, 2};
    KthLargest kthLargest(k, nums);

    cout << kthLargest.add(3) << "\n";  // returns 4
    cout << kthLargest.add(5) << "\n";  // returns 5
    cout << kthLargest.add(10) << "\n"; // returns 5
    cout << kthLargest.add(9) << "\n";  // returns 8
    cout << kthLargest.add(4) << "\n";  // returns 8

    return 0;
}

/*
✅ Approach Overview:
- Uses a min-heap (priority_queue) of size k to track k largest elements efficiently.
- Adding element: O(log k) time.
- Space complexity O(k).
- Simple and efficient for stream-based k largest element queries.
*/
