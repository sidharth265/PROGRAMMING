#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Koko Eating Bananas

Problem Statement:
Given an integer array piles where piles[i] is the number of bananas in the i-th pile, and an integer h (hours),
return the minimum integer eating speed k (bananas per hour) such that Koko can eat all the bananas within h hours.
Each hour she chooses one pile and eats up to k bananas from that pile; if the pile has fewer than k bananas, she eats all of them.
She cannot split an hour across multiple piles.

Examples:
- piles = [3,6,7,11], h = 8  ->  4
- piles = [30,11,23,4,20], h = 5  ->  30

Approach Overview:
- Brute Force: Try speeds from 1 to max(piles) and check feasibility by summing ceil(pile / speed) over piles. O(n * max(piles)).
- Binary Search on Answer (Recommended): The predicate “speed k is sufficient” is monotone.
  Binary search k in [1, max(piles)] and check total hours for mid. O(n log max(piles)).
*/

/*
Approach: Brute Force
Approach Idea:
- The minimum feasible speed is at least 1 and at most max(piles).
- For each speed s from 1..max_pile, compute total hours needed as sum(ceil(pile/s)).
- Return the first speed that finishes within h hours.

Algorithm:
1) max_pile = max(piles)
2) For s in [1..max_pile]:
   - hours = sum over piles of ceil(pile / s)
   - If hours <= h: return s
3) Return -1 (should not happen if h >= piles.size())

Time Complexity: O(n * max(piles))
Space Complexity: O(1)
*/
int minEatingSpeed(vector<int>& piles, int h) {
    int max_pile = *max_element(piles.begin(), piles.end());
    for (int s = 1; s <= max_pile; s++) {
        long long hours = 0;
        for (int pile : piles) {
            // ceil(pile / s) without floating point: (pile + s - 1) / s
            hours += (pile + s - 1) / s;
            if (hours > h) break;
        }
        if (hours <= h) return s;
    }
    return -1;
}

/*
Approach: Binary Search on Speed (Optimal)
Approach Idea:
- Define feasible(s): sum(ceil(pile/s)) over piles <= h.
- Since feasible is monotone (if s works, any s' >= s works), binary search the minimal s in [1, max(piles)].

Algorithm:
1) low = 1, high = max(piles)
2) While low <= high:
   - mid = low + (high - low)/2
   - hours = sum over piles of ceil(pile / mid)
   - If hours <= h: high = mid - 1 (try smaller speed)
   - Else: low = mid + 1 (need faster speed)
3) Return low

Time Complexity: O(n log max(piles))
Space Complexity: O(1)
*/
int minEatingSpeed2(vector<int>& piles, int h) {
    int low = 1, high = *max_element(piles.begin(), piles.end());
    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long hours = 0;
        for (int pile : piles) {
            hours += (pile + mid - 1) / mid; // integer ceil
            if (hours > h) break;
        }
        if (hours <= h) high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;
    cout << "Minimum eating speed (brute force):  " << minEatingSpeed(piles, h) << "\n";
    cout << "Minimum eating speed (binary search): " << minEatingSpeed2(piles, h) << "\n";
    return 0;
}
