#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Longest Repeating Character Replacement
 Problem Link: https://leetcode.com/problems/longest-repeating-character-replacement/

 Problem Statement:
 You are given a string `s` consisting only of uppercase English letters 
 and an integer `k`. You can choose any substring of the string and 
 replace at most `k` characters in it so that all characters in the substring 
 are the same.

 Return the length of the longest such substring.

-------------------------------------------------
 Example 1:
 Input: s = "ABAB", k = 2
 Output: 4
 Explanation: Replace both 'A's with 'B's → "BBBB", length = 4.

 Example 2:
 Input: s = "AABABBA", k = 1
 Output: 4
 Explanation: Replace one 'B' → "AAAA" or "BBBB", longest length = 4.
-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force (Check All Substrings)
// -------------------------------------------------
/*
💡 Idea:
   - For every substring s[i..j], check the most frequent character count. 
   - If the substring length minus max frequency ≤ k, it's valid.
   - Track the longest valid substring.

🧩 Algorithm:
   1. Iterate over all start indices i.
   2. Expand j forward, maintain counts of characters.
   3. At each step, compute max frequency in substring.
   4. If (len - maxFreq) ≤ k, update answer.

⏱ Time Complexity: O(n^2 * 26) ~ O(26 n^2)
📦 Space Complexity: O(26)
*/

int characterReplacementBrute(string s, int k) {
    int n = s.size(), ans = 0;
    for (int i = 0; i < n; i++) {
        vector<int> count(26, 0);
        int maxFreq = 0;
        for (int j = i; j < n; j++) {
            count[s[j]-'A']++;
            maxFreq = max(maxFreq, count[s[j]-'A']);
            int changes = (j - i + 1) - maxFreq;
            if (changes <= k) ans = max(ans, j - i + 1);
        }
    }
    return ans;
}


// -------------------------------------------------
// Approach 2: Sliding Window (Recompute Max Each Shrink)
// -------------------------------------------------
/*
💡 Idea:
   - Use two pointers [left..right].
   - Maintain count of chars in window.
   - Keep track of max frequency in window.
   - If window size - maxFreq > k → shrink from left.
   - Recompute maxFreq (costly but safe).

🧩 Algorithm:
   1. Maintain hash array size 26.
   2. Expand right pointer, increment frequency.
   3. While invalid (need > k changes):
         - move left pointer and decrement count.
         - recompute maxFreq (O(26)).
   4. Track answer.

⏱ Time Complexity: O(26n) ~ O(n)
📦 Space Complexity: O(26)
*/

int characterReplacementSliding(string s, int k) {
    int n = s.size(), ans = 0;
    vector<int> count(26, 0);
    int left = 0, maxFreq = 0;

    for (int right = 0; right < n; right++) {
        count[s[right]-'A']++;
        maxFreq = max(maxFreq, count[s[right]-'A']);

        while ((right - left + 1) - maxFreq > k) {
            count[s[left]-'A']--;
            left++;
            maxFreq = 0;
            for(int i=0; i<26; i++) maxFreq = max(maxFreq, count[i]);
        }
        ans = max(ans, right - left + 1);
    }
    return ans;
}


// -------------------------------------------------
// Approach 3: Optimal Sliding Window (Lazy Max Tracking)
// -------------------------------------------------
/*
💡 Idea:
   - Instead of recomputing maxFreq on every shrink, 
     maintain a "lazy" maxCount that only ever increases.
   - Why safe?
     Because even if maxCount is slightly outdated, 
     the shrink condition ensures correctness:
       if windowLen - maxCount > k, shrink until valid again.

🧩 Algorithm:
   1. Maintain freq[26], left=0, maxCount=0, ans=0.
   2. Expand right pointer:
       - increment freq[s[right]]
       - maxCount = max(maxCount, freq[s[right]]) (only increases)
   3. If invalid: shrink from left (but don't recompute maxCount).
   4. Track max window length.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(26)
*/

int characterReplacementOptimal(string s, int k) {
    int n = s.size();
    vector<int> count(26, 0);
    int left = 0, ans = 0, maxCount = 0;

    for (int right = 0; right < n; right++) {
        count[s[right]-'A']++;
        maxCount = max(maxCount, count[s[right]-'A']);

        while ((right - left + 1) - maxCount > k) {
            count[s[left]-'A']--;
            left++;
        }
        ans = max(ans, right - left + 1);
    }
    return ans;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<pair<string,int>> tests = {
        {"ABAB", 2},
        {"AABABBA", 1},
        {"AAAA", 2},
        {"ABCDE", 1},
        {"BAAAB", 2}
    };

    for (auto &t : tests) {
        string s = t.first; int k = t.second;
        cout << "Input: " << s << ", k=" << k << "\n";
        cout << "Brute Force: " << characterReplacementBrute(s,k) << "\n";
        cout << "Sliding Window: " << characterReplacementSliding(s,k) << "\n";
        cout << "Optimal: " << characterReplacementOptimal(s,k) << "\n";
        cout << "------------------------------\n";
    }

    // ✅ Approach Overview
    /*
    Approach 1 (Brute Force):        TC = O(26 * n^2), SC = O(26)
    Approach 2 (Sliding w/ recompute)TC = O(26n),      SC = O(26)
    Approach 3 (Optimal Sliding):    TC = O(n),        SC = O(26)
    */
    return 0;
}
