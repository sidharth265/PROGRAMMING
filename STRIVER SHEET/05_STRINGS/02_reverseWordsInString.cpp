#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Reverse Words in a String
LeetCode Link: https://leetcode.com/problems/reverse-words-in-a-string/

Problem Statement:
Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

You must return a string of the words in reverse order concatenated by a single space.

The returned string should not contain leading or trailing spaces, and there should be only a single space separating words.

-----------------------------------------------------------
Example 1:
Input: s = "  Hello   World  "
Output: "World Hello"
Explanation: Words are reversed, extra spaces removed.

Example 2:
Input: s = "a good   example"
Output: "example good a"

===========================================================
*/

/*-----------------------------------------------------------
Approach 1: Using a Stack to Reverse Words
💡 Idea:
- Split the input string into words using spaces.
- Push each word onto a stack to reverse their order.
- Pop words from the stack and concatenate with single spaces.

🧩 Algorithm:
1. Initialize an empty stack<string> and temporary word string.
2. Traverse the input string character-by-character.
3. For every non-space character, append it to the word.
4. On encountering a space while word is not empty, push the word into the stack and reset the word.
5. After traversal, if word is not empty, push it into the stack.
6. Pop words from the stack and build the result string with single spaces.
7. Trim trailing space and return the result.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(n) for stack and result string
-----------------------------------------------------------*/
string reverseWordsStack(string s) {
    stack<string> st;
    string word = "";
    for (char ch : s) {
        if (ch == ' ') {
            if (!word.empty()) {
                st.push(word);
                word.clear();
            }
        } else {
            word.push_back(ch);
        }
    }
    if (!word.empty()) st.push(word);

    string result = "";
    while (!st.empty()) {
        result += st.top();
        st.pop();
        if (!st.empty()) result += " ";
    }
    return result;
}

/*-----------------------------------------------------------
Approach 2: In-place Prepending (Better Space Efficiency)
💡 Idea:
- Iterate through the string character by character.
- For every complete word found, prepend it (with space) to result.
- This constructs the reversed string without extra stack.

🧩 Algorithm:
1. Initialize empty result and word string.
2. Iterate characters:
   a) If not space, build word.
   b) On space and if word exists, prepend " " + word to result.
3. After loop, prepend last word if exists.
4. Remove leading space if any and return.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(n)
-----------------------------------------------------------*/
string reverseWordsPrepend(string s) {
    string result = "";
    string word = "";
    for (char ch : s) {
        if (ch != ' ') {
            word.push_back(ch);
        } else {
            if (!word.empty()) {
                result = " " + word + result;
                word.clear();
            }
        }
    }
    if (word.empty()) return result.empty() ? "" : result.substr(1);
    return word + result;
}

/*-----------------------------------------------------------
Main function: Tests multiple cases on both approaches
-----------------------------------------------------------*/
int main() {
    vector<string> tests = {
        "  Hello   World  ",
        "a good   example",
        "  the sky is blue  ",
        "",
        "    "
    };

    for (const string &s : tests) {
        cout << "Input: '" << s << "'" << endl;
        cout << "Output (Stack):        '" << reverseWordsStack(s) << "'" << endl;
        cout << "Output (Prepend):      '" << reverseWordsPrepend(s) << "'" << endl;
        cout << "-----------------------------------------------------------" << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach 1: Using Stack  
       Time: O(n) | Space: O(n)

    Approach 2: Prepend Words  
       Time: O(n) | Space: O(n)
    
    Both approaches efficiently reverse words and handle extra spaces.
    -----------------------------------------------------------
    */
    return 0;
}
