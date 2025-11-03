#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Next Greater Element II (Circular Array)
 Problem Link: (LeetCode 503 or similar)
====================================================

📝 Problem Statement:
Given a circular array `nums`, find the next greater number for every element.
The next greater number for an element x is the first greater number on the right side 
of x in the array, and the array is considered circular (next of last element is first).

📌 Input:
- Vector of integers `nums`

📌 Output:
- Vector with next greater element for each index; if none, -1.

----------------------------------------------------
🔹 Example:
Input: nums = [1, 2, 1]  
Output: [2, -1, 2]

Explanation:
- Next greater for nums[0] = 2  
- No next greater for nums[1]  
- Next greater for nums[2] = 2 (circular)

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Stack + Double Traversal for Circular Array
//////////////////////////////////////////////////////
/*
💡 Idea:
- Traverse array twice (0..2n-1) modulo n indices.
- Use stack to keep indices pending next greater element.
- For each element:
  - Pop all stack indices with smaller element, update their answer.
  - Push current index once (only the first pass).

🧩 Algorithm:
1. Initialize an answer vector with -1.
2. Create empty stack to hold indices.
3. Loop i in [0..2*n-1]:
   - Current index = i % n.
   - While stack not empty and nums[current] > nums[stack.top()], set answer for stack.top() and pop.
   - If i < n, push current index to stack.
4. Return answer.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(n)
*/

vector<int> nextLargerElement(vector<int> &nums) {
    int n = (int)nums.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = 0; i < 2 * n; i++) {
        int curr = i % n;
        while (!st.empty() && nums[curr] > nums[st.top()]) {
            ans[st.top()] = nums[curr];
            st.pop();
        }
        if (i < n) st.push(curr);
    }
    return ans;
}

//////////////////////////////////////////////////////
// Main function with example usage
//////////////////////////////////////////////////////
int main() {
    vector<int> nums = {1, 2, 1};
    vector<int> result = nextLargerElement(nums);
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// The double traversal ensures elements at end can check for next greater in beginning (circular).
// The stack stores indices waiting for a greater element to their right in O(n) time.
``````cpp
#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Next Greater Element II (Circular Array)
 Problem Link: (LeetCode 503 or similar)
====================================================

📝 Problem Statement:
Given a circular array `nums`, find the next greater number for every element.
The next greater number for an element x is the first greater number on the right side 
of x in the array, and the array is considered circular (next of last element is first).

📌 Input:
- Vector of integers `nums`

📌 Output:
- Vector with next greater element for each index; if
