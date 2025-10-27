#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Next Greater Element
 Problem Link: (Common Stack Problem)
====================================================

📝 Problem Statement:
Given an array of integers `arr`, for each element find the next greater element to its right.
If no greater element exists, set -1.

📌 Input:
- Vector of integers `arr`

📌 Output:
- Vector with next greater element for each index.

----------------------------------------------------
🔹 Example:
Input: arr = [4, 5, 2, 10, 8]
Output: [5, 10, 10, -1, -1]

Explanation:
- Next greater for 4 is 5  
- Next greater for 5 is 10  
- Next greater for 2 is 10  
- Next greater for 10 is none (-1)  
- Next greater for 8 is none (-1)

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Using Stack to find Next Greater Elements
//////////////////////////////////////////////////////
/*
💡 Idea:
- Use a stack to keep indices whose next greater elements are not found yet.
- Traverse array, for each element:
  - Pop stack while current element is greater than top element's index value.
  - Set popped indices' answers to current element.
  - Push current index.

🧩 Algorithm:
1. Initialize stack and answer vector with -1.
2. Iterate arr from left to right:
   a. While stack not empty and arr[i] > arr[stack.top()], do:
      - ans[stack.top()] = arr[i]
      - pop stack
   b. Push i onto stack.
3. Return ans vector.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(n)
*/

vector<int> nextLargerElement(vector<int> &arr) {
    int n = (int)arr.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[i] > arr[st.top()]) {
            ans[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }
    return ans;
}

//////////////////////////////////////////////////////
// Main function with example usage
//////////////////////////////////////////////////////
int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> result = nextLargerElement(arr);
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Uses a stack to efficiently track elements awaiting their next greater element.
// Each element is pushed and popped at most once, achieving O(n) time.
