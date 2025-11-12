#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Remove Outermost Parentheses
LeetCode Link: https://leetcode.com/problems/remove-outermost-parentheses/

Problem Statement:
Given a valid parentheses string S, remove the outermost parentheses of every primitive valid parentheses string.

A primitive valid parentheses string is a non-empty string that cannot be split into two non-empty valid parentheses strings.

-----------------------------------------------------------
Example 1:
Input: S = "(()())(())"
Output: "()()()"
Explanation: The primitive decomposition is "(()())" + "(())".
Removing the outermost parentheses from each yields "()()" + "()" = "()()()".

Example 2:
Input: S = "(()())(())(()(()))"
Output: "()()()()(())"

Example 3:
Input: S = "()()"
Output: ""

===========================================================
*/

/*-----------------------------------------------------------
Approach 1: Counting Balance with a Counter
💡 Idea:
- Use a counter to maintain the current nesting depth of parentheses.
- For each '(':
  - If counter > 0, add '(' to result (not outermost).
  - Increment counter.
- For each ')':
  - Decrement counter.
  - If counter > 0, add ')' to result (not outermost).

🧩 Algorithm:
1. Initialize count = 0 and result string as empty.
2. Traverse each character in S:
   a) If '(', and count > 0, append '(' to result, then increment count.
   b) If ')', decrement count, and if count > 0, append ')' to result.
3. Return the result string.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(n)  (for the result string)
-----------------------------------------------------------*/
string removeOuterParentheses(string S) {
    int count = 0;
    string result = "";
    for (char c : S) {
        if (c == '(') {
            if (count > 0) result += c;
            count++;
        } else {
            count--;
            if (count > 0) result += c;
        }
    }
    return result;
}

/*-----------------------------------------------------------
Main Function: Tests for removing outermost parentheses
-----------------------------------------------------------*/
int main() {
    vector<string> testCases = {
        "(()())(())",
        "(()())(())(()(()))",
        "()()",
        "((()()))(()())"
    };

    for (const string& s : testCases) {
        cout << "Original String: " << s << endl;
        cout << "Result after removing outer parentheses: " << removeOuterParentheses(s) << endl;
        cout << "----------------------------------------------" << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach: Counting Balance with a Counter
       Time Complexity: O(n)
       Space Complexity: O(n)
    
    This approach efficiently removes the outermost parentheses while maintaining the valid structure of inner parentheses.
    -----------------------------------------------------------
    */
    return 0;
}
