#include <bits/stdc++.h>
using namespace std;

/*
Problem: Leaders in an Array

Problem Statement:
Given an array of integers, find all the leaders in the array. 
An element is called a leader if it is greater than or equal to all the elements to its right.
The rightmost element is always a leader.

Example:
Input:
  arr = [16, 17, 4, 3, 5, 2]
Output:
  [17, 5, 2]
Explanation:
- 17 >= {4, 3, 5, 2}, 5 >= {2}, and 2 is the rightmost element (always a leader).
*/

/*
Approach 1: Brute Force

Idea:
- For each element, verify it is >= every element to its right.

Algorithm:
- For i in [0..n-1]:
    * isLeader = true
    * For j in [i+1..n-1]: if arr[j] > arr[i], set isLeader=false and break
    * If isLeader, push arr[i] to result

Complexities:
- Time: O(n^2)
- Space: O(1) auxiliary
*/
vector<int> leadersBrute(const vector<int>& arr) {
    int n = arr.size();
    vector<int> res;
    for (int i = 0; i < n; ++i) {
        bool isLeader = true;
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] < arr[j]) {
                isLeader = false;
                break;
            }
        }
        if (isLeader) res.push_back(arr[i]);
    }
    return res;
}

/*
Approach 2A: Optimal Right-to-Left (Collect then Reverse)

Idea:
- Track maxRight; if current >= maxRight, it's a leader.
- Collect in reverse discovery order and reverse at the end.

Algorithm:
1) maxRight = arr[n-1]; push it
2) For i from n-2 down to 0:
    * if arr[i] >= maxRight:
        - maxRight = arr[i]
        - push arr[i]
3) reverse the collected leaders

Complexities:
- Time: O(n)
- Space: O(k) (worst-case O(n))
*/
vector<int> leadersReverse(vector<int>& arr) {
    int n = arr.size();
    vector<int> l;
    l.reserve(n);
    int maxRight = arr[n - 1];
    l.push_back(maxRight);
    for (int i = n - 2; i >= 0; --i) {
        if (arr[i] >= maxRight) {
            maxRight = arr[i];
            l.push_back(arr[i]);
        }
    }
    reverse(l.begin(), l.end());
    return l;
}

/*
Approach 2B: Optimal Right-to-Left (No Reverse, Fill from End)

Idea:
- Same as 2A, but place leaders from the end of a buffer to keep final order without reversing.

Algorithm:
1) Allocate out[n], write = n-1
2) maxRight = arr[n-1], out[write--] = maxRight
3) For i from n-2 down to 0:
    * if arr[i] >= maxRight:
        - maxRight = arr[i]
        - out[write--] = arr[i]
4) Return slice out[write+1..n-1]

Complexities:
- Time: O(n)
- Space: O(k) extracted from buffer (worst-case O(n))
*/
vector<int> leadersNoReverse(const vector<int>& arr) {
    int n = arr.size();
    vector<int> out(n);
    int write = n - 1;
    int maxRight = arr[n - 1];
    out[write--] = maxRight;
    for (int i = n - 2; i >= 0; --i) {
        if (arr[i] >= maxRight) {
            maxRight = arr[i];
            out[write--] = arr[i];
        }
    }
    // Leaders are from out[write+1 ... n-1] in correct left-to-right order
    return vector<int>(out.begin() + write + 1, out.end());
}

int main() {
    vector<int> arr = {16, 17, 4, 3, 5, 2};

    // Brute force
    vector<int> resBrute = leadersBrute(arr);
    cout << "Leaders (Brute Force):     ";
    for (int x : resBrute) cout << x << " ";
    cout << "\n";

    // Optimal with reverse
    vector<int> arrCopy = arr; // leadersReverse doesn't require modification of arr; copy shown for pattern symmetry
    vector<int> resRev = leadersReverse(arrCopy);
    cout << "Leaders (with reverse):    ";
    for (int x : resRev) cout << x << " ";
    cout << "\n";

    // Optimal without reverse
    vector<int> resNoRev = leadersNoReverse(arr);
    cout << "Leaders (no reverse):      ";
    for (int x : resNoRev) cout << x << " ";
    cout << "\n";

    return 0;
}
