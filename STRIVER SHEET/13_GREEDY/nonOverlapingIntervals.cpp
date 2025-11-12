#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Non-overlapping Intervals
 LeetCode Link: https://leetcode.com/problems/non-overlapping-intervals/

 Problem Statement:
 -----------------
 Given an array of intervals intervals where intervals[i] = [starti, endi], 
 return the minimum number of intervals you need to remove to make the rest 
 of the intervals non-overlapping.

 Example 1:
 Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
 Output: 1
 Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

 Example 2:
 Input: intervals = [[1,2],[1,2],[1,2]]
 Output: 2
 Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

 Example 3:
 Input: intervals = [[1,2],[2,3]]
 Output: 0
 Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

 Constraints:
 - 1 <= intervals.length <= 10^5
 - intervals[i].length == 2
 - -5 * 10^4 <= starti < endi <= 5 * 10^4
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Try All Combinations
 -----------------------------------------
 💡 Idea:
 Generate all possible subsets of intervals and find the largest subset
 that contains no overlapping intervals. The answer is total - largest_valid_subset.

 🧩 Algorithm:
 1. Generate all 2^N possible subsets of intervals.
 2. For each subset, check if all intervals are non-overlapping.
 3. Keep track of the largest valid subset size.
 4. Return total intervals - largest valid subset size.

 ⏱ Time Complexity: O(2^N * N^2) - check all subsets, validate each
 📦 Space Complexity: O(N) - to store current subset
*/
bool areNonOverlapping(vector<vector<int>>& subset) {
    for (int i = 0; i < subset.size(); i++) {
        for (int j = i + 1; j < subset.size(); j++) {
            // Check if intervals i and j overlap
            if (max(subset[i][0], subset[j][0]) < min(subset[i][1], subset[j][1])) {
                return false;
            }
        }
    }
    return true;
}

int eraseOverlapIntervalsBruteForce(vector<vector<int>>& intervals) {
    int n = intervals.size();
    int maxValidSize = 0;
    
    // Try all 2^N subsets
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<vector<int>> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset.push_back(intervals[i]);
            }
        }
        
        if (areNonOverlapping(subset)) {
            maxValidSize = max(maxValidSize, (int)subset.size());
        }
    }
    
    return n - maxValidSize;
}


/* 
==========================================
 Approach 2: Better - Sort by Start Time + Greedy
 -----------------------------------------
 💡 Idea:
 Sort intervals by start time, then greedily select intervals that don't
 overlap with the previously selected interval.

 🧩 Algorithm:
 1. Sort intervals by start time.
 2. Keep track of the last selected interval's end time.
 3. For each interval:
    - If it starts after the last selected interval ends, select it
    - Otherwise, skip it (increment removal count)
 4. Return total removals needed.

 ⏱ Time Complexity: O(N log N) - sorting dominates
 📦 Space Complexity: O(1) - only using variables
*/
int eraseOverlapIntervalsBetter(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n <= 1) return 0;
    
    sort(intervals.begin(), intervals.end()); // Sort by start time
    
    int removals = 0;
    int lastEnd = intervals[0][1];
    
    for (int i = 1; i < n; i++) {
        if (intervals[i][0] < lastEnd) {
            // Overlap detected - need to remove one interval
            removals++;
            // Keep the interval with earlier end time (greedy choice)
            lastEnd = min(lastEnd, intervals[i][1]);
        } else {
            // No overlap - update last end time
            lastEnd = intervals[i][1];
        }
    }
    
    return removals;
}


/* 
==========================================
 Approach 3: Optimal - Sort by End Time + Greedy (Activity Selection)
 -----------------------------------------
 💡 Idea:
 This is equivalent to the Activity Selection Problem. Sort by end time and
 greedily select intervals that end earliest to maximize non-overlapping intervals.

 🧩 Algorithm:
 1. Sort intervals by end time (ascending).
 2. Always select the first interval.
 3. For subsequent intervals:
    - If current interval starts >= last selected interval's end: select it
    - Otherwise: skip it (it's an overlap, increment removal count)
 4. Return total removals.

 ⏱ Time Complexity: O(N log N) - sorting dominates
 📦 Space Complexity: O(1) - only using variables
*/
int eraseOverlapIntervalsOptimal(vector<vector<int>>& intervals) {
    int ans = 0, n = intervals.size();
    
    // Sort by end time (ascending)
    sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
        return a[1] < b[1];
    });
    
    int last = intervals[0][1]; // End time of last selected interval
    
    for (int i = 1; i < n; i++) {
        if (intervals[i][0] < last) {
            // Overlap: current interval starts before last selected ends
            ans++; // Remove current interval
        } else {
            // No overlap: select current interval
            last = intervals[i][1]; // Update last selected end time
        }
    }
    
    return ans;
}


