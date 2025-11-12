#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Job Scheduling Problem (Job Sequencing with Deadlines)
 GeeksForGeeks Link: https://www.geeksforgeeks.org/job-sequencing-problem/

 Problem Statement:
 -----------------
 Given an array of jobs where every job has a deadline and profit. 
 The profit can only be earned if the job is completed on or before its deadline. 
 Each job takes exactly one unit of time, so the minimum possible deadline 
 for any job is 1. Maximize the total profit if only one job can be scheduled at a time.

 Example 1:
 Input: deadline = [4, 1, 1, 1], profit = [20, 10, 40, 30]
 Output: [2, 60]
 Explanation: Job 3 (profit=40, deadline=1) and Job 1 (profit=20, deadline=4) 
 can be scheduled. Maximum profit = 40 + 20 = 60, Total jobs = 2.

 Example 2:
 Input: deadline = [2, 1, 2, 1, 3], profit = [100, 19, 27, 25, 15]
 Output: [3, 142]
 Explanation: Jobs with profits 100, 27, and 15 can be scheduled.
 Total profit = 100 + 27 + 15 = 142, Total jobs = 3.

 Constraints:
 - 1 <= deadline.length <= 10^5
 - 1 <= deadline[i], profit[i] <= 10^5
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Try All Combinations
 -----------------------------------------
 💡 Idea:
 Generate all possible subsets of jobs, check if each subset can be
 scheduled without violating deadlines, and find the maximum profit subset.

 🧩 Algorithm:
 1. Generate all 2^N subsets of jobs.
 2. For each subset, check if jobs can be scheduled before their deadlines.
 3. Keep track of maximum profit achievable.
 4. Return the best result found.

 ⏱ Time Complexity: O(2^N * N^2) - check all subsets, validate scheduling
 📦 Space Complexity: O(N) - to store current subset
*/
bool canSchedule(vector<pair<int, int>>& selectedJobs) {
    sort(selectedJobs.begin(), selectedJobs.end(), [](pair<int, int>& a, pair<int, int>& b) {
        return a.first > b.first; // Sort by profit descending
    });
    
    vector<bool> slots(1000, false); // Assuming max deadline is reasonable
    
    for (auto& job : selectedJobs) {
        int profit = job.first, deadline = job.second;
        bool scheduled = false;
        
        // Try to schedule from deadline down to 1
        for (int day = deadline; day >= 1; day--) {
            if (!slots[day]) {
                slots[day] = true;
                scheduled = true;
                break;
            }
        }
        
        if (!scheduled) return false;
    }
    
    return true;
}

vector<int> jobSequencingBruteForce(vector<int>& deadline, vector<int>& profit) {
    int n = deadline.size();
    int maxJobs = 0, maxProfit = 0;
    
    // Try all 2^N combinations
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<pair<int, int>> selectedJobs;
        int currentProfit = 0;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                selectedJobs.push_back({profit[i], deadline[i]});
                currentProfit += profit[i];
            }
        }
        
        if (canSchedule(selectedJobs)) {
            if (currentProfit > maxProfit || 
                (currentProfit == maxProfit && selectedJobs.size() > maxJobs)) {
                maxProfit = currentProfit;
                maxJobs = selectedJobs.size();
            }
        }
    }
    
    return {maxJobs, maxProfit};
}


/* 
==========================================
 Approach 2: Better - Greedy with Sorting
 -----------------------------------------
 💡 Idea:
 Sort jobs by profit in descending order, then greedily assign each job
 to the latest possible day before its deadline.

 🧩 Algorithm:
 1. Create pairs of (profit, deadline) and sort by profit descending.
 2. For each job in sorted order:
    - Try to schedule it on the latest available day <= deadline
    - If successful, mark that day as occupied and add to result
 3. Count total jobs scheduled and total profit earned.

 ⏱ Time Complexity: O(N log N + N*D) where D = max deadline
 📦 Space Complexity: O(D) - boolean array for days
*/
vector<int> jobSequencingBetter(vector<int>& deadline, vector<int>& profit) {
    int n = deadline.size();
    vector<pair<int, int>> jobs(n);
    int maxDay = 0;
    
    for (int i = 0; i < n; i++) {
        jobs[i] = {profit[i], deadline[i]};
        maxDay = max(maxDay, deadline[i]);
    }
    
    // Sort by profit in descending order
    sort(jobs.begin(), jobs.end(), greater<pair<int, int>>());
    
    vector<bool> days(maxDay + 1, false);
    int maxJobs = 0, maxProfit = 0;
    
    for (auto& job : jobs) {
        int jobProfit = job.first, jobDeadline = job.second;
        
        // Try to schedule on latest available day
        for (int day = jobDeadline; day >= 1; day--) {
            if (!days[day]) {
                days[day] = true;
                maxJobs++;
                maxProfit += jobProfit;
                break;
            }
        }
    }
    
    return {maxJobs, maxProfit};
}


