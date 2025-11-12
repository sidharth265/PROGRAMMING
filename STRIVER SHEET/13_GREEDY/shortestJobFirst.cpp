#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Shortest Job First (SJF) - Average Waiting Time
 GeeksForGeeks Link: https://www.geeksforgeeks.org/program-for-shortest-job-first-or-sjf-cpu-scheduling/

 Problem Statement:
 -----------------
 Given an array of burst times of processes, calculate the average waiting time
 using Shortest Job First (SJF) scheduling algorithm. In SJF, the process with
 the shortest burst time is executed first.

 Example 1:
 Input: bt = [4, 3, 7, 1, 2]
 Output: 4
 Explanation: After sorting: [1, 2, 3, 4, 7]
 Waiting times: [0, 1, 3, 6, 10]
 Average = (0+1+3+6+10)/5 = 4

 Example 2:
 Input: bt = [6, 8, 7, 3]
 Output: 7
 Explanation: After sorting: [3, 6, 7, 8]
 Waiting times: [0, 3, 9, 16]
 Average = (0+3+9+16)/4 = 7

 Example 3:
 Input: bt = [1, 2, 3]
 Output: 1
 Explanation: After sorting: [1, 2, 3]
 Waiting times: [0, 1, 3]
 Average = (0+1+3)/3 = 1

 Constraints:
 - 1 <= bt.length <= 10^5
 - 1 <= bt[i] <= 10^6
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Try All Permutations
 -----------------------------------------
 💡 Idea:
 Generate all possible permutations of process execution order and
 calculate average waiting time for each. Return minimum average.

 🧩 Algorithm:
 1. Generate all N! permutations of processes.
 2. For each permutation, calculate waiting time for each process.
 3. Calculate average waiting time for this permutation.
 4. Keep track of minimum average across all permutations.
 5. Return the minimum average waiting time found.

 ⏱ Time Complexity: O(N! * N) - N! permutations, N time to calculate each
 📦 Space Complexity: O(N) - to store current permutation
*/
int calculateWaitingTime(vector<int>& order) {
    int n = order.size();
    long long totalWaitTime = 0;
    long long currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        totalWaitTime += currentTime; // Waiting time for process i
        currentTime += order[i];      // Process i completes, update current time
    }
    
    return totalWaitTime / n;
}

int avgWaitingTimeBruteForce(vector<int>& bt) {
    vector<int> processes = bt;
    sort(processes.begin(), processes.end());
    
    int minAvgWait = INT_MAX;
    
    // Try all permutations
    do {
        int avgWait = calculateWaitingTime(processes);
        minAvgWait = min(minAvgWait, avgWait);
    } while (next_permutation(processes.begin(), processes.end()));
    
    return minAvgWait;
}


/* 
==========================================
 Approach 2: Better - Greedy with Priority Queue
 -----------------------------------------
 💡 Idea:
 Use a priority queue (min-heap) to always select the process with
 shortest burst time next. Simulate the scheduling process.

 🧩 Algorithm:
 1. Insert all processes into min-heap based on burst time.
 2. While heap is not empty:
    - Extract process with minimum burst time
    - Calculate its waiting time (current_time - 0)
    - Add to total waiting time
    - Update current time
 3. Return average waiting time.

 ⏱ Time Complexity: O(N log N) - heap operations
 📦 Space Complexity: O(N) - priority queue storage
*/
int avgWaitingTimeBetter(vector<int>& bt) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    // Insert all burst times into min-heap
    for (int burstTime : bt) {
        minHeap.push(burstTime);
    }
    
    long long totalWaitTime = 0;
    long long currentTime = 0;
    
    while (!minHeap.empty()) {
        int shortestJob = minHeap.top();
        minHeap.pop();
        
        totalWaitTime += currentTime; // Current process waits for currentTime
        currentTime += shortestJob;   // Update time after this process completes
    }
    
    return totalWaitTime / bt.size();
}


