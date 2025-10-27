#include<bits/stdc++.h>
using namespace std;

/*
Problem: Set Mismatch (Find Repeating and Missing Number)

Problem Statement:
Given an integer array arr of size n containing numbers from 1 to n, one number appears twice (repeating) and one number is missing. Find both numbers and return them as [repeating, missing].

Example:
Input:
  arr = [3, 1, 3]
Output:
  [3, 2]
Explanation:
- 3 appears twice; 2 is missing from 1..3.

Approach Overview:
- Frequency Array: Count occurrences using an array of size n+1; detect count==2 as repeating and count==0 as missing.
- Hash Set: Track duplicates via set membership; then scan 1..n to find the missing value.
- Math (Sum and Square Sum): Use equations based on difference in sum and sum of squares to solve for repeating and missing in O(1) extra space.
- XOR Partitioning: XOR all numbers in arr and 1..n; split by a set bit to isolate the two values, then identify which is repeating.

Complexity Overview:
- Frequency Array: Time O(n), Space O(n).
- Hash Set: Time O(n), Space O(n).
- Math: Time O(n), Space O(1).
- XOR: Time O(n), Space O(1) (plus final verification counts).
*/

/*
Approach 1: Frequency Array

Idea:
- Build frequency count for values 1..n.
- Value with freq 2 is repeating; value with freq 0 is missing.

Algorithm:
1) hash[1..n] = 0
2) For each x in arr: hash[x]++
3) For i in 1..n:
     if hash[i]==2: repeating=i
     else if hash[i]==0: missing=i
4) Return [repeating, missing]

Time Complexity: O(n)
Space Complexity: O(n)
*/
vector<int> findTwoElement1(vector<int>& arr) {
    vector<int> ans(2);
    int n = arr.size();
    vector<int> hash(n+1,0);
    for (int i=0; i<n; i++) hash[arr[i]]++;
    for (int i=1; i<=n; i++) {
        if (hash[i] == 2) ans[0] = i;
        else if (hash[i] == 0) ans[1] = i;
    }
    return ans;
}

/*
Approach 2: Hash Set

Idea:
- Insert elements into a set; the first repeated insertion reveals the repeating number.
- After scanning arr, the missing is the number in 1..n not present in the set.

Algorithm:
1) s = {}
2) For each x in arr:
     if x in s: repeating=x
     else insert x
3) For i in 1..n:
     if i not in s: missing=i
4) Return [repeating, missing]

Time Complexity: O(n)
Space Complexity: O(n)
*/
vector<int> findTwoElement2(vector<int>& arr) {
    vector<int> ans(2);
    unordered_set<int> s;
    int n = arr.size();
    for (int i=0; i<n; i++) {
        if (s.find(arr[i]) != s.end()) ans[0] = arr[i];
        else s.insert(arr[i]);
    }
    for (int i=1; i<=n; i++) if (s.find(i) == s.end()) ans[1] = i;
    return ans;
}

/*
Approach 3: Mathematics (Sum and Square Sum)

Idea:
- Let S = sum(1..n), S2 = sum of squares(1..n).
- Let s = sum(arr), s2 = sum of squares(arr).
- Let missing = M, repeating = R.
  We have:
    M - R = S - s = diff
    M^2 - R^2 = (S2 - s2) = (M - R)(M + R) = diff * sumMR
  => sumMR = (S2 - s2) / diff
  Solve:
    M = (diff + sumMR)/2, R = sumMR - M

Algorithm:
1) sn = n*(n+1)/2, s2n = n*(n+1)*(2n+1)/6
2) s = sum(arr), s2 = sum(x*x for x in arr)
3) diff = sn - s
4) sumMR = (s2n - s2)/diff
5) R = (sumMR - diff)/2, M = (sumMR + diff)/2
6) Return [R, M]

Time Complexity: O(n)
Space Complexity: O(1)
Caution:
- Use 64-bit integers during arithmetic to avoid overflow.
*/
vector<int> findTwoElement3(vector<int>& arr) {
    vector<int> ans(2);
    int n = arr.size();
    long long sn = 1LL*n*(n+1)/2;
    long long s2n = 1LL*n*(n+1)*(2LL*n+1)/6;
    long long s = 0, s2 = 0;
    for (int x : arr) {
        s += x;
        s2 += 1LL*x*x;
    }
    long long diff = sn - s;                 // M - R
    long long sum = (s2n - s2)/diff;         // M + R
    ans[0] = (int)((sum - diff)/2);          // R
    ans[1] = (int)((sum + diff)/2);          // M
    return ans;
}

/*
Approach 4: XOR Partitioning (Bit Manipulation)

Idea:
- xorAll = (arr[0] ^ ... ^ arr[n-1]) ^ (1 ^ 2 ^ ... ^ n) = R ^ M
- Let set_bit be a rightmost set bit in xorAll to partition numbers into two groups.
- XOR corresponding groups from arr and 1..n to isolate two values x and y (which are R and M in some order).
- Count occurrences in arr to decide which is repeating.

Algorithm:
1) xorAll = 0; for i in 0..n-1: xorAll ^= arr[i] ^ (i+1)
2) set_bit = xorAll & ~(xorAll - 1)
3) x = y = 0
4) For each arr[i]:
     if arr[i] has set_bit: x ^= arr[i]; else y ^= arr[i]
5) For i in 1..n:
     if i has set_bit: x ^= i; else y ^= i
6) Count occurrences of x and y in arr; the one with count 2 is repeating.
7) Return [repeating, missing]

Time Complexity: O(n)
Space Complexity: O(1)
*/
vector<int> findTwoElement4(vector<int>& arr) {
    vector<int> ans(2);
    int n = arr.size();
    int xor1 = 0;
    for (int i=0; i<n; i++) xor1 = xor1 ^ arr[i] ^ (i+1);
    int set_bit = xor1 & ~(xor1-1);
    int x = 0, y = 0;
    for (int i=0; i<n; i++) {
        if (arr[i] & set_bit) x ^= arr[i];
        else y ^= arr[i];
    }
    for (int i=1; i<=n; i++) {
        if (i & set_bit) x ^= i;
        else y ^= i;
    }
    int count_x = 0, count_y = 0;
    for (int i=0; i<n; i++) {
        if (arr[i] == x) count_x++;
        if (arr[i] == y) count_y++;
    }
    if (count_x == 2) {
        ans[0] = x;
        ans[1] = y;
    } else {
        ans[0] = y;
        ans[1] = x;
    }
    return ans;
}

// Example usage
int main() {
    vector<int> arr = {3, 1, 3};

    // Choose an approach:
    // vector<int> result = findTwoElement1(arr); // Frequency
    // vector<int> result = findTwoElement2(arr); // Set
    // vector<int> result = findTwoElement3(arr); // Math
    vector<int> result = findTwoElement4(arr);     // XOR

    cout << "Repeating: " << result[0] << ", Missing: " << result[1] << endl;
    return 0;
}
