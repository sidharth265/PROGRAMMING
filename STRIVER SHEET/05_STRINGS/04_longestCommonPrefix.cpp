#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Longest Common Prefix
Problem Link: https://leetcode.com/problems/longest-common-prefix/

Problem Statement:
Write a function to find the longest common prefix string amongst an array of strings. 
If there is no common prefix, return an empty string "".

------------------------------------------------------------
Example 1:
Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

------------------------------------------------------------
Constraints:
- 0 <= strs.length <= 200
- 0 <= strs[i].length <= 200
- strs[i] consists of only lowercase English letters.
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Vertical Scanning
==================================================================
💡 Idea:
- Compare characters one-by-one vertically across all strings.
- Stop when a mismatch or end of any string is encountered.

🧩 Algorithm:
1. Find length of shortest string (limit).
2. Iterate over indices from 0 to limit-1:
   - Check character in strs[0].
   - Verify all other strings have same character at that position.
   - If mismatch, break and return prefix so far.
3. Return prefix from strs[0].

⏱ Time Complexity: O(N * M), N=number of strings, M=length of shortest string
📦 Space Complexity: O(1) (result string space ignored)
*/

string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    int n = strs.size();
    int minLength = INT_MAX;
    for (const string& s : strs)
        minLength = min(minLength, (int)s.length());

    string prefix = "";
    for (int i = 0; i < minLength; i++) {
        char c = strs[0][i];
        for (int j = 1; j < n; j++) {
            if (strs[j][i] != c) {
                return prefix;
            }
        }
        prefix.push_back(c);
    }
    return prefix;
}

/*
==================================================================
main() function with test cases
==================================================================
*/
int main() {
    vector<vector<string>> testCases = {
        {"flower", "flow", "flight"},  // Expected: "fl"
        {"dog", "racecar", "car"},     // Expected: ""
        {},                           // Expected: ""
        {"a"},                        // Expected: "a"
        {"abc", "abc", "abc"},        // Expected: "abc"
    };

    for (auto& strs : testCases) {
        cout << "Strings: ";
        for (auto& s : strs) cout << "\"" << s << "\" ";
        cout << "\nLongest Common Prefix: " << longestCommonPrefix(strs) << "\n";
        cout << "---------------------------------\n";
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
- Vertical scanning compares characters one position at a time among all strings.
- Time complexity: O(N*M) where N = number of strings and M = shortest string length.
- Space complexity: O(1) extra space.
- Simple, intuitive, and widely accepted solution for interviews.

Alternative approaches include binary search and divide-and-conquer but vertical scanning is often preferred for simplicity.
==================================================================
*/
