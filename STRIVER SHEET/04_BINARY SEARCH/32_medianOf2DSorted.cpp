#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Median in a Row-wise Sorted Matrix

Problem Statement:
Given an m x n matrix where each row is sorted in non-decreasing order and both m and n are odd,
return the median of all elements (i.e., the element at index (m*n)/2 in the sorted order).

Example:
mat = [
  [1, 3, 5],
  [2, 6, 9],
  [3, 6, 9]
]
Output: 5
Explanation:
Flattened and sorted: [1,2,3,3,5,6,6,9,9]; the middle element (index 4 for 0-based, since m*n=9) is 5.

Approach Overview:
- Approach 1 (Brute Force): Flatten the matrix into a single vector, sort it, and return the middle element.
- Approach 2 (Binary Search on Value) [Recommended]: Binary search over the value range and, for each mid value,
  count how many elements are <= mid using per-row binary search; move the search space based on whether
  the count is <= (m*n)/2 or greater.

Approach 1: Brute Force
Approach Idea:
- Sort all elements explicitly so the median is at the middle index of the flattened sorted list.

Algorithm:
1) Create an array arr of size m*n and copy all matrix elements into it.
2) Sort arr.
3) Return arr[(m*n)/2].

Time Complexity: O(m*n*log(m*n))
Space Complexity: O(m*n)
*/
int median(vector<vector<int>>& mat) {
    int m = (int)mat.size();
    int n = (int)mat[0].size();
    vector<int> arr;
    arr.reserve(1LL * m * n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            arr.push_back(mat[i][j]);
    sort(arr.begin(), arr.end());
    return arr[(m * n) / 2];
}

/*
Helper: Count elements <= num across all rows
- For each sorted row, binary search for the first index > num; that index equals the count of elements <= num in that row.

Time Complexity: O(m * log n)
Space Complexity: O(1)
*/
static int countSmallerEqual(const vector<vector<int>>& mat, int num) {
    int m = (int)mat.size();
    int n = (int)mat[0].size();
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        int low = 0, high = n - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (mat[i][mid] <= num) low = mid + 1;
            else high = mid - 1;
        }
        cnt += low; // number <= num
    }
    return cnt;
}

/*
Approach 2: Binary Search on Value (Recommended)
Approach Idea:
- The function f(x) = number of elements in the matrix <= x is non-decreasing in x.
  We can binary search the smallest x for which f(x) > (m*n)/2, which is the median for odd total count.

Algorithm:
1) Determine the global value range:
   - low = min(mat[i][0]) over all rows i,
   - high = max(mat[i][n-1]) over all rows i.
2) Let need = (m*n)/2 (the number of elements strictly before the median in sorted order).
3) While low <= high:
   - mid = low + (high - low)/2
   - cnt = count of elements <= mid (sum over rows by per-row binary search)
   - If cnt <= need: low = mid + 1 (the median must be larger)
     Else: high = mid - 1 (mid might be the median or we can find a smaller candidate)
4) Return low (the first value with count > need), which is the median.

Time Complexity: O(m * log n * log(range))
Space Complexity: O(1)
*/
int median2(vector<vector<int>>& mat) {
    int m = (int)mat.size();
    int n = (int)mat[0].size();

    int low = mat[0][0], high = mat[0][n - 1];
    for (int i = 0; i < m; i++) {
        low = min(low, mat[i][0]);
        high = max(high, mat[i][n - 1]);
    }

    int need = (m * n) / 2;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cnt = countSmallerEqual(mat, mid);
        if (cnt <= need) {
            low = mid + 1;   // need a larger value to cross the median threshold
        } else {
            high = mid - 1;  // mid is possibly the median, try smaller
        }
    }
    return low; // first value with count > need
}

int main() {
    vector<vector<int>> mat = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };

    cout << "Median (brute force): " << median(mat) << "\n";
    cout << "Median (optimized):   " << median2(mat) << "\n";
    return 0;
}
