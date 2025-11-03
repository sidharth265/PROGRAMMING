#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Lemonade Change
 LeetCode Link: https://leetcode.com/problems/lemonade-change/

 Problem Statement:
 -----------------
 At a lemonade stand, each lemonade costs $5. Customers are standing in a queue 
 to buy from you and order one at a time (in the order specified by bills). 
 Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill. 
 You must provide the correct change to each customer so that the net transaction 
 is that the customer pays $5.

 Note that you do not have any change in hand at first.
 Given an integer array bills where bills[i] is the bill the ith customer pays, 
 return true if you can provide every customer with the correct change, or false otherwise.

 Example 1:
 Input: bills = [5,5,5,10,20]
 Output: true
 Explanation: 
 Customer 1: pays $5, gets $0 change.
 Customer 2: pays $5, gets $0 change.
 Customer 3: pays $5, gets $0 change.
 Customer 4: pays $10, gets $5 change. (we have three $5 bills)
 Customer 5: pays $20, gets $15 change. (we give one $10 and one $5)

 Example 2:
 Input: bills = [5,5,10,10,20]
 Output: false
 Explanation:
 Customer 1: pays $5, gets $0 change.
 Customer 2: pays $5, gets $0 change.
 Customer 3: pays $10, gets $5 change.
 Customer 4: pays $10, gets $5 change.
 Customer 5: pays $20, gets $15 change. We cannot give correct change.

 Constraints:
 - 1 <= bills.length <= 10^5
 - bills[i] is either 5, 10, or 20
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Track All Bills
 -----------------------------------------
 💡 Idea:
 Keep track of all bills we have in separate containers and simulate
 the change-making process by trying different combinations.

 🧩 Algorithm:
 1. Use separate counters for each bill denomination.
 2. For each customer:
    - If $5: just add to our collection
    - If $10: need $5 change, check if we have it
    - If $20: need $15 change, try different combinations
 3. Return false if we can't make change at any point.

 ⏱ Time Complexity: O(N) - process each bill once
 📦 Space Complexity: O(1) - only store counts of bill types
*/
bool lemonadeChangeBruteForce(vector<int>& bills) {
    map<int, int> billCount; // denomination -> count
    
    for (int bill : bills) {
        billCount[bill]++;
        
        int changeNeeded = bill - 5;
        
        // Try to make change using largest bills first
        for (int denom : {20, 10, 5}) {
            while (changeNeeded >= denom && billCount[denom] > 0) {
                changeNeeded -= denom;
                billCount[denom]--;
            }
        }
        
        if (changeNeeded > 0) {
            return false; // Cannot make exact change
        }
    }
    
    return true;
}


/* 
==========================================
 Approach 2: Better - Optimized Tracking
 -----------------------------------------
 💡 Idea:
 Since we only have $5, $10, $20 bills, we can optimize by tracking
 only the bills we need for change-making ($5 and $10).

 🧩 Algorithm:
 1. Track count of $5 and $10 bills (we don't need $20 count).
 2. For $5 payment: just increment $5 count.
 3. For $10 payment: need one $5 for change.
 4. For $20 payment: need $15 change, prefer one $10 + one $5.
 5. If cannot make exact change, return false.

 ⏱ Time Complexity: O(N) - process each bill once
 📦 Space Complexity: O(1) - only store two counters
*/
bool lemonadeChangeBetter(vector<int>& bills) {
    int fives = 0, tens = 0;
    
    for (int bill : bills) {
        if (bill == 5) {
            fives++;
        }
        else if (bill == 10) {
            if (fives == 0) return false; // No $5 for change
            fives--;
            tens++;
        }
        else { // bill == 20
            // Need $15 change: prefer $10 + $5, fallback to $5 + $5 + $5
            if (tens > 0 && fives > 0) {
                tens--;
                fives--;
            }
            else if (fives >= 3) {
                fives -= 3;
            }
            else {
                return false; // Cannot make change
            }
        }
    }
    
    return true;
}


