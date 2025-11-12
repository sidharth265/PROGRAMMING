#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Sum of Subarray Ranges
Problem Link: LeetCode #2104 (https://leetcode.com/problems/sum-of-subarray-ranges/)

Problem Statement:
You are given an integer array `nums`. The range of a subarray of `nums` 
is the difference between the maximum and minimum elements in the subarray.

Return the sum of all subarray ranges of `nums`.

------------------------------------------------------------
Example 1:
Input:  nums = [1,2,3]
Output: 4
Explanation:
Subarrays [1], [2], [3] → ranges = 0,0,0
[1,2] → 2-1=1
[2,3] → 3-2=1
[1,2,3] → 3-1=2
Total = 4

Example 2:
Input:  nums = [1,3,3]
Output: 4

Example 3:
Input:  nums = [4,-2,-3,4,1]
Output: 59
------------------------------------------------------------

Constraints:
- 1 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Brute Force Enumeration (O(n^2))
==================================================================
💡 Idea:
- Generate all possible subarrays.
- For each subarray, compute min and max, add their difference.

🧩 Algorithm:
1. Iterate over all subarray start `i`.
2. For each end `j`, track min and max.
3. Add (max-min) to sum.

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(1)
*/

long long subarrayRangesBrute(vector<int>& arr) {
    int n = arr.size();
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int mn = arr[i], mx = arr[i];
        for (int j = i+1; j < n; j++) {
            mn = min(mn, arr[j]);
            mx = max(mx, arr[j]);
            ans += (mx - mn);
        }
    }
    return ans;
}

/*
==================================================================
Approach 2: Contribution via Next/Prev Smaller & Greater (Better)
==================================================================
💡 Idea:
- The total sum of ranges = sum of contributions as max - min.
- So: result = sum of contributions of each element as "maximum"
     − sum of contributions of each element as "minimum".
- Like subarray minimums/maximums problem.

🧩 Algorithm:
1. Use monotone stacks to find:
   - prevSmaller[i], nextSmaller[i]
   - prevGreater[i], nextGreater[i]
2. Count subarrays where nums[i] is min: 
   (i−prevSmaller[i]) * (nextSmaller[i]−i).
3. Count subarrays where nums[i] is max: 
   (i−prevGreater[i]) * (nextGreater[i]−i).
4. Contribution = nums[i] * (maxCount−minCount).
5. Sum all contributions.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

long long subarrayRangesBetter(vector<int>& nums) {
    int n = nums.size();
    vector<int> prevSmaller(n, -1), nextSmaller(n, n);
    vector<int> prevGreater(n, -1), nextGreater(n, n);
    stack<int> st;

    // Previous Smaller
    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] > nums[i]) st.pop();
        if (!st.empty()) prevSmaller[i] = st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();

    // Next Smaller
    for (int i = n-1; i >= 0; i--) {
        while (!st.empty() && nums[st.top()] >= nums[i]) st.pop();
        if (!st.empty()) nextSmaller[i] = st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();

    // Previous Greater
    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] < nums[i]) st.pop();
        if (!st.empty()) prevGreater[i] = st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();

    // Next Greater
    for (int i = n-1; i >= 0; i--) {
        while (!st.empty() && nums[st.top()] <= nums[i]) st.pop();
        if (!st.empty()) nextGreater[i] = st.top();
        st.push(i);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long maxCount = 1LL * (i - prevGreater[i]) * (nextGreater[i] - i);
        long long minCount = 1LL * (i - prevSmaller[i]) * (nextSmaller[i] - i);
        ans += 1LL * nums[i] * (maxCount - minCount);
    }
    return ans;
}

/*
==================================================================
Approach 3: Unified Stack Passes (Optimal)
==================================================================
💡 Idea:
- Use two stack‑passes for maximums and minimums separately.
- Accumulate contribution directly: 
   - First pass: add maxima contributions.
   - Second pass: subtract minima contributions.

🧩 Algorithm:
1. Process nums with monotonic decreasing stack for maxima contributions.
2. Process nums with monotonic increasing stack for minima contributions.
3. Total sum = contribution(max) − contribution(min).

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

long long subarrayRangesOptimal(vector<int>& nums) {
    int n = nums.size();
    long long res = 0;
    stack<int> st;

    // Max contributions
    for (int i = 0; i <= n; i++) {
        while (!st.empty() && (i == n || nums[st.top()] < nums[i])) {
            int mid = st.top(); st.pop();
            int left = st.empty() ? -1 : st.top();
            res += 1LL * nums[mid] * (mid - left) * (i - mid);
        }
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // Min contributions
    for (int i = 0; i <= n; i++) {
        while (!st.empty() && (i == n || nums[st.top()] > nums[i])) {
            int mid = st.top(); st.pop();
            int left = st.empty() ? -1 : st.top();
            res -= 1LL * nums[mid] * (mid - left) * (i - mid);
        }
        st.push(i);
    }
    return res;
}

/*
==================================================================
main() function
==================================================================
*/
int main() {
    vector<vector<int>> testCases = {
        {1,2,3},          // Expected: 4
        {1,3,3},          // Expected: 4
        {4,-2,-3,4,1}     // Expected: 59
    };

    for (auto nums : testCases) {
        cout << "Array: ";
        for (int x : nums) cout << x << " ";
        cout << endl;
        cout << "Brute Force: " << subarrayRangesBrute(nums) << endl;
        cout << "Better (Contribution w. Stacks): " << subarrayRangesBetter(nums) << endl;
        cout << "Optimal (Unified Stacks): " << subarrayRangesOptimal(nums) << endl;
        cout << "----------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Brute Force:
   - O(n^2), works only for small n.

2. Better (4 monotone stacks):
   - Compute prev/next smaller and greater.
   - Each element contribution = value * (maxCount - minCount).
   - O(n), O(n).

3. Optimal (2 monotone stack passes):
   - One pass for maxima contributions.
   - One pass for minima contributions.
   - Cleaner and faster.
   - O(n), O(n).

👉 Final Suggestion: Use **Optimal Unified Monotone Stack approach** in interviews.
==================================================================
*/
