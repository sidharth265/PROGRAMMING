#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Cheapest Flights Within K Stops
Problem Link: https://leetcode.com/problems/cheapest-flights-within-k-stops/

Problem Statement:
There are n cities and m flights, where each flight[i] = [from, to, price]. You are given src, dst, and integer k. 
Find the cheapest price from src to dst with at most k stops (i.e., up to k+1 total flights).
If there is no such route, return -1.

Examples:
Input:
n = 4, flights = [[0,1,100],[1,2,100],[2,3,100],[0,2,500]], src = 0, dst = 3, k = 1
Output: 700
Explanation:
0 -> 1 -> 2 -> 3 is not valid for k=1, but 0 -> 2 is valid but too expensive. Answer is -1.

Input:
n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation:
0 -> 1 -> 2 is within 1 stop, total cost 200.
*/


// Approach 1: Brute Force DFS (All Paths up to k Stops)
// 💡 Idea:
// Use DFS to try all possible paths from src to dst with at most k stops, collecting minimum cost seen for valid paths.
//
// 🧩 Algorithm:
// 1. Start DFS from src with current stops and current total cost.
// 2. If current node is dst, update global minimum.
// 3. If stops exceed k, return.
// 4. For each outgoing edge, recurse with incremented stop count and accumulated cost.
//
// ⏱ Time Complexity: O((n-1)^k), exponential for large k
// 📦 Space Complexity: O(n) recursion stack

int minDFSCost;
void dfsBrute(int v, int dst, int stops, int k, int cost, vector<vector<pair<int,int>>>& adj, vector<bool>& visited) {
    if (stops > k+1) return;
    if (v == dst) {
        minDFSCost = min(minDFSCost, cost);
        return;
    }
    visited[v] = true;
    for (auto& it : adj[v]) {
        int u = it.first, w = it.second;
        if (!visited[u]) {
            dfsBrute(u, dst, stops+1, k, cost+w, adj, visited);
        }
    }
    visited[v] = false;
}

int findCheapestPriceDFS(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int,int>>> adj(n);
    for (auto& it: flights)
        adj[it[0]].push_back({it[1], it[2]});
    minDFSCost = INT_MAX;
    vector<bool> visited(n, false);
    dfsBrute(src, dst, 0, k, 0, adj, visited);
    return minDFSCost == INT_MAX ? -1 : minDFSCost;
}


// Approach 2: Modified Bellman-Ford (Optimal for This Problem)
// 💡 Idea:
// Use Bellman-Ford up to k+1 rounds, relaxing all edges in each round. 
// This ensures shortest cost up to paths of length at most k+1 are found.
//
// 🧩 Algorithm:
// 1. Initialize cost array and set src to 0.
// 2. For k+1 rounds, make a temp copy of costs. For each edge, try to relax in temp.
// 3. At end of each round, assign temp to cost.
// 4. Return cost[dst] if reachable.
//
// ⏱ Time Complexity: O(nk + m*k)
// 📦 Space Complexity: O(n)

int findCheapestPriceBellmanFord(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> cost(n, INT_MAX);
    cost[src] = 0;

    for (int steps = 0; steps <= k; steps++) {
        vector<int> temp = cost;
        for (auto& it : flights) {
            int u = it[0], v = it[1], w = it[2];
            if (cost[u] != INT_MAX && temp[v] > cost[u] + w)
                temp[v] = cost[u] + w;
        }
        cost = temp;
    }
    return cost[dst] == INT_MAX ? -1 : cost[dst];
}


// Approach 3: BFS/0-1 BFS/Queue with Stops (Optimal for Interview & Leetcode)
// 💡 Idea:
// Use BFS queue storing (stops, city, cost_so_far), and visit/relax only if a cheaper cost is found for a city with the given or fewer stops.
//
// 🧩 Algorithm:
// 1. Build adj list, cost array.
// 2. Start BFS from (0 stops, src, cost=0).
// 3. For each node, if stops exceeds k+1 return/continue.
// 4. On visiting, for each neighbor, relax cost and enqueue with stops+1.
// 5. At end, if no path to dst found, return -1.
//
// ⏱ Time Complexity: O(n + m*k)
// 📦 Space Complexity: O(n)

int findCheapestPriceBFS(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int, int>>> adj(n);
    for(auto& it : flights) {
        adj[it[0]].push_back({it[1], it[2]});
    }

    vector<int> cost(n, INT_MAX);
    queue<vector<int>> q;
    q.push({0, src, 0}); // steps (stops), node, acc_cost
    cost[src] = 0;

    while(!q.empty()) {
        int s = q.front()[0], v = q.front()[1], c = q.front()[2];
        q.pop();
        if(s == k+1) continue;
        for(auto& it : adj[v]) {
            int u = it.first;
            int w = it.second;
            if(cost[u] > c+w) {
                cost[u] = c+w;
                q.push({s+1, u, c+w});
            }
        }
    }
    if(cost[dst] == INT_MAX) return -1;
    return cost[dst];
}


int main() {
    int n1 = 3;
    vector<vector<int>> flights1 = {{0,1,100},{1,2,100},{0,2,500}};
    int src1 = 0, dst1 = 2, k1 = 1;

    int n2 = 4;
    vector<vector<int>> flights2 = {{0,1,100},{1,2,100},{2,3,100},{0,2,500}};
    int src2 = 0, dst2 = 3, k2 = 1;

    // Brute Force DFS (only for small n & k!)
    cout << "DFS: " << findCheapestPriceDFS(n1, flights1, src1, dst1, k1) << "\n";
    cout << "DFS: " << findCheapestPriceDFS(n2, flights2, src2, dst2, k2) << "\n";

    // Bellman-Ford Approach
    cout << "Bellman-Ford: " << findCheapestPriceBellmanFord(n1, flights1, src1, dst1, k1) << "\n";
    cout << "Bellman-Ford: " << findCheapestPriceBellmanFord(n2, flights2, src2, dst2, k2) << "\n";

    // BFS/Queue Approach
    cout << "BFS: " << findCheapestPriceBFS(n1, flights1, src1, dst1, k1) << "\n";
    cout << "BFS: " << findCheapestPriceBFS(n2, flights2, src2, dst2, k2) << "\n";

    return 0;
}

/*
✅ Approach Overview:
| Approach         | Time Complexity       | Space Complexity  | Notes                                               |
|------------------|----------------------|-------------------|-----------------------------------------------------|
| Brute Force DFS  | O((n-1)^k)           | O(n)              | Extremely slow except for very small k              |
| Bellman-Ford     | O(nk + m*k)          | O(n)              | Clean, standard, reliable for this k-stop problem   |
| BFS Queue        | O(n + m*k)           | O(n)              | Simple to code, optimal for this problem            |

Bellman-Ford and BFS/Queue are both efficient for interview-sized inputs, but BFS/Queue is often easier to write under time pressure.
*/