/* Helper function to print intervals with indices */
void printIntervals(const vector<vector<int>>& intervals, const string& label) {
    cout << label << ": [";
    for (int i = 0; i < intervals.size(); i++) {
        cout << "[" << intervals[i][0] << "," << intervals[i][1] << "]";
        if (i < intervals.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

/* Helper function to demonstrate the optimal greedy process */
void demonstrateOptimalProcess(vector<vector<int>>& intervals) {
    cout << "Step-by-step optimal greedy demonstration:\n";
    printIntervals(intervals, "Original intervals");
    
    // Create pairs of (interval, original_index) for tracking
    vector<pair<vector<int>, int>> indexedIntervals;
    for (int i = 0; i < intervals.size(); i++) {
        indexedIntervals.push_back({intervals[i], i});
    }
    
    // Sort by end time
    sort(indexedIntervals.begin(), indexedIntervals.end(), 
         [](const pair<vector<int>, int>& a, const pair<vector<int>, int>& b) {
             return a.first[1] < b.first[1];
         });
    
    cout << "After sorting by end time:\n";
    for (int i = 0; i < indexedIntervals.size(); i++) {
        cout << "  [" << indexedIntervals[i].first[0] << "," << indexedIntervals[i].first[1] 
             << "] (original index " << indexedIntervals[i].second << ")\n";
    }
    
    int removals = 0;
    int lastEnd = indexedIntervals[0].first[1];
    vector<int> kept, removed;
    kept.push_back(indexedIntervals[0].second);
    
    cout << "\nGreedy selection process:\n";
    cout << "Step 1: Select [" << indexedIntervals[0].first[0] << "," 
         << indexedIntervals[0].first[1] << "] (ends earliest)\n";
    
    for (int i = 1; i < indexedIntervals.size(); i++) {
        cout << "Step " << (i+1) << ": Consider [" << indexedIntervals[i].first[0] 
             << "," << indexedIntervals[i].first[1] << "] ";
        
        if (indexedIntervals[i].first[0] < lastEnd) {
            cout << "→ REMOVE (starts at " << indexedIntervals[i].first[0] 
                 << " < " << lastEnd << " last end)\n";
            removals++;
            removed.push_back(indexedIntervals[i].second);
        } else {
            cout << "→ KEEP (starts at " << indexedIntervals[i].first[0] 
                 << " >= " << lastEnd << " last end)\n";
            lastEnd = indexedIntervals[i].first[1];
            kept.push_back(indexedIntervals[i].second);
        }
    }
    
    cout << "\nFinal result:\n";
    cout << "Kept " << kept.size() << " intervals (indices: ";
    for (int i = 0; i < kept.size(); i++) {
        cout << kept[i];
        if (i < kept.size() - 1) cout << ", ";
    }
    cout << ")\n";
    
    cout << "Removed " << removals << " intervals";
    if (removals > 0) {
        cout << " (indices: ";
        for (int i = 0; i < removed.size(); i++) {
            cout << removed[i];
            if (i < removed.size() - 1) cout << ", ";
        }
        cout << ")";
    }
    cout << "\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<vector<vector<int>>> testCases = {
        {{1, 2}, {2, 3}, {3, 4}, {1, 3}},
        {{1, 2}, {1, 2}, {1, 2}},
        {{1, 2}, {2, 3}},
        {{1, 100}, {11, 22}, {1, 11}, {2, 12}},
        {{0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}},
        {{1, 2}, {1, 3}, {2, 3}, {3, 4}},
        {{-1, 1}, {0, 2}, {1, 3}, {2, 4}}
    };

    cout << "=== Testing Non-overlapping Intervals Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<vector<int>> intervals1 = testCases[t];
        vector<vector<int>> intervals2 = testCases[t];
        vector<vector<int>> intervals3 = testCases[t];
        
        cout << "Test Case " << t + 1 << ":\n";
        printIntervals(intervals1, "Input");
        
        int ans1 = (intervals1.size() <= 10) ? eraseOverlapIntervalsBruteForce(intervals1) : -1;
        int ans2 = eraseOverlapIntervalsBetter(intervals2);
        int ans3 = eraseOverlapIntervalsOptimal(intervals3);
        
        if (ans1 != -1) {
            cout << " Brute Force:       " << ans1 << "\n";
        } else {
            cout << " Brute Force:       [Skipped - too slow]\n";
        }
        cout << " Better (Start):    " << ans2 << "\n";
        cout << " Optimal (Your):    " << ans3 << "\n";
        
        // Demonstrate the process for first test case
        if (t == 0) {
            cout << "\n";
            vector<vector<int>> demo = testCases[t];
            demonstrateOptimalProcess(demo);
        }
        
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(2^N * N^2) time, tries all possible interval combinations.\n";
    cout << "2. Better (Start Sort) -> O(N log N) time, greedy based on start times.\n";
    cout << "3. Optimal (End Sort) -> O(N log N) time, classic Activity Selection approach.\n";
    cout << "\nRecommendation: Your optimal approach is the classic solution! ✅\n";
    cout << "Key Insight: This is the Activity Selection Problem in disguise.\n";
    cout << "             Sorting by end time and selecting earliest-ending intervals is optimal.\n";
    cout << "\nWhy Sort by End Time?\n";
    cout << "- Selecting intervals that end early leaves more room for future intervals\n";
    cout << "- This greedy choice leads to the optimal solution (maximum activities)\n";
    cout << "- Minimizing removals ≡ Maximizing non-overlapping intervals\n";
    cout << "\nYour Implementation:\n";
    cout << "- Custom comparator: a[1] < b[1] (sort by end time)\n";
    cout << "- Greedy selection: if current.start >= last.end, keep it\n";
    cout << "- Otherwise: remove current interval (increment counter)\n";
    cout << "\nYour provided solution is the textbook optimal approach! 🎯\n";
    cout << "Perfect application of the Activity Selection greedy algorithm!\n";

    return 0;
}
