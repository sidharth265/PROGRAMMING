#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Longest Palindromic Substring
LeetCode Link: https://leetcode.com/problems/longest-palindromic-substring/

Problem Statement:
Given a string `s`, return the longest palindromic substring in `s`.

A palindrome is a string that reads the same forward and backward.

-----------------------------------------------------------
Example 1:
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"

Example 3:
Input: s = "a"
Output: "a"

Example 4:
Input: s = "ac"
Output: "a"

===========================================================
*/

/*-----------------------------------------------------------
Approach 1: Brute Force (Check all substrings)
💡 Idea:
- Generate all substrings of `s`.
- Check each substring if it is a palindrome.
- Track the longest one found.

🧩 Algorithm:
1. Loop through all starting indices `i`.
2. For each `i`, loop for ending index `j`.
3. Extract substring `s[i..j]`.
4. Check if it's a palindrome by comparing characters from both ends.
5. Keep track of the longest palindromic substring.

⏱ Time Complexity: O(N^3)  
   - O(N^2) for substring generation, O(N) for palindrome check  
📦 Space Complexity: O(N) (for temporary substring storage)
-----------------------------------------------------------*/
string longestPalindromeBrute(string s) {
    string ans = "";
    int n = s.size();

    for (int i = 0; i < n; i++) {
        string sub = "";
        for (int j = i; j < n; j++) {
            sub.push_back(s[j]);

            // Check if `sub` is palindrome
            bool isPal = true;
            int m = sub.size();
            for (int k = 0; k < m / 2; k++) {
                if (sub[k] != sub[m - k - 1]) {
                    isPal = false;
                    break;
                }
            }

            if (isPal && ans.size() < m) {
                ans = sub;
            }
        }
    }
    return ans;
}

/*-----------------------------------------------------------
Approach 2: Expand Around Center
💡 Idea:
- A palindrome mirrors around its center.
- Consider each index (and the gap between two indices) as a center.
- Expand outward while characters match.

🧩 Algorithm:
1. For each index `i` in the string:
   a) Expand with `i` as the middle (odd-length palindromes).
   b) Expand with `i` and `i+1` as the middle (even-length palindromes).
2. Keep track of the longest palindrome found.

⏱ Time Complexity: O(N^2)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/

// Helper to expand palindrome from center
int expandFromCenter(const string &s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1; // length of palindrome
}

string longestPalindromeCenter(string s) {
    int n = s.size();
    if (n == 0) return "";

    int start = 0, end = 0;

    for (int i = 0; i < n; i++) {
        int len1 = expandFromCenter(s, i, i);     // odd length
        int len2 = expandFromCenter(s, i, i + 1); // even length
        int len = max(len1, len2);

        if (len > end - start + 1) {
            start = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }

    return s.substr(start, end - start + 1);
}

/*-----------------------------------------------------------
Approach 3: Dynamic Programming (Optional - Optimal for clarity)
💡 Idea:
- Use a DP table where `dp[i][j] = true` if substring `s[i..j]` is palindrome.
- Fill the table diagonally:
   - Single chars are palindrome
   - Check pairs of chars
   - Expand for longer substrings
- Track the max length substring.

🧩 Algorithm:
1. Initialize `dp[i][i] = true` for all i.
2. Check pairs `s[i]==s[i+1]`.
3. For length >= 3, check `s[i]==s[j] && dp[i+1][j-1]`.
4. Record max length palindrome.

⏱ Time Complexity: O(N^2)  
📦 Space Complexity: O(N^2)
-----------------------------------------------------------*/
string longestPalindromeDP(string s) {
    int n = s.size();
    if (n == 0) return "";

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int start = 0, maxLen = 1;

    // length 1 substrings
    for (int i = 0; i < n; i++) dp[i][i] = true;

    // length 2 substrings
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLen = 2;
        }
    }

    // length >=3 substrings
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (len > maxLen) {
                    start = i;
                    maxLen = len;
                }
            }
        }
    }

    return s.substr(start, maxLen);
}

/*-----------------------------------------------------------
Main Function: Test all approaches
-----------------------------------------------------------*/
int main() {
    vector<string> testCases = {"babad", "cbbd", "a", "ac", "racecar", "abaxyzzyxf"};

    for (string s : testCases) {
        cout << "Input: " << s << endl;
        cout << "  Brute Force      → " << longestPalindromeBrute(s) << endl;
        cout << "  Center Expansion → " << longestPalindromeCenter(s) << endl;
        cout << "  DP Approach      → " << longestPalindromeDP(s) << endl;
        cout << "---------------------------------------------" << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach 1: Brute Force  
       Time: O(N^3) | Space: O(N)  
    Approach 2: Expand Around Center  
       Time: O(N^2) | Space: O(1)  
    Approach 3: Dynamic Programming  
       Time: O(N^2) | Space: O(N^2)  

    Best Practical Choice → Expand Around Center (Approach 2)
    -----------------------------------------------------------
    */
    return 0;
}
