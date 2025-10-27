#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Palindrome Partitioning
 Problem Link: https://leetcode.com/problems/palindrome-partitioning/

 Problem Statement:
 Given a string `s`, partition `s` such that every substring of the partition is a palindrome.
 Return all possible palindrome partitions of `s`.

-------------------------------------------------
 Example:
 Input: s = "aab"
 Output: [
   ["a","a","b"],
   ["aa","b"]
 ]
 Explanation:
   Both partitions contain only palindromic substrings.
-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Backtracking with Palindrome Check
// -------------------------------------------------
/*
💡 Idea:
   - Use backtracking to generate all partitions.
   - At each step, try all substrings starting at current index.
   - If substring is palindrome, recurse for remaining string.
   - Store valid partitions when end of string is reached.

🧩 Algorithm:
   1. Define a helper function to check if a substring is palindrome.
   2. Use backtracking starting from index 0.
   3. For each end index from start to end of string:
       - If substring s[start..end] is palindrome, push to current path.
       - Recur for substring after end.
       - Backtrack by removing last substring.
   4. Collect all valid partitions.

⏱ Time Complexity: O(2^n * n), exponential in worst case
📦 Space Complexity: O(n) recursion stack + result storage
*/

bool isPalindrome(const string &str) {
    int i = 0, j = (int)str.length() - 1;
    while (i <= j) {
        if (str[i++] != str[j--]) return false;
    }
    return true;
}

void backtrack(vector<vector<string>> &result, vector<string> &path, const string &s, int start) {
    if (start == (int)s.length()) {
        result.push_back(path);
        return;
    }
    for (int end = start; end < (int)s.length(); end++) {
        string substr = s.substr(start, end - start + 1);
        if (isPalindrome(substr)) {
            path.push_back(substr);
            backtrack(result, path, s, end + 1);
            path.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    vector<string> path;
    backtrack(result, path, s, 0);
    return result;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    string s = "aab";
    auto partitions = partition(s);

    cout << "All possible palindrome partitions of \"" << s << "\":\n";
    for (const auto &partition : partitions) {
        cout << "[ ";
        for (const auto &str : partition) {
            cout << "\"" << str << "\" ";
        }
        cout << "]\n";
    }

    // Additional test cases
    vector<string> tests = {"efe", "racecar", "abba", "abc"};

    for (const string& testStr : tests) {
        cout << "\nPalindrome partitions of \"" << testStr << "\":\n";
        auto res = partition(testStr);
        for (const auto& parts : res) {
            cout << "[ ";
            for (const auto& p : parts) cout << "\"" << p << "\" ";
            cout << "]\n";
        }
    }

    // ✅ Approach Overview
    /*
    - Backtracking explores all partitionings.
    - Palindrome checks at each step prune invalid partitions.
    - Exponential worst-case time complexity due to branching.
    */

    return 0;
}
