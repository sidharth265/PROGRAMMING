#include<bits/stdc++.h>
using namespace std;

/*
Problem: Longest Consecutive Sequence

Problem Statement:
Given an unsorted array of integers nums, find the length of the longest consecutive elements sequence.

Example:
Input:
  nums = [100, 4, 200, 1, 3, 2]
Output:
  4
Explanation:
- The longest consecutive sequence is [1, 2, 3, 4], so the length is 4.

Approach Overview:
- Hash Map Presence Check: Mark presence of each value, then grow sequences starting only at potential starts.
- Sorting: Sort and scan to count runs of consecutive numbers, skipping duplicates.
- Unordered Set (Bidirectional expansion): Use a set, expand left and right from each unvisited element, erasing as you go.

Complexity Overview:
- Hash Map Presence: Time O(n), Space O(n).
- Sorting: Time O(n log n), Space O(1) extra (ignoring input).
- Unordered Set Expansion: Time O(n) average, Space O(n).
*/

/*
Approach 1: Hash Map Presence Check (O(n))

Idea:
- Insert all numbers into a hash map as present.
- For each number, only start counting if (num-1) is not present (i.e., num is a sequence start).
- Increment forward while (num+1) exists; track max length.

Algorithm:
1) Insert all nums[i] into an unordered_map<int,bool> as present = true.
2) For each nums[i]:
   - If (nums[i]-1) exists, continue (not a start).
   - Else, count forward while (current+1) exists; update answer.
3) Return the maximum length.

Time Complexity: O(n) average
Space Complexity: O(n)
*/
int longestConsecutive(vector<int>& nums) {
    int n = nums.size();
    unordered_map<int,bool> m;
    for (int i=0; i<n; i++) {
        m[nums[i]] = 1;
    }
    int ans = 0;
    for (int i=0; i<n; i++) {
        if (m[nums[i]-1]){
            continue;
        }
        int c = 1;
        while (m[nums[i]+1]) {
            c++;
            nums[i]++;
        }
        ans = max(ans, c); 
    }
    return ans;
}

/*
Approach 2: Sorting (O(n log n))

Idea:
- Sort the array.
- Scan and count the length of consecutive sequences, skipping duplicates.

Algorithm:
1) Sort nums.
2) Initialize count for the current streak; update ans when the streak breaks.
3) Handle duplicates by skipping them without resetting the streak.
4) Return max(ans, count).

Time Complexity: O(n log n)
Space Complexity: O(1) extra (excluding input)
*/
int longestConsecutive2(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int count = 0;
    int ans = 0;
    int e = nums[0];
    for (int i=1; i<n; i++) {
        if (nums[i] == e+1) {
            count++;
        }
        else if (nums[i] == e) {
            continue;
        }
        else{
            ans = max(ans, count);
            count = 1;
        }
        e = nums[i];
    }
    return max(ans, count);
}

/*
Approach 3: Unordered Set Expansion (O(n) average)

Idea:
- Insert all elements into an unordered_set.
- For each element still in the set, expand left and right while neighbors exist, erasing visited elements to avoid reprocessing.

Algorithm:
1) s = set(nums)
2) ans = 0
3) For each x in nums:
   - If x not in s, continue
   - Remove x, expand left (x-1, x-2,...) and right (x+1, x+2,...) erasing as you go
   - Track count = span length, ans = max(ans, count)
4) Return ans

Time Complexity: O(n) average
Space Complexity: O(n)
*/
int longestConsecutive3(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int ans = 0;
    for (int i=0; i<nums.size(); i++) {
        if (s.find(nums[i]) == s.end()) {
            continue;
        }
        int count = 1;
        s.erase(nums[i]);
        int left = nums[i]-1;
        while (s.find(left) != s.end()) {
            count++;
            s.erase(left);
            left--;
        }
        int right = nums[i]+1;
        while (s.find(right) != s.end()) {
            count++;
            s.erase(right);
            right++;
        }
        ans = max(ans, count);
    }
    return ans;
}

int main() {
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << "Longest Consecutive Sequence Length: " << longestConsecutive3(nums) << endl;
    return 0;
}
