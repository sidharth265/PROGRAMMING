#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Single Number (Every element appears twice except one)

Problem Statement:
Given a non-empty integer array nums where every element appears exactly twice except for one element which appears only once, find and return that single element.

Example:
Input:
  nums = [4, 1, 2, 1, 2]
Output:
  4

Approach Overview:
- Approach 1: Brute Force — For each element, check if a duplicate exists by scanning the array.
- Approach 2: Hash Map — Count frequencies and return the element with frequency 1.
- Approach 3: XOR (Recommended) — XOR all numbers; pairs cancel out, leaving the unique number.
*/

/*
Approach: Brute Force
Approach Idea:
- For each element nums[i], scan all j!=i to see if a duplicate exists.
- If none found, nums[i] is the single number.

Algorithm:
1) For i in [0..n-1]:
   - hasDup = false
   - For j in [0..n-1], j!=i:
       - If nums[j] == nums[i]: hasDup = true; break
   - If !hasDup: return nums[i]
2) Fallback return 0 (problem guarantees existence)

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
int singleNumber(vector<int>& nums) {
    int n = nums.size();
    for (int i=0; i<n; i++) {
        bool hasDup = false;
        for (int j=0; j<n; j++) {
            if (i!=j && nums[j] == nums[i]) {
                hasDup = true;
                break;
            }
        }
        if (!hasDup) return nums[i];
    }
    return 0; // problem guarantees existence; fallback
}

/*
Approach: Hash Map
Approach Idea:
- Count occurrences of each value using a hash map.
- The key with frequency 1 is the answer.

Algorithm:
1) Build freq map counts for each x in nums
2) For each (key, count) in map:
   - If count == 1: return key
3) Fallback return 0

Time Complexity: O(n)
Space Complexity: O(n)
*/
int singleNumberOptimized(vector<int>& nums) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
    for (auto &p : freq) {
        if (p.second == 1) return p.first;
    }
    return 0; // fallback
}

/*
Approach: XOR (Recommended)
Approach Idea:
- Use property: a ^ a = 0 and a ^ 0 = a.
- XOR all elements; duplicates cancel out, leaving the single element.

Algorithm:
1) ans = 0
2) For each x in nums: ans ^= x
3) Return ans

Time Complexity: O(n)
Space Complexity: O(1)
*/
int singleNumberXOR(vector<int>& nums) {
    int ans = 0;
    for (int x : nums) ans ^= x;
    return ans;
}

int main() {
    vector<int> nums = {4, 1, 2, 1, 2};
    cout << "Single number using brute force: " << singleNumber(nums) << "\n";
    cout << "Single number using optimized approach: " << singleNumberOptimized(nums) << "\n";
    cout << "Single number using XOR: " << singleNumberXOR(nums) << "\n";
    return 0;
}
