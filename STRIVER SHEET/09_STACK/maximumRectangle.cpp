#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Maximal Rectangle in Binary Matrix
 Problem Link: (LeetCode 85 or similar)
====================================================

📝 Problem Statement:
Given a 2D binary matrix filled with '0's and '1's, find the largest rectangle containing only '1's and return its area.

📌 Input:
- A 2D matrix of chars ('0' or '1')

📌 Output:
- The area of the largest rectangle composed entirely of '1's.

----------------------------------------------------
🔹 Example:
Input:
[
  ['1', '0', '1', '0', '0'],
  ['1', '0', '1', '1', '1'],
  ['1', '1', '1', '1', '1'],
  ['1', '0', '0', '1', '0']
]
Output: 6

Explanation:
The largest rectangle has area 6 in the third row spanning columns 2 through 4.

====================================================
*/

//////////////////////////////////////////////////////
// Approach: Largest Rectangle in Histogram per row
//////////////////////////////////////////////////////
/*
💡 Idea:
- For each row:
  - Build histogram heights using consecutive '1's count in each column.
  - Compute the largest rectangle in this histogram.

🧩 Algorithm:
1. For each row, update heights array representing histogram.
2. Use stacks to calculate previous smaller and next smaller indices.
3. Calculate max area for each bar = height * width (where width = nextSmall - prevSmall - 1).
4. Return max area found across all rows.

⏱ Time Complexity: O(m * n)  
📦 Space Complexity: O(n)
*/

int maxRect(vector<int>& Arr) {
    int n = (int)Arr.size();
    vector<int> prevSmall(n, -1), nextSmall(n, n);
    stack<int> st;

    // Find previous smaller element's index for each bar
    for (int j = 0; j < n; j++) {
        while (!st.empty() && Arr[st.top()] >= Arr[j]) st.pop();
        if (!st.empty()) prevSmall[j] = st.top();
        st.push(j);
    }

    // Clear stack to reuse for next smaller element's index
    st = stack<int>();

    // Find next smaller element's index for each bar
    for (int j = n - 1; j >= 0; j--) {
        while (!st.empty() && Arr[st.top()] > Arr[j]) st.pop();
        if (!st.empty()) nextSmall[j] = st.top();
        st.push(j);
    }

    int ans = 0;
    for (int j = 0; j < n; j++) {
        int area = Arr[j] * (nextSmall[j] - prevSmall[j] - 1);
        ans = max(ans, area);
    }
    return ans;
}

int maximalRectangle(vector<vector<char>>& matrix) {
    int m = (int)matrix.size();
    if (m == 0) return 0;
    int n = (int)matrix[0].size();
    vector<int> arr(n, 0);
    int ans = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == '1') arr[j]++;
            else arr[j] = 0;
        }
        ans = max(ans, maxRect(arr));
    }
    return ans;
}

//////////////////////////////////////////////////////
// Main function with example test case
//////////////////////////////////////////////////////
int main() {
    vector<vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };

    cout << "Maximal Rectangle Area: " << maximalRectangle(matrix) << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// We treat each matrix row as a histogram of heights of consecutive '1's.
// Using stacks to get previous and next smaller elements, we compute largest rectangle areas efficiently in O(m*n).
