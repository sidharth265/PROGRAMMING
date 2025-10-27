#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
📝 Problem: Median of Two Sorted Arrays
-----------------------------------------------------------
Given two sorted arrays nums1 and nums2 of size m and n respectively, 
return the median of the two sorted arrays.

The overall runtime complexity should be O(log (m+n)).

-----------------------------------------------------------
Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3], median is 2

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4], median is (2+3)/2 = 2.5
===========================================================
*/


/*
===========================================================
Approach 1: Brute Force
-----------------------------------------------------------
💡 Idea:
- Merge the two sorted arrays fully into one new sorted array.
- Median is just the middle element (or average of two middle ones).

🧩 Algorithm:
1. Initialize two pointers i, j for nums1 and nums2.
2. Merge them into a new array 'arr' while keeping sorted order.
3. If total length n is odd → return arr[n/2]
   Else → return (arr[n/2-1] + arr[n/2]) / 2

⏱ Time Complexity: O(m + n)
📦 Space Complexity: O(m + n)
===========================================================
*/
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    vector<int> arr;
    arr.reserve(n1 + n2);
    
    int i = 0, j = 0;
    while(i<n1 && j<n2) {
        if(nums1[i] > nums2[j]) arr.push_back(nums2[j++]);
        else arr.push_back(nums1[i++]); 
    }
    while(i<n1) arr.push_back(nums1[i++]);
    while(j<n2) arr.push_back(nums2[j++]);

    int n = n1+n2;
    if (n%2) return double(arr[n/2]);
    return double(arr[n/2-1] + arr[n/2]) / 2;
}


/*
===========================================================
Approach 2: Better (Two Pointers - On-the-fly Median)
-----------------------------------------------------------
💡 Idea:
- We don’t need to store the full merged array.
- Just keep track of elements until we reach the median index.
- Maintain only the last two numbers seen.

🧩 Algorithm:
1. Calculate 'mid' = (n1+n2)/2  (index of median element).
2. Use two pointers i, j and simulate merging till mid-th element.
3. Track two elements: ele1 (= previous), ele2 (= current).
4. If length is odd → return ele2.
   If even → return (ele1 + ele2)/2.

⏱ Time Complexity: O((m+n)/2)
📦 Space Complexity: O(1)
===========================================================
*/
double findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    int i = 0, j = 0, k = 0;
    int ele1 = -1, ele2 = -1;
    
    int mid = (n1+n2)/2 + 1;
    while(i<n1 && j<n2) {
        if(k==mid) break;
        ele1 = ele2;
        if(nums1[i] > nums2[j]) ele2 = nums2[j++];
        else ele2 = nums1[i++];
        k++;
    }
    while(i<n1 && k < mid) {
        ele1 = ele2;
        ele2 = nums1[i++];
        k++;
    }
    while(j<n2 && k < mid) {
        ele1 = ele2;
        ele2 = nums2[j++];
        k++;
    }

    int n = n1+n2;
    if (n%2) return double(ele2);
    return double(ele1 + ele2) / 2;
}


/*
===========================================================
Approach 3: Optimal (Binary Search Partition Method)
-----------------------------------------------------------
💡 Idea:
- Use binary search to partition both arrays correctly.
- Ensure left partition has (m+n+1)/2 elements and 
  max(left) <= min(right).
- Median is derived from max(left) and min(right).

🧩 Algorithm:
1. Always apply binary search on smaller array (nums1).
2. Partition nums1 with i1, partition nums2 with i2 = (leftSize - i1).
3. Define:
   l1 = (i1>0) ? nums1[i1-1] : -∞
   r1 = (i1<n1) ? nums1[i1] : +∞
   l2 = (i2>0) ? nums2[i2-1] : -∞
   r2 = (i2<n2) ? nums2[i2] : +∞
4. If l1 <= r2 and l2 <= r1:
     - If (n1+n2) odd → return max(l1,l2)
     - Else → return (max(l1,l2) + min(r1,r2)) / 2
5. Else if l1 > r2 → search left (high = mid-1)
   Else if l2 > r1 → search right (low = mid+1)

⏱ Time Complexity: O(log(min(m, n)))
📦 Space Complexity: O(1)
===========================================================
*/
double findMedianSortedArrays3(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    if(n1 > n2) return findMedianSortedArrays3(nums2, nums1); // recurse on smaller
    
    int left = (n1+n2+1)/2;
    int low = 0, high = n1;
    
    while(low <= high) {
        int mid = (low + high)/2;
        int i1 = mid;
        int i2 = left - mid;
        
        int l1 = (i1 > 0) ? nums1[i1-1] : INT_MIN;
        int r1 = (i1 < n1) ? nums1[i1] : INT_MAX;
        int l2 = (i2 > 0) ? nums2[i2-1] : INT_MIN;
        int r2 = (i2 < n2) ? nums2[i2] : INT_MAX;

        if(l1 <= r2 && l2 <= r1) {
            if((n1+n2)%2) return double(max(l1,l2));
            return (double(max(l1,l2)) + double(min(r1,r2))) / 2;
        }
        else if(l1 > r2) high = mid-1;
        else low = mid+1;
    }
    return 0.0; // Should never reach
}



// ================================
// Example usage
// ================================
int main() {
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    
    cout << fixed << setprecision(5) 
         << findMedianSortedArrays(nums1, nums2) << endl; // Brute → 2.00000

    nums1 = {1, 2};
    nums2 = {3, 4};
    cout << fixed << setprecision(5) 
         << findMedianSortedArrays2(nums1, nums2) << endl; // Better → 2.50000

    nums1 = {1, 2};
    nums2 = {3, 4};
    cout << fixed << setprecision(5) 
         << findMedianSortedArrays3(nums1, nums2) << endl; // Optimal → 2.50000


    /*
    ===========================================================
    ✅ Approach Overview (Comparison)
    -----------------------------------------------------------
    1. Brute Force:
       - Simulate full merge
       - Time: O(m+n), Space: O(m+n)

    2. Better (Two Pointers):
       - Merge until median position only
       - Time: O((m+n)/2), Space: O(1)

    3. Optimal (Binary Search Partition):
       - Use binary search on smaller array to find partition.
       - Time: O(log(min(m,n))), Space: O(1)

    🔑 Conclusion:
    - Use Brute for clarity (easy to implement).
    - Use Better when saving space is important.
    - Use Optimal for the best efficiency with large arrays.
    ===========================================================
    */

    return 0;
}
