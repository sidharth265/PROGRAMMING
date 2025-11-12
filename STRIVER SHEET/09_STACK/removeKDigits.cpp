#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Remove K Digits
Problem Link: LeetCode #402 (https://leetcode.com/problems/remove-k-digits/)

Problem Statement:
Given a non-negative integer `num` represented as a string and an integer `k`, 
remove exactly `k` digits from the number so that the resulting number is the 
smallest possible.

Note:
- The result should not contain leading zeros.
- If all digits are removed, return "0".

------------------------------------------------------------
Example 1:
Input:  num = "1432219", k = 3
Output: "1219"
Explanation:
Remove 4, 3, and 2 to get smallest number "1219".

Example 2:
Input:  num = "10200", k = 1
Output: "200"
Explanation:
Remove '1' to get "0200" → after trimming leading zeros → "200".

Example 3:
Input:  num = "10", k = 2
Output: "0"
Explanation:
All digits removed.

------------------------------------------------------------
Constraints:
- 1 ≤ num.length ≤ 10^5
- num consists only of digits
- 0 ≤ k ≤ num.length
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Stack / Monotonic Increasing Sequence (Optimal)
==================================================================
💡 Idea:
- To form smallest number, remove digits in decreasing order of value.
- Use stack to maintain increasing digits:
  - While top of stack > current digit and k > 0 → remove top.
  - Push current digit.
- After traversal, remove extra digits if k>0.
- Build result string, remove leading zeros.

🧩 Algorithm:
1. Create empty stack<char>.
2. For each digit in num:
   - While stack not empty AND k > 0 AND top > digit → pop stack, decrement k.
   - Push current digit.
3. Pop more if k > 0.
4. Construct result string from stack.
5. Trim leading zeros.
6. Return result if not empty else "0".

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

string removeKdigits_stack(string num, int k) {
    stack<char> st;
    for (char ch : num) {
        while (!st.empty() && k > 0 && st.top() > ch) {
            st.pop();
            k--;
        }
        st.push(ch);
    }
    while (!st.empty() && k > 0) { 
        st.pop();
        k--;
    }
    string ans;
    while (!st.empty()) { ans.push_back(st.top()); st.pop(); }
    reverse(ans.begin(), ans.end());

    // Remove leading zeros
    int i = 0;
    while (i < ans.size() && ans[i] == '0') i++;
    ans = ans.substr(i);
    return ans.empty() ? "0" : ans;
}

/*
==================================================================
Approach 2: Greedy Erase (Naive, Less Efficient)
==================================================================
💡 Idea:
- Repeat k times:
  - Scan string, find first digit greater than the next digit, remove it.
  - If no such digit found, remove last digit.
- Result trimmed of leading zeros.

🧩 Algorithm:
1. Repeat while k > 0:
   - For i in range num.size():
       if num[i] > num[i+1], erase num[i], break.
   - If not erased, erase last digit.
   - Decrement k.
2. Trim leading zeros.
3. If string empty, return "0".

⏱ Time Complexity: O(n*k) worst case.
📦 Space Complexity: O(1) extra.

(This is not optimal, but helpful for reasoning.)
*/

string removeKdigits_naive(string num, int k) {
    while (k > 0 && !num.empty()) {
        int n = num.size();
        bool erased = false;
        for (int i = 0; i < n-1; i++) {
            if (num[i] > num[i+1]) {
                num.erase(num.begin() + i);
                erased = true;
                break;
            }
        }
        if (!erased) {
            num.pop_back();
        }
        k--;
    }

    // Remove leading zeros
    int i = 0;
    while (i < num.size() && num[i] == '0') i++;
    num = num.substr(i);

    return num.empty() ? "0" : num;
}


/*
==================================================================
main() function
==================================================================
*/
int main() {
    vector<pair<string,int>> testCases = {
        {"1432219", 3},   // Expected: 1219
        {"10200", 1},     // Expected: 200
        {"10", 2},        // Expected: 0
        {"1234567890", 9} // Expected: 0
    };

    for (auto [num, k] : testCases) {
        cout << "Input: num = " << num << ", k = " << k << endl;
        cout << "Output (Stack Optimal): " << removeKdigits_stack(num, k) << endl;
        cout << "Output (Naive Greedy):  " << removeKdigits_naive(num, k) << endl;
        cout << "-----------------------------------------" << endl;
    }
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Stack / Monotone Increasing:
   - Efficient, O(n).
   - Best for large inputs.
   - Recommended in interviews.

2. Naive Greedy:
   - Simple to implement, helps build intuition.
   - O(n*k), poor for large n.
   - Not good for production.

👉 Use the **Stack approach** in interviews and practice.
==================================================================
*/
