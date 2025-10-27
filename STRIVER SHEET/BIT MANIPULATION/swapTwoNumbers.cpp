#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Swap Two Numbers Without Using Temp Variable
🔗 Problem Link: (Classic Interview Problem)

📌 Problem Statement:
Given two integers `a` and `b`, swap their values without using any extra variable.

----------------------------------------------------------
🧩 Example 1:
Input:
    a = 5, b = 10
Output:
    a = 10, b = 5

🧩 Example 2:
Input:
    a = -3, b = 7
Output:
    a = 7, b = -3
----------------------------------------------------------
*/


//////////////////////////////////////////////////////////////
// Approach 1: Using Arithmetic Operations (+ and -)
// 💡 Idea:
//   - Use simple addition & subtraction to exchange values.
//   - a = a + b
//   - b = a - b   (original a)
//   - a = a - b   (original b)
//
// ⚠️ Can cause integer overflow if a+b exceeds range.
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
void swap_AddSub(int &a, int &b) {
    a = a + b;
    b = a - b;
    a = a - b;
}


//////////////////////////////////////////////////////////////
// Approach 2: Using Multiplication & Division
// 💡 Idea:
//   - Swap using multiplication and division.
//   - a = a * b
//   - b = a / b   (original a)
//   - a = a / b   (original b)
//
// ⚠️ Can cause overflow or division by zero → unsafe.
// Not recommended in production, but asked in interviews.
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
void swap_MulDiv(int &a, int &b) {
    if (a == 0 || b == 0) return; // safeguard against division by zero
    a = a * b;
    b = a / b;
    a = a / b;
}


//////////////////////////////////////////////////////////////
// Approach 3: Using XOR Bitwise Operator
// 💡 Idea:
//   - XOR property: x ^ x = 0, x ^ 0 = x
//   - Perform three XOR operations to swap.
//   - This works without overflow.
//
// Steps:
//   a = a ^ b
//   b = a ^ b   (b gets original a)
//   a = a ^ b   (a gets original b)
//
// ⏱ Time Complexity: O(1)
// 📦 Space Complexity: O(1)
// ✅ Best approach (safe, efficient, elegant)
//////////////////////////////////////////////////////////////
void swap_XOR(int &a, int &b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}


//////////////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////////////
int main() {
    vector<pair<int, int>> testCases = {
        {5, 10},
        {-3, 7},
        {0, 25},
        {42, 42}  // swapping same numbers
    };

    for (auto [x, y] : testCases) {
        cout << "Before swapping: a = " << x << ", b = " << y << "\n";

        int a = x, b = y;

        // Using Addition/Subtraction
        swap_AddSub(a, b);
        cout << "   After swap_AddSub: a = " << a << ", b = " << b << "\n";

        a = x; b = y;
        // Using Multiplication/Division
        if (a != 0 && b != 0) {
            swap_MulDiv(a, b);
            cout << "   After swap_MulDiv: a = " << a << ", b = " << b << "\n";
        } else {
            cout << "   swap_MulDiv: Skipped (zero present, unsafe)\n";
        }

        a = x; b = y;
        // Using XOR
        swap_XOR(a, b);
        cout << "   After swap_XOR:    a = " << a << ", b = " << b << "\n";

        cout << "-------------------------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1 (Add/Sub): Works but can overflow.
    // - Approach 2 (Mul/Div): Works but unsafe for zeros & overflow.
    // - Approach 3 (XOR): Best, safe, no temp variable.
    //
    // Recommendation:
    //   → Use XOR trick in interviews/CP. 
    //   → Use temp variable in real-world code for readability!
    ////////////////////////////////////////////////////////////

    return 0;
}
