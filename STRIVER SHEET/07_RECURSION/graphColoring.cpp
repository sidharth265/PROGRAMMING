#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Graph Coloring Problem
 Problem Link: https://practice.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1

 Problem Statement:
 You are given an undirected graph with `V` vertices and a list of edges. 
 Determine if the graph can be colored using **at most M colors** such that 
 no two adjacent vertices have the same color.

 Return true if such a coloring exists, otherwise false.

-------------------------------------------------
 Example 1:
 Input:
   V = 4, Edges = [[0,1],[0,2],[1,2],[1,3]], M = 3
 Output: true
 Explanation:
   One possible coloring: Vertex 0 → Color 1, Vertex 1 → Color 2,
                          Vertex 2 → Color 3, Vertex 3 → Color 1

 Example 2:
 Input:
   V = 3, Edges = [[0,1],[1,2],[2,0]], M = 2
 Output: false
 Explanation:
   A triangle graph needs 3 colors, but we have only 2.
-------------------------------------------------
*/


// -------------------------------------------------
// Approach 1: Brute Force (Try All Assignments)
// -------------------------------------------------
/*
💡 Idea:
   - Assign each vertex one of M colors blindly.
   - After assigning all vertices, check if it's valid.
   - If any valid assignment exists → return true.

🧩 Algorithm:
   1. Generate all (M^V) possible colorings.
   2. Check if for every edge (u,v), color[u] != color[v].
   3. Return true if valid found.

⏱ Time Complexity: O(M^V * V)   (try all colorings)
📦 Space Complexity: O(V)
*/

bool isValidColoring(vector<int>& colorMap, vector<vector<int>>& edges) {
    for (auto &e : edges) {
        if (colorMap[e[0]] == colorMap[e[1]]) return false;
    }
    return true;
}

bool bruteForceAssign(vector<int>& colorMap, int v, int m, int idx, vector<vector<int>>& edges) {
    if (idx == v) return isValidColoring(colorMap, edges);

    for (int color = 1; color <= m; color++) {
        colorMap[idx] = color;
        if (bruteForceAssign(colorMap, v, m, idx+1, edges)) 
            return true;
        colorMap[idx] = 0;
    }
    return false;
}

bool graphColoringBrute(int v, vector<vector<int>>& edges, int m) {
    vector<int> colorMap(v, 0);
    return bruteForceAssign(colorMap, v, m, 0, edges);
}


// -------------------------------------------------
// Approach 2: Backtracking (Early Pruning)
// -------------------------------------------------
/*
💡 Idea:
   - Unlike brute force, validate while assigning.
   - For each vertex, only assign colors that don’t conflict with neighbors.
   - Prune invalid paths early.

🧩 Algorithm:
   1. Start from vertex 0.
   2. For each color from 1..M:
       - Check if assigning this color to current vertex is safe 
         (no adjacent already has same color).
       - If safe, assign and recurse.
   3. If all vertices assigned → success.

⏱ Time Complexity: O(M^V) worst case, but prunes a LOT
📦 Space Complexity: O(V)
*/

bool canColor(vector<int>& colorMap, vector<vector<int>>& edges, int vertex, int color) {
    for (auto &e : edges) {
        if (e[0] == vertex && colorMap[e[1]] == color) return false;
        if (e[1] == vertex && colorMap[e] == color) return false;
    }
    return true;
}

bool backtrackColor(vector<int>& colorMap, int v, int m, int idx, vector<vector<int>>& edges) {
    if (idx == v) return true;

    for (int color = 1; color <= m; color++) {
        if (canColor(colorMap, edges, idx, color)) {
            colorMap[idx] = color;
            if (backtrackColor(colorMap, v, m, idx+1, edges))
                return true;
            colorMap[idx] = 0;
        }
    }
    return false;
}

bool graphColoringBacktrack(int v, vector<vector<int>>& edges, int m) {
    vector<int> colorMap(v, 0);
    return backtrackColor(colorMap, v, m, 0, edges);
}


// -------------------------------------------------
// Approach 3: Greedy Coloring (Heuristic, Approximate)
// -------------------------------------------------
/*
💡 Idea:
   - Assign the smallest available color to each vertex in order.
   - This is a heuristic and may fail 
     (does not guarantee optimal chromatic number).
   - But useful if M >= greedy upper bound.

🧩 Algorithm:
   1. Initialize all vertices with no color.
   2. For each vertex:
       - Mark all colors used by adjacent vertices.
       - Assign first available color.
   3. If any vertex requires a color > M → return false.
   4. Else return true.

⏱ Time Complexity: O(V^2) (scanning adjacency)
📦 Space Complexity: O(V)
*/

bool graphColoringGreedy(int v, vector<vector<int>>& edges, int m) {
    vector<int> colorMap(v, -1);
    colorMap[0] = 1;   // assign color 1 to first vertex

    for (int u = 1; u < v; u++) {
        vector<bool> used(m+1,false); 

        for (auto &e : edges) {
            if (e == u && colorMap[e[1]] != -1) used[colorMap[e[1]]] = true;
            if (e[1] == u && colorMap[e] != -1) used[colorMap[e]] = true;
        }

        int color;
        for (color = 1; color <= m; color++) {
            if (!used[color]) break;
        }

        if (color > m) return false; // needs more than m colors
        colorMap[u] = color;
    }
    return true;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    int v = 4;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {1, 3}};
    int m = 3;

    cout << "Graph Coloring Problem\n";
    cout << "Vertices: " << v << ", Colors Available: " << m << "\n";

    cout << "\nApproach 1 (Brute Force): ";
    cout << (graphColoringBrute(v, edges, m) ? "Possible" : "Not Possible") << "\n";

    cout << "Approach 2 (Backtracking - Optimized): ";
    cout << (graphColoringBacktrack(v, edges, m) ? "Possible" : "Not Possible") << "\n";

    cout << "Approach 3 (Greedy Approximate): ";
    cout << (graphColoringGreedy(v, edges, m) ? "Possible" : "Not Possible") << "\n";

    // -------------------------------------------------
    // ✅ Approach Overview
    // -------------------------------------------------
    /*
    Approach 1 (Brute Force):  TC = O(M^V * V), SC = O(V)
    Approach 2 (Backtracking): TC = O(M^V) with pruning, SC = O(V)
    Approach 3 (Greedy):       TC = O(V^2),   SC = O(V), heuristic only
    */

    return 0;
}
