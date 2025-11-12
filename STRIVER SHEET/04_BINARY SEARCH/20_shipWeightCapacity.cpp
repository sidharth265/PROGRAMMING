#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Capacity To Ship Packages Within D Days
---------------------------------------------------------------
Link: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/

You are given an array `weights` where weights[i] is the weight of the i-th package, 
and an integer `days`.

We need to ship all packages in exactly `days` days using a ship with minimum
possible capacity. Rules:
1. Each day, ship packages in order (can’t reorder).
2. Capacity must be at least max(weights).
3. We need to minimize capacity.

---------------------------------------------------------------
Example:
Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15

Explanation:
If capacity = 15:
  Day 1 → [1,2,3,4,5] = 15
  Day 2 → [6,7]       = 13
  Day 3 → [8]         = 8
  Day 4 →          = 9
  Day 5 →         = 10
Satisfies condition with minimum capacity.
===============================================================
*/


/*
===============================================================
Helper Function `canShip`
---------------------------------------------------------------
Check if given capacity allows shipping in <= days.

- Start with empty day load.
- Add packages sequentially until exceeding capacity.
- Then allocate next day and reset load.
- Count days needed.
===============================================================
*/
bool canShip(vector<int>& weights, int days, int capacity) {
    int usedDays = 1;  // start with day 1
    int currentLoad = 0;
    for (int w : weights) {
        if (currentLoad + w <= capacity) {
            currentLoad += w;
        } else {
            usedDays++;
            currentLoad = w;
        }
        if (usedDays > days) return false;
    }
    return true;
}


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Try every capacity from [max(weights), sum(weights)].
- For each capacity, check if possible in days.
- First valid capacity = answer.

⏱ Time Complexity: O(n * (sum-max))
📦 Space Complexity: O(1)
===============================================================
*/
int shipWithinDays(vector<int>& weights, int days) {
    int low = *max_element(weights.begin(), weights.end());
    int high = accumulate(weights.begin(), weights.end(), 0);

    for (int cap = low; cap <= high; cap++) {
        if (canShip(weights, days, cap)) return cap;
    }
    return -1;
}


/*
===============================================================
Approach 2: Binary Search (Optimal)
---------------------------------------------------------------
💡 Idea:
- Our answer lies in range [max(weights), sum(weights)].
- If mid capacity works, try smaller (search left).
- Otherwise, increase capacity (search right).

⏱ Time Complexity: O(n * log(sum(weights)))
📦 Space Complexity: O(1)
===============================================================
*/
int shipWithinDays2(vector<int>& weights, int days) {
    int low = *max_element(weights.begin(), weights.end());
    int high = accumulate(weights.begin(), weights.end(), 0);
    int ans = high;

    while (low <= high) {
        int mid = low + (high - low)/2;
        if (canShip(weights, days, mid)) {
            ans = mid;
            high = mid - 1; // try smaller capacity
        } else {
            low = mid + 1;  // need more capacity
        }
    }
    return ans;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> weights = {1,2,3,4,5,6,7,8,9,10};
    int days = 5;

    cout << "Brute Force: " 
         << shipWithinDays(weights, days) << endl; // Expected 15

    cout << "Binary Search: " 
         << shipWithinDays2(weights, days) << endl; // Expected 15

    /*
    ===========================================================
    ✅ Approach Overview
    -----------------------------------------------------------
    1. Brute Force:
       - Try all capacities in [maxWeight, sumWeight].
       - Time: O(n*(sum-max)).
       - Too slow for big inputs.

    2. Binary Search (Optimal):
       - Search capacity space with mid.
       - Each check: O(n).
       - Time: O(n log(sum(weights))), Space O(1).
       - 🏆 Accepted optimal solution.
    ===========================================================
    */

    return 0;
}
