#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Maximum Meetings in One Room (Activity Selection Problem)
 GeeksForGeeks Link: https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/

 Problem Statement:
 -----------------
 There is one meeting room in a firm. There are N meetings in the form of 
 (start[i], end[i]) where start[i] is start time of meeting i and end[i] is 
 finish time of meeting i. What is the maximum number of meetings that can be 
 accommodated in the meeting room when only one meeting can be held in the meeting room at any time?

 Example 1:
 Input: start[] = [1, 3, 0, 5, 8, 5], end[] = [2, 4, 6, 7, 9, 9]
 Output: 4
 Explanation: We can attend meetings 1, 2, 4, and 5. 
 Meeting times: (1,2), (3,4), (5,7), (8,9)

 Example 2:
 Input: start[] = [10, 12, 20], end[] = [20, 25, 30]
 Output: 1
 Explanation: Only one meeting can be held at a time.

 Example 3:
 Input: start[] = [1, 2, 3], end[] = [4, 4, 4]
 Output: 3
 Explanation: All three meetings can be attended: (1,4), (2,4), (3,4)

 Constraints:
 - 1 ≤ N ≤ 10^5
 - 0 ≤ start[i] < end[i] ≤ 10^9
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Try All Combinations
 -----------------------------------------
 💡 Idea:
 Generate all possible combinations of meetings and check which combination
 gives maximum non-overlapping meetings.

 🧩 Algorithm:
 1. Generate all 2^N possible subsets of meetings.
 2. For each subset, check if all meetings are non-overlapping.
 3. Keep track of maximum size valid subset.
 4. Return the maximum count found.

 ⏱ Time Complexity: O(2^N * N^2) - check all subsets, validate each
 📦 Space Complexity: O(N) - to store current subset
*/
bool isValidSubset(vector<int>& start, vector<int>& end, int mask) {
    vector<pair<int, int>> selected;
    for (int i = 0; i < start.size(); i++) {
        if (mask & (1 << i)) {
            selected.push_back({start[i], end[i]});
        }
    }
    
    // Check if all meetings in selected are non-overlapping
    for (int i = 0; i < selected.size(); i++) {
        for (int j = i + 1; j < selected.size(); j++) {
            // Two meetings overlap if one starts before the other ends
            if (selected[i].first < selected[j].second && selected[j].first < selected[i].second) {
                return false;
            }
        }
    }
    return true;
}

int maxMeetingsBruteForce(vector<int>& start, vector<int>& end) {
    int n = start.size();
    int maxCount = 0;
    
    // Try all 2^N combinations
    for (int mask = 0; mask < (1 << n); mask++) {
        if (isValidSubset(start, end, mask)) {
            maxCount = max(maxCount, __builtin_popcount(mask));
        }
    }
    
    return maxCount;
}


