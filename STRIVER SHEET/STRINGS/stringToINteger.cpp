#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: String to Integer (atoi)
LeetCode Link: https://leetcode.com/problems/string-to-integer-atoi/

Problem Statement:
Implement the `myAtoi(string s)` function, which converts a string to a 32-bit signed integer (similar to C/C++'s atoi function).

The algorithm for myAtoi(string s) is as follows:

- Read in and ignore any leading whitespace.
- Check if the next character (if not already at the end of the string) is '-' or '+'. Read this character in if it is either. This determines if the final result is negative or positive respectively. Assume the result is positive if neither is present.
- Read in next the characters until the next non-digit character or the end of the input is reached. The rest of the string is ignored.
- Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If no digits were read, then the integer is 0. Change the sign as necessary (from step 2).
- If the integer is out of the 32-bit signed integer range [-2^31, 2^31 – 1], then clamp the integer so that it remains in the range.
- Return the integer as the final result.

-----------------------------------------------------------
Example 1:
Input: s = "42"
Output: 42

Example 2:
Input: s = "   -42"
Output: -42

Example 3:
Input: s = "4193 with words"
Output: 4193

===========================================================
*/

/*-----------------------------------------------------------
Approach: Stepwise Parsing with Overflow Check
💡 Idea:
- Skip leading spaces.
- Detect sign.
- Process digits while converting to integer.
- Check for overflow before multiplication or addition.
- Clamp to INT_MIN or INT_MAX when overflow occurs.

🧩 Algorithm:
1. Initialize index and skip whitespaces.
2. Detect '+' or '-' for sign.
3. Traverse digits converting relevant integer.
4. Before multiplication and addition, check if overflow will happen.
5. Return with proper sign and clamped limits if overflow.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
int myAtoi(string s) {
    int i = 0, n = s.length();
    while (i < n && s[i] == ' ') i++;  // Skip leading spaces
    if (i == n) return 0;               // String was empty or spaces only

    bool negative = false;
    if (s[i] == '-') {
        negative = true;
        i++;
    } else if (s[i] == '+') {
        i++;
    }

    int num = 0;
    while (i < n && isdigit(s[i])) {
        int digit = s[i] - '0';

        // Check overflow
        if (num > (INT_MAX - digit) / 10) {
            return negative ? INT_MIN : INT_MAX;
        }
        num = num * 10 + digit;
        i++;
    }
    return negative ? -num : num;
}

/*-----------------------------------------------------------
Main function: Tests myAtoi with various inputs
-----------------------------------------------------------*/
int main() {
    vector<string> testCases = {
        "42",
        "   -42",
        "4193 with words",
        "words and 987",
        "-91283472332",
        "+1",
        "  0000000000012345678",
        "   +0 123"
    };

    for (auto &s : testCases) {
        cout << "Input: '" << s << "'" << endl;
        cout << "Converted integer: " << myAtoi(s) << endl;
        cout << "---------------------------------" << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach: Stepwise parsing with sign and overflow checks.
       Time Complexity: O(n)
       Space Complexity: O(1)

    This approach mimics the standard atoi function, handling whitespaces, sign, digits, overflow and invalid characters.
    -----------------------------------------------------------
    */
    return 0;
}
