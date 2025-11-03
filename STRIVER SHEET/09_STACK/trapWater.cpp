#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Trapping Rain Water
Problem Link: LeetCode #42 (https://leetcode.com/problems/trapping-rain-water/)

Problem Statement:
Given n non-negative integers representing an elevation map where the width of 
each bar is 1, compute how much water it can trap after raining.

------------------------------------------------------------
Example 1:
Input:  height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation:
The elevation map looks like:
          #
      #~~##~#
  #~~##~~~###
  ------------
Trapped water = 6 units.

Example 2:
Input:  height = [4,2,0,3,2,5]
Output: 9

------------------------------------------------------------
Constraints:
- 1 <= height.length <= 2 * 10^4
- 0 <= height[i] <= 10^5
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Precompute LeftMax + RightMax Arrays
==================================================================
💡 Idea:
- For each bar, trapped water = min(max to left, max to right) - height[i].
- Precompute prefix max and suffix max arrays.

🧩 Algorithm:
1. Compute prefix max array (left).
2. Compute suffix max array (right).
3. For each i: res += min(left[i], right[i]) - height[i].

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

int trap_withArrays(vector<int>& height) {
    int n = height.size();
    vector<int> leftMax(n), rightMax(n);

    leftMax[0] = height[0];
    for (int i = 1; i < n; i++)
        leftMax[i] = max(leftMax[i-1], height[i]);

    rightMax[n-1] = height[n-1];
    for (int i = n-2; i >= 0; i--)
        rightMax[i] = max(rightMax[i+1], height[i]);

    int res = 0;
    for (int i = 0; i < n; i++)
        res += min(leftMax[i], rightMax[i]) - height[i];

    return res;
}

/*
==================================================================
Approach 2: Two-Pointer Technique (Optimal Space)
==================================================================
💡 Idea:
- Instead of storing arrays, track `leftMax` and `rightMax` while scanning.
- Move pointer from lower side towards center.

🧩 Algorithm:
1. Initialize l=0, r=n-1, leftMax=0, rightMax=0.
2. While l<r:
   - If height[l] <= height[r]:
       - If height[l] >= leftMax → update leftMax.
       - Else res += leftMax - height[l].
       - l++
   - Else:
       - If height[r] >= rightMax → update rightMax.
       - Else res += rightMax - height[r].
       - r--
3. Return res.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/

int trap_twoPointers(vector<int>& height) {
    int n = height.size();
    int l = 0, r = n-1, leftMax = 0, rightMax = 0;
    int res = 0;

    while (l < r) {
        if (height[l] <= height[r]) {
            if (height[l] >= leftMax) leftMax = height[l];
            else res += leftMax - height[l];
            l++;
        } else {
            if (height[r] >= rightMax) rightMax = height[r];
            else res += rightMax - height[r];
            r--;
        }
    }
    return res;
}

/*
==================================================================
Approach 3: Monotonic Stack
==================================================================
💡 Idea:
- Use a stack to track bars that can trap water between them.
- When current height > stack.top, pop and compute trapped water.

🧩 Algorithm:
1. Initialize empty stack, res = 0.
2. For each index i:
   - While stack not empty and height[i] > height[top]:
       - Pop top.
       - If stack empty, break.
       - Distance = i - stack.top() - 1
       - BoundedHeight = min(height[i], height[stack.top()]) - height[top]
       - Add distance * boundedHeight to res.
   - Push i.
3. Return res.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

int trap_stack(vector<int>& height) {
    int n = height.size();
    stack<int> st;
    int res = 0;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && height[i] > height[st.top()]) {
            int top = st.top(); st.pop();
            if (st.empty()) break;
            int distance = i - st.top() - 1;
            int boundedHeight = min(height[i], height[st.top()]) - height[top];
            res += distance * boundedHeight;
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
        {0,1,0,2,1,0,1,3,2,1,2,1}, // Expected: 6
        {4,2,0,3,2,5}              // Expected: 9
    };

    for (auto height : testCases) {
        cout << "Heights: ";
        for (int h : height) cout << h << " ";
        cout << endl;
        cout << "Trapped (Two Arrays):   " << trap_withArrays(height) << endl;
        cout << "Trapped (Two Pointers): " << trap_twoPointers(height) << endl;
        cout << "Trapped (Stack):        " << trap_stack(height) << endl;
        cout << "---------------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Precompute with Arrays:
   - Time: O(n), Space: O(n).
   - Intuitive, easy to code.

2. Two Pointers:
   - Time: O(n), Space: O(1).
   - Optimal and elegant.
   - Most common in interviews.

3. Monotonic Stack:
   - Time: O(n), Space: O(n).
   - Useful variation, ties into "largest rectangle in histogram".
   - Good to know.

👉 Final Recommendation: Use **Two Pointers** in interviews (O(n), O(1)).
==================================================================
*/
