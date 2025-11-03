#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Top K Frequent Elements
 Problem Link: https://leetcode.com/problems/top-k-frequent-elements/

 Problem Statement:
 -----------------
 Given an integer array nums and an integer k, return the k most frequent elements. 
 You may return the answer in any order.

 Example:
 Input: nums = [1,1,1,2,2,3], k = 2
 Output: [1,2]

 Constraints:
 - 1 <= nums.length <= 10^5
 - k is in the range [1, the number of unique elements in the array]
 - It is guaranteed that the answer is unique.
====================================================
*/

/* 
==========================================
 Approach 1: Brute Force - Count frequencies and sort
-----------------------------------------
💡 Idea:
Count frequencies using a hashmap, then sort all unique elements by frequency.

🧩 Algorithm:
1. Use an unordered_map to count frequencies.
2. Copy to a vector or use multimap to sort by frequency descending.
3. Pick top k elements.

⏱ Time Complexity: O(N log N)
📦 Space Complexity: O(N)
*/
vector<int> topKFrequentBrute(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
  
    // vector of pairs (num, freq)
    vector<pair<int, int>> freqVec(freq.begin(), freq.end());
    sort(freqVec.begin(), freqVec.end(), [](auto& a, auto& b) {
        return a.second > b.second; // descending freq
    });

    vector<int> result;
    for (int i = 0; i < k; i++) {
        result.push_back(freqVec[i].first);
    }
    return result;
}

/* 
==========================================
 Approach 2: Better - Min-Heap of Size k (Priority Queue)
-----------------------------------------
💡 Idea:
Count frequencies with hashmap, then use a min-heap (priority_queue) to keep track of top k frequencies.

🧩 Algorithm:
1. Count frequencies using hashmap.
2. Push pairs (frequency, number) in a min-heap.
3. Maintain heap size at most k by popping smallest frequency.
4. Extract k elements from the heap.

⏱ Time Complexity: O(N log k)
📦 Space Complexity: O(N)
*/
vector<int> topKFrequentBetter(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (auto& it : freq) {
        pq.push({it.second, it.first});
        if ((int)pq.size() > k) pq.pop();
    }

    vector<int> result;
    while (!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }
    reverse(result.begin(), result.end()); // optional, for descending order
    return result;
}

/* 
==========================================
 Approach 3: Optimal - Bucket Sort
-----------------------------------------
💡 Idea:
Count frequencies, then use buckets where index is frequency.
Traverse buckets from high to low frequency to get top k elements in linear time.

🧩 Algorithm:
1. Count frequencies using hashmap.
2. Create vector of buckets, size = max frequency + 1.
3. Place numbers in bucket according to their frequency.
4. Traverse buckets from high to low, collecting k elements.

⏱ Time Complexity: O(N)
📦 Space Complexity: O(N)
*/
vector<int> topKFrequentOptimal(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
  
    int n = (int)nums.size();
    vector<vector<int>> buckets(n+1);
    for (auto& it : freq) {
        buckets[it.second].push_back(it.first);
    }

    vector<int> result;
    for (int i = n; i >= 0 && (int)result.size() < k; i--) {
        for (int num : buckets[i]) {
            result.push_back(num);
            if ((int)result.size() == k) break;
        }
    }
    return result;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Top K Frequent Elements ===\n\n";

    vector<int> nums = {1,1,1,2,2,3};
    int k = 2;

    vector<int> res1 = topKFrequentBrute(nums, k);
    cout << "Brute Force Result: ";
    for (int v : res1) cout << v << " ";
    cout << "\n";

    vector<int> res2 = topKFrequentBetter(nums, k);
    cout << "Better (Min-Heap) Result: ";
    for (int v : res2) cout << v << " ";
    cout << "\n";

    vector<int> res3 = topKFrequentOptimal(nums, k);
    cout << "Optimal (Bucket Sort) Result: ";
    for (int v : res3) cout << v << " ";
    cout << "\n";

    return 0;
}

/*
✅ Approach Overview:
- Brute: Count + Sort, simplest but O(N log N).
- Better: Count + Min-Heap, more efficient O(N log k).
- Optimal: Count + Bucket Sort, linear O(N), best for large inputs.
*/
