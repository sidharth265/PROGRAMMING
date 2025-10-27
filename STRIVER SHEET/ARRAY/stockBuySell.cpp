#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Best Time to Buy and Sell Stock (Single Transaction)

Problem Statement:
Given an integer array prices where prices[i] is the price of a stock on day i,
return the maximum profit that can be achieved from a single buy-sell transaction.
The buy must occur before the sell. If no profit is possible, return 0.

Example:
Input:  prices = [7, 1, 5, 3, 6, 4]
Output: 5
Explanation: Buy at price=1 (day 1), sell at price=6 (day 4), profit = 6 - 1 = 5.

Approach Overview:
- Single-pass tracking:
  - Keep the minimum price seen so far (mini).
  - At each day i, potential profit = prices[i] - mini.
  - Update the global maximum profit and mini as you go.

----------------------------------------
Approach: Single Pass with Running Minimum
Approach Idea:
- The best sell today is at prices[i]; to maximize profit, buy at the smallest price seen before today.
- Maintain mini = min(previous mini, prices[i]) and profit = max(previous profit, prices[i] - mini).

Algorithm:
1) Initialize mini = prices[0], profit = 0
2) For i from 1 to n-1:
   - cost = prices[i] - mini
   - profit = max(profit, cost)
   - mini = min(mini, prices[i])
3) Return profit

Time Complexity: O(n)
Space Complexity: O(1)
*/
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int profit = 0;
    int mini = prices[0];
    for (int i = 1; i < n; i++) {
        int cost = prices[i] - mini;
        profit = max(profit, cost);
        mini = min(mini, prices[i]);
    }
    return profit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Maximum profit: " << maxProfit(prices) << "\n";
    return 0;
}
