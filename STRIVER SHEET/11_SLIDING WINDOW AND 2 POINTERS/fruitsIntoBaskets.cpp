#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Fruit Into Baskets
 Problem Link: https://leetcode.com/problems/fruit-into-baskets/

 Problem Statement:
 You are given an integer array `fruits` where `fruits[i]` represents 
 the type of fruit at index `i`. 

 You are standing at some position, starting to pick fruits into baskets.  
 Each basket can only hold **one type of fruit**, and you can only carry **two baskets** at a time.  

 Return the maximum number of fruits you can collect in a row (i.e., the 
 length of the longest contiguous subarray containing at most two distinct values).

-------------------------------------------------
 Example 1:
 Input: fruits = [1,2,1,2,3]
 Output: 4
 Explanation: Pick subarray [1,2,1,2] which contains 2 types {1,2}, length = 4.

 Example 2:
 Input: fruits = [0,1,2,2]
 Output: 3
 Explanation: Pick subarray [1,2,2] of length 3.

 Example 3:
 Input: fruits = [1,2,3,2,2]
 Output: 4
 Explanation: Pick subarray [2,3,2,2] of length 4.
-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force
// -------------------------------------------------
/*
💡 Idea:
   - For each starting index `i`, expand subarray as far as possible
     while the set of distinct fruit types ≤ 2.
   - Track the maximum length seen.

🧩 Algorithm:
   1. Initialize ans = 0.
   2. For i from 0 to n-1:
         - Reset an empty set and length counter.
         - Expand j from i forward.
         - Add fruit[j] into set.
         - If set size > 2 → break.
         - Else update length.
   3. Return maximum length.

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(1) extra (set holds ≤ 3 types)
*/

int totalFruitBrute(vector<int>& fruits) {
    int ans = 0;
    int n = fruits.size();
    for (int i = 0; i < n; i++) {
        unordered_set<int> s;
        int len = 0;
        for (int j = i; j < n; j++) {
            s.insert(fruits[j]);
            if ((int)s.size() > 2) break;
            len++;
        }
        ans = max(ans, len);
    }
    return ans;
}


// -------------------------------------------------
// Approach 2: Sliding Window (HashMap)
// -------------------------------------------------
/*
💡 Idea:
   - Use two pointers to maintain window [l..r].
   - Expand r while ≤ 2 types.
   - If > 2 types, shrink l until window valid again.
   - Track max window size.

🧩 Algorithm:
   1. Initialize l = 0, ans = 0, hashmap `freq` for counts.
   2. For each r in [0..n-1]:
        - Increase freq[fruits[r]].
        - While freq.size() > 2:
            - Reduce freq[fruits[l]].
            - If count = 0, erase key.
            - Increment l.
        - Update ans = max(ans, r-l+1).
   3. Return ans.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1) (map holds ≤ 3 keys)
*/

int totalFruitSlidingWindow(vector<int>& fruits) {
    int n = fruits.size();
    int l = 0, ans = 0;
    unordered_map<int,int> freq;

    for (int r = 0; r < n; r++) {
        freq[fruits[r]]++;
        while (freq.size() > 2) {
            int f = fruits[l];
            if (--freq[f] == 0) freq.erase(f);
            l++;
        }
        ans = max(ans, r-l+1);
    }
    return ans;
}


// -------------------------------------------------
// Approach 3: Optimal O(1) State Tracking
// -------------------------------------------------
/*
💡 Idea:
   - Track the **last fruit type**, the **second last type**, and how many 
     of the "last" type appear consecutively at the end of window.
   - Maintain current window length with at most 2 types.
   - Smartly reset window length when a third type introduces.

🧩 Algorithm:
   1. Initialize:
        - last = -1, secondLast = -1
        - lastCount = 0, curr = 0, maxFruits = 0
   2. For each fruit f:
        - If f == last || f == secondLast:
              curr++
          Else:
              curr = lastCount + 1   (keep only last streak + new fruit)
        - If f == last:
              lastCount++
          Else:
              lastCount = 1
              secondLast = last
              last = f
        - maxFruits = max(maxFruits, curr)
   3. Return maxFruits.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/

int totalFruitOptimal(vector<int>& fruits) {
    int last = -1, secondLast = -1;
    int lastCount = 0, curr = 0, maxFruits = 0;

    for (int f : fruits) {
        if (f == last || f == secondLast) curr++;
        else curr = lastCount + 1;

        if (f == last) lastCount++;
        else {
            lastCount = 1;
            secondLast = last;
            last = f;
        }
        maxFruits = max(maxFruits, curr);
    }
    return maxFruits;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<vector<int>> testCases = {
        {1,2,1,2,3},
        {0,1,2,2},
        {1,2,3,2,2},
        {1,1,1,1},
        {3,3,3,1,2,1,1,2,3,3,4}
    };

    for (auto &fruits : testCases) {
        cout << "Fruits: ";
        for (int f : fruits) cout << f << " ";
        cout << "\n";

        cout << "Brute Force: " << totalFruitBrute(fruits) << "\n";
        cout << "Sliding Window: " << totalFruitSlidingWindow(fruits) << "\n";
        cout << "Optimal Tracker: " << totalFruitOptimal(fruits) << "\n";
        cout << "-----------------------------\n";
    }

    // -------------------------------------------------
    // ✅ Approach Overview
    // -------------------------------------------------
    /*
    Approach 1 (Brute Force):      TC = O(n^2), SC = O(1)
    Approach 2 (Sliding Window):   TC = O(n),   SC = O(1)
    Approach 3 (Optimal Tracker):  TC = O(n),   SC = O(1),
                                   simpler than HashMap
    */

    return 0;
}
