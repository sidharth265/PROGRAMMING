#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Alien Dictionary (Order of Characters)
LeetCode Link: https://leetcode.com/problems/alien-dictionary/
GeeksforGeeks Link: https://practice.geeksforgeeks.org/problems/alien-dictionary/1/

Problem Statement:
------------------
Given a sorted list of words from an alien language, determine a valid ordering of its alphabet (only lowercase 'a'-'z').
If ordering impossible, return empty string.

Example 1:
Input: words = ["baa", "abcd", "abca", "cab", "cad"]
Output: "bdac" (or any order consistent with constraints)

Example 2:
Input: words = ["caa", "aaa", "aab"]
Output: "cab"

Constraints:
- 1 <= words.length <= 100
- 1 <= words[i].length <= 100
- Only lowercase English letters used, but ordering may differ.
====================================================
*/

/*
==========================================
Approach 1: Kahn's Algorithm for Topological Sort
------------------------------------------
💡 Idea:
    - Compare consecutive words. Find the first differing character, deduce order.
    - Build a directed graph where edge u->v means u comes before v.
    - Use Kahn's BFS for topological sort. If possible, string of all involved letters is returned, else "".

🧩 Algorithm:
1. For each word, mark letters as present.
2. For every adjacent pair of words, compare letter by letter to build ordering constraints.
   - If prefix issue detected (longer word comes before its prefix), return "" (invalid)
3. Build adjacency list and in-degree for all 26 letters.
4. Run Kahn's algorithm, starting with zero in-degree letters.
5. For each popped node, append to result, decrement neighbor in-degree, enqueue new zero in-degrees.
6. If processed all existing letters, return answer; else "" (cycle/conflict detected).

⏱ Time Complexity: O(N*L + 26*26) (N = words.size(), L = len of longest word)
📦 Space Complexity: O(26*26)
*/
string findOrder(vector<string> &words) {
    vector<vector<int>> adj(26);
    vector<int> inDeg(26, 0);
    vector<bool> exists(26, false);

    // Mark letters present in dictionary
    for (string& word : words)
        for (char ch : word) exists[ch - 'a'] = true;

    // Build graph using ordering constraints
    for (int i = 1; i < words.size(); i++) {
        string& s1 = words[i - 1], s2 = words[i];
        int n = min(s1.size(), s2.size());
        bool found = false;
        for (int j = 0; j < n; j++) {
            int ch1 = s1[j] - 'a';
            int ch2 = s2[j] - 'a';
            if (ch1 != ch2) {
                adj[ch1].push_back(ch2);
                inDeg[ch2]++;
                found = true;
                break;
            }
        }
        // Prefix invalidation (e.g. "abc", "ab") is not allowed
        if (!found && s1.size() > s2.size()) return "";
    }

    queue<int> q;
    string ans = "";

    // Kahn's algorithm
    for (int v = 0; v < 26; v++) {
        if (exists[v] && inDeg[v] == 0) q.push(v);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ans += char(v + 'a');
        for (int u : adj[v]) {
            if (--inDeg[u] == 0) q.push(u);
        }
    }
    int n = count(exists.begin(), exists.end(), true);
    return (ans.size() == n) ? ans : "";
}

/*
================= MAIN FUNCTION ==================
Runs sample cases for Alien Dictionary problem
*/
int main() {
    vector<string> words1 = {"baa", "abcd", "abca", "cab", "cad"};
    vector<string> words2 = {"caa", "aaa", "aab"};
    vector<string> words3 = {"abc", "ab"};
    vector<string> words4 = {"abc", "bcd", "cdb", "dbc"};

    cout << "Test Case 1: Order = " << findOrder(words1) << " (Ex: bdac)\n";
    cout << "Test Case 2: Order = " << findOrder(words2) << " (Ex: cab)\n";
    cout << "Test Case 3: Order = " << findOrder(words3) << " (Expected: \"\")\n";
    cout << "Test Case 4: Order = " << findOrder(words4) << " (Any valid order)\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "Kahn's algorithm is used to build valid order using zero in-degree source nodes.\n";
    cout << "Prefix and cycle invalidation handled—returns empty string if alien dictionary constraints are violated.\n";
    cout << "Efficient, compact and commonly used for ordering problems on character sets!\n";

    return 0;
}
