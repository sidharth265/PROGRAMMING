#include<bits/stdc++.h>
using namespace std;

/*
Problem: Rearrange Array Elements by Sign (Alternate Positive and Negative)

Problem Statement:
Given an integer array nums with an equal number of positive and negative integers (or guaranteed alternation feasibility), rearrange the array so that positive and negative numbers appear in alternating positions, starting with a positive number. Maintain the relative order within positives and within negatives where applicable (depending on approach).

Example:
Input:
  nums = {3, -2, 1, -5, 2, -4}
Output:
  {3, -2, 1, -5, 2, -4}
Explanation:
- Already alternates: +, -, +, -, +, -.

Approach Overview:
- Extra arrays then merge (stable within signs): Split into pos and neg, then interleave into a new vector.
- Extra arrays, fill in-place indexing (stable within signs): Split into pos and neg, then write back into nums at even/odd indices.
- O(1) auxiliary for input, O(n) for output vector (recommended): Single pass, place positives at even indices and negatives at odd indices into a new answer vector.

Notes:
- If the counts of positives and negatives are guaranteed equal or differ by at most 1, these patterns work naturally.
- If the array may not have equal counts, guard against out-of-bounds and place remaining elements at the end if the problem variant allows.

Complexity Overview:
- All approaches: Time O(n).
- Space:
  - Approach 1: O(n) extra (pos+neg+ans).
  - Approach 2: O(n) extra (pos+neg), modifies nums in-place layout.
  - Approach 3: O(n) for the output vector (no extra split arrays).
*/

/*
Approach 1: Split into positives and negatives, then interleave into a new vector

Idea:
- First pass: collect positives and negatives into separate vectors.
- Second pass: interleave pos[i], neg[i] into ans.

Algorithm:
1) For each x in nums:
     if x < 0: neg.push_back(x) else pos.push_back(x)
2) For i in [0..n/2-1]: ans.push_back(pos[i]); ans.push_back(neg[i])
3) Return ans

Time Complexity: O(n)
Space Complexity: O(n)
*/
vector<int> rearrangeArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> pos, neg, ans;
    pos.reserve(n);
    neg.reserve(n);
    ans.reserve(n);

    for (int x : nums) {
        if (x < 0) neg.push_back(x);
        else pos.push_back(x);
    }
    for (int i=0; i<n/2; i++) {
        ans.push_back(pos[i]);
        ans.push_back(neg[i]);
    }
    return ans;
}

/*
Approach 2: Split, then write back into original array at even/odd indices

Idea:
- Store positives and negatives separately.
- Write positives at even positions, negatives at odd positions in nums.

Algorithm:
1) Build pos and neg arrays.
2) For i in [0..n/2-1]:
     nums[2*i] = pos[i]
     nums[2*i+1] = neg[i]
3) Return nums

Time Complexity: O(n)
Space Complexity: O(n) for pos and neg
*/
vector<int> rearrangeArray2(vector<int>& nums) {
    int n = nums.size();
    vector<int> pos, neg;
    pos.reserve(n);
    neg.reserve(n);

    for (int x : nums) {
        if (x < 0) neg.push_back(x);
        else pos.push_back(x);
    }
    for (int i=0; i<n/2; i++) {
        nums[2*i] = pos[i];
        nums[2*i+1] = neg[i];
    }
    return nums;
}

/*
Approach 3: Single pass filling a new array by index parity (Recommended)

Idea:
- Create ans of size n.
- Maintain two pointers: posIdx=0 (even), negIdx=1 (odd).
- For each x in nums: place positive at ans[posIdx], negative at ans[negIdx], advancing by 2.

Algorithm:
1) ans = vector<int>(n)
2) pos=0, neg=1
3) For each x in nums:
     if x < 0: ans[neg] = x; neg += 2
     else: ans[pos] = x; pos += 2
4) Return ans

Time Complexity: O(n)
Space Complexity: O(n) for the output vector
*/
vector<int> rearrangeArray3(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n);
    int pos=0, neg=1;
    for (int x : nums) {
        if (x < 0) {
            ans[neg] = x;
            neg += 2;
        } else {
            ans[pos] = x;
            pos += 2;
        }
    }
    return ans;
}

int main() {
    vector<int> nums = {3, -2, 1, -5, 2, -4};

    // Choose an approach to run:
    // vector<int> result = rearrangeArray(nums);   // Split + merge
    // vector<int> result = rearrangeArray2(nums);  // Split + write back
    vector<int> result = rearrangeArray3(nums);     // Index parity fill

    for (int i=0; i<(int)result.size(); i++) {
        cout << result[i] << " ";
    }
    return 0;
}
