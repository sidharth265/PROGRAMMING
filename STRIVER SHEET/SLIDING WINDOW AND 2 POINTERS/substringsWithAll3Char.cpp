#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Number of Substrings Containing All Three Characters
 Problem Link: https://leetcode.com/problems/check-if-all-characters-have-equal-number-of-occurrences/

 Problem Statement:
 Given a string s consisting only of characters 'a', 'b', and 'c',
 return the number of substrings containing at least one occurrence of all these characters.

-------------------------------------------------
 Example:
 Input: s = "abcabc"
 Output: 10
 Explanation:
 Substrings that contain all three characters counted.

-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force (O(n^2))
// -------------------------------------------------
/*
💡 Idea:
   - For every substring, count 'a', 'b', 'c'.
   - If all non-zero, increment answer.

🧩 Algorithm:
   1. For every start i:
       - Initialize count array [0,0,0]
       - For every end j:
           - Increment count of current char
           - Check if all counts > 0, if yes increment ans

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(1)
*/

int numberOfSubstringsBrute(string s) {
    int ans = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        vector<int> charCount(3, 0);
        for (int j = i; j < n; j++) {
            charCount[s[j] - 'a']++;
            if (charCount[0] > 0 && charCount[1] > 0 && charCount[2] > 0) {
                ans++;
            }
        }
    }
    return ans;
}


// -------------------------------------------------
// Approach 2: Optimized Break (O(n^2))
// -------------------------------------------------
/*
💡 Idea:
   - As soon as substring contains all chars, 
     add all remaining substrings starting at i to answer.
   - Break inner loop after first valid substring.

🧩 Algorithm:
   Same as brute force but break early and add all remaining substrings directly to answer.

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(1)
*/

int numberOfSubstringsBreak(string s) {
    int ans = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        vector<int> charCount(3, 0);
        for (int j = i; j < n; j++) {
            charCount[s[j] - 'a']++;
            if (charCount[0] > 0 && charCount[1] > 0 && charCount[2] > 0) {
                ans += n - j;
                break;
            }
        }
    }
    return ans;
}


// -------------------------------------------------
// Approach 3: Sliding Window (O(n))
// -------------------------------------------------
/*
💡 Idea:
   - Expand right pointer, update counts.
   - When window valid (all chars ≥ 1), move left pointer to shrink as much as possible.
   - Add number of valid substrings ending at right = s.size() - right.

🧩 Algorithm:
   1. Initialize left=0, right=0, ans=0
   2. Expand right, update counts
   3. While valid, add s.size()-right to ans and move left to shrink
   4. Return ans

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/

int numberOfSubstringsSliding(string s) {
    int ans = 0;
    int n = s.size();
    vector<int> charCount(3, 0);
    int left = 0;
    for (int right = 0; right < n; right++) {
        charCount[s[right] - 'a']++;
        while (charCount[0] > 0 && charCount[1] > 0 && charCount[2] > 0) {
            ans += n - right;
            charCount[s[left] - 'a']--;
            left++;
        }
    }
    return ans;
}


// -------------------------------------------------
// Approach 4: Index Tracking (O(n))
// -------------------------------------------------
/*
💡 Idea:
   - Track last seen indices of characters a, b, c.
   - For each position i, min of last seen indices gives earliest valid start of substring.
   - Number of substrings ending at i containing all chars = min(last_seen) + 1

🧩 Algorithm:
   1. Initialize lastSeen = {-1, -1, -1}
   2. For each i in s:
       - Update lastSeen[s[i]]
       - Calculate minIndex = min(lastSeen)
       - Add minIndex + 1 to ans

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/

int numberOfSubstringsIndexTracking(string s) {
    int ans = 0;
    vector<int> lastSeen(3, -1);
    for (int i = 0; i < (int)s.size(); i++) {
        lastSeen[s[i] - 'a'] = i;
        int minIndex = *min_element(lastSeen.begin(), lastSeen.end());
        ans += minIndex + 1;
    }
    return ans;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<string> testCases = {
        "abcabc",
        "aaacb",
        "abc",
        "ab",
        "aaa",
        "cbabcacab"
    };

    for (const string& s : testCases) {
        cout << "String: " << s << "\n";
        cout << "Brute Force: " << numberOfSubstringsBrute(s) << "\n";
        cout << "Break Early: " << numberOfSubstringsBreak(s) << "\n";
        cout << "Sliding Window: " << numberOfSubstringsSliding(s) << "\n";
        cout << "Index Tracking: " << numberOfSubstringsIndexTracking(s) << "\n";
        cout << "------------------------\n";
    }

    // -------------------------------------------------
    // ✅ Approach Overview
    // -------------------------------------------------
    /*
    Approach 1 (Brute Force):    TC = O(n^2), SC = O(1)
    Approach 2 (Break Early):    TC = O(n^2), SC = O(1) (less work)
    Approach 3 (Sliding Window): TC = O(n),   SC = O(1)
    Approach 4 (Index Tracking): TC = O(n),   SC = O(1)
    */

    return 0;
}
