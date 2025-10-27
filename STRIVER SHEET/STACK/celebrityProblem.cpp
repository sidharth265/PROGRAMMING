#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Celebrity Problem
 Problem Link: https://practice.geeksforgeeks.org/problems/the-celebrity-problem/1

 Problem Statement:
 In a party, a celebrity is a person who is known to everyone else 
 but who knows no one (including themselves). Given a n x n matrix mat where mat[i][j]=1 
 means person i knows person j, return the index of the celebrity, 
 or -1 if there is no celebrity.

-------------------------------------------------
 Example:
 Input:
   mat = [
     [0, 1, 1],
     [0, 1, 0],
     [1, 1, 0]
   ]
 Output: 1
 Explanation: Only person 1 satisfies the conditions.
-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force
// -------------------------------------------------
/*
💡 Idea:
   - For each person, check:
     - If they don't know anyone else (row all 0 except self),
     - If everyone knows them (column all 1 except self).
   - If so, return that index.

🧩 Algorithm:
   1. For i = 0..n-1:
       - Check row: mat[i][j] == 0 for all j != i
       - Check column: mat[j][i] == 1 for all j != i
       - If both, return i.
   2. Else, return -1.

⏱ Time Complexity: O(n^2)
📦 Space Complexity: O(1)
*/

int celebrityBrute(vector<vector<int>>& mat) {
    int n = (int)mat.size();
    for (int i = 0; i < n; i++) {
        bool celeb = true;
        for (int j = 0; j < n; j++) {
            if (i != j && mat[i][j] == 1) celeb = false; // i knows j, not celeb
        }
        for (int j = 0; j < n; j++) {
            if (mat[j][i] == 0 && i != j) celeb = false; // someone doesn't know i
        }
        if (celeb) return i;
    }
    return -1;
}


// -------------------------------------------------
// Approach 2: Stack-based Elimination (Optimal)
// -------------------------------------------------
/*
💡 Idea:
   - Use stack to compare pairs.
   - If a knows b, a can't be celebrity, pop a.
   - If a doesn't know b, b can't be celebrity, pop b.
   - Last person left in stack is candidate.
   - Validate the candidate.

🧩 Algorithm:
   1. Push all indices 0..n-1 to stack.
   2. While stack > 1:
       - Pop top two: a,b
       - If mat[a][b] == 1: push b
         Else: push a
   3. Candidate is stack.top().
   4. Validate:
       - Check all others don't know anyone & are known by everyone.

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

int celebrityStack(vector<vector<int>>& mat) {
    int n = (int)mat.size();
    stack<int> s;
    for (int i = 0; i < n; i++) s.push(i);

    while (s.size() > 1) {
        int a = s.top(); s.pop();
        int b = s.top(); s.pop();
        if (mat[a][b] == 1) s.push(b);     // a knows b: a can't be celebrity
        else s.push(a);                    // a doesn't know b: b can't be celebrity
    }

    int ans = s.top();
    for (int i = 0; i < n; i++) {
        if (i != ans && (mat[ans][i] == 1 || mat[i][ans] == 0)) return -1;
    }
    return ans;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<vector<vector<int>>> testMats = {
        {
            {0, 1, 1},
            {0, 1, 0},
            {1, 1, 0}
        },
        {
            {0, 0},
            {1, 0}
        },
        {
            {0, 1, 0},
            {0, 0, 0},
            {1, 1, 0}
        }
    };

    for (const auto& mat : testMats) {
        int celeb_brute = celebrityBrute(const_cast<vector<vector<int>>&>(mat));
        int celeb_stack = celebrityStack(const_cast<vector<vector<int>>&>(mat));
        cout << "Celebrity (Brute force): " 
             << (celeb_brute != -1 ? to_string(celeb_brute) : "None") << endl;
        cout << "Celebrity (Optimal Stack): " 
             << (celeb_stack != -1 ? to_string(celeb_stack) : "None") << endl;
        cout << "---------------------------\n";
    }

    // ✅ Approach Overview
    /*
    Approach 1 (Brute Force): O(n^2) time, O(1) space.
    Approach 2 (Stack):       O(n) time,  O(n) space.
    */
    return 0;
}
