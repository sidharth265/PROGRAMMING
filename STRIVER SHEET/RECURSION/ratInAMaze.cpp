#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Rat in a Maze Problem
 Problem Link: https://practice.geeksforgeeks.org/problems/rat-in-a-maze-problem/1

 Problem Statement:
 Given an n x n matrix representing a maze with blocked (0) and free (1) cells,
 find all possible paths for a rat to go from the top-left corner (0,0) to 
 the bottom-right corner (n-1,n-1). The rat can move Up(U), Down(D), Left(L), Right(R).
 The rat cannot visit the same cell twice on the same path.
 Return all paths sorted lexicographically. If no path exists, return an empty list.
-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Backtracking with DFS and Visited Marking
// -------------------------------------------------
/*
💡 Idea:
   - From each cell, visit neighboring cells if they are free and unvisited.
   - Mark current cell visited before recursion and unmark after to allow other paths.
   - Collect the path in a string using movement characters.
   - Stop and record path when destination is reached.

🧩 Algorithm:
   1. Use recursion starting at (0,0).
   2. At each cell, mark visited, try all moves in lex order: D, L, R, U.
   3. Append move char to path string.
   4. On reaching destination, add path to results.
   5. Backtrack by unmarking visited.

⏱ Time Complexity: O(4^(n^2)) worst case
📦 Space Complexity: O(n^2) recursion stack + path storage
*/

void dfs(vector<string>& result, string path, vector<vector<int>>& maze, int row, int col) {
    int n = maze.size();
    
    // Base case: reached destination
    if (row == n - 1 && col == n - 1 && maze[row][col] == 1) {
        result.push_back(path);
        return;
    }

    // Mark cell as visited
    maze[row][col] = 0;

    // Move Down (D)
    if (row + 1 < n && maze[row + 1][col] == 1)
        dfs(result, path + 'D', maze, row + 1, col);

    // Move Left (L)
    if (col - 1 >= 0 && maze[row][col - 1] == 1)
        dfs(result, path + 'L', maze, row, col - 1);

    // Move Right (R)
    if (col + 1 < n && maze[row][col + 1] == 1)
        dfs(result, path + 'R', maze, row, col + 1);

    // Move Up (U)
    if (row - 1 >= 0 && maze[row - 1][col] == 1)
        dfs(result, path + 'U', maze, row - 1, col);

    // Unmark visited for other paths
    maze[row][col] = 1;
}

vector<string> ratInMaze(vector<vector<int>>& maze) {
    vector<string> result;
    if (maze.empty() || maze[0][0] == 0)
        return result;
    dfs(result, "", maze, 0, 0);
    sort(result.begin(), result.end());  // Ensure lex order as required
    return result;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<vector<int>> maze = {
        {1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 0, 1},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 1, 1, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 0, 1, 1, 1, 1}
    };

    vector<string> paths = ratInMaze(maze);

    if (paths.empty()) {
        cout << "No path found." << endl;
    } else {
        cout << "All lexicographically sorted paths from start to destination:\n";
        for (const string& p : paths) {
            cout << p << "\n";
        }
    }

    return 0;
}
