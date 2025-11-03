#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Sum of Subarray Minimums
Problem Link: LeetCode #907 (https://leetcode.com/problems/sum-of-subarray-minimums/)

Problem Statement:
Given an array of integers `arr`, find the sum of `min(b)` where `b` ranges 
over all possible contiguous subarrays of `arr`.

Since the answer may be large, return it modulo (10^9 + 7).

------------------------------------------------------------
Example 1:
Input:  arr = [3,1,2,4]
Output: 17

Explanation:
Subarrays are: 
[3] → min=3
[1] → min=1
[2] → min=2
[4] → min=4
[3,1] → min=1
[1,2] → min=1
[2,4] → min=2
[3,1,2] → min=1
[1,2,4] → min=1
[3,1,2,4] → min=1
Sum = 17

------------------------------------------------------------
Example 2:
Input:  arr = [11,81,94,43,3]
Output: 444
------------------------------------------------------------

Constraints:
- 1 ≤ arr.length ≤ 3 * 10^4
- 1 ≤ arr[i] ≤ 3 * 10^4
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Brute Force (Naive O(n^2))
==================================================================
💡 Idea:
- Enumerate all subarrays.
- Compute minimum for each subarray and add to result.

🧩 Algorithm:
1. Initialize sum = 0.
2. For each i = 0 to n-1:
   - Set minVal = INT_MAX.
   - For each j = i to n-1:
       - minVal = min(minVal, arr[j]).
       - sum += minVal.
3. Return sum % MOD.

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(1)
*/

int sumSubarrayMinsBrute(vector<int>& arr) {
    int n = arr.size();
    long long sum = 0;
    const int MOD = 1e9+7;
    for(int i=0; i<n; i++) {
        int minVal = INT_MAX;
        for(int j=i; j<n; j++) {
            minVal = min(minVal, arr[j]);
            sum = (sum + minVal) % MOD;
        }
    }
    return (int)sum;
}

/*
==================================================================
Approach 2: Monotonic Stack + Contribution (Optimal O(n))
==================================================================
💡 Idea:
- Each element arr[i] can be the minimum in multiple subarrays.  
- Count how many subarrays where arr[i] is the minimum:
  - Find nearest smaller element index to the left (prevSmaller).
  - Find nearest smaller element index to the right (nextSmaller).
- Contribution = arr[i] * (#subarrays to left) * (#subarrays to right).
- Add up contributions.

🧩 Algorithm:
1. Use monotonic stack to compute:
   - prev[i] = index of previous smaller element than arr[i] (or -1).
   - next[i] = index of next smaller element than arr[i] (or n).
2. For each i:
   - leftCount = i - prev[i]
   - rightCount = next[i] - i
   - contribution = arr[i] * leftCount * rightCount
   - add to result % MOD.
3. Return result.

⏱ Time Complexity: O(n) (each index processed once in stack).
📦 Space Complexity: O(n).
*/

const int MOD = 1e9 + 7;

vector<int> prevSmaller(vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for(int i=0; i<n; i++) {
        while(!st.empty() && arr[st.top()] > arr[i]) st.pop();
        if(!st.empty()) ans[i] = st.top();
        st.push(i);
    }
    return ans;
}

vector<int> nextSmaller(vector<int>& arr) {
    int n = arr.size();
    vector<int> ans(n, n);
    stack<int> st;
    for(int i=n-1; i>=0; i--) {
        while(!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        if(!st.empty()) ans[i] = st.top();
        st.push(i);
    }
    return ans;
}

int sumSubarrayMinsOptimal(vector<int>& arr) {
    int n = arr.size();
    vector<int> prev = prevSmaller(arr);
    vector<int> next = nextSmaller(arr);
    long long ans = 0;

    for(int i=0; i<n; i++) {
        long long left = i - prev[i];
        long long right = next[i] - i;
        ans = (ans + (arr[i] * left % MOD) * right % MOD) % MOD;
    }
    return (int)ans;
}

/*
==================================================================
main() function
==================================================================
*/
int main() {
    vector<vector<int>> testCases = {
        {3, 1, 2, 4},      // Expected = 17
        {11, 81, 94, 43, 3} // Expected = 444
    };

    for (auto arr : testCases) {
        cout << "Array: ";
        for (int x : arr) cout << x << " ";
        cout << endl;
        cout << "Brute Force: " << sumSubarrayMinsBrute(arr) << endl;
        cout << "Optimal Monotone Stack: " << sumSubarrayMinsOptimal(arr) << endl;
        cout << "----------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Brute Force:
   - Double loop, compute min for each subarray.
   - Complexity: O(n^2)
   - Good for small arrays only.

2. Monotonic Stack (Contribution Technique):
   - Compute prev smaller and next smaller.
   - Each element’s contribution = value * (#choices left) * (#choices right).
   - Complexity: O(n)
   - Space: O(n)
   - Perfect for interviews and competitive programming.

👉 Final Recommendation: Use **Monotonic Stack + Contribution** approach.
==================================================================
*/
