#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Maximum Product Subarray

Problem Statement:
Given an integer array nums, find the contiguous non-empty subarray within the array that has the largest product, and return that product.
The array may contain positive numbers, negative numbers, and zeros.

Example:
Input:  nums = [2,3,-2,4]
Output: 6
Explanation: The subarray [2,3] has the largest product 6.

Approach Overview:
- Approach 1 (Brute Force): Try every subarray, compute running product, keep the maximum.
- Approach 2 (Prefix & Suffix Scan): Scan from left and right maintaining running products (reset to 1 on zero) to capture segments separated by zeros and sign changes.
- Approach 3 (Optimized, Kadane-style for Products): Track both max and min product ending at current index because a negative flips roles; swap when encountering a negative.
*/

/*
Approach 1: Brute Force
Approach Idea:
- Enumerate all subarrays by fixing start i and extending end j, maintaining the running product on the fly.
- Update the maximum after each multiplication.

Algorithm:
1) maxProduct = nums[0]
2) For i in [0..n-1]:
     prod = 1
     For j in [i..n-1]:
        prod *= nums[j]
        maxProduct = max(maxProduct, prod)
3) Return maxProduct

Time Complexity: O(n^2)
Space Complexity: O(1)
*/
long long maxProductSubarray(vector<int> &arr) {
    int n = arr.size();
    long long maxProduct = arr[0];
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            product *= arr[j];
            maxProduct = max(maxProduct, product);
        }
    }
    return maxProduct;
}

/*
Approach 2: Prefix and Suffix Product
Approach Idea:
- Zeros split the array into independent segments; within a segment, sign of product depends on count of negatives.
- Scan from left accumulating prefix product (reset to 1 on zero) and from right accumulating suffix product.
- The maximum over all scanned prefix/suffix values covers best subarray within segments.

Algorithm:
1) ans = -inf, pre = 1, suff = 1
2) For i in [0..n-1]:
     if pre == 0: pre = 1
     if suff == 0: suff = 1
     pre *= nums[i]
     suff *= nums[n-1-i]
     ans = max(ans, max((long long)pre, (long long)suff))
3) Return ans

Time Complexity: O(n)
Space Complexity: O(1)
*/
long long maxProduct(vector<int>& nums) {
    int n = nums.size();
    long long ans = LLONG_MIN;
    long long pre = 1, suff = 1;
    for (int i = 0; i < n; i++) {
        pre = (pre == 0 ? 1 : pre) * nums[i];
        suff = (suff == 0 ? 1 : suff) * nums[n - 1 - i];
        ans = max(ans, max(pre, suff));
    }
    return ans;
}

/*
Approach 3: Optimized (Kadane-style for product)
Approach Idea:
- Maintain two values at each index: maxProduct (best positive product ending here) and minProduct (worst/most negative ending here).
- When encountering a negative number, max and min swap roles; update both with current number or extending the previous product.
- Reset behavior emerges naturally: if multiplying by current makes it worse than current alone, restart at current.

Algorithm:
1) maxProd = nums[0], minProd = nums[0], result = nums[0]
2) For i in [1..n-1]:
     if nums[i] < 0: swap(maxProd, minProd)
     maxProd = max((long long)nums[i], maxProd * nums[i])
     minProd = min((long long)nums[i], minProd * nums[i])
     result = max(result, maxProd)
3) Return result

Time Complexity: O(n)
Space Complexity: O(1)
*/
long long maxProductSubarrayOptimized(vector<int>& nums) {
    int n = nums.size();
    long long maxProd = nums[0];
    long long minProd = nums[0];
    long long result = nums[0];

    for (int i = 1; i < n; i++) {
        if (nums[i] < 0) swap(maxProd, minProd);
        maxProd = max((long long)nums[i], maxProd * nums[i]);
        minProd = min((long long)nums[i], minProd * nums[i]);
        result = max(result, maxProd);
    }
    return result;
}


int main() {
    vector<int> a = {2, 3, -2, 4};
    vector<int> b = {-2, 0, -1};
    cout << "Brute force: " << maxProductSubarray(a) << "\n";
    cout << "Prefix/Suffix: " << maxProduct(a) << "\n";
    cout << "Optimized: " << maxProductSubarrayOptimized(a) << "\n";
    cout << "Optimized (b): " << maxProductSubarrayOptimized(b) << "\n";
    return 0;
}
