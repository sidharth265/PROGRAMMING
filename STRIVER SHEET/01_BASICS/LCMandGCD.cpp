#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Compute LCM and GCD of Two Numbers

Problem Statement:
Given two integers a and b, compute their Least Common Multiple (LCM) and Greatest Common Divisor (GCD).
Return a vector containing the LCM and GCD.

-----------------------------------------------------------
Example 1:
Input: a = 12, b = 15
Output: LCM: 60, GCD: 3

Example 2:
Input: a = 8, b = 20
Output: LCM: 40, GCD: 4

===========================================================
*/

/*-----------------------------------------------------------
Approach: Euclidean Algorithm for GCD and formula for LCM
💡 Idea:
- Use Euclidean algorithm to calculate GCD efficiently.
- Calculate LCM using formula: LCM(a, b) = (a * b) / GCD(a, b).

🧩 Algorithm:
1. Initialize gcd = a, b1 = b.
2. While b1 != 0:
   a) temp = b1
   b) b1 = gcd % b1
   c) gcd = temp
3. Calculate lcm = (a * b) / gcd
4. Return vector {lcm, gcd}

⏱ Time Complexity: O(log(min(a, b))) due to Euclidean GCD  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
vector<int> lcmAndGcd(int a, int b) {
    int gcd = a;
    int b1 = b;
    while (b1 != 0) {
        int temp = b1;
        b1 = gcd % b1;
        gcd = temp;
    }
    int lcm = (a / gcd) * b;  // To avoid overflow, divide first
    return {lcm, gcd};
}

/*-----------------------------------------------------------
Main function: Input two numbers and output LCM and GCD
-----------------------------------------------------------*/
int main() {
    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;

    vector<int> result = lcmAndGcd(a, b);
    cout << "LCM: " << result[0] << ", GCD: " << result[1] << endl;

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach:
      - Euclidean Algorithm for GCD calculation
      - LCM using formula LCM = (a*b)/GCD
    
    Time Complexity: O(log(min(a,b)))
    Space Complexity: O(1)
    -----------------------------------------------------------
    */
    return 0;
}
