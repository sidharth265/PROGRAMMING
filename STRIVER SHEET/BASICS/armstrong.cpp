#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Armstrong Number Check

Problem Statement:
An Armstrong number (also known as a narcissistic number) is an n-digit number that is equal to the sum of its own digits each raised to the power n.

For example:
- 153 is an Armstrong number because it has 3 digits, and \(1^3 + 5^3 + 3^3 = 153\).
- 9474 is an Armstrong number because it has 4 digits, and \(9^4 + 4^4 + 7^4 + 4^4 = 9474\).

Given a number, check if it is an Armstrong number.

-----------------------------------------------------------
Example 1:
Input: 153
Output: true
Explanation: \(1^3 + 5^3 + 3^3 = 153\)

Example 2:
Input: 123
Output: false
Explanation: \(1^3 + 2^3 + 3^3 = 36 \neq 123\)

===========================================================
*/

/*-----------------------------------------------------------
Approach: Calculate sum of digits raised to power of digit count
💡 Idea:
- Count number of digits \(k\).
- Extract digits and calculate sum of each digit raised to power \(k\).
- Compare sum with original number.

🧩 Algorithm:
1. Calculate \(k =\) number of digits (using `log10` or string conversion).
2. Initialize sum = 0.
3. Copy original number to temp.
4. While temp > 0:
    - Extract digit = temp % 10.
    - Add pow(digit, k) to sum.
    - temp = temp / 10.
5. Check if sum equals original number.

⏱ Time Complexity: O(log n) (number of digits)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
bool isArmstrong(int num) {
    int k = log10(num) + 1;  // number of digits
    int sum = 0, temp = num;

    while (temp > 0) {
        int digit = temp % 10;
        sum += pow(digit, k);
        temp /= 10;
    }
    return sum == num;
}

/*-----------------------------------------------------------
Main function: Test Armstrong number function with examples
-----------------------------------------------------------*/
int main() {
    vector<int> testCases = {153, 9474, 123, 370, 0, 9, 1634};

    for (int num : testCases) {
        cout << num << (isArmstrong(num) ? " is " : " is not ") << "an Armstrong number." << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach: Sum of digits raised to count of digits, compare with original.
       Time Complexity: O(log n)
       Space Complexity: O(1)

    Covers all standard Armstrong numbers for positive integers.
    -----------------------------------------------------------
    */
    return 0;
}
