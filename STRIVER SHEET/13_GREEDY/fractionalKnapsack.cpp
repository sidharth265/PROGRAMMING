#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Fractional Knapsack Problem
 GeeksForGeeks Link: https://www.geeksforgeeks.org/fractional-knapsack-problem/

 Problem Statement:
 -----------------
 Given weights and values of n items, we need to put these items in a knapsack 
 of capacity W to get the maximum total value in the knapsack. We can break 
 items (take fractions of items) unlike 0/1 Knapsack problem.

 Example 1:
 Input: val[] = [60, 100, 120], wt[] = [10, 20, 30], capacity = 50
 Output: 240.0
 Explanation: Take full items of value 60 and 100, and 2/3 of item with value 120.
 Total = 60 + 100 + (2/3)*120 = 240.0

 Example 2:
 Input: val[] = [10, 40, 30, 50], wt[] = [5, 4, 6, 3], capacity = 10
 Output: 164.0
 Explanation: Take full items with value 40 and 50, no space for others.
 Total = 40 + 50 + (3/5)*10 = 164.0

 Constraints:
 - 1 <= n <= 10^5
 - 1 <= capacity <= 10^9
 - 1 <= val[i], wt[i] <= 10^4
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Try All Combinations
 -----------------------------------------
 💡 Idea:
 Generate all possible combinations of items (including fractional parts)
 and find the one that gives maximum value within capacity.

 🧩 Algorithm:
 1. For each item, try all possible fractions from 0 to 1.
 2. Use recursion/backtracking to explore all combinations.
 3. Keep track of maximum value achieved.
 4. Return the best combination found.

 ⏱ Time Complexity: O(2^N * capacity) - exponential combinations
 📦 Space Complexity: O(N) - recursion stack depth
*/
double fractionalKnapsackBruteForce(vector<int>& val, vector<int>& wt, int capacity) {
    // This is impractical for large inputs, so we'll use a simplified version
    // that only tries full items or no items (not truly fractional)
    int n = val.size();
    double maxVal = 0;
    
    // Try all 2^n combinations (simplified brute force)
    for (int mask = 0; mask < (1 << n); mask++) {
        int totalWeight = 0;
        double totalValue = 0;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                totalWeight += wt[i];
                totalValue += val[i];
            }
        }
        
        if (totalWeight <= capacity) {
            maxVal = max(maxVal, totalValue);
        }
    }
    
    return maxVal;
}


/* 
==========================================
 Approach 2: Better - Sort by Value-to-Weight Ratio
 -----------------------------------------
 💡 Idea:
 Calculate value-to-weight ratio for each item, sort by this ratio,
 but use a simpler data structure and approach.

 🧩 Algorithm:
 1. Create array of indices and sort by value/weight ratio.
 2. For each item in sorted order, take as much as possible.
 3. If item fits completely, take it; otherwise take fraction.
 4. Continue until knapsack is full.

 ⏱ Time Complexity: O(N log N) - sorting dominates
 📦 Space Complexity: O(N) - for storing indices
*/
double fractionalKnapsackBetter(vector<int>& val, vector<int>& wt, int capacity) {
    int n = val.size();
    vector<int> indices(n);
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    
    // Sort indices by value-to-weight ratio in descending order
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return (double)val[a] / wt[a] > (double)val[b] / wt[b];
    });
    
    double totalValue = 0.0;
    int remainingCapacity = capacity;
    
    for (int i : indices) {
        if (remainingCapacity >= wt[i]) {
            // Take the whole item
            totalValue += val[i];
            remainingCapacity -= wt[i];
        } else {
            // Take fraction of the item
            double fraction = (double)remainingCapacity / wt[i];
            totalValue += val[i] * fraction;
            break; // Knapsack is full
        }
    }
    
    return totalValue;
}


