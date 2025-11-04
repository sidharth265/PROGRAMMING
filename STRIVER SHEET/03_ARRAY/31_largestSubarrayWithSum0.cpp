#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;


// Function to find the length of the largest subarray with sum 0
// Brute force approach
// Time complexity: O(n^2)
// Space complexity: O(1)
// This approach uses two nested loops to check all possible subarrays and their sums.
// If the sum of a subarray is 0, it updates the maximum length found so far.
int maxLen(vector<int>& arr) {
    int n = arr.size();
    int ans = 0;
    for(int i=0; i<n; i++) {
        int sum = 0;
        for(int j=i; j<n; j++) {
            sum += arr[j];
            if (sum == 0) {
                ans = max(ans, j-i+1);
            }
        }
    }
    return ans;
}


// Optimized approach using HashMap
// Time complexity: O(n)
// Space complexity: O(n)
// This approach uses a HashMap to store the cumulative sum and its first occurrence index.
// If the same cumulative sum occurs again, it means the subarray between those two indices has a sum of 0.
// The length of that subarray is calculated and the maximum length found so far is updated.
int maxLen2(vector<int>& arr) {
    int n = arr.size();
    int ans = 0;
    int sum = 0;
    unordered_map<int, int> m;
    for (int i=0; i<n; i++) {
        sum += arr[i];
        if (sum == 0) {
            ans = i+1;
        }
        else if (m.find(sum) != m.end()) {
            ans = max(ans, i-m[sum]);
        } 
        else {
            m[sum] = i;
        }
    }
    return ans;
}


int main() {
    vector<int> arr = {1, -1, 2, -2, 3, -3};
    cout << "Length of largest subarray with sum 0 (Brute force): " << maxLen(arr) << endl;
    cout << "Length of largest subarray with sum 0 (Optimized): " << maxLen2(arr) << endl;
    return 0;
}