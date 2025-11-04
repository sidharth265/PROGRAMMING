#include<bits/stdc++.h>
using namespace std;

/*
Problem: 4Sum (Find all unique quadruplets summing to target)

Problem Statement:
Given an integer array nums and an integer target, return all unique quadruplets [a, b, c, d] such that:
a + b + c + d == target.
Each quadruplet should be in non-decreasing order, and the output must not contain duplicate quadruplets.

Example:
Input:
  nums = [1, 0, -1, 0, -2, 2], target = 0
Output:
  [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]
Explanation:
These are all unique sets of four numbers that sum to 0.
*/


/*
Approach 1: Brute Force (Enumerate all quadruplets)

Idea:
- Use four nested loops to pick all 4-index combinations (i<j<k<l).
- If the sum equals target, store the quadruplet after sorting it to avoid ordering differences.
- Use a set to deduplicate identical quadruplets.

Algorithm:
1) Initialize an empty set S to store unique quadruplets.
2) For i in [0..n-1]:
   For j in [i+1..n-1]:
     For k in [j+1..n-1]:
       For l in [k+1..n-1]:
         - If nums[i]+nums[j]+nums[k]+nums[l] == target:
             * q = sorted({nums[i], nums[j], nums[k], nums[l]})
             * Insert q into S
3) Convert S to a vector and return.

Time Complexity: O(n^4)
Space Complexity: O(1) auxiliary (set for dedup; output not counted)
*/
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> ans;
    set<vector<int>> s;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    if (nums[i] + nums[j] + nums[k] + nums[l] == target) {
                        vector<int> quadruplet = {nums[i], nums[j], nums[k], nums[l]};
                        sort(quadruplet.begin(), quadruplet.end());
                        s.insert(quadruplet);
                    }
                }
            }
        }
    }
    return vector<vector<int>>(s.begin(), s.end());
}


/*
Approach 2: Triple Loop + Hash Map Lookup

Idea:
- Precompute a value->index map of the array (last occurrence).
- Fix three indices (i, j, k), compute the needed fourth value t = target - (nums[i]+nums[j]+nums[k]).
- If t exists at an index distinct from i, j, k, record the quadruplet.
- Use a set to deduplicate.

Algorithm:
1) Build a hashmap mp: value -> last index where it appears.
2) Initialize a set S for unique quadruplets.
3) For i in [0..n-1]:
     For j in [i+1..n-1]:
       For k in [j+1..n-1]:
         - t = target - (nums[i]+nums[j]+nums[k])
         - If t in mp and mp[t] != i, j, k:
             * q = sorted({nums[i], nums[j], nums[k], t})
             * Insert q into S
4) Return the vector made from S.

Time Complexity: O(n^3 log n) due to set insertions
Space Complexity: O(n) for the map (excluding result)
*/
vector<vector<int>> fourSum1(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> ans;
    set<vector<int>> s;
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++) {
        mp[nums[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int target2 = target - (nums[i] + nums[j] + nums[k]);
                if (mp.find(target2) != mp.end() && mp[target2] != i && mp[target2] != j && mp[target2] != k) {
                    vector<int> quadruplet = {nums[i], nums[j], nums[k], target2};
                    sort(quadruplet.begin(), quadruplet.end());
                    s.insert(quadruplet);
                }
            }
        }
    }
    return vector<vector<int>>(s.begin(), s.end());
}


/*
Approach 3: Set-assisted O(n^3) Pattern

Idea:
- For each fixed pair (i, j), scan forward with a running set of seen values to find complements for pair sum.
- When the needed complement is present in the set, create a quadruplet.
- Sort and deduplicate via a set of vectors.

Algorithm:
1) Initialize a set S for quadruplets.
2) For i in [0..n-4]:
     For j in [i+1..n-3]:
       - Create empty set seen.
       - For k in [j+2..n-1]:
           * Insert nums[k-1] into seen (rolling window).
           * f = target - (nums[i] + nums[j])
           * If f in seen:
               - q = sorted({nums[i], nums[j], f, nums[k]})
               - Insert q into S
3) Return vector from S.

Time Complexity: O(n^3 log n) (due to set operations)
Space Complexity: O(n) for the rolling set plus result dedup structure
*/
vector<vector<int>> fourSum2(vector<int>& nums, int target) {
    int n = nums.size();
    set<vector<int>> s;
    for (int i=0; i<n-3; i++) {
        for (int j=i+1; j<n-2; j++) {
            set<int> st;
            for (int k=j+2; k<n; k++) {
                st.insert(nums[k-1]);
                int f = target - (nums[i] + nums[j]);
                if (st.find(f) != st.end()) {
                    vector<int> quadruplet = {nums[i], nums[j], f, nums[k]};
                    sort(quadruplet.begin(), quadruplet.end());
                    s.insert(quadruplet);
                }
            }
        }
    }
    return vector<vector<int>>(s.begin(), s.end());
}


/*
Approach 4: Optimized Sorting + Two Pointers

Idea:
- Sort the array.
- Fix two indices (i, j). Then solve 2-sum on the subarray [j+1..n-1] with two pointers to reach target - (nums[i]+nums[j]).
- Skip duplicates at every level (i, j, left, right) to ensure uniqueness.

Algorithm:
1) Sort nums.
2) For i in [0..n-4]:
   - If i>0 and nums[i]==nums[i-1], continue.
   - For j in [i+1..n-3]:
       * If j>i+1 and nums[j]==nums[j-1], continue.
       * left = j+1, right = n-1
       * While left < right:
           - sum = nums[i] + nums[j] + nums[left] + nums[right]
           - If sum < target: left++
           - Else if sum > target: right--
           - Else:
               + Record [nums[i], nums[j], nums[left], nums[right]]
               + While left<right and nums[left]==nums[left+1], left++
               + While left<right and nums[right]==nums[right-1], right--
               + left++, right--
3) Return the collected list.

Time Complexity: O(n^3) (sorting O(n log n) is dominated by triple loops)
Space Complexity: O(1) auxiliary (excluding output)
*/
vector<vector<int>> fourSum3(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> ans; 
    sort(nums.begin(), nums.end());
    for (int i=0; i<n-3; i++) {
        if (i!=0 && nums[i-1] == nums[i]) continue;
        for (int j=i+1; j<n-2; j++) {
            if (j!=i+1 && nums[j-1] == nums[j]) continue;
            int left = j+1, right = n-1;
            while (left < right) {
                long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                if (sum < target) left++;
                else if (sum > target) right--;
                else {
                    ans.push_back({nums[i], nums[j], nums[left], nums[right]});
                    while (left < right && nums[left+1] == nums[left]) left++;
                    while (left < right && nums[right-1] == nums[right]) right--;
                    left++;
                    right--; 
                } 
            }
        }
    }
    return ans;
}


// Example usage
int main() {
    vector<int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;
    vector<vector<int>> result = fourSum3(nums, target);
    for (const auto& quadruplet : result) {
        for (int num : quadruplet) cout << num << " ";
        cout << endl;
    }
    return 0;
}