/* 
==========================================
 Approach 3: Optimal - Greedy Strategy
 -----------------------------------------
 💡 Idea:
 Use greedy strategy: always prioritize using larger denominations for change
 because $10 bills are less flexible than $5 bills for future transactions.

 🧩 Algorithm:
 1. Track only $5 and $10 bill counts.
 2. For each bill:
    - $5: increment fives count
    - $10: use one $5 for change, increment tens
    - $20: greedily use $10+$5 if possible, else use three $5s
 3. Return false immediately if change cannot be made.

 ⏱ Time Complexity: O(N) - single pass through bills
 📦 Space Complexity: O(1) - only two integer variables
*/
bool lemonadeChangeOptimal(vector<int>& bills) {
    int fives = 0, tens = 0;
    
    for (int bill : bills) {
        if (bill == 5) {
            fives++;
        }
        else if (bill == 10) {
            if (fives == 0) return false;
            fives--;
            tens++;
        }
        else { // bill == 20
            if (fives == 0) return false; // Need at least one $5
            
            if (tens > 0) {
                // Prefer using $10 + $5 (greedy choice)
                tens--;
                fives--;
            }
            else {
                // Use three $5s as fallback
                if (fives < 3) return false;
                fives -= 3;
            }
        }
    }
    
    return true;
}


/* Helper function to simulate the process step by step */
void simulateProcess(vector<int>& bills) {
    int fives = 0, tens = 0;
    cout << "Step-by-step simulation:\n";
    
    for (int i = 0; i < bills.size(); i++) {
        int bill = bills[i];
        cout << "Customer " << (i+1) << " pays $" << bill << " -> ";
        
        if (bill == 5) {
            fives++;
            cout << "No change needed. Have: $5x" << fives << ", $10x" << tens << "\n";
        }
        else if (bill == 10) {
            if (fives == 0) {
                cout << "FAILED! Cannot give $5 change.\n";
                return;
            }
            fives--;
            tens++;
            cout << "Give $5 change. Have: $5x" << fives << ", $10x" << tens << "\n";
        }
        else { // bill == 20
            cout << "Need $15 change -> ";
            if (fives == 0) {
                cout << "FAILED! Need at least one $5.\n";
                return;
            }
            
            if (tens > 0) {
                tens--;
                fives--;
                cout << "Give $10+$5. Have: $5x" << fives << ", $10x" << tens << "\n";
            }
            else {
                if (fives < 3) {
                    cout << "FAILED! Need three $5s but only have " << fives << ".\n";
                    return;
                }
                fives -= 3;
                cout << "Give $5+$5+$5. Have: $5x" << fives << ", $10x" << tens << "\n";
            }
        }
    }
    cout << "SUCCESS! All customers served.\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<vector<int>> testCases = {
        {5, 5, 5, 10, 20},
        {5, 5, 10, 10, 20},
        {5, 5, 10, 20, 5, 5, 5, 5, 5, 5, 5, 5, 5, 10, 5, 5, 20, 5, 20, 5},
        {5},
        {10},
        {20},
        {5, 10},
        {5, 5, 5, 5, 20, 20, 5, 5, 5, 5}
    };

    cout << "=== Testing Lemonade Change Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> bills = testCases[t];
        
        cout << "Test Case " << t + 1 << ":\n";
        cout << "Bills: [";
        for (int i = 0; i < bills.size(); i++) {
            cout << bills[i];
            if (i < bills.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        bool ans1 = lemonadeChangeBruteForce(bills);
        bool ans2 = lemonadeChangeBetter(bills);
        bool ans3 = lemonadeChangeOptimal(bills);
        
        cout << " Brute Force:       " << (ans1 ? "true" : "false") << "\n";
        cout << " Better Approach:   " << (ans2 ? "true" : "false") << "\n";
        cout << " Optimal (Your):    " << (ans3 ? "true" : "false") << "\n";
        
        simulateProcess(bills);
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N) time, uses map to track all denominations.\n";
    cout << "2. Better Approach -> O(N) time, optimized to track only needed bills.\n";
    cout << "3. Optimal Greedy -> O(N) time, uses greedy strategy for change-making.\n";
    cout << "\nRecommendation: Your optimal greedy approach is perfect! ✅\n";
    cout << "Key Insight: Always prefer using $10 bills for $20 transactions because\n";
    cout << "             $5 bills are more flexible for future transactions.\n";
    cout << "\nGreedy Choice: For $20 payment, use $10+$5 rather than $5+$5+$5 when possible.\n";
    cout << "This preserves $5 bills for situations where only $5s can be used.\n";
    cout << "\nYour provided solution implements this optimal strategy perfectly! 🎯\n";

    return 0;
}
