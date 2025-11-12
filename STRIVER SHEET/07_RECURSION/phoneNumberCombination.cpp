#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Letter Combinations of a Phone Number
 Problem Link: https://leetcode.com/problems/letter-combinations-of-a-phone-number/

 Problem Statement:
 Given a string containing digits from 2-9 inclusive, return all possible letter combinations 
 that the number could represent on a phone keypad. Return the answer in any order.
 The mapping is the same as on telephone buttons:
 2 -> "abc", 3 -> "def", 4 -> "ghi", 5 -> "jkl", 6 -> "mno", 7 -> "pqrs", 8 -> "tuv", 9 -> "wxyz".

 Note: 1 does not map to any letters.

-------------------------------------------------
 Example:
 Input: digits = "23"
 Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Backtracking / DFS
// -------------------------------------------------
/*
💡 Idea:
   - Traverse the digits string recursively.
   - For each digit, iterate through corresponding letters and append one by one.
   - When the combination is of the digits length, add to results.

🧩 Algorithm:
   1. Base case: if current index equals digits length, add formed string to results.
   2. Recursive case: for each letter mapped from current digit, append and recurse.
   3. Backtrack by removing last added letter.

⏱ Time Complexity: O(4^N), where N is digits length (max letters per digit is 4)
📦 Space Complexity: O(N) recursion stack + O(1) additional space excluding output
*/

void generate(string m[], vector<string>& result, string& s, const string& digits, int i) {
    if (i == (int)digits.length()) {
        result.push_back(s);
        return;
    }
    for (char ch : m[digits[i] - '2']) {
        s.push_back(ch);
        generate(m, result, s, digits, i + 1);
        s.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};
    vector<string> result;
    string s = "";
    string m[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    generate(m, result, s, digits, 0);
    return result;
}


// -------------------------------------------------
// Main Function (Demo)
// -------------------------------------------------
int main() {
    string digits = "23";
    cout << "Input digits: " << digits << "\n";
    vector<string> combinations = letterCombinations(digits);
    
    cout << "Letter Combinations:\n";
    for (const string& comb : combinations) {
        cout << comb << "\n";
    }

    // Additional test case
    digits = "79";
    cout << "\nInput digits: " << digits << "\n";
    combinations = letterCombinations(digits);
    cout << "Letter Combinations:\n";
    for (const string& comb : combinations) {
        cout << comb << "\n";
    }

    // ✅ Approach Overview
    /*
    - Uses backtracking to explore letter combinations.
    - Time complexity grows exponentially with the number of digits due to branching.
    - Space complexity is linear in recursion depth.
    */

    return 0;
}
