#include<bits/stdc++.h>
using namespace std;

/*
Problem: Union of Two Sorted Arrays (Unique Elements)

Problem Statement:
Given two sorted integer arrays a and b (each may contain duplicates), compute their union as a sorted array that contains each distinct element exactly once.

Example:
Input:
  a = [1, 2, 4, 5, 6]
  b = [2, 3, 5]
Output:
  [1, 2, 3, 4, 5, 6]
Explanation:
- Merge the arrays in sorted order while skipping duplicates so that each value appears once.

Approach:
- Use a two-pointer technique to traverse both sorted arrays simultaneously.
- At each step, compare a[i1] and b[i2]:
  - Push the smaller (or equal) element to the result only if it’s different from the last pushed element.
  - Advance the pointer(s) from which the element was taken.
- After one array is exhausted, continue with the remaining elements of the other array, still skipping duplicates by checking the last pushed element.

Algorithm:
1) Initialize i1 = 0, i2 = 0 and an empty vector ans.
2) While i1 < n1 and i2 < n2:
   - If a[i1] <= b[i2]:
       * If ans is empty or ans.back() != a[i1], push a[i1] to ans.
       * Increment i1.
   - Else:
       * If ans is empty or ans.back() != b[i2], push b[i2] to ans.
       * Increment i2.
3) While i2 < n2:
   - If ans is empty or ans.back() != b[i2], push b[i2].
   - Increment i2.
4) While i1 < n1:
   - If ans is empty or ans.back() != a[i1], push a[i1].
   - Increment i1.
5) Return ans.

Time Complexity:
- O(n1 + n2), where n1 = a.size() and n2 = b.size(), since each array is scanned at most once.

Space Complexity:
- O(n1 + n2) in the worst case, when all elements are unique and included in the output.
- Additional auxiliary space beyond output is O(1).

*/

vector<int> findUnion(vector<int> &a, vector<int> &b) {
    int n1 = a.size();
    int n2 = b.size();
    int i1=0;
    int i2=0;
    vector<int> ans;
    while (i1 < n1 && i2 < n2) {
        if (a[i1] <= b[i2]) {
            if (ans.size()==0 || ans.back() != a[i1]) {
                ans.push_back(a[i1]);
            }
            i1++;
        }
        else{
            if (ans.size()==0 || ans.back() != b[i2]) {
                ans.push_back(b[i2]);
            }
            i2++;
        }
    }
    while(i2<n2) {
        if (ans.size()==0 || ans.back() != b[i2]) {
            ans.push_back(b[i2]);
        }
        i2++;  
    }
    while (i1<n1) {
        if (ans.size()==0 || ans.back() != a[i1]) {
            ans.push_back(a[i1]);
        }
        i1++;
    }
    return ans;
}


int main() {
    vector<int> a = {1, 2, 4, 5, 6};
    vector<int> b = {2, 3, 5};
    vector<int> result = findUnion(a, b);
    for (int i : result) {
        cout << i << " ";
    }
    return 0;
}
