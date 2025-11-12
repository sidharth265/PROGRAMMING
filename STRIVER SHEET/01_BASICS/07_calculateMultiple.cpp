#include <iostream>
using namespace std;

/*
===========================================================
Problem Title: Print Multiples of a Number
Problem Statement:
Given a number n, print the first 10 multiples of n in descending order 
(from 10*n down to 1*n).

-----------------------------------------------------------
Example:
Input: 3
Output: 30 27 24 21 18 15 12 9 6 3

===========================================================
*/

/*-----------------------------------------------------------
Approach: Simple loop decreasing from 10 to 1
💡 Idea:
- Use a loop from 10 down to 1.
- Multiply n by the loop variable and print result.

🧩 Algorithm:
1. Initialize i = 10.
2. While i > 0, print i*n and decrement i by 1.
3. Stop at 1.

⏱ Time Complexity: O(1) (fixed 10 iterations)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
void calculateMultiple(int n) {
    int i = 10;
    while (i > 0) {
        cout << i * n << " ";
        i--;
    }
    cout << endl;
}

/*-----------------------------------------------------------
Main function: Example test case
-----------------------------------------------------------*/
int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    calculateMultiple(n);
    return 0;
}
