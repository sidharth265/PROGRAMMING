#include <bits/stdc++.h>
using namespace std;

/*
Problem:
K-th Smallest Element in Two Sorted Arrays

Problem Statement:
Given two sorted arrays a (size n1) and b (size n2), and an integer k (1-based),
return the k-th smallest element in the merged order of the two arrays.
Assume 1 <= k <= n1 + n2.

Example:
a = [2, 3, 6, 7, 9], b = [1, 4, 8, 10], k = 5
Answer: 6

Approach Overview:
- Brute Force: Merge fully, then pick the (k-1)-th index.
- Better: Two-pointer walk until k elements are consumed.
- Optimal: Binary-search the partition size taken from a (or b) to form a valid split where left side has exactly k elements.
*/

/*
Approach: Brute Force Merge
Approach Idea:
- Merge arrays like in merge sort into a single sorted vector, then return merged[k-1].

Algorithm:
1) i = j = 0; merged = []
2) While i<n1 and j<n2: push smaller of a[i], b[j].
3) Append remaining elements.
4) Return merged[k-1].

Time Complexity: O(n1 + n2)
Space Complexity: O(n1 + n2)
*/
int kthElement(vector<int>& a, vector<int>& b, int k) {
    int n1 = (int)a.size(), n2 = (int)b.size();
    vector<int> merged;
    merged.reserve(n1 + n2);
    int i = 0, j = 0;
    while (i < n1 && j < n2) {
        if (a[i] <= b[j]) merged.push_back(a[i++]);
        else merged.push_back(b[j++]);
    }
    while (i < n1) merged.push_back(a[i++]);
    while (j < n2) merged.push_back(b[j++]);
    return merged[k - 1];
}

/*
Approach: Better Two-Pointer without full merge
Approach Idea:
- Walk both arrays with two pointers and count how many elements have been "taken" until k is reached.

Algorithm:
1) i=j=0, cnt=0
2) While i<n1 && j<n2:
   - take min(a[i], b[j]); cnt++; if cnt==k return that value
3) Continue the remaining array until cnt==k.

Time Complexity: O(k)
Space Complexity: O(1)
*/
int kthElement2(vector<int>& a, vector<int>& b, int k) {
    int n1 = (int)a.size(), n2 = (int)b.size();
    int i = 0, j = 0, cnt = 0, val = -1;
    while (i < n1 && j < n2) {
        if (a[i] <= b[j]) val = a[i++]; else val = b[j++];
        if (++cnt == k) return val;
    }
    while (i < n1) { val = a[i++]; if (++cnt == k) return val; }
    while (j < n2) { val = b[j++]; if (++cnt == k) return val; }
    return -1; // k is guaranteed valid
}

/*
Approach: Optimal Binary Search on Partition
Approach Idea:
- Let i be the number of elements taken from a (thus k-i from b) to form the left partition of size k.
- We need l1 = a[i-1], l2 = b[k-i-1], r1 = a[i], r2 = b[k-i], with sentinels when indices are out of range.
- Valid partition if l1 <= r2 and l2 <= r1. Then answer is max(l1, l2).
- Search i in [max(0, k - n2), min(k, n1)].

Algorithm:
1) Ensure a is the smaller array; if not, swap and call again.
2) low = max(0, k - n2), high = min(k, n1)
3) While low <= high:
   - i = (low+high)/2, j = k - i
   - l1 = (i>0 ? a[i-1] : -inf), r1 = (i<n1 ? a[i] : +inf)
   - l2 = (j>0 ? b[j-1] : -inf), r2 = (j<n2 ? b[j] : +inf)
   - If l1 > r2: high = i - 1
     Else if l2 > r1: low = i + 1
     Else: return max(l1, l2)

Time Complexity: O(log min(n1, n2))
Space Complexity: O(1)
*/
int kthElement3(vector<int>& a, vector<int>& b, int k) {
    int n1 = (int)a.size(), n2 = (int)b.size();
    if (n1 > n2) return kthElement3(b, a, k);

    int low = max(0, k - n2);
    int high = min(k, n1);

    while (low <= high) {
        int i = (low + high) / 2;
        int j = k - i;

        int l1 = (i > 0) ? a[i - 1] : INT_MIN;
        int r1 = (i < n1) ? a[i] : INT_MAX;
        int l2 = (j > 0) ? b[j - 1] : INT_MIN;
        int r2 = (j < n2) ? b[j] : INT_MAX;

        if (l1 > r2) {
            high = i - 1;
        } else if (l2 > r1) {
            low = i + 1;
        } else {
            return max(l1, l2);
        }
    }
    return -1; // should not happen if 1 <= k <= n1+n2
}

int main() {
    vector<int> arr1 = {2, 3, 6, 7, 9};
    vector<int> arr2 = {1, 4, 8, 10};
    int k = 5;

    cout << "Kth (brute merge):   " << kthElement(arr1, arr2, k) << "\n";
    cout << "Kth (two-pointer):   " << kthElement2(arr1, arr2, k) << "\n";
    cout << "Kth (binary search): " << kthElement3(arr1, arr2, k) << "\n";
    return 0;
}
