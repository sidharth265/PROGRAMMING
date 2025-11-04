#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Sort Characters By Frequency
LeetCode Link: https://leetcode.com/problems/sort-characters-by-frequency/

Problem Statement:
Given a string s, sort it in decreasing order based on the frequency of characters.

The frequency of a character is the number of times it appears in the string.  
Return the sorted string. If there are multiple answers, return any of them.

-----------------------------------------------------------
Example 1:
Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.  
"eetr" is also a valid answer.

Example 2:
Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times. "cccaaa" is also valid.

===========================================================
*/

/*-----------------------------------------------------------
Approach 1: Using unordered_map + Sorting  
💡 Idea:
- Count frequency of each character in a hashmap.
- Convert to vector of (char, freq).
- Sort vector by freq in descending order.
- Construct result string by repeating characters.

🧩 Algorithm:
1. Traverse the string, count char frequencies using unordered_map.
2. Copy map to vector<pair<char,int>>.
3. Sort vector by frequency descending.
4. Build result string by appending chars repeated freq times.

⏱ Time Complexity: O(n log n) (dominated by sorting unique chars)  
📦 Space Complexity: O(n) for frequency map and result string
-----------------------------------------------------------*/
string frequencySort(string s) {
    unordered_map<char, int> freqMap;
    for (char ch : s) freqMap[ch]++;

    vector<pair<char, int>> freqVec(freqMap.begin(), freqMap.end());
    sort(freqVec.begin(), freqVec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        return a.second > b.second;
    });

    string result;
    for (auto& p : freqVec) {
        result += string(p.second, p.first);
    }

    return result;
}

/*-----------------------------------------------------------
Approach 2: Using Priority Queue (Max-Heap)  
💡 Idea:
- Use frequency map as before.
- Push entries to max-heap by frequency.
- Pop from heap and build result string.

🧩 Algorithm:
1. Count frequencies in unordered_map.
2. Push all pairs (freq, char) into max heap.
3. Pop from heap and append char freq times to result.

⏱ Time Complexity: O(n log k), k = unique chars  
📦 Space Complexity: O(n)
-----------------------------------------------------------*/
string frequencySortUsingHeap(string s) {
    unordered_map<char, int> freqMap;
    for (char ch : s) freqMap[ch]++;

    priority_queue<pair<int, char>> maxHeap;
    for (auto& p : freqMap) {
        maxHeap.push({p.second, p.first});
    }

    string result;
    while (!maxHeap.empty()) {
        auto p = maxHeap.top();
        maxHeap.pop();
        result += string(p.first, p.second);
    }

    return result;
}

/*-----------------------------------------------------------
Main Function: Testing both approaches with sample inputs
-----------------------------------------------------------*/
int main() {
    vector<string> tests = {"tree", "cccaaa", "Aabb"};

    for (const string &s : tests) {
        cout << "Input: " << s << endl;
        cout << "Sorted by frequency (unordered_map + sort): " << frequencySort(s) << endl;
        cout << "Sorted by frequency (max-heap): " << frequencySortUsingHeap(s) << endl;
        cout << "--------------------------------------------" << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach 1: unordered_map + sorting unique chars  
       Time: O(n log k) (n = length, k = unique chars)  
       Space: O(n)

    Approach 2: unordered_map + max-heap  
       Time: O(n log k)  
       Space: O(n)

    Both approaches efficiently sort characters by frequency.
    -----------------------------------------------------------
    */
    return 0;
}
