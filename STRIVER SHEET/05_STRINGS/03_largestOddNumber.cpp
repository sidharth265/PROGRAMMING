#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Largest Odd Number in String
Problem Link: https://leetcode.com/problems/largest-odd-number/

Problem Statement:
Given a string `num` representing a non-negative integer, return the largest odd number 
(as a substring from the start) that can be formed by removing some digits from the end 
(i.e., by truncating digits from right).  
If no odd number can be formed, return an empty string.

------------------------------------------------------------
Example 1:
Input:  num = "4206"
Output: ""
Explanation: No odd digits found → empty string.

Example 2:
Input:  num = "354"
Output: "354"
Explanation: 354 is already odd.

Example 3:
Input:  num = "220"
Output: "22"
Explanation: Removing last digit '0', "22" ends with '2' (even) but next step removes digit '2'? Need largest odd → continue check from right to left for odd digit.

------------------------------------------------------------
Constraints:
- 1 <= num.length <= 10^5
- num consists of digits only
------------------------------------------------------------
*/

/*
==================================================================
Approach: Right-to-Left Scan for Odd Digit
==================================================================
💡 Idea:
- Scan string from right to left.
- Return substring up to (and including) the first odd digit found.
- If none found, return empty string.

🧩 Algorithm:
1. Iterate from last index to 0.
2. Check if character represents odd digit.
3. If yes, return substring[0..i].
4. If loop finishes without find, return "".

⏱ Time Complexity: O(n)
📦 Space Complexity: O(1)
*/

string largestOddNumber(string num) {
    for (int i = (int)num.length() - 1; i >= 0; i--) {
        int n = num[i] - '0';
        if (n % 2 == 1) {
            return num.substr(0, i + 1);
        }
    }
    return "";
}

/*
==================================================================
main() function to test the implementation
==================================================================
*/

int main() {
    vector<string> testCases = {
        "4206",    // Output: ""
        "354",     // Output: "354"
        "220",     // Output: "2"
        "123456",  // Output: "12345"
        "7",       // Output: "7"
        "2468",    // Output: ""
        "987654321"// Output: "987654321"
    };

    for (const string& num : testCases) {
        cout << "Original String: " << num << endl;
        cout << "Largest Odd Number: " << largestOddNumber(num) << endl;
        cout << "--------------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
- The solution only requires a single pass scanning from the right.
- Detecting the last odd digit provides the largest possible odd substring starting from the left.
- Time complexity: O(n), space complexity: O(1).
- Optimal and straightforward solution.

Use this approach directly in interviews.
==================================================================
*/
