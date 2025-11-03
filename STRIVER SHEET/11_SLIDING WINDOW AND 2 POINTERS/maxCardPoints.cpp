#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------
 Problem Title: Maximum Points You Can Obtain from Cards
 Problem Link: https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/

 Problem Statement:
 You have an array cardPoints where each element represents points awarded for that card.
 You can take exactly k cards from either the beginning or end of the array.
 Return the maximum score you can obtain by taking cards from either side.

-------------------------------------------------
 Example:
 Input: cardPoints = [1,2,3,4,5,6,1], k = 3
 Output: 12
 Explanation:
   One optimal choice is to take the last three cards (6 + 1 + 5) or (1 + 6 + 5) for total 12.

-------------------------------------------------
*/


// -------------------------------------------------
// Approach: Sliding Window (Prefix + Suffix sum)
// -------------------------------------------------
/*
💡 Idea:
   - Take first k cards initially.
   - Then try taking fewer cards from the front and more from the back.
   - Track max sum over all such combinations.

🧩 Algorithm:
   1. Compute sum of first k cards: leftSum.
   2. Initialize rightSum = 0, ans = leftSum.
   3. For each i from k-1 down to 0:
       - Remove cardPoints[i] from leftSum
       - Add cardPoints[back] to rightSum (where back moves from end backward)
       - Update ans = max(ans, leftSum + rightSum)
   4. Return ans.

⏱ Time Complexity: O(k)
📦 Space Complexity: O(1)
*/

int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    int leftSum = 0, rightSum = 0;
    // Sum of first k cards
    for (int i = 0; i < k; i++) leftSum += cardPoints[i];
    int ans = leftSum;
    int back = n - 1;
    for (int i = k - 1; i >= 0; i--) {
        leftSum -= cardPoints[i];        // remove from left
        rightSum += cardPoints[back--];  // add from right
        ans = max(ans, leftSum + rightSum);
    }
    return ans;
}


// -------------------------------------------------
// Main Function (Demo with Test Cases)
// -------------------------------------------------
int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1,2,3,4,5,6,1}, 3},
        {{2,2,2}, 2},
        {{9,7,7,9,7,7,9}, 7},
        {{1,1000,1}, 1},
        {{1,79,80,1,1,1,200,1}, 3}
    };

    for (const auto& test : tests) {
        const vector<int>& cards = test.first;
        int k = test.second;
        for (int c : cards) cout << c << " ";
        cout << "\nk = " << k << "\n";
        cout << "Max Score: " << maxScore(const_cast<vector<int>&>(cards), k) << "\n";
        cout << "--------------------------\n";
    }

    // ✅ Approach Overview
    /*
    - Sliding window approach with prefix & suffix sums combined.
    - Runs in O(k) time and O(1) space.
    */

    return 0;
}
