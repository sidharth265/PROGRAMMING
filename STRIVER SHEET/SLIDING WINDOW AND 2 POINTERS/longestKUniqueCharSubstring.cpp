#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Longest Substring with Exactly K Distinct Characters
 Problem Link: https://practice.geeksforgeeks.org/problems/longest-k-unique-characters-substring/0

 Problem Statement:
 Given a string s and an integer k, find the length of the longest substring that contains exactly k distinct characters.
 If no such substring exists, return -1.

-------------------------------------------------
 Example:
 Input: s = "araaci", k = 2
 Output: 4
 Explanation: The longest substring with 2 distinct characters is "araa".

-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force (Check all substrings)
// -------------------------------------------------
/*
💡 Idea:
   - For every substring, store distinct characters in a set.
   - If set size == k, update max length.
   - Break early if distinct characters exceed k.

🧩 Algorithm:
   1. For i in [0..n-1]:
       - Initialize empty set
       - For j in [i..n-1]:
           - Insert s[j] into set
           - If set size == k, update answer
           - If set size > k, break

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(k)
*/
int longestKSubstrBrute(string &s, int k) {
    int ans = -1;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        unordered_set<char> distinct;
        for (int j = i; j < n; j++) {
            distinct.insert(s[j]);
            if ((int)distinct.size() == k)
                ans = max(ans, j - i + 1);
            else if ((int)distinct.size() > k)
                break;
        }
    }
    return ans;
}


// -------------------------------------------------
// Approach 2: Sliding Window with HashMap (Clean)
// -------------------------------------------------
/*
💡 Idea:
   - Use two pointers (left and right) and a hashmap to count characters.
   - Expand right and add character counts.
   - If distinct chars > k, move left pointer to shrink window.
   - When distinct chars == k, update answer.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(k)
*/
int longestKSubstrSliding(string &s, int k) {
    int ans = -1;
    unordered_map<char, int> charCount;
    int left = 0;
    for (int right = 0; right < (int)s.size(); right++) {
        charCount[s[right]]++;

        while ((int)charCount.size() > k) {
            charCount[s[left]]--;
            if (charCount[s[left]] == 0)
                charCount.erase(s[left]);
            left++;
        }

        if ((int)charCount.size() == k) {
            ans = max(ans, right - left + 1);
        }
    }
    return ans;
}


// -------------------------------------------------
// Approach 3: Sliding Window with HashMap (Slightly Different Control)
// -------------------------------------------------
/*
💡 Idea:
   - Similar to approach 2, but handles shrinking only if distinct count > k at the moment of insertion.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(k)
*/

int longestKSubstrSlidingAlt(string &s, int k) {
    int ans = -1;
    unordered_map<char, int> charCount;
    int left = 0;
    for (int right = 0; right < (int)s.size(); right++) {
        charCount[s[right]]++;

        if ((int)charCount.size() > k) {
            charCount[s[left]]--;
            if (charCount[s[left]] == 0)
                charCount.erase(s[left]);
            left++;
        }

        if ((int)charCount.size() == k)
            ans = right - left + 1;
    }
    return ans;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<pair<string, int>> tests = {
        {"araaci", 2},
        {"araaci", 1},
        {"cbbebi", 3},
        {"aaabbb", 3},
        {"abcdef", 4},
        {"aabbcc", 3}
    };

    for (auto &test : tests) {
        string s = test.first;
        int k = test.second;
        cout << "String: " << s << ", k = " << k << "\n";
        cout << "Brute Force: " << longestKSubstrBrute(s, k) << "\n";
        cout << "Sliding Window: " << longestKSubstrSliding(s, k) << "\n";
        cout << "Sliding Window Alt: " << longestKSubstrSlidingAlt(s, k) << "\n";
        cout << "---------------------------\n";
    }

    // ✅ Approach Overview
    /*
    Approach 1 (Brute Force): O(n^2), SC=O(k)
    Approach 2 (Sliding Window): O(n), SC=O(k)
    Approach 3 (Sliding Window Alternative): O(n), SC=O(k)
    */

    return 0;
}
