#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Sum of Beauty of All Substrings
Problem Link: https://leetcode.com/problems/sum-of-beauty-of-all-substrings/

Problem Statement:
The beauty of a string is defined as the difference between the frequency of the most frequent and least frequent characters in the string.
Given a string s consisting of only lowercase English letters, return the sum of beauty values of all its substrings.

Example 1:
Input: s = "aabcb"
Output: 5
Explanation:
The substrings with non-zero beauty values are ["aab","aabc","aabcb","abcb","bcb"], each having beauty = 1, giving total = 5.

Example 2:
Input: s = "aabcbaa"
Output: 17
*/


// Approach 1: Brute Force Frequency Counting
// 💡 Idea:
// Enumerate all substrings and compute their beauty using frequency counts.
// For each starting position, maintain and update frequency as substring expands.
//
// 🧩 Algorithm:
// 1. Iterate over all possible start positions `i` of substrings.
// 2. Initialize a frequency vector of size 26 to zero.
// 3. For each end position `j`, update frequency count for s[j].
// 4. Compute the max and min frequency (ignoring zeros).
// 5. Add (maxFreq - minFreq) to the result.
//
// ⏱ Time Complexity: O(n² * 26)
// 📦 Space Complexity: O(26)

int beautySum(string s) {
    int l = s.length();
    int result = 0, maxFreq, minFreq;

    for (int i = 0; i < l; i++) {
        vector<int> freq(26, 0);
        for (int j = i; j < l; j++) {
            freq[s[j] - 'a']++;
            maxFreq = INT_MIN;
            minFreq = INT_MAX;

            for (int k : freq) {
                if (k > 0) {
                    maxFreq = max(maxFreq, k);
                    minFreq = min(minFreq, k);
                }
            }

            if (minFreq != INT_MAX)
                result += (maxFreq - minFreq);
        }
    }
    return result;
}


// Approach 2: Optimized Frequency Counting (Reduced Constants)
// 💡 Idea:
// Similar to Approach 1 but avoids recalculating full max/min arrays by tracking non-zero frequencies dynamically.
//
// 🧩 Algorithm:
// 1. Use frequency vector and update it incrementally.
// 2. Track current seen characters to minimize redundant checks.
//
// ⏱ Time Complexity: O(n² * 26)
// 📦 Space Complexity: O(26)

int beautySumOptimized(string s) {
    int n = s.size(), ans = 0;

    for (int i = 0; i < n; i++) {
        vector<int> count(26, 0);
        int distinct = 0;
        for (int j = i; j < n; j++) {
            int ch = s[j] - 'a';
            count[ch]++;
            int maxF = 0, minF = INT_MAX;
            for (int k = 0; k < 26; k++) {
                if (count[k] > 0) {
                    maxF = max(maxF, count[k]);
                    minF = min(minF, count[k]);
                }
            }
            ans += (maxF - minF);
        }
    }
    return ans;
}

int main() {
    string s1 = "aabcb";
    string s2 = "aabcbaa";
    string s3 = "abc";

    cout << "Test 1: " << beautySum(s1) << "\n";      // Expected 5
    cout << "Test 2: " << beautySum(s2) << "\n";      // Expected 17
    cout << "Test 3: " << beautySum(s3) << "\n";      // Expected 0

    cout << "\nUsing optimized version:\n";
    cout << "Test 1: " << beautySumOptimized(s1) << "\n";  
    cout << "Test 2: " << beautySumOptimized(s2) << "\n";  
    cout << "Test 3: " << beautySumOptimized(s3) << "\n";  

    return 0;
}

/*
✅ Approach Overview:
| Approach               | Time Complexity | Space Complexity | Notes                                         |
|------------------------|----------------|------------------|-----------------------------------------------|
| Brute Force Frequency  | O(n² * 26)     | O(26)            | Simple, works within constraints (n ≤ 500)   |
| Optimized Version      | O(n² * 26)     | O(26)            | Cleaner constant factor, same core logic     |

Both approaches are efficient enough for n ≤ 500 (constraint in the original problem). Datasets up to 500²=250000 substrings are manageable.
*/
