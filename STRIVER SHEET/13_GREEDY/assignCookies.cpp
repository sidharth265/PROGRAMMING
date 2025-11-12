#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Assign Cookies
 LeetCode Link: https://leetcode.com/problems/assign-cookies/

 Problem Statement:
 -----------------
 Assume you are an awesome parent and want to give your children some cookies. 
 But, you should give each child at most one cookie.
 
 Each child i has a greed factor g[i], which is the minimum size of a cookie 
 that the child will be content with; and each cookie j has a size s[j]. 
 If s[j] >= g[i], we can assign the cookie j to the child i, and the child 
 i will be content. Your goal is to maximize the number of your content children.

 Example 1:
 Input: g = [1,2,3], s = [1,1]
 Output: 1
 Explanation: You have 3 children and 2 cookies. The greed factors are [1,2,3].
 Although you have 2 cookies, since their sizes are both 1, you could only make 
 the child whose greed factor is 1 content.

 Example 2:
 Input: g = [1,2], s = [1,2,3]
 Output: 2
 Explanation: You have 2 children and 3 cookies. The greed factors are [1,2].
 You have 3 cookies and their sizes are big enough to gratify all children.

 Constraints:
 - 1 <= g.length <= 3 * 10^4
 - 0 <= s.length <= 3 * 10^4
 - 1 <= g[i], s[j] <= 2^31 - 1
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Try All Combinations
 -----------------------------------------
 💡 Idea:
 For each child, try to assign the smallest possible cookie that satisfies
 their greed factor. Use nested loops to check all possibilities.

 🧩 Algorithm:
 1. For each child, iterate through all cookies.
 2. Find the smallest cookie that can satisfy the child's greed.
 3. Mark that cookie as used and move to next child.
 4. Count total satisfied children.

 ⏱ Time Complexity: O(N * M) where N = children, M = cookies
 📦 Space Complexity: O(M) - to track used cookies
*/
int findContentChildrenBruteForce(vector<int>& g, vector<int>& s) {
    vector<bool> used(s.size(), false);
    int count = 0;
    
    for (int i = 0; i < g.size(); i++) {
        int bestCookie = -1;
        for (int j = 0; j < s.size(); j++) {
            if (!used[j] && s[j] >= g[i]) {
                if (bestCookie == -1 || s[j] < s[bestCookie]) {
                    bestCookie = j;
                }
            }
        }
        if (bestCookie != -1) {
            used[bestCookie] = true;
            count++;
        }
    }
    
    return count;
}


/* 
==========================================
 Approach 2: Better - Sort Ascending + Greedy
 -----------------------------------------
 💡 Idea:
 Sort both arrays in ascending order. For each child (starting from least greedy),
 try to assign the smallest cookie that can satisfy them.

 🧩 Algorithm:
 1. Sort children by greed factor (ascending).
 2. Sort cookies by size (ascending).
 3. Use two pointers: try to satisfy each child with smallest available cookie.
 4. If current cookie satisfies current child, move both pointers.
 5. Otherwise, move to next larger cookie.

 ⏱ Time Complexity: O(N log N + M log M) - sorting dominates
 📦 Space Complexity: O(1) - only using pointers
*/
int findContentChildrenAscending(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());  // Sort children by greed (ascending)
    sort(s.begin(), s.end());  // Sort cookies by size (ascending)
    
    int i = 0, j = 0;  // i for children, j for cookies
    
    while (i < g.size() && j < s.size()) {
        if (s[j] >= g[i]) {
            i++;  // Child i is satisfied
        }
        j++;  // Move to next cookie regardless
    }
    
    return i;  // Number of satisfied children
}


/* 
==========================================
 Approach 3: Optimal - Sort Descending + Greedy
 -----------------------------------------
 💡 Idea:
 Sort both arrays in descending order. Start with the most greedy child
 and try to assign the largest available cookie. This is more efficient
 as we handle harder cases first.

 🧩 Algorithm:
 1. Sort children by greed factor (descending).
 2. Sort cookies by size (descending).
 3. Use two pointers: for each child, try largest available cookie.
 4. If current cookie satisfies current child, move cookie pointer.
 5. Always move to next child.

 ⏱ Time Complexity: O(N log N + M log M) - sorting dominates
 📦 Space Complexity: O(1) - only using pointers
*/
int findContentChildrenDescending(vector<int>& g, vector<int>& s) {
    sort(g.rbegin(), g.rend());  // Sort children by greed (descending)
    sort(s.rbegin(), s.rend());  // Sort cookies by size (descending)
    
    int i = 0, j = 0;  // i for children, j for cookies
    
    while (i < g.size() && j < s.size()) {
        if (s[j] >= g[i]) {
            j++;  // Cookie j is assigned to child i
        }
        i++;  // Move to next child
    }
    
    return j;  // Number of cookies used = satisfied children
}


/* Helper function to print arrays */
void printArray(const vector<int>& arr, const string& name) {
    cout << name << " = [";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<pair<vector<int>, vector<int>>> testCases = {
        {{1, 2, 3}, {1, 1}},
        {{1, 2}, {1, 2, 3}},
        {{1, 2, 7, 8, 9}, {1, 3, 5, 9, 10}},
        {{4, 3, 2, 1}, {1, 2, 3}},
        {{10, 9, 8, 7}, {5, 6, 7, 8}},
        {{}, {1, 2, 3}},  // No children
        {{1, 2, 3}, {}}   // No cookies
    };

    cout << "=== Testing Assign Cookies Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> g1 = testCases[t].first, g2 = testCases[t].first, g3 = testCases[t].first;
        vector<int> s1 = testCases[t].second, s2 = testCases[t].second, s3 = testCases[t].second;
        
        cout << "Test Case " << t + 1 << ":\n";
        printArray(g1, "Children greed");
        cout << "\n";
        printArray(s1, "Cookie sizes");
        cout << "\n";
        
        int ans1 = findContentChildrenBruteForce(g1, s1);
        int ans2 = findContentChildrenAscending(g2, s2);
        int ans3 = findContentChildrenDescending(g3, s3);
        
        cout << " Brute Force:         " << ans1 << "\n";
        cout << " Ascending Sort:      " << ans2 << "\n";
        cout << " Descending Sort:     " << ans3 << "\n";
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N*M) time, tries all combinations but inefficient.\n";
    cout << "2. Ascending Sort -> O(N log N + M log M), satisfy least greedy children first.\n";
    cout << "3. Descending Sort -> O(N log N + M log M), satisfy most greedy children first.\n";
    cout << "\nRecommendation: Both sorted approaches work equally well in interviews.\n";
    cout << "Key Insight: Greedy algorithm works because we want to maximize satisfied children,\n";
    cout << "             so we should be efficient with cookie allocation.\n";
    cout << "\nYour provided solution uses the Descending Sort approach - excellent choice! ✅\n";

    return 0;
}
