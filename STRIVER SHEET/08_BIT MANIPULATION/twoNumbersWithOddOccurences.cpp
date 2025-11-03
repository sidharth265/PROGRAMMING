#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------------------
📝 Problem Title: Find Two Numbers with Odd Occurrences
🔗 Problem Link: (GFG & InterviewBit classic problem)

📌 Problem Statement:
Given an array `Arr` of size `N` where **exactly two elements occur an odd number of times**,  
and all other elements occur an even number of times.  
Find these two numbers.

⚠️ Both numbers are unique and appear at least once.

----------------------------------------------------------
🧩 Example 1:
Input:
    Arr = [1, 2, 3, 2, 1, 4, 5, 4]
Output:
    [5, 3]
Explanation:
    - Elements 1,2,4 appear an even number of times.
    - 3 appears once (odd), 5 appears once (odd).
    - Answer = [5,3] (order doesn’t matter, but usually return larger number first).

🧩 Example 2:
Input:
    Arr = [10, 20, 10, 30, 20, 40]
Output:
    [40, 30]
Explanation:
    - 10, 20 appear twice each (even).
    - 30 and 40 appear once.
----------------------------------------------------------
*/


//////////////////////////////////////////////////////////////
// Approach 1: Brute Force Frequency Count
// 💡 Idea:
//   - Count frequency of each element using hash map.
//   - Collect elements with odd count.
//
// 🧩 Algorithm:
//   1. Create unordered_map<int,int> freq.
//   2. Count occurrences of each array element.
//   3. Collect numbers with odd frequency.
//   4. Return them in descending order.
//
// ⏱ Time Complexity: O(N)
// 📦 Space Complexity: O(N)
//////////////////////////////////////////////////////////////
vector<long long> twoOddNum_BruteForce(long long Arr[], long long N) {
    unordered_map<long long, int> freq;
    for (int i = 0; i < N; i++) freq[Arr[i]]++;

    vector<long long> ans;
    for (auto &it : freq) {
        if (it.second % 2 == 1) ans.push_back(it.first);
    }
    sort(ans.rbegin(), ans.rend()); // larger first
    return ans;
}


//////////////////////////////////////////////////////////////
// Approach 2: XOR Bit Manipulation Trick
// 💡 Idea:
//   - XOR of all elements = Xor = a ^ b
//       (where a and b are the two odd occurring numbers).
//   - Find the rightmost set bit in Xor (denote as setBit).
//   - Partition numbers into two groups based on setBit:
//       • If bit is set → XOR group = a
//       • Else → XOR group = b
//   - Finally return (max, min).
//
// 🧩 Algorithm:
//   1. Compute XOR of all elements → gives XOR = a ^ b.
//   2. Get rightmost set bit: setBit = Xor & (-Xor).
//   3. Partition numbers and XOR separately.
//   4. The two results are a and b.
//
// ⏱ Time Complexity: O(N)
// 📦 Space Complexity: O(1)
//////////////////////////////////////////////////////////////
vector<long long> twoOddNum_XOR(long long Arr[], long long N) {
    long long Xor = 0;
    for (int i = 0; i < N; i++) Xor ^= Arr[i];

    // Rightmost set bit from XOR
    long long setBit = Xor & -Xor;

    long long num1 = 0, num2 = 0;
    for (int i = 0; i < N; i++) {
        if (Arr[i] & setBit) num1 ^= Arr[i];
        else num2 ^= Arr[i];
    }
    return {max(num1, num2), min(num1, num2)};
}


//////////////////////////////////////////////////////////////
// Main Function with Test Cases
//////////////////////////////////////////////////////////////
int main() {
    vector<vector<long long>> testCases = {
        {1, 2, 3, 2, 1, 4, 5, 4},       // odd = 5,3
        {10, 20, 10, 30, 20, 40},       // odd = 40,30
        {7, 7, 8, 8, 9, 11}             // odd = 11,9
    };

    for (auto &arr : testCases) {
        int N = arr.size();
        long long Arr[N]; 
        for (int i = 0; i < N; i++) Arr[i] = arr[i];

        cout << "Array: ";
        for (int x : arr) cout << x << " ";
        cout << "\n";

        // Brute Force
        auto res1 = twoOddNum_BruteForce(Arr, N);
        cout << "   Approach 1 (Brute Force): " << res1[0] << ", " << res1 << "\n";

        // XOR Bit Trick
        auto res2 = twoOddNum_XOR(Arr, N);
        cout << "   Approach 2 (XOR Trick):   " << res2 << ", " << res2 << "\n";

        cout << "-------------------------------------------------\n";
    }

    ////////////////////////////////////////////////////////////
    // ✅ Approach Overview
    // - Approach 1 (Brute Force):
    //     → Easy to implement, works in O(N) but requires O(N) space.
    //
    // - Approach 2 (XOR Trick):
    //     → Optimal solution, pure bit trick, O(N) time, O(1) space.
    //
    // ⭐ Recommended: XOR Trick (Approach 2).
    ////////////////////////////////////////////////////////////

    return 0;
}
