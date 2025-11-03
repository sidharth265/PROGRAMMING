#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Subset Sum (All Possible Subset Sums)
 Problem Link: (Common Backtracking Problem)
====================================================

📝 Problem Statement:
Given an integer array nums, return all possible sums of subsets (including empty subset 0).
The output should be sorted in non-decreasing order.

📌 Input:
- An array of integers `nums`

📌 Output:
- A sorted vector of all subset sums

----------------------------------------------------
🔹 Example:
Input: nums = [3, 1, 2]  
Output: [0, 1, 2, 3, 3, 4, 5, 6]  

Explanation:
Subsets and their sums:  
[] = 0  
[1] = 1  
[2] = 2  
[3] = 3  
[1,2] = 3  
[1,3] = 4  
[2,3] = 5  
[1,2,3] = 6  

Sorted sums as output.

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Backtracking to generate all subset sums
//////////////////////////////////////////////////////
/*
💡 Idea:
- Use recursion to either include or exclude each element.
- Keep track of current sum.
- Store sum when we reach the end.

🧩 Algorithm:
1. Define generate(result, arr, sum, index).
2. If index == arr.size(), push sum to result.
3. Else recurse excluding arr[index].
4. Then recurse including arr[index].
5. After all calls, sort the result.

⏱ Time Complexity: O(2^n) – exploring all subsets  
📦 Space Complexity: O(n) – recursion stack depth
*/

void generate(vector<int> &result, vector<int> &arr, int sum, int i) {
    if (i == arr.size()) {
        result.push_back(sum);
        return;
    }
    // Exclude current element
    generate(result, arr, sum, i + 1);
    // Include current element
    generate(result, arr, sum + arr[i], i + 1);
}

vector<int> subsetSum(vector<int> &num) {
    vector<int> result;
    generate(result, num, 0, 0);
    sort(result.begin(), result.end());
    return result;
}

//////////////////////////////////////////////////////
// Main function with example
//////////////////////////////////////////////////////
int main() {
    vector<int> num = {3, 1, 2};
    vector<int> result = subsetSum(num);

    cout << "Subset sums in non-decreasing order:\n";
    for (int sum : result) {
        cout << sum << " ";
    }
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// Single approach: Backtracking to enumerate all subsets and compute sums.
// Time complexity exponential O(2^n), space complexity O(n) for recursion stack.
