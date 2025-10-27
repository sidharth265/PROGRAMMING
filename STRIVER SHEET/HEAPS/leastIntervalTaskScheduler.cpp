#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Task Scheduler
Problem Link: https://leetcode.com/problems/task-scheduler

Problem Statement:
Given a list of tasks represented by characters, and a non-negative cooling interval n,
determine the least number of units of times that the CPU will take to finish all the given tasks. 
Tasks of the same kind must be separated by at least n units of time.

Example 1:
Input: tasks = ['A','A','A','B','B','B'], n = 2
Output: 8
Explanation: One possible scheduling is A -> B -> idle -> A -> B -> idle -> A -> B

Example 2:
Input: tasks = ['A','A','A','A','B','B','B','C','C','D','D'], n = 2
Output: 11

=========================================================
*/

/* ------------------------------------------------------
   Approach 1: Simulation with Priority Queue and Cooldown Queue
   ------------------------------------------------------
   💡 Idea:
   Use a max-heap to always pick the most frequent available task.
   After executing a task, put it in a cooldown queue to wait for `n` units before reuse.

   🧩 Algorithm:
   1. Count frequencies of tasks.
   2. Push all frequencies into a max-heap.
   3. For each time unit:
      a. Pop the most frequent task from max-heap.
      b. Decrement frequency and put in cooldown with timer.
      c. When cooldown expires, push frequency back to max-heap.
   4. Count total time steps until all tasks finish.

   ⏱ Time Complexity: O(T log K), T = #tasks, K = distinct tasks
   📦 Space Complexity: O(K)
------------------------------------------------------ */
int leastIntervalSimulation(vector<char>& tasks, int n) {
    unordered_map<char, int> freq;
    for (char t : tasks) freq[t]++;

    priority_queue<int> maxHeap;
    for (auto& it : freq) maxHeap.push(it.second);

    queue<pair<int, int>> cooldown;
    int time = 0;

    while (!maxHeap.empty() || !cooldown.empty()) {
        time++;
        if (!maxHeap.empty()) {
            int count = maxHeap.top();
            maxHeap.pop();
            count--;
            if (count > 0) cooldown.push({count, time + n});
        }
        if (!cooldown.empty() && cooldown.front().second == time) {
            maxHeap.push(cooldown.front().first);
            cooldown.pop();
        }
    }
    return time;
}

/* ------------------------------------------------------
   Approach 2: Mathematical Formula (Optimal)
   ------------------------------------------------------
   💡 Idea:
   Arrange the most frequent tasks first with proper intervals.
   Calculate the minimum length based on max frequency and how many tasks have that max frequency.

   🧩 Algorithm:
   1. Count frequencies of tasks.
   2. Find max frequency (maxFreq).
   3. Count how many tasks have maxFreq (maxCount).
   4. Calculate minimum length:
       least = (maxFreq - 1) * (n + 1) + maxCount
   5. Result is max of least and total tasks length.

   ⏱ Time Complexity: O(T)
   📦 Space Complexity: O(K)
------------------------------------------------------ */
int leastIntervalFormula(vector<char>& tasks, int n) {
    unordered_map<char, int> freq;
    for (char ch : tasks) freq[ch]++;
    int maxFreq = 0, maxCount = 0;
    for (auto& it : freq) {
        if (it.second > maxFreq) {
            maxFreq = it.second;
            maxCount = 1;
        } else if (it.second == maxFreq) {
            maxCount++;
        }
    }
    int least = (maxFreq - 1) * (n + 1) + maxCount;
    return max((int)tasks.size(), least);
}

/* ===================== Main Function ===================== */
int main() {
    vector<pair<vector<char>, int>> testCases = {
        {{'A','A','A','B','B','B'}, 2},
        {{'A','A','A','A','B','B','B','C','C','D','D'}, 2},
        {{'A','A','A','A','A','A','B','C','D','E','F','G'}, 2},
    };

    for (int i = 0; i < (int)testCases.size(); i++) {
        const auto& tasks = testCases[i].first;
        int n = testCases[i].second;
        cout << "Test Case " << i+1 << ":\n";
        cout << "Tasks: ";
        for (char t : tasks) cout << t << " ";
        cout << "\nCooldown n = " << n << "\n";

        int res1 = leastIntervalSimulation(const_cast<vector<char>&>(tasks), n);
        int res2 = leastIntervalFormula(const_cast<vector<char>&>(tasks), n);

        cout << "Simulation Result: " << res1 << endl;
        cout << "Formula Result   : " << res2 << endl << endl;
    }

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method         | Time Complexity | Space Complexity | Notes                     |
       |----------------|-----------------|------------------|---------------------------|
       | Simulation     | O(T log K)      | O(K)             | Easier to understand      |
       | Mathematical   | O(T)            | O(K)             | Efficient, optimal formula |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}

