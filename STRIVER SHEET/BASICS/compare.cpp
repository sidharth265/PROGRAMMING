#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Compare Two Integers
Problem Statement:
Given two integers n and m, return "equal" if they are equal,
"greater" if n is greater than m, and "lesser" if n is less than m.

-----------------------------------------------------------
Example:
Input: n = 5, m = 3
Output: "greater"

Input: n = 10, m = 10
Output: "equal"

Input: n = 2, m = 7
Output: "lesser"

===========================================================
*/

/*-----------------------------------------------------------
Approach: Simple comparison using if-else
💡 Idea:
- Compare integers directly using relational operators.
- Return appropriate string based on comparison.

🧩 Algorithm:
1. If n == m return "equal".
2. Else if n > m return "greater".
3. Else return "lesser".

⏱ Time Complexity: O(1)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
string compareNM(int n, int m) {
    if (n == m) return "equal";
    else if (n > m) return "greater";
    else return "lesser";
}

/*-----------------------------------------------------------
Main function: Tests the compareNM function
-----------------------------------------------------------*/
int main() {
    int n, m;
    cout << "Enter two numbers separated by space: ";
    cin >> n >> m;
    cout << compareNM(n, m) << endl;

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach: straightforward if-else comparison.
       Time: O(1)
       Space: O(1)
    -----------------------------------------------------------
    */
    return 0;
}
