#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Minimize the maximum distance between adjacent gas stations after adding k new stations.

Problem Statement:
Given a sorted list of existing gas station positions (stations) along a road and an integer k,
add exactly k new stations (at real positions) so that the maximum distance between any two adjacent
stations is minimized. Return that minimized maximum distance as a double with good precision.

Example:
stations = [1, 2, 5, 10], k = 2
Answer: 2.5
We can place new stations to split the largest gaps so that the largest resulting segment length is minimized.

Approach Overview:
- Brute Force (Greedy by Sections): Repeatedly split the currently largest gap by adding a station into that segment.
- Better (Max-Heap): Use a priority queue keyed by current segment length after splits for each original gap.
- Optimal (Binary Search on Answer): Binary search the maximal allowed gap D; check if at most k stations suffice so all gaps <= D.

Notes:
- stations should be sorted before processing.
- All approaches assume stations.size() >= 2 and k >= 0.
*/

/*
Approach 1: Brute Force "by sections"

Approach Idea:
- For each original gap, track how many extra stations are placed in it (Section[i]).
- The effective maximum sub-gap in gap i after t splits is length/(t+1).
- Repeat k times: find the current gap with the largest effective sub-gap and add a station to it (increase Section[i]).
- After k insertions, compute the resulting maximum sub-gap.

Algorithm:
1) Sort stations
2) Section[0..n-2] = 0
3) Repeat k times:
   - Find index idx that maximizes (stations[i+1]-stations[i]) / (Section[i]+1)
   - Section[idx]++
4) Answer = max_i (stations[i+1]-stations[i]) / (Section[i]+1)

Time Complexity: O(k * n)
Space Complexity: O(n)
*/
static int findMaxDistanceSection(const vector<int> &stations, const vector<int> &Section) {
    int n = (int)stations.size();
    double maxDist = -1.0;
    int idx = 0;
    for (int i = 0; i < n - 1; i++) {
        double length = (double)(stations[i + 1] - stations[i]);
        double dist = length / (Section[i] + 1.0);
        if (dist > maxDist) {
            maxDist = dist;
            idx = i;
        }
    }
    return idx;
}

double findSmallestMaxDist_bruteforce(vector<int> stations, int k) {
    sort(stations.begin(), stations.end());
    int n = (int)stations.size();
    if (n < 2) return 0.0;
    vector<int> Section(n - 1, 0);

    for (int t = 0; t < k; t++) {
        int idx = findMaxDistanceSection(stations, Section);
        Section[idx]++;
    }

    double ans = 0.0;
    for (int i = 0; i < n - 1; i++) {
        double length = (double)(stations[i + 1] - stations[i]);
        double dist = length / (Section[i] + 1.0);
        ans = max(ans, dist);
    }
    return ans;
}

/*
Approach 2: Priority Queue (Max-Heap)

Approach Idea:
- For each gap i, maintain (current effective sub-gap length, i).
- Initially, no splits (Section[i]=0), so the sub-gap is gap length.
- Repeat k times:
  - Extract the gap with largest current sub-gap
  - Increment splits Section[i], recompute new sub-gap length = length / (Section[i]+1), and push back.
- The top after k operations is the minimized maximum distance.

Algorithm:
1) Sort stations
2) For each i in [0..n-2], push (gap length, i) into max-heap; also track Section[i]=0
3) Repeat k times:
   - Pop top (current largest sub-gap, i)
   - Section[i]++
   - Recompute new sub-gap = length / (Section[i]+1)
   - Push back into heap
4) Answer is heap.top().first

Time Complexity: O(k log n)
Space Complexity: O(n)
*/
double findSmallestMaxDist_heap(vector<int> stations, int k) {
    sort(stations.begin(), stations.end());
    int n = (int)stations.size();
    if (n < 2) return 0.0;

    vector<int> splits(n - 1, 0);

    // max-heap of (current sub-gap length, index)
    priority_queue<pair<double,int>> pq;
    for (int i = 0; i < n - 1; i++) {
        double length = (double)(stations[i + 1] - stations[i]);
        pq.push({length, i});
    }

    while (k--) {
        auto [curr, idx] = pq.top(); pq.pop();
        splits[idx]++;
        double length = (double)(stations[idx + 1] - stations[idx]);
        double next = length / (splits[idx] + 1.0);
        pq.push({next, idx});
    }

    return pq.top().first;
}

/*
Approach 3: Binary Search on Answer (Optimal)

Approach Idea:
- Suppose we guess a candidate maximum allowed distance D for adjacent stations.
- For each original gap length L, the number of additional stations needed to ensure sub-gaps <= D is:
     need = ceil(L / D) - 1
  Which can be computed as: need = max(0, (int)ceil(L / D) - 1).
- Summing need over all gaps gives total new stations required. If total <= k, D is feasible; otherwise infeasible.
- Binary search D over [0, max_gap] until precision threshold.

Algorithm:
1) Sort stations
2) Compute max_gap among consecutive stations
3) low = 0, high = max_gap
4) While high - low > eps:
   - mid = (low + high)/2
   - total = sum over gaps: max(0, ceil((stations[i+1]-stations[i]) / mid) - 1)
   - If total <= k: high = mid (feasible)
   - Else: low = mid (infeasible)
5) Return high

Time Complexity: O(n log R) where R relates to range/precision
Space Complexity: O(1)
*/
static bool canAchieve(const vector<int> &stations, int k, double D) {
    int n = (int)stations.size();
    long long needed = 0;
    for (int i = 0; i < n - 1; i++) {
        double gap = (double)(stations[i + 1] - stations[i]);
        // number of pieces = ceil(gap / D)
        // stations to add = pieces - 1 = ceil(gap/D) - 1
        if (D > 0.0) {
            long long add = (long long)ceil(gap / D) - 1;
            if (add > 0) needed += add;
            if (needed > k) return false; // early break
        } else {
            // D == 0 only feasible if all gaps are zero
            if (gap > 0) return false;
        }
    }
    return needed <= k;
}

double findSmallestMaxDist_binary(vector<int> stations, int k) {
    sort(stations.begin(), stations.end());
    int n = (int)stations.size();
    if (n < 2) return 0.0;

    double maxGap = 0.0;
    for (int i = 0; i < n - 1; i++) {
        maxGap = max(maxGap, (double)(stations[i + 1] - stations[i]));
    }

    double low = 0.0, high = maxGap;
    const double eps = 1e-6; // precision
    while (high - low > eps) {
        double mid = (low + high) / 2.0;
        if (canAchieve(stations, k, mid)) high = mid;
        else low = mid;
    }
    return high;
}

int main() {
    vector<int> stations = {1, 2, 5, 10};
    int k = 2;

    cout << fixed << setprecision(6);

    cout << "Brute Force (sections): " << findSmallestMaxDist_bruteforce(stations, k) << "\n";
    cout << "Priority Queue:         " << findSmallestMaxDist_heap(stations, k) << "\n";
    cout << "Binary Search:          " << findSmallestMaxDist_binary(stations, k) << "\n";

    return 0;
}
