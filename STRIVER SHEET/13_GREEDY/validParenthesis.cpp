#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Valid Parentheses String
 LeetCode Link: https://leetcode.com/problems/valid-parentheses-string/

 Problem Statement:
 -----------------
 Given a string s containing only three types of characters: '(', ')' and '*', 
 return true if s is a valid parentheses string.

 The following rules define a valid parentheses string:
 - Any left parenthesis '(' must have a corresponding right parenthesis ')'.
 - Any right parenthesis ')' must have a corresponding left parenthesis '('.
 - Left parenthesis '(' must go before the corresponding right parenthesis ')'.
 - '*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".

 Example 1:
 Input: s = "()"
 Output: true

 Example 2:
 Input: s = "(*)"
 Output: true

 Example 3:
 Input: s = "(*))"
 Output: true

 Example 4:
 Input: s = "((("
 Output: false

 Constraints:
 - 1 <= s.length <= 100
 - s[i] is '(', ')' or '*'
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Recursion with Backtracking
 -----------------------------------------
 💡 Idea:
 For each '*' character, try all three possibilities: '(', ')' or empty string.
 Use recursion to explore all combinations and check if any leads to valid string.

 🧩 Algorithm:
 1. Use recursion with balance counter (count of unmatched '(' brackets).
 2. For '(': increment counter and recurse.
 3. For ')': decrement counter and recurse.
 4. For '*': try all three options (treat as '(', ')' or empty).
 5. Base case: if we reach end and counter is 0, return true.
 6. Early termination: if counter goes negative, return false.

 ⏱ Time Complexity: O(3^N) - for each '*', we try 3 options
 📦 Space Complexity: O(N) - recursion stack depth
*/
bool generateBruteForce(string& s, int count, int i) {
    if (count < 0) return false; // More ')' than '(' so far
    if (i == s.size()) return count == 0; // Check if balanced at end
    
    if (s[i] == '(') {
        return generateBruteForce(s, count + 1, i + 1);
    }
    else if (s[i] == ')') {
        return generateBruteForce(s, count - 1, i + 1);
    }
    else { // s[i] == '*'
        // Try all three possibilities for '*'
        return generateBruteForce(s, count + 1, i + 1) || // '*' as '('
               generateBruteForce(s, count - 1, i + 1) || // '*' as ')'
               generateBruteForce(s, count, i + 1);       // '*' as empty
    }
}

bool checkValidStringBruteForce(string s) {
    return generateBruteForce(s, 0, 0);
}


/* 
==========================================
 Approach 2: Better - Dynamic Programming with Memoization
 -----------------------------------------
 💡 Idea:
 Use memoization to avoid recalculating same states. State is defined by
 current index and current balance count.

 🧩 Algorithm:
 1. Use 2D DP table: dp[i][count] = can we make valid string from index i with count balance.
 2. Same recursive logic as brute force but store results.
 3. For each state (i, count), if already computed, return stored result.
 4. Otherwise, compute using recursion and store result.

 ⏱ Time Complexity: O(N^2) - at most N*N states to compute
 📦 Space Complexity: O(N^2) - DP table + recursion stack
*/
unordered_map<string, bool> memo;

bool generateMemoized(string& s, int count, int i) {
    if (count < 0) return false;
    if (i == s.size()) return count == 0;
    
    string key = to_string(i) + "," + to_string(count);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }
    
    bool result = false;
    if (s[i] == '(') {
        result = generateMemoized(s, count + 1, i + 1);
    }
    else if (s[i] == ')') {
        result = generateMemoized(s, count - 1, i + 1);
    }
    else { // s[i] == '*'
        result = generateMemoized(s, count + 1, i + 1) ||
                 generateMemoized(s, count - 1, i + 1) ||
                 generateMemoized(s, count, i + 1);
    }
    
    return memo[key] = result;
}

bool checkValidStringMemoized(string s) {
    memo.clear();
    return generateMemoized(s, 0, 0);
}


