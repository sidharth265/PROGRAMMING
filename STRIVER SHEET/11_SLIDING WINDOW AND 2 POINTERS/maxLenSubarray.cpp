#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Longest Substring Without Repeating Characters

Problem Statement:
Given a string s, return the length of the longest substring without repeating characters.

Example:
Input:  s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with length 3.

Approach Overview:
- Brute Force: For each start index, expand while tracking seen characters; stop on repeat.
- Optimized Sliding Window: Keep a left pointer and the last index of each character; when a repeat occurs, move left just past the previous occurrence.
*/

/*
Approach: Brute Force
Approach Idea:
- For every starting position i, grow the substring to the right,
  tracking whether a character has been seen in the current window.
- Stop growth when encountering a repeated character.

Algorithm:
1) ans = 0
2) For i in [0..n-1]:
   - seen = empty hash set (or map to bool)
   - For j in [i..n-1]:
       - If s[j] in seen: break
       - Insert s[j] into seen
       - ans = max(ans, j - i + 1)
3) Return ans

Time Complexity: O(n^2)
Space Complexity: O(n)
*/
int lengthOfLongestSubstring(string s) {
    int n = s.length();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        unordered_set<char> seen;
        for (int j = i; j < n; j++) {
            if (seen.count(s[j])) break;
            seen.insert(s[j]);
            ans = max(ans, j - i + 1);
        }
    }
    return ans;
}

/*
Approach: Optimized Sliding Window (Two-pointer with last seen index)
Approach Idea:
- Maintain left boundary l of current window and an array last[c] storing the last index where character c appeared.
- Iterate r from left to right:
  - If last[s[r]] >= l, move l to last[s[r]] + 1 to avoid repeating character.
  - Update last[s[r]] = r and compute window length r - l + 1.

Algorithm:
1) Initialize last[256] = -1, l = 0, ans = 0
2) For r in [0..n-1]:
   - c = s[r]
   - If last[c] >= l: l = last[c] + 1
   - last[c] = r
   - ans = max(ans, r - l + 1)
3) Return ans

Time Complexity: O(n)
Space Complexity: O(min(n, m)) where m is charset size (256 for extended ASCII)
*/
int lengthOfLongestSubstring2(string s) {
    vector<int> last(256, -1);
    int n = s.size(), ans = 0, l = 0;
    for (int r = 0; r < n; r++) {
        unsigned char c = s[r];
        if (last[c] >= l) l = last[c] + 1;
        last[c] = r;
        ans = max(ans, r - l + 1);
    }
    return ans;
}

int main() {
    string s = "abcabcbb";
    cout << "Brute Force: " << lengthOfLongestSubstring(s) << "\n";
    cout << "Optimized: " << lengthOfLongestSubstring2(s) << "\n";
    return 0;
}