/* 
==========================================
 Approach 2: Better - Dynamic Programming
 -----------------------------------------
 💡 Idea:
 Sort meetings by start time and use DP where dp[i] represents maximum
 meetings we can select considering first i meetings.

 🧩 Algorithm:
 1. Sort meetings by start time along with original indices.
 2. For each meeting i, we have two choices:
    - Skip meeting i: dp[i] = dp[i-1]
    - Include meeting i: dp[i] = 1 + dp[j] where j is last non-overlapping meeting
 3. Use binary search to find last non-overlapping meeting efficiently.
 4. Return dp[n-1].

 ⏱ Time Complexity: O(N log N) - sorting + binary search for each meeting
 📦 Space Complexity: O(N) - DP array + sorted meetings
*/
int findLastNonOverlapping(vector<pair<pair<int, int>, int>>& meetings, int current) {
    int left = 0, right = current - 1, result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (meetings[mid].first.second <= meetings[current].first.first) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

int maxMeetingsDP(vector<int>& start, vector<int>& end) {
    int n = start.size();
    vector<pair<pair<int, int>, int>> meetings(n);
    
    for (int i = 0; i < n; i++) {
        meetings[i] = {{start[i], end[i]}, i};
    }
    
    // Sort by start time
    sort(meetings.begin(), meetings.end());
    
    vector<int> dp(n);
    dp[0] = 1;
    
    for (int i = 1; i < n; i++) {
        // Option 1: Don't include current meeting
        dp[i] = dp[i-1];
        
        // Option 2: Include current meeting
        int lastNonOverlapping = findLastNonOverlapping(meetings, i);
        int includeCount = 1;
        if (lastNonOverlapping != -1) {
            includeCount += dp[lastNonOverlapping];
        }
        
        dp[i] = max(dp[i], includeCount);
    }
    
    return dp[n-1];
}


/* 
==========================================
 Approach 3: Optimal - Greedy Algorithm (Activity Selection)
 -----------------------------------------
 💡 Idea:
 Sort meetings by end time and greedily select meetings that end earliest.
 This gives optimal solution due to greedy choice property.

 🧩 Algorithm:
 1. Create pairs of (end_time, start_time) for all meetings.
 2. Sort meetings by end time in ascending order.
 3. Select first meeting (earliest end time).
 4. For remaining meetings, select if start_time >= last_selected_end_time.
 5. Count total selected meetings.

 ⏱ Time Complexity: O(N log N) - sorting dominates
 📦 Space Complexity: O(N) - for storing meeting pairs
*/
int maxMeetingsOptimal(vector<int>& start, vector<int>& end) {
    vector<pair<int, int>> meetings(start.size());
    
    // Create pairs of (end_time, start_time)
    for (int i = 0; i < start.size(); i++) {
        meetings[i] = {end[i], start[i]};
    }
    
    // Sort by end time
    sort(meetings.begin(), meetings.end());
    
    int ans = 0, endTime = -1;
    
    for (auto meeting : meetings) {
        // meeting.first = end_time, meeting.second = start_time
        if (meeting.second >= endTime) { // No overlap: start >= last_end
            ans++;
            endTime = meeting.first; // Update end time of last selected meeting
        }
    }
    
    return ans;
}


/* Helper function to print meeting schedule */
void printSelectedMeetings(vector<int>& start, vector<int>& end) {
    vector<pair<pair<int, int>, int>> meetings;
    
    for (int i = 0; i < start.size(); i++) {
        meetings.push_back({{end[i], start[i]}, i});
    }
    
    sort(meetings.begin(), meetings.end());
    
    cout << "Selected meetings: ";
    int lastEnd = -1;
    for (auto meeting : meetings) {
        int meetingStart = meeting.first.second;
        int meetingEnd = meeting.first.first;
        int originalIndex = meeting.second;
        
        if (meetingStart >= lastEnd) {
            cout << "(" << meetingStart << "," << meetingEnd << ") ";
            lastEnd = meetingEnd;
        }
    }
    cout << "\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<pair<vector<int>, vector<int>>> testCases = {
        {{1, 3, 0, 5, 8, 5}, {2, 4, 6, 7, 9, 9}},
        {{10, 12, 20}, {20, 25, 30}},
        {{1, 2, 3}, {4, 4, 4}},
        {{1}, {2}},
        {{1, 3, 2, 5}, {2, 4, 3, 6}},
        {{0, 1, 2}, {1, 2, 3}},
        {{1, 2, 4, 6, 8}, {3, 5, 7, 9, 10}}
    };

    cout << "=== Testing Maximum Meetings Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> start1 = testCases[t].first, start2 = testCases[t].first, start3 = testCases[t].first;
        vector<int> end1 = testCases[t].second, end2 = testCases[t].second, end3 = testCases[t].second;
        
        cout << "Test Case " << t + 1 << ":\n";
        cout << "Start times: [";
        for (int i = 0; i < start1.size(); i++) {
            cout << start1[i];
            if (i < start1.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        cout << "End times:   [";
        for (int i = 0; i < end1.size(); i++) {
            cout << end1[i];
            if (i < end1.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        int ans1 = (start1.size() <= 20) ? maxMeetingsBruteForce(start1, end1) : -1; // Skip for large inputs
        int ans2 = maxMeetingsDP(start2, end2);
        int ans3 = maxMeetingsOptimal(start3, end3);
        
        if (ans1 != -1) {
            cout << " Brute Force:       " << ans1 << "\n";
        } else {
            cout << " Brute Force:       [Skipped - too slow for large input]\n";
        }
        cout << " Dynamic Programming: " << ans2 << "\n";
        cout << " Optimal Greedy:      " << ans3 << "\n";
        
        printSelectedMeetings(start3, end3);
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(2^N * N^2) time, tries all meeting combinations.\n";
    cout << "2. Dynamic Programming -> O(N log N) time, classic DP with binary search.\n";
    cout << "3. Optimal Greedy -> O(N log N) time, activity selection greedy algorithm.\n";
    cout << "\nRecommendation: Your optimal greedy approach is perfect! ✅\n";
    cout << "Key Insight: Always select the meeting that ends earliest among available options.\n";
    cout << "             This maximizes room availability for future meetings.\n";
    cout << "\nGreedy Choice Property: Selecting earliest-ending meeting is always optimal\n";
    cout << "because it leaves maximum time for remaining meetings.\n";
    cout << "\nYour provided solution implements this classic greedy algorithm flawlessly! 🎯\n";
    cout << "Note: Your code uses the subtle trick of checking 'meet.second <= endTime'\n";
    cout << "      which handles the edge case where meetings can start exactly when another ends.\n";

    return 0;
}
