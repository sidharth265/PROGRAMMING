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
Approach 1: Brute Force  
💡 Idea:
- Generate all substrings of `s`.
- For each substring, check if it is a palindrome.
- Track the longest one.

🧩 Algorithm:
1. Loop over all possible starting indices `i`.
2. For each `i`, loop over ending index `j`.
3. Extract substring `s[i..j]`.
4. Check palindrome condition manually.
5. If valid and longer, update answer.

⏱ Time Complexity: O(N^3)  
📦 Space Complexity: O(1) (only strings used)
-----------------------------------------------------------*/
bool isPalindrome(const string &sub) {
    int n = sub.size();
    for (int i = 0; i < n / 2; i++) {
        if (sub[i] != sub[n - i - 1]) return false;
    }
    return true;
}

string longestPalindromeBrute(string s) {
    string ans = "";
    int n = s.size();

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            string sub = s.substr(i, j - i + 1);
            if (isPalindrome(sub) && sub.size() > ans.size()) {
                ans = sub;
            }
        }
    }
    return ans;
}

/*-----------------------------------------------------------
Approach 2: Expand Around Center (Better)  
💡 Idea:
- Every palindrome is centered around a character (odd-length) 
  or between two characters (even-length).
- Expand outwards from each center to grow the palindrome.

🧩 Algorithm:
1. Iterate through each index `i`.
2. Expand around single center (odd palindromes).
3. Expand around double center (even palindromes).
4. Track longest palindrome.

⏱ Time Complexity: O(N^2)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
int expandFromCenter(const string &s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1; // length of the palindrome
}

string longestPalindromeCenter(string s) {
    int n = s.size();
    if (n == 0) return "";

    int start = 0, end = 0;

    for (int i = 0; i < n; i++) {
        int len1 = expandFromCenter(s, i, i);     // odd
        int len2 = expandFromCenter(s, i, i + 1); // even
        int len = max(len1, len2);

        if (len > end - start + 1) {
            start = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }
    return s.substr(start, end - start + 1);
}

/*-----------------------------------------------------------
Approach 3: Dynamic Programming (Optimal for clarity)  
💡 Idea:
- Use DP table where dp[i][j] is true if substring s[i..j] is palindrome.
- Fill length 1, 2, then grow lengths.
- Track longest palindrome.

🧩 Algorithm:
1. dp[i][i] = true for all i.
2. dp[i][i+1] = (s[i]==s[i+1]).
3. For length ≥ 3, dp[i][j] = (s[i]==s[j]) && dp[i+1][j-1].
4. Track max length found.

⏱ Time Complexity: O(N^2)  
📦 Space Complexity: O(N^2)
-----------------------------------------------------------*/
string longestPalindromeDP(string s) {
    int n = s.size();
    if (n == 0) return "";

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int start = 0, maxLen = 1;

    for (int i = 0; i < n; i++) dp[i][i] = true;

    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLen = 2;
        }
    }

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
Main Function: Run Multiple Test Cases
-----------------------------------------------------------*/
int main() {
    vector<string> testCases = {"babad", "cbbd", "a", "ac", "racecar", "forgeeksskeegfor"};

    for (string s : testCases) {
        cout << "Input: " << s << endl;
        cout << "  Brute Force      → " << longestPalindromeBrute(s) << endl;
        cout << "  Center Expansion → " << longestPalindromeCenter(s) << endl;
        cout << "  DP Approach      → " << longestPalindromeDP(s) << endl;
        cout << "--------------------------------------------------" << endl;
    }

    /* ✅ Approach Overview
    --------------------------------------------------
    Approach 1: Brute Force  
       Time: O(N^3) | Space: O(1)  

    Approach 2: Expand Around Center  
       Time: O(N^2) | Space: O(1)  

    Approach 3: Dynamic Programming  
       Time: O(N^2) | Space: O(N^2)  

    Best Practical Choice: Expand Around Center (Approach 2)
    --------------------------------------------------
    */
    return 0;
}
