#include<bits/stdc++.h>
using namespace std;

/*
Problem: Missing Number in Range [0..n]

Problem Statement:
Given an array nums of length n containing distinct numbers in the range [0, n], return the one number in the range that is missing from the array.

Example:
Input:
  nums = [0, 1, 2, 3, 5]
Output:
  4
Explanation:
- Numbers should be 0..5; 4 is missing.

Approach Overview:
- Sum Formula: Expected sum n*(n+1)/2 minus actual sum gives the missing number.
- XOR Trick: XOR all numbers from 0..n and XOR all elements of nums; their XOR yields the missing value.

Complexity Overview:
- Both approaches run in O(n) time and O(1) space.
*/

/*
Approach 1: Arithmetic Sum Formula

Idea:
- Expected sum of 0..n is n*(n+1)/2.
- Subtract the actual sum of elements to get the missing number.

Algorithm:
1) n = nums.size()
2) expected = n*(n+1)/2
3) actual = sum over nums
4) return expected - actual

Time Complexity: O(n)
Space Complexity: O(1)
*/
int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int act_sum = n*(n+1)/2;
    int sum = 0;
    for (int i=0; i<n; i++) {
        sum += nums[i];
    }
    return act_sum - sum;
}

/*
Approach 2: XOR Trick

Idea:
- XOR has the property a^a=0 and a^0=a.
- XOR all values in [0..n] and XOR all nums; pairs cancel, leaving the missing number.

Algorithm:
1) n = nums.size()
2) x1 = XOR of 1..n (or 0..n; align with loop choice)
3) x2 = XOR of all nums[i]
4) return x1 ^ x2

Time Complexity: O(n)
Space Complexity: O(1)
*/
int missingNumber2(vector<int>& nums) {
    int n = nums.size();
    int xor1 = 0;
    int xor2 = 0;
    for(int i=0; i<n; i++){
        xor1 ^= i+1;     // XOR from 1 to n
        xor2 ^= nums[i]; // XOR of array elements
    }
    return xor1 ^ xor2;  // missing = (1^2^...^n) ^ (nums[0]^...^nums[n-1])
}

int main() {
    vector<int> nums = {0, 1, 2, 3, 5}; // Example input array
    cout << "The missing number is: " << missingNumber(nums) << endl;
    return 0;
}
