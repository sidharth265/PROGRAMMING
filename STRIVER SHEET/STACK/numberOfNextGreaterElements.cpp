#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Count of Greater Elements to the Right
 Problem Link: (Custom / Similar to Next Greater Element)
====================================================

📝 Problem Statement:
Given an array `arr`, for each index i, find the number of indices j such that j > i and arr[j] > arr[i].
Return an array `ans` where ans[i] is count of such indices.

Given a set of query indices, return counts for those indices.

📌 Input:
- Integer array `arr`
- Vector of query indices `query`

📌 Output:
- Vector ans where ans[i] = count of arr[j] > arr[query[i]] for j > query[i]

----------------------------------------------------
🔹 Example:
Input:
arr = [3, 2, 5, 4, 6]
query = [0, 1, 2, 3]
Output: [2, 2, 0, 0]

Explanation:
- For arr[0]=3, next greater elements are arr[2]=5, arr[4]=6 → 2
- For arr[1]=2, next greater elements are arr[2]=5, arr[4]=6 → 2
- For arr[2]=5, next greater elements none after index 2 greater than 5 → 0
- For arr[3]=4, next greater elements none after index 3 greater than 4 → 0

====================================================
*/

//////////////////////////////////////////////////////
// Approach 1: Brute Force
//////////////////////////////////////////////////////
/*
💡 Idea:
- For each query index, iterate right over arr, count elements greater.

🧩 Algorithm:
1. For each query index j, count elements arr[k] > arr[j] for k > j.
2. Store counts in ans.

⏱ Time Complexity: O(n*q) where q = query.size()  
📦 Space Complexity: O(q)
*/

vector<int> countGreater(vector<int>& arr, vector<int>& query) {
    vector<int> ans(query.size(), 0);
    for (int i = 0; i < (int)query.size(); i++) {
        int j = query[i];
        for (int k = j + 1; k < (int)arr.size(); k++) {
            if (arr[k] > arr[j]) ans[i]++;
        }
    }
    return ans;
}

//////////////////////////////////////////////////////
// Approach 2: Optimized using Next Greater Element with Stack
//////////////////////////////////////////////////////
/*
💡 Idea:
- Compute next greater element index for each position.
- Number of elements greater after position j = nextGreater[j] - j - 1 or 0 if none.

🧩 Algorithm:
1. Use stack to find next greater indices.
2. For each query index j, answer = nextGreater[j] - j -1 (number of elements between j and nextGreater[j]).
3. Return answers.

⏱ Time Complexity: O(n + q)  
📦 Space Complexity: O(n + q)
*/

vector<int> countGreater2(vector<int>& arr, vector<int>& query) {
    int n = (int)arr.size();
    vector<int> ans(query.size(), 0);
    vector<int> nextGreater(n, n); // initialize with n meaning no greater element

    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            nextGreater[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    for (int i = 0; i < (int)query.size(); i++) {
        int j = query[i];
        // Number of elements between j and nextGreater[j]
        ans[i] = max(0, nextGreater[j] - j - 1);
    }
    return ans;
}

//////////////////////////////////////////////////////
// Main function to test the code
//////////////////////////////////////////////////////
int main() {
    vector<int> arr = {3, 2, 5, 4, 6};
    vector<int> query = {0, 1, 2, 3};
    vector<int> result = countGreater2(arr, query);

    cout << "Number of next greater elements for each query index: ";
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////
// ✅ Approach Overview
//////////////////////////////////////////////////////
// The optimized approach finds next greater elements with a stack in O(n).
// Then number of elements strictly between current index and next greater index gives count of greater elements.
// This yields O(n + q) efficiency compared to brute force.
