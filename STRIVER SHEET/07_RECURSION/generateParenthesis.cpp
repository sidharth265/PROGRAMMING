#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Generate Parentheses
 Problem Link: https://leetcode.com/problems/generate-parentheses/

 Problem Statement:
 Given `n` pairs of parentheses, write a function to generate
 all combinations of well-formed (valid) parentheses.

 A parenthesis sequence is valid if:
 1. Open brackets must be closed by the same type of brackets.
 2. Open brackets must be closed in the correct order.

 Examples:
 -------------------------------------------------
 Input: n = 3
 Output: ["((()))","(()())","(())()","()(())","()()()"]
 Explanation:
   For n=3, these are all possible valid ways to arrange parentheses.

 Input: n = 1
 Output: ["()"]
-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force (Generate All, Then Validate)
// -------------------------------------------------
/*
💡 Idea:
   - Generate **all possible sequences** of '(' and ')' of length 2*n.
   - For each sequence, check if it is valid using a stack.
   - If valid, add to result.

🧩 Algorithm:
   1. Generate all strings recursively of length `2*n`.
   2. At each step, append '(' or ')'.
   3. When the length is 2*n, validate using stack.
   4. Keep only valid strings.

⏱ Time Complexity: O(2^(2n)) to generate + O(2n) check per string
   ≈ O(2^(2n) * n)
📦 Space Complexity: O(n) recursion + result storage
*/

bool isValidParentheses(string str) {
    stack<char> s;
    for (char ch : str) {
        if (ch == '(') s.push(ch);
        else {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

void bruteGenerate(vector<string> &result, string str, int n) {
    if ((int)str.size() == 2*n) {
        if (isValidParentheses(str)) result.push_back(str);
        return;
    }
    bruteGenerate(result, str+'(', n);
    bruteGenerate(result, str+')', n);
}

vector<string> generateParenthesisBrute(int n) {
    vector<string> result;
    bruteGenerate(result, "", n);
    return result;
}


// -------------------------------------------------
// Approach 2: Backtracking (Optimized Recursive Generation)
// -------------------------------------------------
/*
💡 Idea:
   - Instead of generating invalid ones, only build valid strings directly.
   - Ensure at every step: 
     - We can add '(' if open < n.
     - We can add ')' if close < open.

🧩 Algorithm:
   1. Use recursion with parameters (current string, open count, close count).
   2. Base case: if string length == 2*n → store result.
   3. Otherwise:
      - If open < n → add '('
      - If close < open → add ')'

⏱ Time Complexity: O(4^n / sqrt(n))  (Catalan Number Cn)
📦 Space Complexity: O(n) recursion + result storage
*/

void backtrackGenerate(vector<string> &result, string curr, int open, int close, int n) {
    if ((int)curr.size() == 2*n) {
        result.push_back(curr);
        return;
    }
    if (open < n) backtrackGenerate(result, curr+'(', open+1, close, n);
    if (close < open) backtrackGenerate(result, curr+')', open, close+1, n);
}

vector<string> generateParenthesisBacktrack(int n) {
    vector<string> result;
    backtrackGenerate(result, "", 0, 0, n);
    return result;
}


// -------------------------------------------------
// Approach 3: DP + Memoization (Catalan Numbers)
// -------------------------------------------------
/*
💡 Idea:
   - The count of valid parentheses follows Catalan numbers.
   - We can use DP to build all valid parentheses for n:
     f(n) = "(" + f(i) + ")" + f(n-1-i)  for all i in [0..n-1]

🧩 Algorithm:
   1. Use recursion with memoization.
   2. For n=0 → return {""}
   3. For n>0 → for each i from 0..n-1:
        - Left = f(i)
        - Right = f(n-1-i)
        - Combine: "(" + left + ")" + right
   4. Store result in memo.

⏱ Time Complexity: Exponential in nature, but avoids redundant work.
📦 Space Complexity: O(Cn * n) for memo storage
*/

unordered_map<int, vector<string>> memo;

vector<string> dpGenerate(int n) {
    if (memo.count(n)) return memo[n];
    vector<string> res;
    if (n == 0) {
        res.push_back("");
    } else {
        for (int i = 0; i < n; i++) {
            for (string left : dpGenerate(i)) {
                for (string right : dpGenerate(n-1-i)) {
                    res.push_back("(" + left + ")" + right);
                }
            }
        }
    }
    return memo[n] = res;
}

vector<string> generateParenthesisDP(int n) {
    memo.clear();
    return dpGenerate(n);
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    int n;
    cout << "Enter n (number of parentheses pairs): ";
    cin >> n;

    // Test Case 1: Brute Force
    cout << "\nBrute Force Approach:\n";
    vector<string> bruteRes = generateParenthesisBrute(n);
    for (auto &s : bruteRes) cout << s << "\n";

    // Test Case 2: Backtracking
    cout << "\nBacktracking (Optimized) Approach:\n";
    vector<string> backtrackRes = generateParenthesisBacktrack(n);
    for (auto &s : backtrackRes) cout << s << "\n";

    // Test Case 3: DP + Memoization
    cout << "\nDP + Memoization Approach:\n";
    vector<string> dpRes = generateParenthesisDP(n);
    for (auto &s : dpRes) cout << s << "\n";

    // -------------------------------------------------
    // ✅ Approach Overview
    // -------------------------------------------------
    /*
    Approach 1 (Brute Force):  TC = O(2^(2n)*n),   SC = O(n)
    Approach 2 (Backtracking): TC = O(4^n / sqrt(n)), SC = O(n)
    Approach 3 (DP + Memo):    TC ≈ Catalan growth,   SC = O(Cn * n)
    */

    return 0;
}