/* 
==========================================
 Approach 3: Optimal - Sort and Calculate
 -----------------------------------------
 💡 Idea:
 Sort processes by burst time (SJF principle). Calculate cumulative
 waiting times efficiently in a single pass.

 🧩 Algorithm:
 1. Sort burst times in ascending order (shortest job first).
 2. For each process (starting from 2nd):
    - Its waiting time = sum of all previous burst times
    - Add to total waiting time
 3. Return average = total waiting time / number of processes.

 ⏱ Time Complexity: O(N log N) - sorting dominates
 📦 Space Complexity: O(1) - only using variables
*/
int avgWaitingTimeOptimal(vector<int>& bt) {
    int n = bt.size();
    long long totalTime = 0;
    long long waitTime = 0;
    
    sort(bt.begin(), bt.end()); // Sort in ascending order (SJF)
    
    // Calculate cumulative waiting times
    for (int i = 1; i < n; i++) {
        waitTime += bt[i-1];    // Add previous process's burst time to wait
        totalTime += waitTime;  // Add this process's waiting time to total
    }
    
    return totalTime / n;
}


/* Helper function to show step-by-step SJF scheduling */
void demonstrateSJF(vector<int>& bt) {
    vector<int> originalBt = bt;
    sort(bt.begin(), bt.end());
    
    cout << "SJF Scheduling demonstration:\n";
    cout << "Original burst times: [";
    for (int i = 0; i < originalBt.size(); i++) {
        cout << originalBt[i];
        if (i < originalBt.size() - 1) cout << ", ";
    }
    cout << "]\n";
    
    cout << "Sorted burst times:   [";
    for (int i = 0; i < bt.size(); i++) {
        cout << bt[i];
        if (i < bt.size() - 1) cout << ", ";
    }
    cout << "]\n\n";
    
    cout << "Process execution:\n";
    long long currentTime = 0;
    long long totalWaitTime = 0;
    
    for (int i = 0; i < bt.size(); i++) {
        cout << "Process " << (i+1) << " (burst=" << bt[i] << "): ";
        cout << "waits " << currentTime << " units, ";
        cout << "executes from " << currentTime << " to " << (currentTime + bt[i]) << "\n";
        
        totalWaitTime += currentTime;
        currentTime += bt[i];
    }
    
    cout << "\nWaiting times: [";
    currentTime = 0;
    for (int i = 0; i < bt.size(); i++) {
        cout << currentTime;
        if (i < bt.size() - 1) cout << ", ";
        currentTime += bt[i];
    }
    cout << "]\n";
    
    cout << "Total waiting time: " << totalWaitTime << "\n";
    cout << "Average waiting time: " << (totalWaitTime / bt.size()) << "\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<vector<int>> testCases = {
        {4, 3, 7, 1, 2},
        {6, 8, 7, 3},
        {1, 2, 3},
        {5},
        {3, 3, 3},
        {10, 1, 5, 2},
        {1, 2, 3, 4, 5}
    };

    cout << "=== Testing Shortest Job First (Average Waiting Time) ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> bt1 = testCases[t], bt2 = testCases[t], bt3 = testCases[t];
        
        cout << "Test Case " << t + 1 << ":\n";
        cout << "Burst Times: [";
        for (int i = 0; i < bt1.size(); i++) {
            cout << bt1[i];
            if (i < bt1.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        int ans1 = (bt1.size() <= 8) ? avgWaitingTimeBruteForce(bt1) : -1; // Skip for large inputs
        int ans2 = avgWaitingTimeBetter(bt2);
        int ans3 = avgWaitingTimeOptimal(bt3);
        
        if (ans1 != -1) {
            cout << " Brute Force:       " << ans1 << "\n";
        } else {
            cout << " Brute Force:       [Skipped - too slow]\n";
        }
        cout << " Priority Queue:    " << ans2 << "\n";
        cout << " Optimal (Your):    " << ans3 << "\n";
        
        demonstrateSJF(bt3);
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N! * N) time, tries all possible execution orders.\n";
    cout << "2. Priority Queue -> O(N log N) time, uses heap for shortest job selection.\n";
    cout << "3. Optimal Sort -> O(N log N) time, direct calculation after sorting.\n";
    cout << "\nRecommendation: Your optimal sorting approach is perfect! ✅\n";
    cout << "Key Insight: SJF scheduling minimizes average waiting time.\n";
    cout << "             Sort processes by burst time, then calculate cumulative waits.\n";
    cout << "\nMathematical Insight:\n";
    cout << "- Process 1: waits 0 (executes immediately)\n";
    cout << "- Process 2: waits bt[0] (waits for process 1)\n";
    cout << "- Process 3: waits bt[0] + bt[1] (waits for processes 1 & 2)\n";
    cout << "- And so on...\n";
    cout << "\nYour provided solution implements this optimal calculation efficiently! 🎯\n";
    cout << "The cumulative sum approach (waitTime += bt[i-1]) is mathematically elegant!\n";

    return 0;
}
