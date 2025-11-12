#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Area Calculation Using Switch Case

Problem Statement:
Given a choice and relevant parameters, calculate either the area of a circle or
the area of a rectangle using a switch-case statement.

- Choice 1: Area of circle with radius R
- Choice 2: Area of rectangle with length L and breadth B

If an invalid choice is made, print an error message and return -1.

-----------------------------------------------------------
Example 1:
Input:
Choice: 1
R: 5
Output: Area = 78.5398 (π * 5^2)

Example 2:
Input:
Choice: 2
L: 4, B: 7
Output: Area = 28

Example 3:
Input:
Choice: 3
Output: Invalid choice

===========================================================
*/

/*-----------------------------------------------------------
Approach: Use switch-case for choice-based computation
💡 Idea:
- Use switch-case on the choice input:
  1. Compute area of circle => π * R^2
  2. Compute area of rectangle => L * B
- Default case returns error.

🧩 Algorithm:
1. Read choice.
2. Prepare a vector with inputs at indices 0,1,2 = R,L,B.
3. Switch on choice:
   - case 1: return π*R*R
   - case 2: return L*B
   - default: print error and return -1

⏱ Time Complexity: O(1)  
📦 Space Complexity: O(1)
-----------------------------------------------------------*/
double switchCase(int choice, vector<double> &arr) {
    switch (choice) {
        case 1: {
            return (M_PI * arr[0] * arr[0]);
        }
        case 2: {
            return (arr[1] * arr[2]);
        }
        default:
            cout << "Invalid choice" << endl;
            return -1;
    }
}

/*-----------------------------------------------------------
Main function: Input choice and parameters, output area
-----------------------------------------------------------*/
int main() {
    int choice;
    cout << "Enter your choice (1 for circle, 2 for rectangle): ";
    cin >> choice;

    double R, L, B;
    cout << "Enter the values of R, L, B: ";
    cin >> R >> L >> B;

    vector<double> arr(3);
    arr[0] = R; // Radius for circle
    arr[1] = L; // Length for rectangle
    arr[2] = B; // Breadth for rectangle

    double result = switchCase(choice, arr);
    if (result != -1) {
        cout << "Result: " << result << endl;
    }

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach: Use switch-case to branch calculation based on choice.
    Time Complexity: O(1)
    Space Complexity: O(1)
    -----------------------------------------------------------
    */
    return 0;
}
