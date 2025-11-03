#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Merge Intervals
 LeetCode Link: https://leetcode.com/problems/merge-intervals/

 Problem Statement:
 -----------------
 Given an array of intervals where intervals[i] = [starti, endi], merge all 
 overlapping intervals, and return an array of the non-overlapping intervals 
 that cover all the intervals in the input.

 Example 1:
 Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 Output: [[1,6],[8,10],[15,18]]
 Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

 Example 2:
 Input: intervals = [[1,4],[4,5]]
 Output: [[1,5]]
 Explanation: Intervals [1,4] and [4,5] are considered overlapping.

 Example 3:
 Input: intervals = [[1,4],[2,3]]
 Output: [[1,4]]
 Explanation: [2,3] is completely inside [1,4], so merge into [1,4].

 Constraints:
 - 1 <= intervals.length <= 10^4
 - intervals[i].length == 2
 - 0 <= starti <= endi <= 10^4
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Check All Pairs
 -----------------------------------------
 💡 Idea:
 For each interval, check if it overlaps with any other interval.
 Keep merging overlapping intervals until no more merges possible.

 🧩 Algorithm:
 1. Repeat until no changes in one iteration:
    - For each pair of intervals, check if they overlap
    - If they overlap, merge them and remove the second interval
    - Continue until no more merges in current iteration
 2. Return the final merged intervals.

 ⏱ Time Complexity: O(N^3) - nested loops with potential multiple passes
 📦 Space Complexity: O(N) - result array
*/
bool hasOverlap(vector<int>& a, vector<int>& b) {
    return max(a[0], b[0]) <= min(a[1], b[1]);
}

vector<vector<int>> mergeBruteForce(vector<vector<int>>& intervals) {
    vector<vector<int>> result = intervals;
    bool merged = true;
    
    while (merged) {
        merged = false;
        
        for (int i = 0; i < result.size() && !merged; i++) {
            for (int j = i + 1; j < result.size(); j++) {
                if (hasOverlap(result[i], result[j])) {
                    // Merge intervals i and j
                    result[i][0] = min(result[i][0], result[j][0]);
                    result[i][1] = max(result[i][1], result[j][1]);
                    result.erase(result.begin() + j);
                    merged = true;
                    break;
                }
            }
        }
    }
    
    return result;
}


/* 
==========================================
 Approach 2: Better - Sort Then Merge
 -----------------------------------------
 💡 Idea:
 Sort intervals by start time, then iterate through and merge consecutive
 overlapping intervals. Use a separate result array to build the answer.

 🧩 Algorithm:
 1. Sort intervals by start time.
 2. Initialize result with first interval.
 3. For each subsequent interval:
    - If it doesn't overlap with last interval in result, add it
    - If it overlaps, merge by extending the end time of last interval
 4. Return merged intervals.

 ⏱ Time Complexity: O(N log N) - sorting dominates
 📦 Space Complexity: O(N) - result array
*/
vector<vector<int>> mergeBetter(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> result;
    result.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        vector<int>& lastInterval = result.back();
        vector<int>& currentInterval = intervals[i];
        
        if (lastInterval[1] < currentInterval[0]) {
            // No overlap - add current interval
            result.push_back(currentInterval);
        } else {
            // Overlap - merge intervals
            lastInterval[1] = max(lastInterval[1], currentInterval[1]);
        }
    }
    
    return result;
}


/* 
==========================================
 Approach 3: Optimal - Sort and Merge In-Place
 -----------------------------------------
 💡 Idea:
 Same as better approach but with cleaner code. Sort intervals by start time,
 then merge overlapping intervals in a single pass.

 🧩 Algorithm:
 1. Sort intervals by start time (intervals are sorted by first element by default).
 2. Start with first interval in result.
 3. For each subsequent interval:
    - If current.start > last.end: no overlap, add current interval
    - Else: overlap exists, merge by updating last.end = max(last.end, current.end)
 4. Return the merged result.

 ⏱ Time Complexity: O(N log N) - sorting step dominates
 📦 Space Complexity: O(1) - excluding output array, only using constant space
*/
vector<vector<int>> mergeOptimal(vector<vector<int>>& intervals) {
    int n = intervals.size();
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    
    for (int i = 1; i < n; i++) {
        if (ans.back()[1] < intervals[i][0]) {
            // No overlap: last interval ends before current starts
            ans.push_back(intervals[i]);
        } else {
            // Overlap: merge by extending the end time
            ans.back()[1] = max(ans.back()[1], intervals[i][1]);
        }
    }
    
    return ans;
}