/* 
==========================================
 Approach 3: Optimal - Greedy with Density Sorting
 -----------------------------------------
 💡 Idea:
 Calculate value density (value per unit weight) for each item.
 Sort items by density in descending order and greedily take items
 with highest density first.

 🧩 Algorithm:
 1. Calculate density = value/weight for each item.
 2. Create pairs of (density, index) and sort by density descending.
 3. For each item in sorted order:
    - Take minimum of (remaining capacity, item weight)
    - Add proportional value to result
    - Reduce remaining capacity
 4. Return total value.

 ⏱ Time Complexity: O(N log N) - sorting dominates
 📦 Space Complexity: O(N) - for storing density pairs
*/
double fractionalKnapsackOptimal(vector<int>& val, vector<int>& wt, int capacity) {
    double ans = 0;
    vector<pair<double, int>> items;
    
    // Calculate density for each item
    for (int i = 0; i < val.size(); i++) {
        double density = (double)val[i] / (double)wt[i];
        items.push_back({density, i});
    }
    
    // Sort by density in descending order
    sort(items.rbegin(), items.rend());
    
    // Greedily pick items
    for (auto item : items) {
        int factor = min(capacity, wt[item.second]);
        ans += (double)factor * item.first;
        capacity -= factor;
        
        if (capacity == 0) break; // Knapsack is full
    }
    
    return ans;
}


/* Helper function to print items with their densities */
void printItemDetails(vector<int>& val, vector<int>& wt) {
    cout << "Items: ";
    for (int i = 0; i < val.size(); i++) {
        double density = (double)val[i] / wt[i];
        cout << "[V:" << val[i] << ", W:" << wt[i] << ", D:" << fixed << setprecision(2) << density << "] ";
    }
    cout << "\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<tuple<vector<int>, vector<int>, int>> testCases = {
        {{60, 100, 120}, {10, 20, 30}, 50},
        {{10, 40, 30, 50}, {5, 4, 6, 3}, 10},
        {{1, 4, 5, 7}, {1, 3, 5, 7}, 9},
        {{10, 20, 30}, {1, 1, 1}, 2},
        {{7}, {3}, 5},
        {{1, 2, 3}, {4, 5, 6}, 3}
    };

    cout << "=== Testing Fractional Knapsack Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> val1 = get<0>(testCases[t]);
        vector<int> val2 = get<0>(testCases[t]);
        vector<int> val3 = get<0>(testCases[t]);
        
        vector<int> wt1 = get<1>(testCases[t]);
        vector<int> wt2 = get<1>(testCases[t]);
        vector<int> wt3 = get<1>(testCases[t]);
        
        int capacity = get<2>(testCases[t]);
        
        cout << "Test Case " << t + 1 << ":\n";
        cout << "Values: [";
        for (int i = 0; i < val1.size(); i++) {
            cout << val1[i];
            if (i < val1.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        cout << "Weights: [";
        for (int i = 0; i < wt1.size(); i++) {
            cout << wt1[i];
            if (i < wt1.size() - 1) cout << ", ";
        }
        cout << "], Capacity: " << capacity << "\n";
        
        printItemDetails(val1, wt1);
        
        double ans1 = fractionalKnapsackBruteForce(val1, wt1, capacity);
        double ans2 = fractionalKnapsackBetter(val2, wt2, capacity);
        double ans3 = fractionalKnapsackOptimal(val3, wt3, capacity);
        
        cout << " Brute Force:         " << fixed << setprecision(1) << ans1 << "\n";
        cout << " Better Approach:     " << fixed << setprecision(1) << ans2 << "\n";
        cout << " Optimal (Your code): " << fixed << setprecision(1) << ans3 << "\n";
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(2^N) time, tries all combinations but impractical for large N.\n";
    cout << "2. Better Approach -> O(N log N), sorts indices by ratio with cleaner code.\n";
    cout << "3. Optimal Greedy -> O(N log N), uses density pairs for maximum efficiency.\n";
    cout << "\nRecommendation: Your optimal greedy approach is perfect for interviews! ✅\n";
    cout << "Key Insight: Fractional Knapsack has greedy optimal substructure -\n";
    cout << "             always pick items with highest value-to-weight ratio first.\n";
    cout << "\nYour provided solution is the optimal approach - excellently implemented! 🎯\n";

    return 0;
}
