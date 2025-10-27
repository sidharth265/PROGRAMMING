#include <bits/stdc++.h>
using namespace std;

/*
Problem:
K-th Missing Positive Number

Problem Statement:
Given a strictly increasing array arr of positive integers and an integer k,
return the k-th positive integer that is missing from this array.

Example:
Input:  arr = [2, 3, 4, 7, 11], k = 5
Output: 9
Explanation: Missing positives are [1,5,6,8,9,10,...]; the 5th missing is 9.

Approach Overview:
- Brute Force: Walk through natural numbers, compare against arr, count missing until reaching k.
- Better (Single Pass Adjustment): Sweep arr; for each value <= k, increment k. Answer is k after the sweep.
- Optimal (Binary Search): Use missing(mid) = arr[mid] - (mid + 1) to find smallest index with missing >= k, then compute answer.
*/

/*
Approach: Brute Force
Approach Idea:
- Iterate current from 1 upward, moving pointer i along arr when matched.
- Count numbers not present in arr; when count reaches k, return current.

Algorithm:
1) i=0, current=1, missing=0
2) while missing < k:
   - if i<n and arr[i]==current: i++
     else: missing++; if missing==k: return current
   - current++
3) (Unreachable)

Time Complexity: O(n + k)
Space Complexity: O(1)
*/
int findKthPositive(vector<int>& arr, int k) {
    int i = 0, n = (int)arr.size();
    int current = 1, missing = 0;
    while (missing < k) {
        if (i < n && arr[i] == current) {
            i++;
        } else {
            missing++;
            if (missing == k) return current;
        }
        current++;
    }
    return -1;
}

/*
Approach: Better Single-Pass Adjustment
Approach Idea:
- For each x in arr, if x <= k, then one missing number at or before x is "accounted for", so increment k.
- When done, the answer is k.

Algorithm:
1) For x in arr:
   - if x <= k: k++
   - else: break (optional optimization)
2) return k

Time Complexity: O(n)
Space Complexity: O(1)
*/
int findKthPositive2(vector<int>& arr, int k) {
    for (int x : arr) {
        if (x <= k) k++;
        else break;
    }
    return k;
}

/*
Approach: Binary Search
Approach Idea:
- For index mid, the count of missing numbers up to arr[mid] is:
    missing(mid) = arr[mid] - (mid + 1)
  Because in a perfect array [1,2,3,...], the value at mid would be mid+1.
- Find the first index low such that missing(low) >= k.
- If low is that index, the answer is k + low.

Derivation:
- For low elements in arr that are <= their "ideal" positions plus missing, the k-th missing lies after those low elements.
- Result: k + low.

Algorithm:
1) low=0, high=n-1
2) while low <= high:
   - mid = (low+high)/2
   - if arr[mid] - (mid+1) < k: low = mid + 1
     else: high = mid - 1
3) return k + low

Time Complexity: O(log n)
Space Complexity: O(1)
*/
int findKthPositive3(vector<int>& arr, int k) {
    int n = (int)arr.size();
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low)/2;
        int missing = arr[mid] - (mid + 1);
        if (missing < k) low = mid + 1;
        else high = mid - 1;
    }
    return k + low;
}

int main() {
    vector<int> arr = {2, 3, 4, 7, 11};
    int k = 5;

    cout << "Brute force approach:  " << findKthPositive(arr, k) << "\n";
    cout << "Better approach:       " << findKthPositive2(arr, k) << "\n";
    cout << "Optimized (binary):    " << findKthPositive3(arr, k) << "\n";

    return 0;
}
