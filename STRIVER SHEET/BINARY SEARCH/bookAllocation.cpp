#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Allocate Minimum Number of Pages

Problem Statement:
Given an array arr of n positive integers where arr[i] denotes pages in the i-th book, and an integer k (number of students),
allocate books in order (contiguous segments) to exactly k students such that the maximum pages assigned to any student is minimized.
Each book must be assigned to exactly one student. If k > n, return -1.

Example:
Input:  arr = {12, 34, 67, 90}, n = 4, k = 2
Output: 113
Explanation:
  - Allocation: [12, 34] and [67, 90]
  - Loads: 46 and 157 → max 157 (not minimal)
  - Best: [12, 34, 67] and [90] → max 113 (minimal achievable)

Approach Overview:
- Brute Force (linear scan of answer range): Try each possible max cap from max(arr) to sum(arr) and check feasibility.
- Optimal (Binary Search on Answer): Binary search on the max pages cap; feasibility via greedy partition into at most k segments.
Note: Books must be allocated contiguously.

Key Corrections:
- Feasibility should also fail if any single book > max cap (handled by initializing low=max(arr)).
- In the feasibility check, count how many students (segments) are needed for a given cap. It’s feasible if students_needed <= k.
- In the binary search feasibility function, ensure the return condition reflects students_needed <= k (avoid off-by-one).
*/

/*
Approach 1: Brute Force over possible maximum pages

Approach Idea:
- The minimum possible cap is low = max(arr) (since each book must fit into a student's allocation).
- The maximum possible cap is high = sum(arr).
- For cap in [low..high], the first feasible cap is the answer.

Algorithm:
1) If k > n: return -1
2) low = max(arr), high = sum(arr)
3) For cap from low to high:
   - If feasible(cap): return cap
4) Return -1 (shouldn’t happen if k <= n)

Time Complexity: O(n * (high - low))  [too slow for large sums]
Space Complexity: O(1)
*/
static bool feasibleLinear(const vector<int> &arr, int k, int cap) {
    int students = 1;
    long long pages = 0;
    for (int x : arr) {
        if (x > cap) return false; // a single book exceeds cap
        if (pages + x > cap) {
            students++;
            pages = x;
        } else {
            pages += x;
        }
    }
    return students <= k;
}

int findPages_linear(vector<int> &arr, int k) {
    int n = arr.size();
    if (k > n) return -1;

    int low = *max_element(arr.begin(), arr.end());
    long long high = accumulate(arr.begin(), arr.end(), 0LL);

    for (long long cap = low; cap <= high; cap++) {
        if (feasibleLinear(arr, k, (int)cap)) return (int)cap;
    }
    return -1;
}

/*
Approach 2: Binary Search on the Answer (Recommended)

Approach Idea:
- The predicate “cap is feasible” is monotonic: if a cap is feasible, any larger cap is also feasible.
- Binary search cap in [max(arr), sum(arr)] and use greedy feasibility:
  - Accumulate pages until adding the next book exceeds cap; start a new student segment.
  - Count segments; feasible if segments <= k.

Algorithm:
1) If k > n: return -1
2) low = max(arr), high = sum(arr)
3) While low <= high:
   - mid = (low + high) / 2
   - If feasible(mid): ans = mid, high = mid - 1
   - Else: low = mid + 1
4) Return ans

Time Complexity: O(n log(sum(arr) - max(arr)))
Space Complexity: O(1)
*/
static bool feasibleBS(const vector<int> &arr, int k, long long cap) {
    int students = 1;
    long long pages = 0;
    for (int x : arr) {
        if (x > cap) return false;
        if (pages + x > cap) {
            students++;
            pages = x;
        } else {
            pages += x;
        }
    }
    return students <= k;
}

int findPages_bs(vector<int> &arr, int k) {
    int n = arr.size();
    if (k > n) return -1;

    long long low = *max_element(arr.begin(), arr.end());
    long long high = accumulate(arr.begin(), arr.end(), 0LL);
    long long ans = -1;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (feasibleBS(arr, k, mid)) {
            ans = mid;
            high = mid - 1; // try to minimize the cap
        } else {
            low = mid + 1;
        }
    }
    return (int)ans;
}

int main() {
    vector<int> arr = {12, 34, 67, 90};
    int k = 2;

    cout << "Minimum pages (linear scan):   " << findPages_linear(arr, k) << "\n";
    cout << "Minimum pages (binary search): " << findPages_bs(arr, k) << "\n";
    return 0;
}
