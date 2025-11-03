#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Minimum Window Substring
 LeetCode Link: https://leetcode.com/problems/minimum-window-substring/

 Problem Statement:
 -----------------
 Given two strings `s` and `t` of lengths m and n respectively,
 return the minimum window substring of `s` such that 
 every character in `t` (including duplicates) is included 
 in the window. If no such substring exists, return an empty string "".

 Example 1:
 Input: s = "ADOBECODEBANC", t = "ABC"
 Output: "BANC"
 Explanation: The minimum window substring that contains "A", "B", and "C" is "BANC".

 Example 2:
 Input: s = "a", t = "a"
 Output: "a"

 Example 3:
 Input: s = "a", t = "aa"
 Output: ""
 Explanation: Both 'a's are not present in s.

 Constraints:
 - 1 <= s.length, t.length <= 10^5
 - s and t consist of uppercase and lowercase English letters.
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force
 -----------------------------------------
 💡 Idea:
 Try all substrings of `s`, and check if each contains all chars of `t`. 
 Keep track of the smallest valid substring.

 🧩 Algorithm:
 1. Initialize an answer `(start, length)` as invalid.
 2. Loop over all possible start indices `i`.
 3. For each start, expand substring with `j` until all chars of `t` are present.
 4. If valid, update answer with min length.
 5. Return smallest substring found.

 ⏱ Time Complexity: O(N^2 * |t|) [expensive substring checks]
 📦 Space Complexity: O(|t|) [character counts]
*/
string minWindowBruteForce(string s, string t) {
    int n = s.size();
    pair<int, int> ans = {n, n}; // {start, length}
    for (int i = 0; i < n; i++) {
        int count = 0;
        unordered_map<char, int> charCount;
        for (char ch : t) charCount[ch]++;

        for (int j = i; j < n; j++) {
            if (--charCount[s[j]] >= 0) count++;
            if (count == t.size()) {
                if (ans.second >= j - i + 1) ans = {i, j - i + 1};
                break;
            }
        }
    }
    return (ans.first == n) ? "" : s.substr(ans.first, ans.second);
}


/* 
==========================================
 Approach 2: Sliding Window (Optimal)
 -----------------------------------------
 💡 Idea:
 Use two pointers (`left`, `right`) with a sliding window and maintain counts.
 Expand right until all characters of `t` are covered.
 Then contract from the left to minimize window.

 🧩 Algorithm:
 1. Count frequency of characters in `t` (hashmap `need`).
 2. Expand `right` pointer, decrementing counts in hashmap.
 3. Each time we "cover" all characters, 
    - Try moving `left` forward while still valid.
    - Update answer with min length.
 4. Return min window found.

 ⏱ Time Complexity: O(N) (each char visited at most twice)
 📦 Space Complexity: O(|t|) for the hashmap
*/
string minWindowSlidingWindow(string s, string t) {
    pair<int, int> ans = {-1, (int)s.size()}; // {start, length}
    int left = 0, count = 0;
    unordered_map<char, int> charCount;
    for (char ch : t) charCount[ch]++;

    for (int right = 0; right < s.size(); right++) {
        if (--charCount[s[right]] >= 0) count++;

        while (count == t.size()) {
            if (ans.second >= (right - left + 1)) {
                ans = {left, right - left + 1};
            }
            if (++charCount[s[left]] > 0) count--;
            left++;
        }
    }

    return (ans.first == -1) ? "" : s.substr(ans.first, ans.second);
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<pair<string,string>> testCases = {
        {"ADOBECODEBANC", "ABC"},
        {"a", "a"},
        {"a", "aa"},
        {"aa", "aa"},
        {"ab", "b"}
    };

    cout << "=== Testing Minimum Window Substring Problem ===\n\n";
    for (auto &tc : testCases) {
        string s = tc.first, t = tc.second;
        cout << "Input: s = \"" << s << "\", t = \"" << t << "\"\n";
        
        string ans1 = minWindowBruteForce(s, t);
        string ans2 = minWindowSlidingWindow(s, t);

        cout << " Brute Force:       \"" << ans1 << "\"\n";
        cout << " Sliding Window:    \"" << ans2 << "\"\n";
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N^2 * |t|), not feasible for large input.\n";
    cout << "2. Sliding Window -> O(N), optimal and widely used in interviews.\n";

    return 0;
}
