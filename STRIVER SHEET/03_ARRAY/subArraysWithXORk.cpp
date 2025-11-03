#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Count Subarrays With XOR Equal to k

Problem Statement:
Given an integer array arr and an integer k, return the total number of contiguous subarrays whose bitwise XOR equals k.

Example:
Input:  arr = [1, 2, 3, 4, 5], k = 5
Output: 2
Explanation:
- Subarrays with XOR 5: [1, 4] (indices 0..3 XOR-wise doesn’t match contiguously here), actual contiguous ones are:
  [2, 3] = 2^3 = 1 (not 5), [1, 4] is not contiguous. For the given example, the contiguous subarrays are:
  [2, 7] style check is wrong; correct ones are:
  - [1, 4] is not contiguous; proper contiguous solutions in this input are:
  [1, 4] mistaken earlier. Working out:
  Prefix XORs: px = [1, 3, 0, 4, 1]
  We need px[j] ^ px[i-1] = k ⇒ px[i-1] = px[j] ^ k.
  Matches yield count = 2 for this example.

Approach Overview:
- Brute Force: Enumerate all subarrays, compute running XOR; count matches with k.
- Optimized (Prefix XOR + HashMap): Let prefix XOR up to j be P. For each j, the number of i with P ^ P_(i-1) = k is the frequency of P ^ k seen so far. Accumulate in O(n).
*/

/*
Approach: Brute Force
Approach Idea:
- Fix start index i, expand end index j, maintain running XOR over arr[i..j].
- Increment answer whenever running XOR equals k.

Algorithm:
1) ans = 0
2) For i = 0..n-1:
   - xr = 0
   - For j = i..n-1:
     - xr ^= arr[j]
     - If xr == k: ans++
3) Return ans

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
long subarrayXor(vector<int> &arr, int k) {
    int n = arr.size();
    long ans = 0;
    for (int i = 0; i < n; i++) {
        int xr = 0;
        for (int j = i; j < n; j++) {
            xr ^= arr[j];
            if (xr == k) ans++;
        }
    }
    return ans;
}

/*
Approach: Optimized (Prefix XOR + HashMap)
Approach Idea:
- Let prefix XOR up to index j be P = arr[0] ^ ... ^ arr[j].
- For a subarray (i..j], XOR equals k iff P ^ P_(i-1) = k ⇒ P_(i-1) = P ^ k.
- Maintain a frequency map of prefix XORs seen so far; for current P, add freq[P ^ k] to answer, then increment freq[P].

Algorithm:
1) freq[0] = 1, P = 0, ans = 0
2) For each x in arr:
   - P ^= x
   - ans += freq[P ^ k] if exists
   - freq[P]++
3) Return ans

Time Complexity: O(n)
Space Complexity: O(n)
*/
long subarrayXor2(vector<int> &arr, int k) {
    unordered_map<int,int> freq;
    freq[0] = 1;     // subarrays starting at index 0
    int P = 0;
    long ans = 0;
    for (int x : arr) {
        P ^= x;
        auto it = freq.find(P ^ k);
        if (it != freq.end()) ans += it->second;
        freq[P]++;
    }
    return ans;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 5;

    cout << "Number of subarrays with XOR equal to " << k << " (Brute Force): " << subarrayXor(arr, k) << "\n";
    cout << "Number of subarrays with XOR equal to " << k << " (Optimized): " << subarrayXor2(arr, k) << "\n";
    return 0;
}
