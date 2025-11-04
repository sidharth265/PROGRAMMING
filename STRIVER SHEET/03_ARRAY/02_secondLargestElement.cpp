#include<bits/stdc++.h>
using namespace std;

/*
Problem: Second Largest Element in an Array

Problem Statement:
Given an integer array arr of size n, find the second largest distinct element. If it does not exist (e.g., all elements equal or array size < 2 with distinct values), return -1.

Example:
Input:
  arr = [12, 35, 1, 10, 34, 1]
Output:
  34
Explanation:
- The largest is 35, and the second largest distinct value is 34.

Approach:
- Single pass, track two best values:
  - Maintain largest and secondLargest initialized to the minimal sentinel.
  - For each value x:
    - If x > largest: secondLargest = largest; largest = x
    - Else if x != largest and x > secondLargest: secondLargest = x
- At the end, if secondLargest stays at sentinel, no valid second largest exists.

Algorithm:
1) Set largest = -inf, secondLargest = -inf
2) For each x in arr:
   - If x > largest: secondLargest = largest; largest = x
   - Else if x < largest and x > secondLargest: secondLargest = x
3) If secondLargest is -inf, return -1; else return secondLargest

Time Complexity: O(n)
Space Complexity: O(1)
*/
int findSecondLargest(int n, vector<int> &arr)
{
    int largest = INT_MIN;
    int secondLargest = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] > largest) {
            secondLargest = largest;
            largest = arr[i];
        } else if (arr[i] > secondLargest && arr[i] != largest) {
            secondLargest = arr[i];
        }
    }

    return (secondLargest == INT_MIN) ? -1 : secondLargest;
}

int main() {
    vector<int> arr = {12, 35, 1, 10, 34, 1};
    int n = arr.size();
    int result = findSecondLargest(n, arr);
    if (result == -1) {
        cout << "No second largest element found.\n";
    } else {
        cout << "The second largest element is: " << result << "\n";
    }
    return 0;
}
