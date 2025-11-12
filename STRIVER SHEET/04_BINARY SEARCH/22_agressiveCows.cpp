#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Aggressive Cows (Maximize the minimum distance between any two placed cows)

Problem Statement:
Given N stall positions (not necessarily sorted) and an integer M (number of cows),
place the cows in stalls such that the minimum distance between any two cows is maximized.
Return that maximum possible minimum distance.

Example:
Input:
  N = 5, M = 3, stalls = [1, 2, 4, 8, 9]
Output:
  3
Explanation:
  Place cows at positions 1, 4, and 8. The pairwise minimum distance is min(3,4,7)=3, which is optimal.

Approach Overview:
- Brute Force (linear scan over distance): Sort stalls. Try every candidate distance d from the smallest gap up to the largest gap, and check feasibility greedily.
- Optimal (Binary Search on Answer): Sort stalls. Binary search the distance d. For each mid, greedily check if at least M cows can be placed with pairwise distance >= mid.
*/


/*
Approach: Brute Force over distances

Approach Idea:
- Sort the stalls.
- The feasible minimum distance d lies between:
  - low = minimum adjacent gap among sorted stalls,
  - high = largest gap = stalls.back() - stalls.front().
- For each integer d from low to high (inclusive), check if placing M cows is possible
  by greedily placing the next cow at the earliest stall that is at least d away from the last placed one.
- Track the largest feasible d.

Algorithm:
1) Sort stalls.
2) Compute low = min adjacent gap; high = stalls[n-1] - stalls[0].
3) For d in [low..high]:
   - If feasible(d): ans = d; else break (since larger d will also fail).
4) Return ans.

Time Complexity: O(N log N + (high-low+1) * N)  [often too slow if coordinates are large]
Space Complexity: O(1)
*/
static bool feasibleLinear(const vector<int> &stalls, int cows, int dist) {
    int placed = 1; // place first cow at stalls[0]
    int lastPos = stalls[0];
    for (int i = 1; i < (int)stalls.size() && placed < cows; i++) {
        if (stalls[i] - lastPos >= dist) {
            placed++;
            lastPos = stalls[i];
        }
    }
    return placed >= cows;
}

int aggressiveCows_linear(vector<int> stalls, int cows) {
    int n = stalls.size();
    sort(stalls.begin(), stalls.end());
    if (n == 0 || cows <= 1) return 0;

    int high = stalls.back() - stalls.front();
    int low = high;
    for (int i = 1; i < n; i++) low = min(low, stalls[i] - stalls[i - 1]);

    int ans = 0;
    for (int d = low; d <= high; d++) {
        if (feasibleLinear(stalls, cows, d)) ans = d;
        else break; // further distances will fail
    }
    return ans;
}

/*
Approach: Binary Search on Answer (Recommended)

Approach Idea:
- The answer (maximum minimum distance) is monotonic: if distance d is feasible, then any distance <= d is also feasible.
- Binary search d between 0 and (stalls.back() - stalls.front()).
- For a given mid, greedily place cows:
  - Place the first cow at stalls[0].
  - For each next stall, if it's at least mid away from the last placed, place the next cow.
  - If we can place at least M cows, mid is feasible; otherwise infeasible.

Algorithm:
1) Sort stalls.
2) low = 0, high = stalls[n-1] - stalls[0].
3) While low <= high:
   - mid = (low + high)/2
   - If feasible(mid): ans = mid, low = mid + 1
   - Else: high = mid - 1
4) Return ans.

Time Complexity: O(N log N + N log R), where R = stalls[n-1] - stalls[0]
Space Complexity: O(1)
*/
static bool feasibleBS(const vector<int> &stalls, int cows, int dist) {
    int placed = 1;
    int lastPos = stalls[0];
    for (int i = 1; i < (int)stalls.size() && placed < cows; i++) {
        if (stalls[i] - lastPos >= dist) {
            placed++;
            lastPos = stalls[i];
        }
    }
    return placed >= cows;
}

int aggressiveCows_bs(vector<int> stalls, int cows) {
    int n = stalls.size();
    sort(stalls.begin(), stalls.end());
    if (n == 0 || cows <= 1) return 0;

    int low = 0;
    int high = stalls.back() - stalls.front();
    int ans = 0;

    while (low <= high) {
        int mid = low + (high - low)/2;
        if (feasibleBS(stalls, cows, mid)) {
            ans = mid;
            low = mid + 1;     // try for a larger minimum distance
        } else {
            high = mid - 1;    // reduce distance
        }
    }
    return ans;
}

int main() {
    vector<int> stalls = {1, 2, 4, 8, 9};
    int M = 3;

    cout << "Maximum distance (linear scan over d): " << aggressiveCows_linear(stalls, M) << "\n";
    cout << "Maximum distance (binary search):      " << aggressiveCows_bs(stalls, M) << "\n";
    return 0;
}
