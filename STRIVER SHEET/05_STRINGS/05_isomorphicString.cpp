#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Isomorphic Strings
Problem Link: LeetCode #205 (https://leetcode.com/problems/isomorphic-strings/)

Problem Statement:
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.
- All occurrences of a character must be replaced with another character 
  while preserving the order of characters.
- No two characters may map to the same character, but a character may map to itself.

------------------------------------------------------------
Example 1:
Input: s = "egg", t = "add"
Output: true
Explanation:
'e' → 'a', 'g' → 'd' works.

Example 2:
Input: s = "foo", t = "bar"
Output: false
Explanation:
'f' → 'b', 'o' → 'a'/'r' causes conflict.

Example 3:
Input: s = "paper", t = "title"
Output: true
Explanation:
'p' → 't', 'a' → 'i', 'e' → 'l', 'r' → 'e'.

------------------------------------------------------------
Constraints:
- 1 ≤ s.length ≤ 5 * 10^4
- s and t consist of valid ASCII characters
------------------------------------------------------------
*/


/*
==================================================================
Approach 1: Two Pass Mapping (Two Maps)
==================================================================
💡 Idea:
- Ensure both directions are consistent (s → t and t → s).
- First pass: enforce mapping t[i] -> s[i].
- Second pass: enforce mapping s[i] -> t[i].

🧩 Algorithm:
1. Iterate both strings, update map for t→s; if mismatch, return false.
2. Clear map, repeat for s→t.
3. Return true if consistent both ways.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1) (limited to 256 chars)
*/
bool isIsomorphic1(string s, string t) {
    if (s.size() != t.size()) return false;
    map<char,char> m;
    for (int i=0; i<s.size(); i++) {
        if (m.count(t[i])==0) m[t[i]] = s[i];
        else if (m[t[i]] != s[i]) return false;
    }
    m.clear();
    for (int i=0; i<s.size(); i++) {
        if (m.count(s[i])==0) m[s[i]] = t[i];
        else if (m[s[i]] != t[i]) return false;
    }
    return true;
}


/*
==================================================================
Approach 2: Using Two Hash Arrays
==================================================================
💡 Idea:
- Direct mapping using arrays of size 256 for constant-time lookup.
- Track mapping in both directions.

🧩 Algorithm:
1. Create two arrays mapST and mapTS.
2. If mapST[c1]==0 and mapTS[c2]==0 → set mapping.
3. Else check consistency, return false on conflict.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/
bool isIsomorphic2(string s, string t) {
    if (s.length() != t.length()) return false;
    int mapST[256] = {0}, mapTS[256] = {0};
    for (int i=0; i<s.size(); i++) {
        char c1 = s[i], c2 = t[i];
        if (mapST[c1]==0 && mapTS[c2]==0) {
            mapST[c1]=c2; mapTS[c2]=c1;
        } else if (mapST[c1]!=c2 || mapTS[c2]!=c1) {
            return false;
        }
    }
    return true;
}


/*
==================================================================
Approach 3: HashMap (Bidirectional)
==================================================================
💡 Idea:
- Use unordered_map for mapping both ways.
- Similar to array mapping, but cleaner and extensible.

🧩 Algorithm:
1. For each pair (c1,c2):
   - If not mapped yet in both directions → map.
   - Else check consistency.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1) (bounded by character set)
*/
bool isIsomorphic3(string s, string t) {
    if (s.length() != t.length()) return false;
    unordered_map<char,char> mapST;
    unordered_map<char,char> mapTS;
    for (int i=0; i<s.size(); i++) {
        char c1 = s[i], c2 = t[i];
        if (mapST.count(c1)==0 && mapTS.count(c2)==0) {
            mapST[c1]=c2; mapTS[c2]=c1;
        } else if (mapST[c1] != c2 || mapTS[c2] != c1)
            return false;
    }
    return true;
}


/*
==================================================================
Approach 4: Single Map + Set
==================================================================
💡 Idea:
- Only one mapping, but also track used values in a set.
- If target char already used by someone else → invalid.

🧩 Algorithm:
1. For each char in s→t:
   - If mapping exists, check consistency.
   - Else if target already used in set → conflict → return false.
   - Else, establish new mapping and record usage in set.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/
bool isIsomorphic4(string s, string t) {
    if (s.length() != t.length()) return false;
    map<char,char> m;
    set<char> used;
    for (int i=0; i<s.size(); i++) {
        if (m.count(t[i])==0) {
            if (used.count(s[i])) return false;
            m[t[i]]=s[i];
            used.insert(s[i]);
        } else if (m[t[i]] != s[i]) return false;
    }
    return true;
}


/*
==================================================================
main() function
==================================================================
*/
int main() {
    vector<pair<string,string>> testCases = {
        {"egg","add"},   // true
        {"foo","bar"},   // false
        {"paper","title"}, // true
        {"ab","aa"}      // false
    };

    for (auto [s,t] : testCases) {
        cout << "s = " << s << ", t = " << t << endl;
        cout << "Approach 1 (Two Pass):  " << (isIsomorphic1(s,t)?"true":"false") << endl;
        cout << "Approach 2 (Arrays):    " << (isIsomorphic2(s,t)?"true":"false") << endl;
        cout << "Approach 3 (HashMap):   " << (isIsomorphic3(s,t)?"true":"false") << endl;
        cout << "Approach 4 (Map+Set):   " << (isIsomorphic4(s,t)?"true":"false") << endl;
        cout << "----------------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Two-Pass Mapping (Two Maps):
   - Straightforward, explicit check both directions.
   - O(n), O(1).

2. Two Hash Arrays:
   - Very fast, constant memory tables.
   - O(n), O(1).
   - Most efficient in practice.

3. Two HashMaps:
   - Cleaner, logical mapping.
   - O(n), O(1).
   - Extensible for larger charsets.

4. Single Map + Set:
   - Less common, extra set usage.
   - O(n), O(1).
   - Still works.

👉 Final Recommendation:
Use **Approach 2 (Two Arrays)** or **Approach 3 (HashMap)** in interviews — concise and optimal.
==================================================================
*/