/* 
==========================================
 Approach 3: Optimal - Range Tracking (Two Pointers)
 -----------------------------------------
 💡 Idea:
 Track the range of possible unmatched '(' brackets at each step.
 minimum = minimum possible unmatched '(' count
 maximum = maximum possible unmatched '(' count

 🧩 Algorithm:
 1. Initialize minimum = 0, maximum = 0.
 2. For each character:
    - '(': both minimum and maximum increase by 1
    - ')': both minimum and maximum decrease by 1  
    - '*': minimum decreases by 1 (treat as ')'), maximum increases by 1 (treat as '(')
 3. If minimum < 0, reset to 0 (we can use '*' as empty to balance)
 4. If maximum < 0, return false (impossible to balance)
 5. At end, return minimum == 0 (valid if we can have 0 unmatched brackets)

 ⏱ Time Complexity: O(N) - single pass through string
 📦 Space Complexity: O(1) - only two variables
*/
bool checkValidStringOptimal(string s) {
    int minimum = 0, maximum = 0;
    
    for (char ch : s) {
        if (ch == '(') {
            minimum++;
            maximum++;
        }
        else if (ch == ')') {
            minimum--;
            maximum--;
        }
        else { // ch == '*'
            minimum--; // '*' treated as ')' in worst case
            maximum++; // '*' treated as '(' in best case
        }
        
        // If minimum goes negative, we can use '*' as empty to reset
        if (minimum < 0) minimum = 0;
        
        // If maximum goes negative, impossible to balance
        if (maximum < 0) return false;
    }
    
    // Valid if we can achieve exactly 0 unmatched brackets
    return minimum == 0;
}


/* Helper function to show step-by-step process */
void showStepByStep(string s) {
    int minimum = 0, maximum = 0;
    cout << "Step-by-step for \"" << s << "\":\n";
    cout << "Initial: min=0, max=0\n";
    
    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];
        cout << "Process '" << ch << "' -> ";
        
        if (ch == '(') {
            minimum++;
            maximum++;
        }
        else if (ch == ')') {
            minimum--;
            maximum--;
        }
        else {
            minimum--;
            maximum++;
        }
        
        if (minimum < 0) minimum = 0;
        
        cout << "min=" << minimum << ", max=" << maximum;
        if (maximum < 0) {
            cout << " -> INVALID (max < 0)\n";
            return;
        }
        cout << "\n";
    }
    
    cout << "Result: " << (minimum == 0 ? "VALID" : "INVALID") << 
            " (minimum=" << minimum << ")\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<string> testCases = {
        "()",
        "(*)",
        "(*))",
        "(((",
        "())",
        "*",
        "**",
        "(**))",
        "(((((*(()((((*((**(((()()*)()()()*((((**)())*)*)))))))(())(()))())((*()()(((()((()*(())*(()**)()(())",
        "",
        "(*)))",
        "((*)",
        "((*))"
    };

    cout << "=== Testing Valid Parentheses String Problem ===\n\n";
    
    for (string s : testCases) {
        cout << "Input: \"" << s << "\"\n";
        
        bool ans1 = checkValidStringBruteForce(s);
        bool ans2 = checkValidStringMemoized(s);
        bool ans3 = checkValidStringOptimal(s);
        
        cout << " Brute Force:       " << (ans1 ? "true" : "false") << "\n";
        cout << " Memoized:          " << (ans2 ? "true" : "false") << "\n";
        cout << " Optimal (Your):    " << (ans3 ? "true" : "false") << "\n";
        
        showStepByStep(s);
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(3^N) time, tries all '*' combinations recursively.\n";
    cout << "2. Memoized DP -> O(N^2) time, optimizes recursion with state caching.\n";
    cout << "3. Optimal Range Tracking -> O(N) time, tracks min/max possible balance.\n";
    cout << "\nRecommendation: Your optimal range tracking approach is brilliant! ✅\n";
    cout << "Key Insight: Instead of trying all possibilities for '*', track the range\n";
    cout << "             of possible unmatched '(' counts at each step.\n";
    cout << "\nRange Meaning:\n";
    cout << "- minimum: fewest unmatched '(' if we use '*' optimally (as ')' or empty)\n";
    cout << "- maximum: most unmatched '(' if we use '*' as '(' whenever possible\n";
    cout << "\nYour provided solutions showcase both recursive and optimal approaches perfectly! 🎯\n";

    return 0;
}
