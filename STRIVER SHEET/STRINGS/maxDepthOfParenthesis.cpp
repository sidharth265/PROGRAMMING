#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Maximum Nesting Depth of the Parentheses
LeetCode Link: https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/

Problem Statement:
Given a string s containing parentheses and other characters, return the maximum nesting depth of the parentheses in s.

The nesting depth is defined as the maximum number of nested parentheses that are open at the same time.

-----------------------------------------------------------
Example 1:
Input: s = "((()))"
Output: 3
Explanation: The deepest nesting is 3 parentheses inside.

Example 2:
Input: s = "(a(b(c)d)e)"
Output: 3

Example 3:
Input: s = "((a)(b(c)))"
Output: 2

===========================================================
*/

/*-----------------------------------------------------------
Approach 1: Counting Depth with a Counter
💡 Idea:
- Use a counter to track current open parentheses count.
- Increase counter on '(' and update max depth.
- Decrease counter on ')'.

🧩 Algorithm:
1. Initialize two integers: `count` = 0 (current depth), `maxDepth` = 0.
2. Traverse each character in the string:
   a) If '(', increment `count` and update `maxDepth` = max(`maxDepth`, `count`).
   b) If ')', decrement `count`.
3. After traversal, `maxDepth` stores the maximum nesting depth.

⏱ Time Complexity: O(n) - one pass over string  
📦 Space Complexity: O(1) - constant extra space
-----------------------------------------------------------*/
int maxDepth(const string& s) {
    int count = 0, maxDepth = 0;
    for (char ch : s) {
        if (ch == '(') {
            count++;
            maxDepth = max(maxDepth, count);
        } else if (ch == ')') {
            count--;
        }
    }
    return maxDepth;
}

/*-----------------------------------------------------------
Main Function: Tests the maxDepth function
-----------------------------------------------------------*/
int main() {
    vector<string> tests = {
        "((()))",
        "(a(b(c)d)e)",
        "((a)(b(c)))",
        "(x((y))z)",
        "()()()",
        ""
    };

    for (const string& s : tests) {
        cout << "Input: " << s << endl;
        cout << "Maximum depth of nested parentheses: " << maxDepth(s) << endl;
        cout << "---------------------------------------" << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach: Counting Depth with Counter
       Time Complexity: O(n)
       Space Complexity: O(1)
    
    This is the optimal and standard approach for maximum nesting depth in parentheses.
    -----------------------------------------------------------
    */
    return 0;
}
