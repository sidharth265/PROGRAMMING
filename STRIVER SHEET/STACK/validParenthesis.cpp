#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Valid Parentheses
Problem Link: LeetCode #20 (https://leetcode.com/problems/valid-parentheses/)

Problem Statement:
Given a string `s` containing just the characters '(', ')', '{', '}', '[' and ']', 
determine if the input string is valid.

A string is valid if:
1. Open brackets are closed by the same type of brackets.
2. Open brackets are closed in the correct order.
3. Every closing bracket has a corresponding open bracket.

------------------------------------------------------------
Example 1:
Input:  s = "()"
Output: true

Example 2:
Input:  s = "()[]{}"
Output: true

Example 3:
Input:  s = "(]"
Output: false

Example 4:
Input:  s = "([)]"
Output: false

Example 5:
Input:  s = "{[]}"
Output: true

------------------------------------------------------------
Constraints:
- 1 <= s.length <= 10^4
- s consists only of '()[]{}'
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Stack Matching (Optimal)
==================================================================
💡 Idea:
- Push opening brackets onto stack.
- For closing brackets:
  - Check if stack top matches expected opening bracket.
  - If mismatch → return false.
- At end, stack must be empty.

🧩 Algorithm:
1. Initialize empty stack<char>.
2. For each character in s:
   - If opening → push.
   - If closing → check top for matching pair.
     - If mismatch or stack empty → invalid.
     - Else pop().
3. If stack empty → valid, else invalid.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n) in worst case (all openings).
*/

bool isValidStack(string s) {
    stack<char> st;
    for(char ch : s) {
        if(ch=='(' || ch=='[' || ch=='{') {
            st.push(ch);
        } else {
            if(st.empty()) return false;
            if((ch==')' && st.top()!='(') ||
               (ch==']' && st.top()!='[') ||
               (ch=='}' && st.top()!='{'))
                return false;
            st.pop();
        }
    }
    return st.empty();
}

/*
==================================================================
Approach 2: Using Hash Map for Pair Matching (Cleaner)
==================================================================
💡 Idea:
- Use map {closing → opening}.
- For each character:
  - If opening → push.
  - If closing → verify top of stack matches required opening.

🧩 Algorithm:
1. Initialize map: {')':'(', ']':'[', '}':'{'}.
2. Traverse string:
   - If opening → push.
   - If closing and stack empty → return false.
   - If top != map[ch] → return false.
   - Else pop.
3. At end, check stack empty.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

bool isValidHashMap(string s) {
    unordered_map<char,char> match = {
        {')','('}, {']','['}, {'}','{'}
    };

    stack<char> st;
    for(char ch : s) {
        if(match.count(ch)) {
            if(st.empty() || st.top()!=match[ch]) return false;
            st.pop();
        } else {
            st.push(ch);
        }
    }
    return st.empty();
}

/*
==================================================================
main() function
==================================================================
*/
int main() {
    vector<string> testCases = {
        "()", "()[]{}", "(]", "([)]", "{[]}"
    };

    for(string s : testCases) {
        cout << "Input: " << s << endl;
        cout << "Valid (Stack method):   " << (isValidStack(s)?"true":"false") << endl;
        cout << "Valid (HashMap method): " << (isValidHashMap(s)?"true":"false") << endl;
        cout << "----------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Stack Matching:
   - Straightforward check of pairs.
   - O(n), O(n).
   - Common interview solution.

2. Hash Map:
   - Cleaner and more extensible.
   - O(n), O(n).
   - Preferred for concise code.

👉 Recommendation: **Hash Map + Stack** is elegant and should be your go-to in interviews.
==================================================================
*/
