#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Word Break
 Problem Link: (LeetCode 139 or similar)
====================================================

📝 Problem Statement:
Given a string `s` and a dictionary of strings `wordDict`, 
return true if `s` can be segmented into a sequence of one or more dictionary words.
The same word in the dictionary may be reused multiple times.

📌 Input:
- String `s`
- Vector of strings `wordDict`

📌 Output:
- Boolean indicating if segmentation is possible

----------------------------------------------------
🔹 Example:
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true  
Explanation: Because "leetcode" can be segmented as "leet code".

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Backtracking (Recursion)
// Time Complexity: O(n^2 * m) where n = length of s,
// m = average length of words in dictionary
// Space Complexity: O(n) for recursion stack
//////////////////////////////////////////////////////
bool inDict(const string &str, const vector<string> &wordDict) {
    for (const string &word : wordDict) {
        if (word == str) return true;
    }
    return false;
}

void generate(bool &ans, const vector<string> &wordDict, const string &s, int i) {
    if (i == (int)s.length()) {
        ans = true;
        return;
    }
    string str = "";
    for (int j = i; j < (int)s.length(); j++) {
        str += s[j];
        if (!inDict(str, wordDict)) continue;
        generate(ans, wordDict, s, j + 1);
        if (ans) break;
    }
}

bool wordBreakBacktracking(string s, vector<string> &wordDict) {
    bool ans = false;
    generate(ans, wordDict, s, 0);
    return ans;
}

//////////////////////////////////////////////////////
// Approach 2: Optimized Dynamic Programming
//////////////////////////////////////////////////////
/*
💡 Idea:
- Use a DP boolean array dp of size n+1 where dp[i] means s[0..i-1]
  can be segmented into dictionary words.
- dp[0] = true (empty string).
- For each position i, check all j < i, if dp[j] is true and s[j..i-1] in wordDict,
  then dp[i] = true.

🧩 Algorithm:
1. Initialize dp with dp[0] = true, else false.
2. For i in [1..n]:
    For j in [0..i-1]:
       - If dp[j] == true and s.substr(j, i-j) in wordDict,
         dp[i] = true, break;
3. Return dp[n].

⏱ Time Complexity: O(n^2 * m) with efficient lookups  
📦 Space Complexity: O(n)
*/
bool wordBreakDP(string s, vector<string> &wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && dict.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[n];
}

//////////////////////////////////////////////////////
// Main function with example test case
//////////////////////////////////////////////////////
int main() {
    string s = "leetcode";
    vector<string> wordDict = {"leet", "code"};

    cout << "Backtracking: " << wordBreakBacktracking(s, wordDict) << endl;
    cout << "DP:           " << wordBreakDP(s, wordDict) << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// 1. Backtracking: Simple but can be very slow due to repeated computations.
// 2. Dynamic Programming: Efficient caching of solutions to subproblems.
