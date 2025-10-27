#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Asteroid Collision
 Problem Link: https://leetcode.com/problems/asteroid-collision/

 Problem Statement:
 Given an array of integers asteroids, where asteroids[i] represents the size of the ith asteroid. Positive values indicate right-moving asteroids, negative values indicate left-moving.
 When two asteroids collide:
   - The smaller is destroyed.
   - If they are equal, both are destroyed.
   - Asteroids moving in the same direction never collide.

 Return the state of the asteroids after all collisions.

-------------------------------------------------
 Example 1:
 Input: asteroids = [5, 10, -5]
 Output: [5, 10]
 Explanation:
   10 and -5 collide; 10 survives.

 Example 2:
 Input: asteroids = [8, -8]
 Output: []
 Explanation:
   Both collide and are destroyed.

 Example 3:
 Input: asteroids = [10, 2, -5]
 Output: [10]
-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Stack Simulation
// -------------------------------------------------
/*
💡 Idea:
   - Use a stack to store asteroids that are still moving ("active").
   - For each asteroid:
       - If moving right or stack is empty, push it.
       - If moving left, compare/collide with all right-moving asteroids on top of stack:
           - If right is smaller: pop it and continue.
           - If right is equal: pop it and don't add left.
           - If right is bigger: left is destroyed.

🧩 Algorithm:
   1. For each asteroid x:
         - While stack not empty, x is left (<0), and top is right (>0):
             - If top < abs(x): pop and continue
             - If top == abs(x): pop and mark left as destroyed
             - If top > abs(x): mark left as destroyed
         - If not destroyed, push x to stack
   2. The stack holds surviving asteroids (in reverse).

⏱ Time Complexity: O(n)
📦 Space Complexity: O(n)
*/

vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> st;
    for (int x : asteroids) {
        bool destroyed = false;
        while (!st.empty() && x < 0 && st.top() > 0) {
            if (st.top() < -x) {
                st.pop();
                continue;
            }
            else if (st.top() == -x) {
                st.pop();
            }
            destroyed = true;
            break;
        }
        if (!destroyed) st.push(x);
    }
    int n = st.size();
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = st.top();
        st.pop();
    }
    return ans;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<vector<int>> testCases = {
        {5, 10, -5},
        {8, -8},
        {10, 2, -5},
        {-2, -1, 1, 2},
        {1, -1, -2, 2, -2},
        {2, -2, -2, 2}
    };

    for (const auto& asteroids : testCases) {
        cout << "Input: ";
        for (int x : asteroids) cout << x << " ";
        cout << "\nOutput: ";
        vector<int> result = asteroidCollision(const_cast<vector<int>&>(asteroids));
        for (int x : result) cout << x << " ";
        cout << "\n-------------------------\n";
    }

    // ✅ Approach Overview
    /*
    - Stack simulates all asteroid collisions in-place.
    - TC: O(n), SC: O(n)
    */

    return 0;
}
