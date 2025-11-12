#include <bits/stdc++.h>
using namespace std;

/*
===============================================================
📝 Problem: Minimum Number of Days to Make m Bouquets
---------------------------------------------------------------
Link: https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/

You are given an integer array bloomDay, an integer m and an integer k.

- We need to make "m" bouquets.
- To make one bouquet, we need "k" **adjacent** flowers.
- A flower blooms on bloomDay[i].
- We must wait until at least "m" bouquets can be formed.

Return the **minimum number of days** needed to make m bouquets.
If impossible, return -1.

---------------------------------------------------------------
Example 1:
Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
Output: 3
Explanation: Wait until day 3 → 3 flowers ready → 3 bouquets.

Example 2:
Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
Output: -1
Explanation: Need total 6 flowers, only 5 available ⇒ impossible.
===============================================================
*/


/*
===============================================================
Approach 1: Brute Force
---------------------------------------------------------------
💡 Idea:
- Try each day in range [minDay, maxDay].
- For each day, check if enough bouquets can be formed.

🧩 Algorithm:
1. If total flowers < m*k → impossible → return -1.
2. Find min and max bloom days.
3. For each day from min → max:
   - Count adjacent blooming flowers.
   - Count bouquets formed.
   - If bouquets >= m → return day.
4. If not found → return -1.

⏱ Time Complexity: O(n * (maxDay - minDay))
📦 Space Complexity: O(1)
===============================================================
*/
int minDays(vector<int>& bloomDay, int m, int k) {
    int n = bloomDay.size();
    if(1LL * m * k > n) return -1;

    int low = *min_element(bloomDay.begin(), bloomDay.end());
    int high = *max_element(bloomDay.begin(), bloomDay.end());

    for(int day=low; day<=high; day++) {
        int bouquets = 0, flowers = 0;
        for(int x : bloomDay) {
            if(x <= day) {
                flowers++;
                if(flowers == k) {
                    bouquets++;
                    flowers = 0;
                }
            } else {
                flowers = 0;
            }
        }
        if(bouquets >= m) return day;
    }
    return -1;
}


/*
===============================================================
Approach 2: Better using Set of Unique Days
---------------------------------------------------------------
💡 Idea:
- Instead of iterating through every day from min → max,
  only check bloomDay’s **unique values**.

🧩 Algorithm:
1. If flowers < m*k → return -1.
2. Insert all bloomDay values into a set (unique days).
3. For each unique bloom day in ascending order:
   - Check if we can form m bouquets.
   - Return the first valid day.

⏱ Time Complexity: O(n log n)  (set overhead)
📦 Space Complexity: O(n)       (store unique days)
===============================================================
*/
int minDays2(vector<int>& bloomDay, int m, int k) {
    int n = bloomDay.size();
    if(1LL * m * k > n) return -1;

    set<int> uniqueDays(bloomDay.begin(), bloomDay.end());

    for(int day : uniqueDays) {
        int bouquets = 0, flowers = 0;
        for(int x : bloomDay) {
            if(x <= day) {
                flowers++;
                if(flowers == k) {
                    bouquets++;
                    flowers = 0;
                }
            } else {
                flowers = 0;
            }
        }
        if(bouquets >= m) return day;
    }
    return -1;
}


/*
===============================================================
Approach 3: Optimal (Binary Search)
---------------------------------------------------------------
💡 Idea:
- "If we can form m bouquets on day D, then also possible on day > D."
- This monotonic property ⇒ Binary Search on answer.

🧩 Algorithm:
Helper function `canMake(day)`:
    - Traverse flowers.
    - Count adjacent blooms <= day.
    - Count bouquets formed.
    - Return true if bouquets >= m.

Main:
1. If flowers < m*k → return -1.
2. low = min bloomDay, high = max bloomDay.
3. Binary search:
   - mid = (low+high)/2
   - If canMake(mid) → possible, shrink to find smaller day (high=mid-1).
   - Else → need more days (low=mid+1).
4. Return low (smallest valid day).

⏱ Time Complexity: O(n log(maxDay - minDay))
📦 Space Complexity: O(1)
===============================================================
*/
bool canMake(vector<int>& bloomDay, int m, int k, int day) {
    int bouquets = 0, flowers = 0;
    for(int x : bloomDay) {
        if(x <= day) {
            flowers++;
            if(flowers == k) {
                bouquets++;
                flowers = 0;
            }
        } else {
            flowers = 0;
        }
    }
    return bouquets >= m;
}

int minDays3(vector<int>& bloomDay, int m, int k) {
    int n = bloomDay.size();
    if(1LL * m * k > n) return -1;

    int low = *min_element(bloomDay.begin(), bloomDay.end());
    int high = *max_element(bloomDay.begin(), bloomDay.end());

    while(low <= high) {
        int mid = low + (high-low)/2;
        if(canMake(bloomDay, m, k, mid))
            high = mid - 1; // try earlier day
        else
            low = mid + 1;  // need more days
    }
    return low;
}


/*
===============================================================
Example Usage
===============================================================
*/
int main() {
    vector<int> bloomDay = {1,10,3,10,2};
    
    int m = 3, k = 1;
    cout << "Brute: " << minDays(bloomDay, m, k) << endl;   // 3
    cout << "Better: " << minDays2(bloomDay, m, k) << endl; // 3
    cout << "Optimal: " << minDays3(bloomDay, m, k) << endl; // 3

    m = 3; k = 2;
    cout << "Brute: " << minDays(bloomDay, m, k) << endl;   // -1
    cout << "Better: " << minDays2(bloomDay, m, k) << endl; // -1
    cout << "Optimal: " << minDays3(bloomDay, m, k) << endl; // -1

    /*
    ===========================================================
    ✅ Approach Overview (Comparison)
    -----------------------------------------------------------
    1. Brute Force:
       - Try all days sequentially.
       - Time: O(n * (maxDay-minDay)), Space: O(1)

    2. Better (Unique Days in Set):
       - Check only unique bloom days.
       - Time: O(n log n), Space: O(n)

    3. Optimal (Binary Search):
       - Binary search the answer.
       - Time: O(n log(maxDay-minDay)), Space: O(1)

    🔑 Conclusion:
    - Brute: Easy, but slow if range of days is huge.
    - Better: Avoids useless days, faster than brute.
    - Optimal: Best for large inputs, uses Binary Search.
    ===========================================================
    */
    return 0;
}
