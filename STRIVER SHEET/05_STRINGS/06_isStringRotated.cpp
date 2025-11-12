#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Rotate String
Problem Link: https://leetcode.com/problems/rotate-string/

Problem Statement:
Given two strings s and goal, determine if s can be rotated some number of times 
(left-rotations) to become goal. Specifically, a "shift" consists of moving the 
leftmost character of s to the rightmost position.

Return true if and only if s can become goal after any number of such shifts.

------------------------------------------------------------
Example 1:
Input: s = "abcde", goal = "cdeab"
Output: true
Explanation: Rotating "abcde" two times to the left results in "cdeab".

Example 2:
Input: s = "abcde", goal = "abced"
Output: false
Explanation: No rotation of "abcde" can produce "abced".

------------------------------------------------------------
Constraints:
- 1 <= s.length, goal.length <= 100
- s and goal consist of lowercase English letters
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Concatenation and Substring Check (Optimal)
==================================================================
💡 Idea:
- If goal is a rotation of s, then goal will be a substring of s+s.
- Check if lengths are equal, and whether goal occurs inside s+s.

🧩 Algorithm:
1. Return false if s.length != goal.length.
2. Concatenate s with itself: doubled = s + s.
3. Check if goal is substring of doubled.
4. Return result.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/
bool rotateString(string s, string goal) {
    if (s.length() != goal.length()) return false;
    string doubled = s + s;
    return doubled.find(goal) != string::npos;
}

/*
==================================================================
Approach 2: Manual Rotation Check (Naive)
==================================================================
💡 Idea:
- Try all possible rotations by slicing and concatenating.
- Check if any rotation matches goal.

🧩 Algorithm:
1. Return false if lengths differ.
2. For i in [0, s.length):
   - Construct rotation = s.substr(i) + s.substr(0, i).
   - If rotation == goal, return true.
3. Return false if none match.

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(1)
*/
bool isRotation(string s, string goal) {
    if (s.length() != goal.length()) return false;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        string rotated = s.substr(i) + s.substr(0, i);
        if (rotated == goal) return true;
    }
    return false;
}

/*
==================================================================
main() function to test both approaches
==================================================================
*/
int main() {
    vector<pair<string,string>> testCases = {
        {"abcde", "cdeab"},    // true
        {"abcde", "abced"},    // false
        {"aa", "aa"},          // true
        {"", ""},              // true
        {"waterbottle", "erbottlewat"} // true
    };

    for (auto& it : testCases) {
        string s = it.first;
        string goal = it.second;
        cout << "s = \"" << s << "\", goal = \"" << goal << "\"" << endl;
        cout << "rotateString (Optimal): " 
             << (rotateString(s, goal) ? "True" : "False") << endl;
        cout << "isRotation (Naive):     " 
             << (isRotation(s, goal) ? "True" : "False") << endl;
        cout << "-------------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Concatenation Check:
   - Time: O(n), Space: O(n)
   - Simple and efficient solution.
   - Recommended for interviews.

2. Manual Rotation:
   - Time: O(n^2), Space: O(1)
   - Less efficient.
   - Good for understanding rotation logic.

👉 Use **Concatenation Check** for best performance and readability.
==================================================================
*/
