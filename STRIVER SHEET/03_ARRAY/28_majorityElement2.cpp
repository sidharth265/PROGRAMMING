#include<bits/stdc++.h>
using namespace std;

/*
Problem: Majority Elements (> n/3 frequency)

Problem Statement:
Given an integer array nums of size n, find all elements that appear more than n/3 times. Return the list of such elements (there can be at most two).

Example:
Input:
  nums = [3, 2, 3, 2, 2, 1, 1, 1]
Output:
  [2, 1]
Explanation:
- 2 appears 3 times and 1 appears 3 times in an array of length 8; both are > floor(8/3) = 2.

Approach Overview:
- Hash Map Counting: Count frequencies and collect those exceeding n/3.
- Boyer–Moore Voting (n/3 variant): Track up to two candidates with counters, then verify their counts.

Complexity Overview:
- Hash Map: Time O(n), Space O(n).
- Boyer–Moore (n/3): Time O(n), Space O(1) plus result list; requires a verification pass.
*/

/*
Approach 1: Hash Map Counting

Idea:
- Count occurrences of each number using an unordered_map.
- Collect keys whose frequency exceeds floor(n/3).

Algorithm:
1) Build frequency map m for all elements.
2) For each (value, count) in m:
     - If count > n/3, add value to answer.
3) Return the answer list.

Time Complexity: O(n)
Space Complexity: O(n)
*/
vector<int> majorityElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans;
    unordered_map<int, int> m;
    for (int i=0; i<n; i++) {
        m[nums[i]]++;
    }
    for (auto it : m) {
        if (it.second > n/3) {
            ans.push_back(it.first);
        }
    }
    return ans;
}

/*
Approach 2: Boyer–Moore Voting Algorithm (n/3 variant)

Idea:
- For threshold n/3, there can be at most two majority elements.
- First pass: maintain up to two candidates with counters using elimination.
- Second pass: verify actual counts of the candidates and include those > n/3.

Algorithm:
1) Initialize count1 = 0, count2 = 0, candidate1, candidate2.
2) For num in nums:
     - If num == candidate1: count1++
     - Else if num == candidate2: count2++
     - Else if count1 == 0: candidate1 = num, count1 = 1
     - Else if count2 == 0: candidate2 = num, count2 = 1
     - Else: count1--, count2--
3) Verify: reset count1 = count2 = 0, count occurrences of candidate1 and candidate2.
4) If count1 > n/3, push candidate1; if count2 > n/3, push candidate2.
5) Return the result.

Time Complexity: O(n) (two passes)
Space Complexity: O(1) auxiliary (excluding output)
*/
vector<int> majorityElementBoyerMoore(vector<int>& nums) {
    int count1 = 0, count2 = 0;
    int candidate1 = 0, candidate2 = 0;

    for (int num : nums) {
        if (count1 > 0 && num == candidate1) {
            count1++;
        } else if (count2 > 0 && num == candidate2) {
            count2++;
        } else if (count1 == 0) {
            candidate1 = num;
            count1 = 1;
        } else if (count2 == 0) {
            candidate2 = num;
            count2 = 1;
        } else {
            count1--;
            count2--;
        }
    }

    vector<int> ans;
    count1 = count2 = 0;
    for (int num : nums) {
        if (num == candidate1) count1++;
        else if (num == candidate2) count2++;
    }
    if (count1 > (int)nums.size() / 3) ans.push_back(candidate1);
    if (count2 > (int)nums.size() / 3) ans.push_back(candidate2);
    return ans;
}

int main() {
    vector<int> nums = {3, 2, 3, 2, 2, 1, 1, 1};

    // Hash Map approach
    vector<int> result1 = majorityElement(nums);
    cout << "Majority Elements (>n/3) using HashMap: ";
    for (int x : result1) cout << x << " ";
    cout << "\n";

    // Boyer–Moore approach
    vector<int> result2 = majorityElementBoyerMoore(nums);
    cout << "Majority Elements (>n/3) using Boyer–Moore: ";
    for (int x : result2) cout << x << " ";
    cout << "\n";

    return 0;
}