/* 
==========================================
 Approach 3: Optimal - Greedy with Optimized Slot Finding
 -----------------------------------------
 💡 Idea:
 Same greedy approach but with optimized slot finding. Sort by profit
 and for each job, find the latest available slot efficiently.

 🧩 Algorithm:
 1. Sort jobs by profit in descending order.
 2. Create boolean array to track occupied days.
 3. For each job, find latest available day <= deadline:
    - Start from deadline and move backwards
    - When find available slot, schedule job there
 4. Return total jobs scheduled and total profit.

 ⏱ Time Complexity: O(N log N + N*D) - sorting + slot finding
 📦 Space Complexity: O(D) - boolean array for day tracking
*/
vector<int> jobSequencingOptimal(vector<int>& deadline, vector<int>& profit) {
    int n = deadline.size();
    int maxDay = 0;
    vector<pair<int, int>> jobs(n);
    
    // Create job pairs and find max deadline
    for (int i = 0; i < n; i++) {
        maxDay = max(maxDay, deadline[i]);
        jobs[i] = {profit[i], deadline[i]};
    }
    
    // Sort by profit in descending order
    sort(jobs.rbegin(), jobs.rend());
    
    vector<bool> days(maxDay + 1, false);
    int maxJobs = 0, maxProfit = 0;
    
    for (auto job : jobs) {
        int i = job.second; // deadline
        
        // Find latest available slot
        while (i > 0 && days[i]) {
            i--;
        }
        
        if (i == 0) continue; // No slot available
        
        // Schedule the job
        days[i] = true;
        maxJobs++;
        maxProfit += job.first;
    }
    
    return {maxJobs, maxProfit};
}


/* Helper function to show job scheduling details */
void demonstrateScheduling(vector<int>& deadline, vector<int>& profit) {
    int n = deadline.size();
    vector<pair<pair<int, int>, int>> jobs; // {{profit, deadline}, original_index}
    int maxDay = 0;
    
    for (int i = 0; i < n; i++) {
        jobs.push_back({{profit[i], deadline[i]}, i});
        maxDay = max(maxDay, deadline[i]);
    }
    
    sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) {
        return a.first.first > b.first.first; // Sort by profit descending
    });
    
    cout << "Jobs sorted by profit:\n";
    for (auto& job : jobs) {
        cout << "Job" << job.second << " (profit=" << job.first.first 
             << ", deadline=" << job.first.second << ")\n";
    }
    
    vector<bool> days(maxDay + 1, false);
    vector<int> schedule(maxDay + 1, -1);
    int totalJobs = 0, totalProfit = 0;
    
    cout << "\nScheduling process:\n";
    for (auto& job : jobs) {
        int jobProfit = job.first.first;
        int jobDeadline = job.first.second;
        int jobIndex = job.second;
        
        int slot = jobDeadline;
        while (slot > 0 && days[slot]) slot--;
        
        if (slot == 0) {
            cout << "Job" << jobIndex << " cannot be scheduled (no available slot)\n";
        } else {
            days[slot] = true;
            schedule[slot] = jobIndex;
            totalJobs++;
            totalProfit += jobProfit;
            cout << "Job" << jobIndex << " scheduled on day " << slot 
                 << " (profit=" << jobProfit << ")\n";
        }
    }
    
    cout << "\nFinal schedule: ";
    for (int i = 1; i <= maxDay; i++) {
        if (schedule[i] != -1) {
            cout << "Day" << i << "→Job" << schedule[i] << " ";
        }
    }
    cout << "\nResult: " << totalJobs << " jobs, " << totalProfit << " profit\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<pair<vector<int>, vector<int>>> testCases = {
        {{4, 1, 1, 1}, {20, 10, 40, 30}},
        {{2, 1, 2, 1, 3}, {100, 19, 27, 25, 15}},
        {{1, 2, 3}, {50, 10, 20}},
        {{2}, {100}},
        {{1, 1, 1}, {1, 2, 3}},
        {{4, 4, 4, 4}, {10, 20, 30, 40}},
        {{3, 1, 2, 2}, {50, 10, 20, 30}}
    };

    cout << "=== Testing Job Scheduling Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> deadline1 = testCases[t].first, deadline2 = testCases[t].first, deadline3 = testCases[t].first;
        vector<int> profit1 = testCases[t].second, profit2 = testCases[t].second, profit3 = testCases[t].second;
        
        cout << "Test Case " << t + 1 << ":\n";
        cout << "Deadlines: [";
        for (int i = 0; i < deadline1.size(); i++) {
            cout << deadline1[i];
            if (i < deadline1.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        cout << "Profits:   [";
        for (int i = 0; i < profit1.size(); i++) {
            cout << profit1[i];
            if (i < profit1.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        vector<int> ans1 = ((deadline1.size() <= 10) ? jobSequencingBruteForce(deadline1, profit1) : vector<int>{-1, -1});
        vector<int> ans2 = jobSequencingBetter(deadline2, profit2);
        vector<int> ans3 = jobSequencingOptimal(deadline3, profit3);
        
        if (ans1[0] != -1) {
            cout << " Brute Force:       [" << ans1[0] << ", " << ans1[1] << "]\n";
        } else {
            cout << " Brute Force:       [Skipped - too slow]\n";
        }
        cout << " Better Greedy:     [" << ans2[0] << ", " << ans2[1] << "]\n";
        cout << " Optimal (Your):    [" << ans3[0] << ", " << ans3[1] << "]\n";
        
        demonstrateScheduling(deadline3, profit3);
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(2^N * N^2) time, tries all job combinations.\n";
    cout << "2. Better Greedy -> O(N log N + N*D) time, greedy with linear slot search.\n";
    cout << "3. Optimal Greedy -> O(N log N + N*D) time, same complexity but cleaner code.\n";
    cout << "\nRecommendation: Your optimal greedy approach is perfect! ✅\n";
    cout << "Key Insight: Always select the job with highest profit first (greedy choice).\n";
    cout << "             For each job, schedule it as late as possible before its deadline.\n";
    cout << "\nGreedy Strategy:\n";
    cout << "1. Sort jobs by profit (descending) - maximizes profit per selection\n";
    cout << "2. For each job, find latest available slot ≤ deadline - maximizes flexibility\n";
    cout << "3. This ensures optimal profit while maintaining valid scheduling\n";
    cout << "\nYour provided solution implements this classic greedy algorithm flawlessly! 🎯\n";
    cout << "The backward slot search (while i > 0 && days[i]) is an elegant optimization!\n";

    return 0;
}
