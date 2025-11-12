#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Word Ladder (Shortest Transformation Sequence Length)
LeetCode Link: https://leetcode.com/problems/word-ladder/

Problem Statement:
------------------
Given two words, beginWord and endWord, and a list of words (wordList), find the length of the shortest transformation sequence from beginWord to endWord,
such that:
1. Only one letter can be changed at a time.
2. Each intermediate word must exist in the wordList.

Return the number of words in the shortest transformation sequence, or 0 if no sequence exists.

Example 1:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: 
"hit" -> "hot" -> "dot" -> "dog" -> "cog"

Example 2:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation:
"cog" is not in wordList, so no transformation.

Constraints:
- 1 <= beginWord.length <= 10
- endWord.length == beginWord.length
- 1 <= wordList.length <= 5000
- All words consist of lowercase English letters.
====================================================
*/

/*
==========================================
Approach 1: Single-End BFS (Shortest Path)
------------------------------------------
💡 Idea:
BFS guarantees shortest path in unweighted graphs. Treat each word as a node; edges exist if words differ by one letter. Start BFS from beginWord, try all one-letter changes, and use a set for O(1) lookups.

🧩 Algorithm:
1. Insert all words into a set for quick lookup.
2. Push {beginWord, step=1} to queue.
3. While queue not empty:
   - Pop word, if it's endWord, return its level.
   - For each position, change character to 'a'...'z'.
   - If new word in set, push to queue and erase from set.
4. If endWord unreachable, return 0.

⏱ Time Complexity: O(N * L^2) (N = wordList.size(), L = word length, as for each BFS step, try L*26 transformations)
📦 Space Complexity: O(N * L) (queue/set)
*/
int ladderLength_BFS(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    queue<pair<string, int>> q; // {currentWord, stepsFromBegin}
    q.push({beginWord, 1});
    st.erase(beginWord);
    while (!q.empty()) {
        string word = q.front().first;
        int len = q.front().second;
        q.pop();
        if (word == endWord) return len;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            for (int j = 0; j < 26; j++) {
                word[i] = 'a' + j;
                if (st.find(word) != st.end()) {
                    q.push({word, len + 1});
                    st.erase(word);
                }
            }
            word[i] = ch;
        }
    }
    return 0;
}

/*
==========================================
Approach 2: Bidirectional BFS (Faster)
------------------------------------------
💡 Idea:
Expand from both beginWord and endWord using BFS, meeting in the middle. Heuristic halves the search space.

🧩 Algorithm:
1. Setup two sets, 'front' for beginWord and 'back' for endWord; 'wordList' as USet.
2. Loop while both sets are nonempty:
   - Always expand the smaller set for efficiency.
   - For each word in set, try all L*26 transformations.
   - If next word in other set, found the answer.
   - Else, add valid next words to temporary set and erase from wordList.
3. When paths meet, return total steps + 1. If never meet, return 0.

⏱ Time Complexity: O(N * L)
📦 Space Complexity: O(N * L)
*/
int ladderLength_Bidirectional(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    if (!st.count(endWord)) return 0;

    unordered_set<string> front{beginWord}, back{endWord};
    int len = 2, wordLen = beginWord.length();
    st.erase(beginWord);
    st.erase(endWord);

    while (!front.empty() && !back.empty()) {
        // Expand from the smaller frontier set
        if (front.size() > back.size()) swap(front, back);

        unordered_set<string> nextLevel;
        for (const string& word : front) {
            string curr = word;
            for (int i = 0; i < wordLen; i++) {
                char orig = curr[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    curr[i] = c;
                    if (back.count(curr)) return len;
                    if (st.count(curr)) {
                        nextLevel.insert(curr);
                        st.erase(curr);
                    }
                }
                curr[i] = orig;
            }
        }
        front = move(nextLevel);
        len++;
    }
    return 0;
}

/* Main function for testing both approaches */
int main() {
    vector<string> words1 = {"hot","dot","dog","lot","log","cog"};
    vector<string> words2 = {"hot","dot","dog","lot","log"};

    cout << "Test Case 1: " << ladderLength_BFS("hit", "cog", words1) << " (Expected: 5)\n";
    cout << "Test Case 1 (bi-BFS): " << ladderLength_Bidirectional("hit", "cog", words1) << "\n";

    cout << "Test Case 2: " << ladderLength_BFS("hit", "cog", words2) << " (Expected: 0)\n";
    cout << "Test Case 2 (bi-BFS): " << ladderLength_Bidirectional("hit", "cog", words2) << "\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. BFS: O(N*L^2), standard, easy to implement for interview, good for moderate wordList sizes.\n";
    cout << "2. Bi-directional BFS: O(N*L), optimal for very large wordList as it halves search space from both ends.\n";
    cout << "Bi-directional BFS is the best for time-sensitive problems, but single-end BFS is sufficient for most interviews.\n";
    return 0;
}
