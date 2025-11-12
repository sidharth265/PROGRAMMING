#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Minimum Number of Coins (Change Making Problem)
 GeeksForGeeks Link: https://www.geeksforgeeks.org/greedy-algorithm-to-find-minimum-number-of-coins/

 Problem Statement:
 -----------------
 Given a value n, find the minimum number of coins that make change for n cents.
 We have infinite supply of each coin denomination.
 For Indian currency system: coins = {1, 2, 5, 10}

 Example 1:
 Input: n = 43
 Output: 6
 Explanation: 43 = 10*4 + 2*1 + 1*1 = 40 + 2 + 1 (6 coins total)

 Example 2:
 Input: n = 18
 Output: 4  
 Explanation: 18 = 10*1 + 5*1 + 2*1 + 1*1 = 10 + 5 + 2 + 1 (4 coins total)

 Example 3:
 Input: n = 7
 Output: 2
 Explanation: 7 = 5*1 + 2*1 = 5 + 2 (2 coins total)

 Constraints:
 - 1 <= n <= 10^9
 - Coin denominations: {1, 2, 5, 10} (Indian currency)
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Recursive with All Combinations
 -----------------------------------------
 💡 Idea:
 Try all possible combinations of coins recursively. For each coin denomination,
 try using 0, 1, 2, ... coins of that type and recurse for remaining amount.

 🧩 Algorithm:
 1. For current amount, try each coin denomination.
 2. For each coin, try using it 0 to n/coin times.
 3. Recursively solve for remaining amount.
 4. Return minimum coins needed across all combinations.
 5. Use memoization to avoid recomputation.

 ⏱ Time Complexity: O(n^k) where k = number of coin types
 📦 Space Complexity: O(n) - recursion stack + memoization
*/
int getMinBruteForceHelper(int n, vector<int>& coins, vector<int>& memo) {
    if (n == 0) return 0;
    if (n < 0) return INT_MAX;
    if (memo[n] != -1) return memo[n];
    
    int minCoins = INT_MAX;
    
    for (int coin : coins) {
        int result = getMinBruteForceHelper(n - coin, coins, memo);
        if (result != INT_MAX) {
            minCoins = min(minCoins, result + 1);
        }
    }
    
    return memo[n] = minCoins;
}

int getMinBruteForce(int n) {
    vector<int> coins = {10, 5, 2, 1};
    vector<int> memo(n + 1, -1);
    return getMinBruteForceHelper(n, coins, memo);
}


/* 
==========================================
 Approach 2: Better - Dynamic Programming
 -----------------------------------------
 💡 Idea:
 Use bottom-up DP where dp[i] represents minimum coins needed for amount i.
 For each amount, try all coin denominations and take minimum.

 🧩 Algorithm:
 1. Create dp array where dp[i] = min coins for amount i.
 2. Initialize dp[0] = 0, others = infinity.
 3. For each amount from 1 to n:
    - Try each coin denomination
    - dp[i] = min(dp[i], dp[i-coin] + 1)
 4. Return dp[n].

 ⏱ Time Complexity: O(n * k) where k = number of coin types
 📦 Space Complexity: O(n) - DP array
*/
int getMinDP(int n) {
    vector<int> coins = {10, 5, 2, 1};
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int coin : coins) {
            if (i >= coin && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[n];
}


/* 
==========================================
 Approach 3: Optimal - Greedy Algorithm
 -----------------------------------------
 💡 Idea:
 For Indian currency system {1, 2, 5, 10}, greedy approach works optimally.
 Always pick the largest coin that doesn't exceed the remaining amount.

 🧩 Algorithm:
 1. Sort coins in descending order.
 2. For each coin denomination:
    - Use as many coins of this type as possible
    - Add count to result
    - Reduce remaining amount
 3. Continue until amount becomes 0.

 ⏱ Time Complexity: O(k) where k = number of coin types
 📦 Space Complexity: O(1) - only using variables
*/
int getMinGreedy(int n) {
    vector<int> coins = {10, 5, 2, 1};
    int ans = 0;
    
    for (int coin : coins) {
        ans += n / coin;        // Add number of coins of this denomination
        n %= coin;              // Reduce remaining amount
        if (n == 0) break;      // Early termination if done
    }
    
    return ans;
}

// Alternative cleaner version of the same greedy approach
int getMinGreedyClean(int n) {
    vector<int> coins = {10, 5, 2, 1};
    int ans = 0;
    
    for (int coin : coins) {
        if (n >= coin) {
            ans += n / coin;
            n %= coin;
        }
    }
    
    return ans;
}


/* Helper function to show coin breakdown */
void showCoinBreakdown(int n) {
    vector<int> coins = {10, 5, 2, 1};
    vector<string> names = {"10-rupee", "5-rupee", "2-rupee", "1-rupee"};
    
    cout << "Breakdown for n = " << n << ": ";
    for (int i = 0; i < coins.size(); i++) {
        int count = n / coins[i];
        if (count > 0) {
            cout << count << "x" << names[i] << " ";
        }
        n %= coins[i];
    }
    cout << "\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<int> testCases = {43, 18, 7, 1, 2, 5, 10, 15, 23, 99, 100};

    cout << "=== Testing Minimum Number of Coins Problem ===\n\n";
    
    for (int n : testCases) {
        cout << "Input: n = " << n << "\n";
        showCoinBreakdown(n);
        
        int ans1 = getMinBruteForce(n);
        int ans2 = getMinDP(n);
        int ans3 = getMinGreedy(n);
        
        cout << " Brute Force (Memoized): " << ans1 << "\n";
        cout << " Dynamic Programming:    " << ans2 << "\n";
        cout << " Greedy (Your code):     " << ans3 << "\n";
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(n^k) with memoization, explores all possibilities.\n";
    cout << "2. Dynamic Programming -> O(n*k), works for any coin system.\n";
    cout << "3. Greedy -> O(k), optimal ONLY for canonical coin systems like {1,2,5,10}.\n";
    cout << "\nRecommendation: Your greedy approach is perfect for Indian currency! ✅\n";
    cout << "Key Insight: Greedy works for canonical coin systems where larger denominations\n";
    cout << "             are multiples of smaller ones, guaranteeing optimal substructure.\n";
    cout << "\nNote: For arbitrary coin systems, DP would be required, but for standard\n";
    cout << "      currency systems (like Indian coins), greedy is both optimal and efficient.\n";
    cout << "\nYour provided solution is the optimal greedy approach - perfectly implemented! 🎯\n";

    return 0;
}
