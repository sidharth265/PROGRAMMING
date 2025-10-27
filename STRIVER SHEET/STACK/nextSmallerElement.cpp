#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Next Smaller Element
 Problem Link: (Common Stack Problem)
====================================================

📝 Problem Statement:
Given an array of integers `arr`, for each element find the next smaller element to its right.
If no smaller element exists, set -1.

📌 Input:
- Vector of integers `arr`

📌 Output:
- Vector with next smaller element for each index.

----------------------------------------------------
🔹 Example:
Input: arr = [4, 5, 2, 10, 8]
Output: [2, 2, -1, 8, -1]

Explanation:
- Next smaller for 4 is 2  
- Next smaller for 5 is 2  
- No smaller element right of 2, so -1  
- Next smaller for 10 is 8  
- No smaller element right of 8, so -1

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Using Stack to find Next Smaller Elements
//////////////////////////////////////////////////////
/*
💡 Idea:
- Traverse array from right to left.
- Use a stack to keep potential smaller elements.
- For each element, pop elements from the stack which are >= current element.
- Top of the stack then is the next smaller element or -1 if none.

🧩 Algorithm:
1. Initialize stack with -1 (sentinel).
2. Initialize answer vector.
3. Loop i from n-1 down to 0:
   a. While stack top >= arr[i], pop.
   b. answer[i] = stack top.
   c. push arr[i] on stack.
4. Return answer.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(n)
*/

vector<int> nextSmallerElement(vector<int> &arr) {
    int n = (int)arr.size();
    stack<int> s;
    s.push(-1);
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        int curr = arr[i];
        while (s.top() >= curr) {
            s.pop();
        }
        ans[i] = s.top();
        s.push(curr);
    }
    return ans;
}

//////////////////////////////////////////////////////
// Main function with example usage
//////////////////////////////////////////////////////
int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> result = nextSmallerElement(arr);
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// The stack method allows us to find next smaller elements in one pass (right to left).
// Each element is pushed and popped at most once, leading to O(n) time.
