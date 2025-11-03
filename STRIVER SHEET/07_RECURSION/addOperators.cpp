#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------------
Problem Title: Expression Add Operators
Link: (LeetCode #282)

Problem Statement:
Given a string `num` that contains only digits and an integer `target`, 
we return all possible expressions formed by inserting `+`, `-`, or `*` 
between digits in `num` such that the expression evaluates exactly to `target`.

Constraints:
- Digits must remain in order.
- You cannot add parentheses.
- No leading zeros allowed except single "0".

---------------------------------------------------------------
Examples:

Example 1:
Input: num = "123", target = 6
Output: ["1+2+3","1*2*3"]

Example 2:
Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]

Example 3:
Input: num = "105", target = 5
Output: ["1*0+5","10-5"]

Example 4:
Input: num = "00", target = 0
Output: ["0+0","0-0","0*0"]

---------------------------------------------------------------
*/


/* -----------------------------------------------------------
   Approach: Backtracking with Expression Evaluation
------------------------------------------------------------
💡 Idea:
- Use recursion with backtracking to try all possibilities.
- At each digit, split string into a number and consider:
   - Addition
   - Subtraction
   - Multiplication
- Maintain running `eval` result and `multed` (for multiplication handling).

🧩 Algorithm:
1. Use DFS from index=0.
2. At each step, pick substring num[index..i].
3. Skip leading zeros.
4. Convert substring → number.
5. If index==0 → start with this number.
6. Else, try placing '+' / '-' / '*' before number.
7. For '*', handle operator precedence by adjusting previous multiplication.
8. If at end and eval == target → store expression.

⏱ Time Complexity: ≈ O(4^N) (since at each position, 3 ops considered).
📦 Space Complexity: O(N) recursion depth.
------------------------------------------------------------ */
void addOperatorsUtil(string num, int target, string path,
                     long long eval, long long multed, int index,
                     vector<string>& result) {
    if (index == num.size()) {
        if (eval == target) result.push_back(path);
        return;
    }

    for (int i = index; i < num.size(); i++) {
        if (i != index && num[index] == '0') break; // skip leading zeros

        string currStr = num.substr(index, i - index + 1);
        long long currNum = stoll(currStr);

        if (index == 0) {
            // starting number (no operator before it)
            addOperatorsUtil(num, target, currStr, currNum, currNum, i + 1, result);
        } else {
            // Try addition
            addOperatorsUtil(num, target, path + "+" + currStr, eval + currNum, currNum, i + 1, result);
            // Try subtraction
            addOperatorsUtil(num, target, path + "-" + currStr, eval - currNum, -currNum, i + 1, result);
            // Try multiplication
            addOperatorsUtil(num, target, path + "*" + currStr, eval - multed + multed * currNum, multed * currNum, i + 1, result);
        }
    }
}

vector<string> addOperators(string num, int target) {
    vector<string> result;
    if (num.empty()) return result;
    addOperatorsUtil(num, target, "", 0, 0, 0, result);
    return result;
}


/* -----------------------------------------------------------
   Driver Code (Testing)
------------------------------------------------------------ */
int main() {
    vector<pair<string,int>> testCases = {
        {"123", 6},   // ["1+2+3", "1*2*3"]
        {"232", 8},   // ["2*3+2", "2+3*2"]
        {"105", 5},   // ["1*0+5","10-5"]
        {"00", 0},    // ["0+0","0-0","0*0"]
        {"3456237490", 9191} // []
    };

    for (auto& [num, target] : testCases) {
        cout << "-----------------------------------\n";
        cout << "Input: num = " << num << ", target = " << target << endl;
        vector<string> result = addOperators(num, target);

        cout << "Valid Expressions:\n";
        if (result.empty()) cout << "None\n";
        for (auto& expr : result) {
            cout << expr << endl;
        }
    }

    /* -------------------------------------------------------
       ✅ Approach Overview
       - Backtracking with recursive exploration.
       - Handles operator precedence via `multed` trick.
       - Exponential time complexity but acceptable for small n (<=10).
       - Classic interview backtracking question.
    ------------------------------------------------------- */

    return 0;
}
