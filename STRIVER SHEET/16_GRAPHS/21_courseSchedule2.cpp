#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Course Schedule II (Find Course Order)
LeetCode Link: https://leetcode.com/problems/course-schedule-ii/

Problem Statement:
------------------
There are numCourses courses, labeled 0 to numCourses-1. Some courses have prerequisites [a, b], 
meaning to take a you must first take b. Return a valid order to take all courses, or [] if impossible.

Example 1:
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3] or [0,1,2,3]

Example 2:
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: []

Constraints:
- 1 <= numCourses <= 2000
- 0 <= prerequisites.length <= 5000
- prerequisites[i].length == 2
====================================================
*/

/*
==========================================
Approach 1: Kahn's Algorithm (Topological Sort BFS)
------------------------------------------
💡 Idea:
Calculate in-degree of all nodes. Start from nodes with in-degree 0, iteratively remove and update in-degree. 
If all nodes are scheduled, return order; else, return empty.

🧩 Algorithm:
1. For each [a, b] in prerequisites, build edge b -> a, increment in-degree of a.
2. Enqueue all nodes with in-degree 0.
3. Pop queue, add to result, decrement neighbors in-degree, enqueue new 0 in-degree.
4. If result size == numCourses, return it; otherwise return [] (cycle exists).

⏱ Time Complexity: O(V + E)
📦 Space Complexity: O(V + E)
*/
vector<int> findOrder_Kahn(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> inDeg(numCourses, 0);
    for (auto& it : prerequisites) {
        adj[it[1]].push_back(it[0]);
        inDeg[it[0]]++;
    }
    queue<int> q;
    vector<int> ans;
    for (int v = 0; v < numCourses; v++) {
        if (inDeg[v] == 0) q.push(v);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (--inDeg[u] == 0) q.push(u);
        }
        ans.push_back(v);
    }
    return (ans.size() == numCourses) ? ans : vector<int>();
}

/*
==========================================
Approach 2: DFS with Cycle Detection & Topological Ordering
------------------------------------------
💡 Idea:
Run DFS, mark nodes in recursion stack (pathVisited) to detect cycles. 
Push node to stack after visiting all neighbors. If cycle detected, return empty.

🧩 Algorithm:
1. For each [a,b] in prerequisites, build edge b -> a.
2. Use visited and pathVisited arrays for DFS.
3. On each unvisited node:
    - If revisit on same path, cycle exists, so return empty.
    - After exploring all neighbors, push node to stack.
4. After all DFS, reverse stack for valid order.

⏱ Time Complexity: O(V + E)
📦 Space Complexity: O(V + E)
*/
bool dfs(vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& pathVisited, stack<int>& st, int v) {
    visited[v] = true;
    pathVisited[v] = true;
    for (int u : adj[v]) {
        if (visited[u] && pathVisited[u]) return true;
        if (!visited[u]) {
            if (dfs(adj, visited, pathVisited, st, u)) return true;
        }
    }
    pathVisited[v] = false;
    st.push(v);
    return false;
}

vector<int> findOrder_DFS(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<bool> visited(numCourses);
    vector<bool> pathVisited(numCourses);
    stack<int> st;

    for (auto& it : prerequisites) {
        adj[it[1]].push_back(it[0]);
    }
    for (int v = 0; v < numCourses; v++) {
        if (!visited[v]) {
            if (dfs(adj, visited, pathVisited, st, v)) return {};
        }
    }
    vector<int> ans;
    while (!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}

/*
============= MAIN FUNCTION ==============
Tests both topological sort approaches for Course Schedule II
*/
int main() {
    vector<vector<int>> prereq1 = {{1,0},{2,0},{3,1},{3,2}};
    vector<vector<int>> prereq2 = {{1,0},{0,1}};

    cout << "Test Case 1 (Kahn): ";
    vector<int> order1 = findOrder_Kahn(4, prereq1);
    for (int v : order1) cout << v << " ";
    cout << "\n";

    cout << "Test Case 1 (DFS): ";
    vector<int> order2 = findOrder_DFS(4, prereq1);
    for (int v : order2) cout << v << " ";
    cout << "\n";

    cout << "Test Case 2 (Kahn): ";
    vector<int> order3 = findOrder_Kahn(2, prereq2);
    for (int v : order3) cout << v << " ";
    cout << "\n";

    cout << "Test Case 2 (DFS): ";
    vector<int> order4 = findOrder_DFS(2, prereq2);
    for (int v : order4) cout << v << " ";
    cout << "\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Kahn's Algorithm (BFS): Removes courses layer by layer by in-degree 0; returns order if all scheduled.\n";
    cout << "2. DFS + Stack: Uses DFS for ordering, cycle detection by pathVisited, stack for order reversal.\n";
    cout << "Both are O(V+E), reliable, and accepted in interviews and competitive programming.\n";

    return 0;
}
