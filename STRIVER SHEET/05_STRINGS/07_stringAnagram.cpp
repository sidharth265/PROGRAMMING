#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Valid Anagram
LeetCode Link: https://leetcode.com/problems/valid-anagram/

Problem Statement:
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all original letters exactly once.

-----------------------------------------------------------
Example 1:
Input: s = "anagram", t = "nagaram"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false

===========================================================
*/

/*-----------------------------------------------------------
Approach 1: Using unordered_map to count character frequencies
💡 Idea:
- Count frequency of each character in s.
- Decrement frequency by traversing t.
- If any frequency differs from zero, return false.

🧩 Algorithm:
1. If s and t are different lengths, return false.
2. Initialize unordered_map<char, int> for frequency counts.
3. Increment counts for characters in s.
4. Decrement counts for characters in t.
5. Check map values; if any value not zero, return false.
6. Otherwise, return true.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(1) as map size limited by alphabet (typically 256)
-----------------------------------------------------------*/
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;

    unordered_map<char, int> freq;
    for (char ch : s) freq[ch]++;
    for (char ch : t) freq[ch]--;

    for (auto &p : freq) {
        if (p.second != 0) return false;
    }
    return true;
}

/*-----------------------------------------------------------
Approach 2: Using a fixed size array for lowercase letters
💡 Idea:
- Use fixed-size frequency array for characters 'a'-'z'.
- Increment counts for s, decrement for t.
- Check if all counts are zero.

🧩 Algorithm:
1. If s and t differ in length, return false.
2. Initialize vector<int> of size 26 to zero.
3. For each character in s, increment corresponding count.
4. For each character in t, decrement corresponding count.
5. If any count is not zero, return false.
6. Else, return true.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(1) (fixed size 26)
-----------------------------------------------------------*/
bool isAnagram2(string s, string t) {
    if (s.length() != t.length()) return false;

    vector<int> count(26, 0);
    for (char ch : s) count[ch - 'a']++;
    for (char ch : t) count[ch - 'a']--;

    for (int c : count) {
        if (c != 0) return false;
    }
    return true;
}

/*-----------------------------------------------------------
Approach 3: Sorting and comparing strings
💡 Idea:
- Sort both strings.
- If identical, they are anagrams; else not.

🧩 Algorithm:
1. If lengths differ, return false.
2. Sort s and t.
3. Compare characters at each position.
4. Return true if all match, else false.

⏱ Time Complexity: O(n log n)  
📦 Space Complexity: O(1) (if in-place sort)
-----------------------------------------------------------*/
bool isAnagram3(string s, string t) {
    if (s.length() != t.length()) return false;

    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    return s == t;
}

/*-----------------------------------------------------------
Approach 4: Using fixed-size frequency array for ASCII characters
💡 Idea:
- Like approach 2 but use a 256-sized array for all ASCII chars.

🧩 Algorithm:
1. Check length equality.
2. Initialize int arr[256] to 0.
3. Increment for s chars, decrement for t chars.
4. Check if any arr[i] != 0, return false.
5. Else return true.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
bool isAnagram4(string s, string t) {
    if (s.length() != t.length()) return false;

    int arr[256] = {0};
    for (char ch : s) arr[ch]++;
    for (char ch : t) arr[ch]--;

    for (int i = 0; i < 256; i++) {
        if (arr[i] != 0) return false;
    }
    return true;
}

/*-----------------------------------------------------------
Main function: Testing all approaches on the same example
-----------------------------------------------------------*/
int main() {
    string s = "anagram";
    string t = "nagaram";

    cout << "Using unordered_map: " << (isAnagram(s, t) ? "True" : "False") << endl;
    cout << "Using fixed array (26 letters): " << (isAnagram2(s, t) ? "True" : "False") << endl;
    cout << "Using sorting: " << (isAnagram3(s, t) ? "True" : "False") << endl;
    cout << "Using ASCII array (256 chars): " << (isAnagram4(s, t) ? "True" : "False") << endl;

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach 1: unordered_map frequency counting  
       Time: O(n) | Space: O(1) (bounded by character set)

    Approach 2: Fixed-size array frequency for lowercase letters  
       Time: O(n) | Space: O(1)

    Approach 3: Sorting strings and comparing  
       Time: O(n log n) | Space: O(1)

    Approach 4: Fixed-size array for ASCII characters  
       Time: O(n) | Space: O(1)

    Approach 2 is often the most efficient for lowercase English alphabets.
    -----------------------------------------------------------
    */
    return 0;
}
