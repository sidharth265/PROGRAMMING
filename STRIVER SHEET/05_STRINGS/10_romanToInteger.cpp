#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Roman to Integer
LeetCode Link: https://leetcode.com/problems/roman-to-integer/

Problem Statement:
Convert a Roman numeral string to its integer equivalent.

Roman numerals are represented by the symbols: I(1), V(5), X(10), L(50), C(100), D(500), M(1000).
Normally, symbols are written from largest to smallest left to right, and values are added.
However, if a smaller numeral is before a larger one, it is subtracted (e.g., IV = 4).

-----------------------------------------------------------
Example 1:
Input: s = "III"
Output: 3

Example 2:
Input: s = "IV"
Output: 4

Example 3:
Input: s = "MCMXCIV"
Output: 1994

===========================================================
*/

/*-----------------------------------------------------------
Approach 1: Left-to-Right with Subtraction Rule
💡 Idea:
- Map each Roman numeral to its integer value.
- Iterate over the string characters from left to right.
- If the current numeral is less than the next, subtract current value.
- Else add current value.
- Add the last numeral's value at the end.

🧩 Algorithm:
1. Create a hash map from Roman chars to int values.
2. Initialize result = 0.
3. Loop through string from 0 to n-2:
   - If value(current) < value(next), subtract value(current).
   - Else add value(current).
4. Add value(last char).
5. Return result.

⏱ Time Complexity: O(n), n = length of string  
📦 Space Complexity: O(1), fixed size map
-----------------------------------------------------------*/
int romanToInt(string s) {
    unordered_map<char, int> romanMap = {
        {'I', 1}, {'V', 5}, {'X', 10},
        {'L', 50}, {'C', 100}, {'D', 500},
        {'M', 1000}
    };
    int result = 0;
    int n = s.length();
    for (int i = 0; i < n - 1; i++) {
        if (romanMap[s[i]] < romanMap[s[i + 1]]) {
            result -= romanMap[s[i]];
        } else {
            result += romanMap[s[i]];
        }
    }
    result += romanMap[s[n - 1]];
    return result;
}

/*-----------------------------------------------------------
Main Function: Tests for Roman to Integer conversion
-----------------------------------------------------------*/
int main() {
    vector<string> testCases = {"III", "IV", "IX", "LVIII", "MCMXCIV"};

    for (string roman : testCases) {
        cout << "Roman numeral: " << roman << endl;
        cout << "Integer value: " << romanToInt(roman) << endl;
        cout << "-----------------------------" << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach: Single pass with hash map and subtraction logic.
       Time Complexity: O(n)
       Space Complexity: O(1)

    This approach efficiently converts Roman numerals to integers by handling subtractive notation.
    -----------------------------------------------------------
    */
    return 0;
}