/* Helper function to print intervals */
void printIntervals(const vector<vector<int>>& intervals, const string& label) {
    cout << label << ": [";
    for (int i = 0; i < intervals.size(); i++) {
        cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]";
        if (i < intervals.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

/* Helper function to demonstrate the merging process */
void demonstrateMerging(vector<vector<int>>& intervals) {
    cout << "Step-by-step merging demonstration:\n";
    printIntervals(intervals, "Original intervals");
    
    sort(intervals.begin(), intervals.end());
    printIntervals(intervals, "After sorting");
    
    vector<vector<int>> result;
    result.push_back(intervals[0]);
    cout << "\nMerging process:\n";
    cout << "Initialize result with [" << intervals[0][0] << "," << intervals[0][1] << "]\n";
    
    for (int i = 1; i < intervals.size(); i++) {
        cout << "\nStep " << i << ": Consider interval [" << intervals[i][0] << "," << intervals[i][1] << "]\n";
        
        if (result.back()[1] < intervals[i][0]) {
            cout << "  No overlap (" << result.back()[1] << " < " << intervals[i][0] << ")\n";
            cout << "  → Add [" << intervals[i][0] << "," << intervals[i][1] << "] to result\n";
            result.push_back(intervals[i]);
        } else {
            cout << "  Overlap detected (" << result.back()[1] << " >= " << intervals[i][0] << ")\n";
            cout << "  → Merge: [" << result.back()[0] << "," << result.back()[1] << "] + [" 
                 << intervals[i][0] << "," << intervals[i][1] << "]";
            result.back()[1] = max(result.back()[1], intervals[i][1]);
            cout << " = [" << result.back()[0] << "," << result.back()[1] << "]\n";
        }
        
        cout << "  Current result: ";
        printIntervals(result, "");
    }
    
    cout << "\n";
    printIntervals(result, "Final merged intervals");
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<vector<vector<int>>> testCases = {
        {{1, 3}, {2, 6}, {8, 10}, {15, 18}},
        {{1, 4}, {4, 5}},
        {{1, 4}, {2, 3}},
        {{1, 4}, {0, 4}},
        {{1, 4}, {0, 0}},
        {{2, 3}, {4, 5}, {6, 7}, {8, 9}, {1, 10}},
        {{1, 3}, {2, 6}, {8, 10}, {9, 12}, {15, 18}},
        {{1, 4}, {5, 6}},
        {{0, 0}, {1, 4}}
    };

    cout << "=== Testing Merge Intervals Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<vector<int>> intervals1 = testCases[t];
        vector<vector<int>> intervals2 = testCases[t];
        vector<vector<int>> intervals3 = testCases[t];
        
        cout << "Test Case " << t + 1 << ":\n";
        printIntervals(intervals1, "Input");
        
        auto ans1 = (intervals1.size() <= 6) ? mergeBruteForce(intervals1) : vector<vector<int>>{};
        auto ans2 = mergeBetter(intervals2);
        auto ans3 = mergeOptimal(intervals3);
        
        if (!ans1.empty()) {
            printIntervals(ans1, " Brute Force");
        } else {
            cout << " Brute Force: [Skipped - too slow for large input]\n";
        }
        printIntervals(ans2, " Better Approach");
        printIntervals(ans3, " Optimal (Your)");
        
        // Demonstrate the process for first test case
        if (t == 0) {
            cout << "\n";
            vector<vector<int>> demo = testCases[t];
            demonstrateMerging(demo);
        }
        
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N^3) time, repeatedly finds and merges overlapping pairs.\n";
    cout << "2. Better Approach -> O(N log N) time, sort then merge with detailed logic.\n";
    cout << "3. Optimal (Your) -> O(N log N) time, clean and concise implementation.\n";
    cout << "\nRecommendation: Your optimal approach is perfectly implemented! ✅\n";
    cout << "Key Insight: After sorting by start time, overlapping intervals will be adjacent.\n";
    cout << "             We only need to compare each interval with the last merged interval.\n";
    cout << "\nYour Implementation Highlights:\n";
    cout << "- Clean and readable code with minimal lines\n";
    cout << "- Efficient single-pass merging after sorting\n";
    cout << "- Handles all edge cases: no overlap, complete overlap, partial overlap\n";
    cout << "- Optimal time complexity with minimal space usage\n";
    cout << "\nOverlap Condition: intervals[i][0] <= ans.back()[1]\n";
    cout << "If current interval starts before or when last interval ends → overlap exists!\n";
    cout << "\nYour provided solution is the gold standard for merge intervals! 🎯\n";

    return 0;
}
