#include <bits/stdc++.h>
using namespace std;

/*
====================================================
Problem Title: Course Schedule (Detect Cycle in Prerequisite Graph)
LeetCode Link: https://leetcode.com/problems/course-schedule/

Problem Statement:
------------------
There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1. 
Some courses may have prerequisites given as a list of pairs [a, b], meaning to take course a you must first take course b.
Return true if you can finish all courses (i.e., it is possible to finish all courses), otherwise return false.

Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: You can take course 0 then course 1.

Example 2:
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There is a cycle - you cannot complete the courses.

Constraints:
- 1 <= numCourses <= 2000
- 0 <= prerequisites.length <= 5000
- prerequisites[i].length == 2
====================================================
*/

/*
==========================================
Approach 1: Kahn's Algorithm (BFS Topological Sort)
------------------------------------------
💡 Idea:
Convert prerequisites to a graph (edges from prerequisite to course). 
Try a topological sort; if all courses can be ordered, there is no cycle.

🧩 Algorithm:
1. For each [a, b] in prerequisites, put edge b -> a, and increment in-degree of a.
2. Add all courses with in-degree 0 to a queue.
3. Pop queue, for each neighbor decrement in-degree and enqueue if it becomes 0.
4. If processed count equals numCourses, no cycle, return true; else, false.

⏱ Time Complexity: O(V + E)
📦 Space Complexity: O(V + E)
*/
bool canFinish_Kahn(int numCourses, vector<vector<int>>& prerequisites) {
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
    return (ans.size() == numCourses);
}

/*
==========================================
Approach 2: DFS Cycle Detection in Directed Graph
------------------------------------------
💡 Idea:
DFS each node. In the recursion stack (pathVisited), if we revisit a node, there's a cycle (unsatisfiable).

🧩 Algorithm:
1. Build adjacency list from prerequisites.
2. For each course, if unvisited, run DFS.
   - Mark node as visited and pathVisited.
   - If neighbor is on the current path, return false (cycle).
   - Else recursively DFS neighbor.
   - Remove node from pathVisited on backtrack.
3. If any node returns false (cycle), entire routine returns false.

⏱ Time Complexity: O(V + E)
📦 Space Complexity: O(V)
*/
bool dfs(vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& pathVisited, int v) {
    visited[v] = true;
    pathVisited[v] = true;
    for (int u : adj[v]) {
        if (visited[u] && pathVisited[u]) return true;
        if (!visited[u]) {
            if (dfs(adj, visited, pathVisited, u)) return true;
        }
    }
    pathVisited[v] = false;
    return false;
}

bool canFinish_DFS(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<bool> visited(numCourses, false);
    vector<bool> pathVisited(numCourses, false);
    for (auto& it : prerequisites) {
        adj[it[1]].push_back(it[0]);
    }
    for (int v = 0; v < numCourses; v++) {
        if (!visited[v]) {
            if (dfs(adj, visited, pathVisited, v)) return false;
        }
    }
    return true;
}

/* 
==================== MAIN FUNCTION ====================
Runs test cases for both approaches to the course schedule problem.
*/
int main() {
    vector<vector<int>> prereq1 = {{1, 0}};
    vector<vector<int>> prereq2 = {{1, 0}, {0, 1}};

    cout << std::boolalpha;
    cout << "Test Case 1 (Kahn): " << canFinish_Kahn(2, prereq1) << " (Expected: true)\n";
    cout << "Test Case 1 (DFS) : " << canFinish_DFS(2, prereq1) << " (Expected: true)\n";

    cout << "Test Case 2 (Kahn): " << canFinish_Kahn(2, prereq2) << " (Expected: false)\n";
    cout << "Test Case 2 (DFS) : " << canFinish_DFS(2, prereq2) << " (Expected: false)\n";

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Kahn's Algorithm: BFS/in-degree based topological sort. Returns true if all courses can be scheduled (acyclic).\n";
    cout << "2. DFS: Classic cycle detection in a directed graph via recursion stack. Returns false if a cycle is found.\n";
    cout << "Both methods are efficient (O(V+E)) and commonly used in coding interviews.\n";

    return 0;
}
