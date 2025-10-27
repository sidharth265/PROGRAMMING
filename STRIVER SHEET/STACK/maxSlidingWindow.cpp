#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Sliding Window Maximum
 Problem Link: (LeetCode 239 or similar)
====================================================

📝 Problem Statement:
Given an array of integers `nums` and a sliding window size `k`,
return an array of the maximum values in each sliding window moving from left to right.

📌 Input:
- Vector of integers `nums`
- Integer window size `k`

📌 Output:
- Vector of integers representing max of each sliding window

----------------------------------------------------
🔹 Example:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3  
Output: [3,3,5,5,6,7]  

Explanation:
Windows and their max:
[1,3,-1] -> 3  
[3,-1,-3] -> 3  
[-1,-3,5] -> 5  
[-3,5,3] -> 5  
[5,3,6] -> 6  
[3,6,7] -> 7

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Brute Force
//////////////////////////////////////////////////////
/*
💡 Idea:
- For every window, check all k elements to find max.

🧩 Algorithm:
1. For each window starting i, find max in nums[i..i+k-1].
2. Store max in answer array.

⏱ Time Complexity: O(n*k)  
📦 Space Complexity: O(n)
*/

vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    int l = (int)nums.size() - k + 1;
    vector<int> ans(l);
    for (int i = 0; i < l; i++) {
        int maxWindow = nums[i];
        for (int j = i + 1; j < i + k; j++) {
            maxWindow = max(maxWindow, nums[j]);
        }
        ans[i] = maxWindow;
    }
    return ans;
}


//////////////////////////////////////////////////////
// Approach 2: Optimized using Deque
//////////////////////////////////////////////////////
/*
💡 Idea:
- Maintain indices of potential max elements in a deque.
- Ensure elements in deque are in decreasing order.
- Remove indices out of window bounds.
- Front of deque is max for current window.

🧩 Algorithm:
1. Iterate over nums with index i.
2. Remove front idx if it's out of window (i-k).
3. Pop from back while nums[dq.back()] < nums[i].
4. Add current index i at back.
5. Once i >= k-1, record nums[dq.front()] as max.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(k)
*/

vector<int> maxSlidingWindow2(vector<int> &nums, int k) {
    int n = (int)nums.size();
    vector<int> ans;
    deque<int> dq;
    for (int i = 0; i < n; i++) {
        if (!dq.empty() && dq.front() == i - k) 
            dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) 
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) 
            ans.push_back(nums[dq.front()]);
    }
    return ans;
}

//////////////////////////////////////////////////////
// Main function with example test case
//////////////////////////////////////////////////////
int main() {
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    cout << "Optimized Sliding Window Maximum: ";
    vector<int> result = maxSlidingWindow2(nums, k);
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Brute force approach checks each window individually and is inefficient.
// Optimized deque-based method maintains candidate max indices for O(n) overall time.
