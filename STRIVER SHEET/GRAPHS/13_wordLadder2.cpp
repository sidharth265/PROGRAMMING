#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Word Ladder II (All Shortest Transformation Sequences)
LeetCode Link: https://leetcode.com/problems/word-ladder-ii/

Problem Statement:
------------------
Given two words (beginWord and endWord), and a dictionary wordList, find all shortest transformation sequences from beginWord to endWord,
such that:
1. Only one letter can be changed at a time.
2. Each transformed word must exist in the wordList.

Return all such sequences. The order of sequences does not matter.

Example:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]

Constraints:
- All words have the same length.
- All words contain only lowercase letters.
====================================================
*/

/*
==========================================
Approach 1: DFS with Pruning (Backtracking)
-------------------------------------------
💡 Idea:
Run DFS from beginWord to endWord, pruning paths longer than the current shortest.
Use a set to track remaining words to avoid revisiting.

🧩 Algorithm:
1. Initialize minLen with large value.
2. Run DFS maintaining current sequence and used words set.
3. If current sequence length exceeds minLen, backtrack.
4. On reaching endWord, update minLen and record sequence.
5. Return all sequences of minimum length.

⏱ Time Complexity: Exponential worst case (not efficient for large input)
📦 Space Complexity: O(N) for recursion and auxiliary sets.
*/
void dfsPrune(unordered_set<string>& st, string word, const string& endWord, vector<string>& seq,
             vector<vector<string>>& ans, int& minLen) {
    seq.push_back(word);
    st.erase(word);

    if (seq.size() > minLen) {
        seq.pop_back();
        st.insert(word);
        return;
    }
    if (word == endWord) {
        if (seq.size() < minLen) {
            ans.clear();
            minLen = seq.size();
        }
        ans.push_back(seq);
        seq.pop_back();
        st.insert(word);
        return;
    }

    for (int i = 0; i < word.size(); i++) {
        char ch = word[i];
        for (int j = 0; j < 26; j++) {
            word[i] = 'a' + j;
            if (st.find(word) != st.end()) {
                dfsPrune(st, word, endWord, seq, ans, minLen);
            }
        }
        word[i] = ch;
    }

    seq.pop_back();
    st.insert(word);
}

vector<vector<string>> findLaddersDFS(string beginWord, string endWord, vector<string>& wordList) {
    vector<vector<string>> ans;
    unordered_set<string> st(wordList.begin(), wordList.end());
    vector<string> seq;
    int minLen = INT_MAX;
    dfsPrune(st, beginWord, endWord, seq, ans, minLen);
    return ans;
}

/*
==========================================
Approach 2: BFS + DFS Backtracking via Distance Map
--------------------------------------------------
💡 Idea:
Use BFS from beginWord to record shortest distance for each word,
then backtrack with DFS from endWord to beginWord by traveling 
to neighbors at distance = currentDistance - 1. This builds all shortest paths.

🧩 Algorithm:
1. Initialize map<string, int> distance for BFS distances, set all to -1.
2. Run BFS from beginWord, assign distance levels.
3. Once BFS completes, if endWord unreachable, return empty.
4. DFS backtrack from endWord to beginWord:
   - For each neighbor differing by one char:
   - If distance is exactly one less, recurse.
5. Record all paths of minimal length.

⏱ Time Complexity: O(N * L^2) (N words, L word length)
📦 Space Complexity: O(N * L)
*/
void dfsBacktrack(unordered_map<string, int>& distance, string& word, string& beginWord,
                  vector<string>& seq, vector<vector<string>>& ans) {
    seq.push_back(word);
    if (word == beginWord) {
        vector<string> tmp = seq;
        reverse(tmp.begin(), tmp.end());
        ans.push_back(tmp);
        seq.pop_back();
        return;
    }
    int len = distance[word];
    for (int i = 0; i < word.size(); i++) {
        char ch = word[i];
        for (int j = 0; j < 26; j++) {
            word[i] = 'a' + j;
            if (distance.find(word) != distance.end() && distance[word] + 1 == len) {
                dfsBacktrack(distance, word, beginWord, seq, ans);
            }
        }
        word[i] = ch;
    }
    seq.pop_back();
}

vector<vector<string>> findLaddersBFSDFS(string beginWord, string endWord, vector<string>& wordList) {
    vector<vector<string>> ans;
    unordered_map<string, int> distance;
    for (auto& w : wordList) distance[w] = -1;
    if (distance.find(beginWord) == distance.end()) distance[beginWord] = 1;

    queue<string> q;
    q.push(beginWord);
    distance[beginWord] = 1;

    while (!q.empty()) {
        string word = q.front();
        int len = distance[word];
        q.pop();
        if (word == endWord) break;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            for (int j = 0; j < 26; j++) {
                word[i] = 'a' + j;
                if (distance.find(word) != distance.end() && distance[word] == -1) {
                    q.push(word);
                    distance[word] = len + 1;
                }
            }
            word[i] = ch;
        }
    }

    vector<string> seq;
    if (distance.find(endWord) != distance.end() && distance[endWord] != -1)
        dfsBacktrack(distance, endWord, beginWord, seq, ans);

    return ans;
}

/* Main for testing both approaches */

int main() {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};

    cout << "DFS + Pruning Approach:\n";
    vector<vector<string>> ans1 = findLaddersDFS(beginWord, endWord, wordList);
    for (auto& path : ans1) {
        for (const string& w : path) cout << w << " ";
        cout << "\n";
    }

    cout << "\nBFS + DFS Backtracking Approach:\n";
    vector<vector<string>> ans2 = findLaddersBFSDFS(beginWord, endWord, wordList);
    for (auto& path : ans2) {
        for (const string& w : path) cout << w << " ";
        cout << "\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. DFS + Pruning: Explores all paths with pruning. Can be slow for large inputs.\n";
    cout << "2. BFS + DFS Backtracking: Uses shortest distances from BFS to build all shortest paths via DFS backtracking.\n";
    cout << "BFS + DFS Backtracking is the recommended and efficient standard approach.\n";

    return 0;
}
