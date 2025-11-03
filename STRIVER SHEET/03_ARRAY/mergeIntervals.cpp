#include<bits/stdc++.h>
using namespace std;

/*
Problem: Merge Overlapping Intervals

Problem Statement:
Given an array of intervals where each interval is represented as [start, end], merge all overlapping intervals and return the resulting list of non-overlapping intervals sorted by start.

Example:
Input:
  intervals = [[1, 3], [2, 6], [8, 10], [15, 18], [17, 20]]
Output:
  [[1, 6], [8, 10], [15, 20]]
Explanation:
- [1, 3] and [2, 6] overlap -> merge to [1, 6]
- [15, 18] and [17, 20] overlap -> merge to [15, 20]
- [8, 10] remains as is

Approach:
- Sort and Sweep:
  - Sort intervals by starting time.
  - Initialize result with the first interval.
  - For each next interval, compare with the last interval in result:
    - If overlapping (current.start <= last.end), merge by updating last.end = max(last.end, current.end).
    - Otherwise, append the current interval to result.

Algorithm:
1) Sort intervals by start.
2) Push the first interval into ans.
3) For each interval i from 1..n-1:
   - If ans.back().end < intervals[i].start: push intervals[i].
   - Else: ans.back().end = max(ans.back().end, intervals[i].end).
4) Return ans.

Time Complexity:
- O(n log n) due to sorting.

Space Complexity:
- O(n) for the output list (auxiliary beyond output is O(1)).
*/
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int n = intervals.size();
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    for (int i=1; i<n; i++) {
        if (ans.back()[1] < intervals[i][0]) {
            ans.push_back(intervals[i]);
        }
        else {
            ans.back()[1] = max(ans.back()[1], intervals[i][1]);
        }
    }
    return ans;
}

// Example usage
int main() {
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}, {17, 20}};
    vector<vector<int>> mergedIntervals = merge(intervals);
    
    for (const auto& interval : mergedIntervals) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    return 0;
}
