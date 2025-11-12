#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------------
Problem Title: Generate Binary Strings Without Consecutive 1s
Problem Link: (Custom problem, often asked in interviews)

Problem Statement:
Given an integer n, generate all binary strings of length n such that 
no two consecutive 1's appear in the string.

Example:
Input:
n = 3

Output:
000
001
010
100
101

Explanation:
All binary strings of length 3 are:
000, 001, 010, 011, 100, 101, 110, 111
But we remove those containing consecutive 1s: 011, 110, 111
Final valid strings: 000, 001, 010, 100, 101
--------------------------------------------------
*/

/* 
---------------------------------------------
Approach 1: Brute Force (Generate All Strings, Then Filter)
💡 Idea:
- Generate ALL possible binary strings of length n (2^n possibilities).
- For each string, check if it contains consecutive 1s.
- Keep only the valid ones.

🧩 Algorithm:
1. Generate all binary strings of length n.
2. For each generated string, scan it to see if "11" occurs.
3. If no consecutive 1s, store it in the result.
4. Return the result.

⏱ Time Complexity: O(2^n * n)  (generate 2^n strings, each length n check)
📦 Space Complexity: O(n * 2^n)
---------------------------------------------
*/
bool hasConsecutiveOnes(const string &s) {
    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] == '1' && s[i-1] == '1') return true;
    }
    return false;
}

void bruteForceGenerate(int n, vector<string> &result) {
    int total = 1 << n; // 2^n
    for (int mask = 0; mask < total; mask++) {
        string str = "";
        for (int i = n-1; i >= 0; i--) {
            str.push_back((mask & (1 << i)) ? '1' : '0');
        }
        if (!hasConsecutiveOnes(str)) {
            result.push_back(str);
        }
    }
}

/* 
---------------------------------------------
Approach 2: Recursive Backtracking (Better)
💡 Idea:
- Instead of generating invalid strings, build valid ones directly.
- At each index, we can:
   - Always place '0'
   - Place '1' only if the last bit was '0'
- This prunes invalid paths early.

🧩 Algorithm:
1. Use a recursive function "generate" that takes:
   - Current string `str`
   - Remaining length `num`
2. Base case: if num == 0 → push result.
3. Recursive step:
   - Append '0' and recurse.
   - If last char is '0', append '1' and recurse.

⏱ Time Complexity: O(2^n) (but smaller constant than brute force)
📦 Space Complexity: O(n * 2^n) (to store results)
---------------------------------------------
*/
void generateValidStrings(vector<string> &result, string str, int num) {
    if (num == 0) {
        result.push_back(str);
        return;
    }

    // Always add '0'
    generateValidStrings(result, str + '0', num-1);

    // Add '1' only if last character is '0'
    if (str.back() == '0') {
        generateValidStrings(result, str + '1', num-1);
    }
}

vector<string> backtrackingGenerate(int n) {
    vector<string> result;
    generateValidStrings(result, "0", n-1);
    generateValidStrings(result, "1", n-1);
    return result;
}

/* 
---------------------------------------------
Approach 3: Dynamic Programming (Optimal Counting, Not Listing)
💡 Idea:
- If we don’t need to list the strings, only count them, we can use DP.
- Define:
   dp0[i]: number of valid strings of length i ending with '0'
   dp1[i]: number of valid strings of length i ending with '1'
- Recurrence:
   dp0[i] = dp0[i-1] + dp1[i-1]   // can put '0' after both
   dp1[i] = dp0[i-1]              // can put '1' only after '0'

🧩 Algorithm:
1. Initialize dp0[1] = 1 (string "0"), dp1 = 1 (string "1").
2. Fill dp arrays up to n.
3. Answer = dp0[n] + dp1[n].

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) (can be reduced to O(1))
---------------------------------------------
*/
int countValidBinaryStrings(int n) {
    if (n == 1) return 2; // "0", "1"
    vector<int> dp0(n+1, 0), dp1(n+1, 0);

    dp0[1] = 1, dp1 = 1;
    for (int i = 2; i <= n; i++) {
        dp0[i] = dp0[i-1] + dp1[i-1];
        dp1[i] = dp0[i-1];
    }
    return dp0[n] + dp1[n];
}

/* 
--------------------------------------------------
MAIN FUNCTION to demonstrate all approaches
--------------------------------------------------
*/
int main() {
    // Example problem inputs
    vector<int> testCases = {2, 3, 4};

    for (int n : testCases) {
        cout << "\n=== Test Case: n = " << n << " ===\n";

        // Brute force
        vector<string> bruteRes;
        bruteForceGenerate(n, bruteRes);
        cout << "[Brute Force] Generated Strings:\n";
        for (auto &s : bruteRes) cout << s << "\n";

        // Backtracking
        vector<string> backtrackRes = backtrackingGenerate(n);
        cout << "[Backtracking] Generated Strings:\n";
        for (auto &s : backtrackRes) cout << s << "\n";

        // DP (just count, not list)
        int count = countValidBinaryStrings(n);
        cout << "[DP] Count of valid strings: " << count << "\n";
    }

    /* 
    ✅ Approach Overview:
    - Brute Force:
        🔴 Generates ALL strings (2^n), then filters → slow & wasteful
        Time: O(2^n * n)
    - Backtracking:
        🟡 Directly builds VALID strings, avoids waste
        Time: O(2^n), Space: O(n*2^n)
    - Dynamic Programming:
        🟢 Best if we only need count, not actual strings
        Time: O(n), Space: O(n)
    */
    return 0;
}
