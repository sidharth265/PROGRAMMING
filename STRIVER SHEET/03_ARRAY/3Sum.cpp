#include<bits/stdc++.h>
using namespace std;

/*
Problem: 3Sum (Find all unique triplets summing to zero)

Problem Statement:
Given an integer array nums, return all unique triplets [a, b, c] such that:
a + b + c == 0, with distinct indices (i != j, i != k, j != k). The result must not contain duplicate triplets.

Example:
Input:
  nums = [-1, 0, 1, 2, -1, -4]
Output:
  [[-1, -1, 2], [-1, 0, 1]]
Explanation:
- These are all unique triplets that sum to 0.

Approach Overview:
- Brute Force: Enumerate all triplets (i<j<k), sum, and deduplicate via a set.
- Hashing (value->index): Fix two indices and look up the needed third value; deduplicate via a set.
- Set-assisted O(n^2 log n): For each i, use a rolling set while scanning j to detect complements; deduplicate via a set.
- Optimized Two Pointers: Sort, fix i, and use two pointers j/k to find pairs for -nums[i] while skipping duplicates.

Complexity Overview:
- Brute Force: O(n^3) time, O(1) aux space (excluding dedup structure/output).
- Hash/Set-assisted: O(n^2 log n) time due to set inserts, O(n) aux space.
- Two Pointers (recommended): O(n^2) time, O(1) aux space beyond output.
*/


/*
Approach 1: Brute Force (Enumerate all triplets)

Idea:
- Try all i<j<k and check if nums[i]+nums[j]+nums[k]==0.
- Sort each triplet before insertion into a set to avoid duplicates.

Algorithm:
1) Initialize an empty set S of vectors.
2) For i in [0..n-1]:
     For j in [i+1..n-1]:
       For k in [j+1..n-1]:
         - If nums[i]+nums[j]+nums[k]==0:
             * t = {nums[i], nums[j], nums[k]}
             * sort(t), insert into S
3) Return vector built from S.

Time Complexity: O(n^3)
Space Complexity: O(1) auxiliary (set used for dedup; output not counted)
*/
vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> ans;
    set<vector<int>> s;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            for (int k=j+1; k<n; k++) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> triplet = {nums[i], nums[j], nums[k]};
                    sort(triplet.begin(), triplet.end());
                    s.insert(triplet);
                }
            }
        }
    }
    return vector<vector<int>> (s.begin(), s.end());
}

/*
Approach 2: Hash Map Lookup (value -> last index)

Idea:
- Build a map from value to an index where it appears.
- Fix i and j, compute t = -(nums[i]+nums[j]) and check if t exists at an index different from i and j.
- Sort triplet and deduplicate via set.

Algorithm:
1) Build mp: value -> last index.
2) Initialize set S for unique triplets.
3) For i in [0..n-1]:
     For j in [i+1..n-1]:
       - t = -(nums[i]+nums[j])
       - If t in mp and mp[t] != i and mp[t] != j:
           * q = {nums[i], nums[j], t}, sort(q), insert into S
4) Return vector from S.

Time Complexity: O(n^2 log n) due to set insertions
Space Complexity: O(n) for the map (excluding output)
*/
vector<vector<int>> threeSum2(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> s;
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++) {
        mp[nums[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int target = -(nums[i] + nums[j]); // Find the target that would make the sum zero
            if (mp.find(target) != mp.end() && mp[target] != i && mp[target] != j) { // Check target exists and isn't i or j
                vector<int> triplet = {nums[i], nums[j], target};
                sort(triplet.begin(), triplet.end());
                s.insert(triplet);
            }
        }
    }
    return vector<vector<int>>(s.begin(), s.end());
}

/*
Approach 3: Set-assisted O(n^2 log n)

Idea:
- For each fixed i, scan j forward while maintaining a set of seen elements (rolling window).
- For each j, compute f = -(nums[i]+nums[j]); if f is in seen, we found a triplet.
- Sort and deduplicate via a set of vectors.

Algorithm:
1) Initialize set S for triplets.
2) For i in [0..n-3]:
     - Initialize empty set seen.
     - For j in [i+2..n-1]:
         * Insert nums[j-1] into seen.
         * f = -(nums[i] + nums[j]).
         * If f in seen:
             - q = {nums[i], nums[j], f}, sort, insert into S
3) Return vector from S.

Time Complexity: O(n^2 log n) (set ops)
Space Complexity: O(n) for the rolling set (excluding output)
*/
vector<vector<int>> threeSum3(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> s;
    for (int i=0; i<n-2; i++) {
        set<int> st;
        for (int j=i+2; j<n; j++) {
            st.insert(nums[j-1]);
            int f = -(nums[i]+nums[j]);
            if (st.find(f) != st.end()) {
                vector<int> triplet = {nums[i], nums[j], f};
                sort(triplet.begin(), triplet.end());
                s.insert(triplet);
            }
        }
    }
    return vector<vector<int>> (s.begin(), s.end());
}

/*
Approach 4: Optimized Sorting + Two Pointers (Recommended)

Idea:
- Sort nums.
- For each i, solve 2-sum for target = -nums[i] using two pointers j (i+1) and k (n-1).
- Skip duplicates for i, j, and k to ensure unique triplets.

Algorithm:
1) Sort nums.
2) For i in [0..n-3]:
   - If i>0 and nums[i]==nums[i-1], continue (skip i duplicates).
   - If nums[i] > 0, break (no triplet can sum to 0 beyond this).
   - Set j=i+1, k=n-1.
   - While j<k:
       * sum = nums[i]+nums[j]+nums[k]
       * If sum > 0: k--
       * Else if sum < 0: j++
       * Else:
           - push [nums[i], nums[j], nums[k]]
           - while j<k and nums[j]==nums[j+1], j++
           - while j<k and nums[k]==nums[k-1], k--
           - j++, k--

Time Complexity: O(n^2)
Space Complexity: O(1) auxiliary (excluding output)
*/
vector<vector<int>> threeSum4(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    for (int i=0; i<n-2; i++) {
        if (i!=0 && nums[i-1] == nums[i]) continue; // Skip duplicates for i
        if (nums[i] > 0) break; // Early stop when smallest is positive
        int j=i+1, k=n-1; // Two pointers
        while (j < k) {
            long long sum = (long long)nums[i] + nums[j] + nums[k];
            if (sum > 0) k--;
            else if (sum < 0) j++;
            else {
                ans.push_back({nums[i], nums[j], nums[k]});
                while (j<k && nums[j+1] == nums[j]) j++; // Skip duplicates for j
                while (j<k && nums[k-1] == nums[k]) k--; // Skip duplicates for k
                j++;
                k--;
            }
        }
    }
    return ans;
}

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};

    // Choose the desired approach to run:
    // vector<vector<int>> result = threeSum(nums);   // Brute Force
    // vector<vector<int>> result = threeSum2(nums);  // Hash Map Lookup
    // vector<vector<int>> result = threeSum3(nums);  // Set-assisted
    vector<vector<int>> result = threeSum4(nums);     // Optimized Two Pointers

    for (const auto& triplet : result) {
        cout << "[";
        for (int i = 0; i < (int)triplet.size(); i++) {
            cout << triplet[i];
            if (i < (int)triplet.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    return 0;
}
