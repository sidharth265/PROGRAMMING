#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Check Palindrome (String and Integer)
Problem Statement:
Check whether a given string or integer is a palindrome.

- A palindrome string reads the same forwards and backwards.
- A palindrome integer reads the same forwards and backwards numerically.

-----------------------------------------------------------
Example 1 (String):
Input: "madam"
Output: true

Example 2 (String):
Input: "hello"
Output: false

Example 3 (Integer):
Input: 121
Output: true

Example 4 (Integer):
Input: 123
Output: false

===========================================================
*/

/*-----------------------------------------------------------
Approach 1: Check Palindrome for String
💡 Idea:
- Compare characters from beginning and end moving towards center.
- If any mismatch, return false; else return true.

🧩 Algorithm:
1. Get length n.
2. Loop i from 0 to n/2:
   - If s[i] != s[n - i - 1], return false.
3. Return true if no mismatches.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
bool isPalindromeString(const string &str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++) {
        if (str[i] != str[n - i - 1]) {
            return false;
        }
    }
    return true;
}

/*-----------------------------------------------------------
Approach 2: Check Palindrome for Integer
💡 Idea:
- Reverse the number.
- Compare reversed number with original.

🧩 Algorithm:
1. Initialize reversed number r = 0 and copy of original number n.
2. While n > 0:
   - Extract last digit.
   - Add to reversed number (r = r * 10 + digit).
   - Remove digit from n.
3. Return true if reversed == original; else false.

⏱ Time Complexity: O(log n) (digits count)
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
bool isPalindromeInt(int x) {
    if (x < 0) return false; // Negative numbers are not palindrome
    long long r = 0;
    int n = x;
    while (x > 0) {
        r = (r * 10) + (x % 10);
        x = x / 10;
    }
    return r == n;
}

/*-----------------------------------------------------------
Main function: Demonstrate palindrome checks on strings and numbers
-----------------------------------------------------------*/
int main() {
    string s = "madam";
    cout << "Is \"" << s << "\" a palindrome string? " << (isPalindromeString(s) ? "Yes" : "No") << endl;

    s = "hello";
    cout << "Is \"" << s << "\" a palindrome string? " << (isPalindromeString(s) ? "Yes" : "No") << endl;

    int num = 121;
    cout << "Is " << num << " a palindrome integer? " << (isPalindromeInt(num) ? "Yes" : "No") << endl;

    num = 123;
    cout << "Is " << num << " a palindrome integer? " << (isPalindromeInt(num) ? "Yes" : "No") << endl;

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach 1: String palindrome check
       Time: O(n) | Space: O(1)

    Approach 2: Integer palindrome check by reversal
       Time: O(log n) | Space: O(1)

    Both approaches handle palindrome checks efficiently.
    -----------------------------------------------------------
    */
    return 0;
}
