#include<bits/stdc++.h>
using namespace std;

/*
Problem: Majority Element (> n/2 frequency)

Problem Statement:
Given an integer array nums of size n, find the element that appears more than n/2 times (the majority element). It is guaranteed that a majority element exists in the typical problem setting; if not guaranteed, a fallback approach may return -1 when none exceeds n/2.

Example:
Input:
  nums = [2, 2, 1, 1, 1, 2, 2]
Output:
  2
Explanation:
- The value 2 appears 4 times out of 7 (> 7/2), so it is the majority element.

Approach Overview:
- Hash Map Counting: Count frequencies of all values and return the one with count > n/2.
- Boyer–Moore Voting Algorithm: Track a candidate and a counter in one pass, O(1) space.

Complexity Overview:
- Hash Map: Time O(n), Space O(n).
- Boyer–Moore: Time O(n), Space O(1).
*/

/*
Approach 1: Hash Map Counting

Idea:
- Count occurrences of each number; return the one with frequency > n/2.
- If no majority exists (problem variant), return -1.

Algorithm:
1) Create an unordered_map<int,int> cnt.
2) For each x in nums: cnt[x]++.
3) Scan cnt: if any count > n/2, return its key.
4) Otherwise, return -1.

Time Complexity: O(n)
Space Complexity: O(n)
*/
int majorityElement2(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int, int> m;
    for (int i=0; i<n; i++) {
        m[nums[i]]++;
    }
    for (auto it : m) {
        if (it.second > (n/2)) {
            return it.first;
        }
    }
    return -1;
}

/*
Approach 2: Boyer–Moore Voting Algorithm (Recommended)

Idea:
- Maintain a candidate and a counter.
- If the counter is 0, set the current element as candidate.
- Increment counter if current equals candidate; otherwise decrement.
- With a guaranteed majority, the final candidate is the answer.
- If not guaranteed, optionally verify the candidate by counting occurrences.

Algorithm:
1) count = 0
2) For each num in nums:
     - if count == 0: candidate = num
     - count += (num == candidate) ? 1 : -1
3) return candidate  // if majority is guaranteed; otherwise, verify occurrence > n/2

Time Complexity: O(n)
Space Complexity: O(1)
*/
int majorityElement(vector<int>& nums) {
    int count = 0, candidate = 0;
    for (int num : nums) {
        if (count == 0) {
            candidate = num;
        }
        count += (num == candidate) ? 1 : -1;
    }
    return candidate;
}

int main() {
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
    cout << "Majority Element (Boyer-Moore): " << majorityElement(nums) << endl;
    cout << "Majority Element (HashMap): " << majorityElement2(nums) << endl;
    return 0;
}
