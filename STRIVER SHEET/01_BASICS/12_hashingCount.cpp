#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
Problem Title: Frequency Count of Elements in Array

Problem Statement:
Given an array of integers where the elements are in the range 1 to n (size of array),
return a frequency count of all elements from 1 to n.

For each number from 1 to n, count how many times it appears in the array.

-----------------------------------------------------------
Example:
Input: arr = {1, 2, 2, 3, 3, 5, 3}
Output: 1 2 3 0 1
Explanation:
- Number 1 appears once.
- Number 2 appears twice.
- Number 3 appears thrice.
- Number 4 appears zero times.
- Number 5 appears once.

===========================================================
*/

/*-----------------------------------------------------------
Approach: Use a hash array indexed by element values
💡 Idea:
- Since elements range from 1 to n, create a frequency vector of size n.
- Increment frequency at index (element - 1) for each element.
- Return the frequency vector.

🧩 Algorithm:
1. Initialize a vector<int> frequency with size n, all zeros.
2. Iterate over the array:
   - For each element e, increment frequency[e-1].
3. Return frequency vector.

⏱ Time Complexity: O(n)  
📦 Space Complexity: O(n)
-----------------------------------------------------------*/
vector<int> frequencyCount(vector<int> &arr) {
    int n = arr.size();
    vector<int> frequency(n, 0);
    for (int e : arr) {
        frequency[e - 1]++;
    }
    return frequency;
}

/*-----------------------------------------------------------
Main function: Tests frequency count on sample input
-----------------------------------------------------------*/
int main() {
    vector<int> arr = {1, 2, 2, 3, 3, 5, 3};
    vector<int> freq = frequencyCount(arr);

    cout << "Frequency of elements from 1 to " << freq.size() << ":" << endl;
    for (int count : freq) {
        cout << count << " ";
    }
    cout << endl;

    /* ✅ Approach Overview
    -----------------------------------------------------------
    Approach: Hash array indexed by element value - 1
       Time Complexity: O(n)
       Space Complexity: O(n)
    -----------------------------------------------------------
    */
    return 0;
}
