#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Replace Elements with Their Ranks
 Problem Context:
 -----------------
 Given an array, replace each element with its rank, where rank represents the position of the element if the array was sorted 
 with duplicates sharing the same rank.

 Example:
 Input: arr = [40, 10, 20, 30]
 Output: [4, 1, 2, 3]

 Constraints:
 - 1 <= N <= 10^5
 - Elements can be any integer
====================================================
*/

/* 
==========================================
 Approach 1: Sorting + HashMap for Rank Assigning

 Algorithm:
 1. Copy the original array and sort the copy.
 2. Iterate through the sorted array to assign ranks:
    - Skip duplicates to ensure equal numbers get the same rank.
    - Assign increasing rank starting from 1.
 3. Use a hash map to map from element to its assigned rank.
 4. Replace elements in the original array with their ranks using the map.

 Time Complexity: O(N log N) due to sorting.
 Space Complexity: O(N) for copy and hashmap.
------------------------------------------
*/
vector<int> replaceWithRank(vector<int>& arr, int N) {
    vector<int> temp(arr.begin(), arr.end());
    sort(temp.begin(), temp.end());

    unordered_map<int, int> rankMap;
    int rank = 1;
    for (int i = 0; i < N; i++) {
        // Skip duplicates to assign same rank
        if (i > 0 && temp[i] == temp[i - 1]) continue;
        rankMap[temp[i]] = rank++;
    }

    for (int i = 0; i < N; i++) {
        arr[i] = rankMap[arr[i]];
    }
    return arr;
}

/* ========= MAIN FUNCTION ========= */
int main() {
    cout << "=== Replace Elements with Rank ===\n\n";

    vector<int> arr = {40, 10, 20, 30};
    int N = (int)arr.size();

    vector<int> ranked = replaceWithRank(arr, N);

    cout << "Original array: ";
    for (int v : arr) cout << v << " ";
    cout << "\nRanked array:   ";
    for (int v : ranked) cout << v << " ";
    cout << "\n";

    return 0;
}

/*
✅ Approach Overview:
- Sorting based algorithm assigns ranks based on sorted order.
- Duplicates get the same rank by skipping equal previous elements.
- Overall time complexity O(N log N).
- Space complexity O(N).
*/
