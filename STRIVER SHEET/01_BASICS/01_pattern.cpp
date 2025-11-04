#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Print Triangle Pattern

Problem Statement:
Given an integer n, print a symmetric triangle (or pyramid) pattern of stars (*) 
with n rows. Each row contains an increasing number of stars, centered 
by preceding spaces for pyramid shape.

-----------------------------------------------------------
Example:
Input: 6
Output:
     *
    ***
   *****
  *******
 *********
***********

===========================================================
*/

/*-----------------------------------------------------------
Approach: Nested loops for spaces and stars
💡 Idea:
- For each row from 1 to n:
  - Print (n - i) spaces.
  - Print (2*i - 1) stars.
  - Move to the next line.

🧩 Algorithm:
1. For i in [1..n]:
   a) Print (n - i) spaces.
   b) Print (2*i - 1) stars.
   c) Print newline.

⏱ Time Complexity: O(n^2) for printing all characters  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
void printTriangle(int n) {
    for (int i = 1; i <= n; i++) {
        // Print leading spaces
        for (int j = n; j > i; j--) {
            cout << " ";
        }
        // Print stars
        for (int k = 1; k < i * 2; k++) {
            cout << "*";
        }
        cout << endl;
    }
}

/*-----------------------------------------------------------
Main function: Execute the triangle printing with example input
-----------------------------------------------------------*/
int main() {
    int n = 6;
    printTriangle(n);

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Nested loops to print spaces and stars per row.
    Time Complexity: O(n^2)
    Space Complexity: O(1)
    -----------------------------------------------------------
    */
    return 0;
}
