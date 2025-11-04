#include<bits/stdc++.h>
using namespace std;

/*
Problem: Pascal's Triangle (Rows, Elements, and Variants)

Problem Statement:
- Generate Pascal's Triangle up to numRows.
- Generate a specific row of Pascal's Triangle.
- Compute a specific binomial coefficient (element) C(n, k).

Background:
- Pascal’s Triangle entries are binomial coefficients.
- Each entry (except borders) is the sum of the two entries above it.
- Row i (0-indexed) has i+1 elements: C(i,0), C(i,1), ..., C(i,i).
- Iterative relation: C(n, k) = C(n, k-1) * (n - k + 1) / k.

Example:
Triangle for numRows=6:
  1
  1 1
  1 2 1
  1 3 3 1
  1 4 6 4 1
  1 5 10 10 5 1

Approach Overview:
- DP build (sum of two above): O(numRows^2) time, O(numRows^2) space.
- Row via iterative binomial formula: O(numRow) time/space with 64-bit arithmetic care.
- Element via iterative multiplicative formula: O(k) time, O(1) space.

Complexity:
- Build full triangle: O(R^2) time, O(R^2) space where R=numRows.
- Generate a row: O(R) time, O(R) space.
- Single element: O(k) time, O(1) space.
*/

/*
Approach 1: Build entire Pascal's Triangle using DP relation

Idea:
- ans[i][0] = ans[i][i] = 1
- ans[i][j] = ans[i-1][j-1] + ans[i-1][j] for 1 <= j < i

Algorithm:
1) Initialize ans with numRows rows.
2) For each row i:
   - Resize to i+1
   - Set borders to 1
   - Fill internal elements as sum of two from previous row
3) Return ans

Time Complexity: O(numRows^2)
Space Complexity: O(numRows^2)
*/
vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> ans(numRows);
    for (int i = 0; i < numRows; i++)
    {
        ans[i].resize(i + 1);
        ans[i][0] = 1;
        ans[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
        }
    }
    return ans;
}

/*
Approach 2: Build triangle using iterative binomial progression per row

Idea:
- For row i (0-indexed), compute elements using:
  element(j) = element(j-1) * (i - (j - 1)) / j
- Avoid factorials; use integer-safe progression.

Algorithm:
1) For each row i from 0..numRow-1:
   - Start element = 1 (C(i,0))
   - For j from 1..i:
       element = element * (i - j + 1) / j
       push to row
2) Collect rows

Time Complexity: O(numRow^2)
Space Complexity: O(numRow^2)
*/
vector<vector<int>> generate2(int numRow)
{
    vector<vector<int>> ansT(numRow);
    for (int i = 0; i < numRow; i++)
    {
        ansT[i].resize(i + 1);
        long long element = 1;
        ansT[i][0] = (int)element;
        for (int j = 1; j <= i; j++)
        {
            element = element * (i - j + 1) / j;
            ansT[i][j] = (int)element;
        }
    }
    return ansT;
}

/*
Approach 3: Compute single element C(n, k) efficiently

Idea:
- Use multiplicative formula to avoid factorial overflow:
  C(n, k) = product_{t=1..k} (n - k + t) / t
- Use k = min(k, n-k) for fewer iterations.

Algorithm:
1) Normalize k = min(k, n-k).
2) ans = 1
3) For t in 1..k:
     ans = ans * (n - k + t) / t
4) Return ans

Time Complexity: O(k)
Space Complexity: O(1)
Note:
- Inputs in provided code are 1-based-like; adjust carefully if needed.
*/
long long binom(int n, int k) {
    if (k < 0 || k > n) return 0;
    k = min(k, n - k);
    long long ans = 1;
    for (int t = 1; t <= k; t++) {
        ans = ans * (n - k + t) / t;
    }
    return ans;
}

// Original generateElement adapted to a standard C(n, k) calculator (0-indexed k)
int generateElement(int numRow, int numCol)
{
    // Interpret as C(numRow-1, numCol-1) if inputs are 1-based in calls,
    // or directly C(numRow, numCol) if using 0-based.
    // The original function logic was non-standard; we provide a robust version:
    // Here, assume numRow is n and numCol is k (0-based). Adjust as needed.
    return (int)binom(numRow, numCol);
}

/*
Approach 4: Generate a specific row (0-indexed) using iterative formula

Idea:
- element(0) = 1
- element(i) = element(i-1) * (row - i + 1) / i

Algorithm:
1) ans size = numRow
2) element = 1, ans[0] = 1
3) For i from 1..numRow-1:
     element = element * (numRow - i) / i
     ans[i] = (int)element
4) Return ans

Time Complexity: O(numRow)
Space Complexity: O(numRow)
*/
vector<int> generateRow(int numRow)
{
    vector<int> ans(numRow);
    long long element = 1;
    ans[0] = (int)element;
    for (int i = 1; i < numRow; i++)
    {
        element = (element * (numRow - i)) / i;
        ans[i] = (int)element;
    }
    return ans;
}

int main()
{
    // Example element queries:
    // Using standard 0-based C(n,k): C(9,4) = 126
    int ans = generateElement(9, 4);
    cout << ans << endl;

    // Specific row (size = 6), 0-indexed row length convention
    vector<int> ansRow = generateRow(6);
    for (int i = 0; i < (int)ansRow.size(); i++)
    {
        cout << ansRow[i] << " ";
    }
    cout << endl;

    // Full triangle via DP
    vector<vector<int>> ansTri = generate(6);
    for (int i = 0; i < (int)ansTri.size(); i++)
    {
        for (int j = 0; j < (int)ansTri[i].size(); j++)
        {
            cout << ansTri[i][j] << " ";
        }
        cout << endl;
    }

    // Full triangle via row-wise binomial progression
    vector<vector<int>> ansTri2 = generate2(6);
    for (int i = 0; i < (int)ansTri2.size(); i++)
    {
        for (int j = 0; j < (int)ansTri2[i].size(); j++)
        {
            cout << ansTri2[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
