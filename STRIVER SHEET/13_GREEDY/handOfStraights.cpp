#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
Problem Title: Hand of Straights
Problem Link: https://leetcode.com/problems/hand-of-straights

Problem Statement:
Given an array of integers representing cards and a group size W, determine if the cards can be rearranged into groups of consecutive cards of size W.

Example 1:
Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Explanation: The cards can be rearranged as [1,2,3], [2,3,4], [6,7,8]

Example 2:
Input: hand = [1,2,3,4,5], groupSize = 4
Output: false
Explanation: You cannot rearrange the cards into groups of 4 consecutive cards.

=========================================================
*/

/* ------------------------------------------------------
   Approach: Greedy Using Sorted Map
   ------------------------------------------------------
   💡 Idea:
   Use a sorted map to track card counts and greedily form consecutive groups starting from the smallest card.

   🧩 Algorithm:
   1. Check if hand size is divisible by groupSize. If not, return false.
   2. Count occurrences of each card using a sorted map.
   3. While map is not empty:
       a. Get smallest card `start`.
       b. Get count of `start`.
       c. For i from start to start + groupSize - 1:
          - If card i not present or count less than count of start, return false.
          - Decrement card i count by count.
          - If card i count becomes zero, remove it from the map.
   4. If all groups were formed successfully, return true.

   ⏱ Time Complexity: O(N log N) due to sorted map operations
   📦 Space Complexity: O(N)
------------------------------------------------------ */
bool isNStraightHand(vector<int>& hand, int groupSize) {
    int n = hand.size();
    if (n % groupSize != 0) return false;

    map<int, int> m;
    for (int x : hand) m[x]++;

    while (!m.empty()) {
        int start = m.begin()->first;
        int count = m[start];
        for (int i = start; i < start + groupSize; i++) {
            if (m.find(i) == m.end() || m[i] < count) return false;
            m[i] -= count;
            if (m[i] == 0) m.erase(i);
        }
    }
    return true;
}

/* ===================== Main Function ===================== */
int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{1,2,3,6,2,3,4,7,8}, 3},
        {{1,2,3,4,5}, 4},
        {{1,2,3,4,5,6}, 2},
        {{1,2,3,4,5,6}, 3}
    };

    for (int i = 0; i < (int)testCases.size(); i++) {
        const auto& hand = testCases[i].first;
        int groupSize = testCases[i].second;
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Hand: ";
        for (int x : hand) cout << x << " ";
        cout << "\nGroup Size: " << groupSize << "\n";
        bool res = isNStraightHand(const_cast<vector<int>&>(hand), groupSize);
        cout << "Can be rearranged? " << (res ? "Yes" : "No") << "\n\n";
    }

    /* ------------------------------------------------------
       ✅ Approach Overview
       ------------------------------------------------------
       | Method           | Time Complexity | Space Complexity | Notes                       |
       |------------------|-----------------|------------------|-----------------------------|
       | Greedy with Map  | O(N log N)       | O(N)             | Efficient for ordered cards  |
       ------------------------------------------------------
    ------------------------------------------------------ */
    return 0;
}
