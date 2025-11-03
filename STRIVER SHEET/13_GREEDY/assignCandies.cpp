#include <bits/stdc++.h>
using namespace std;

/*
====================================================
 Problem Title: Candy Distribution Problem
 LeetCode Link: https://leetcode.com/problems/candy/

 Problem Statement:
 -----------------
 There are n children standing in a line. Each child is assigned a rating value 
 given in the integer array ratings. You are giving candies to these children 
 subjected to the following requirements:

 - Each child must have at least one candy.
 - Children with a higher rating get more candies than their neighbors with lower ratings.

 Return the minimum number of candies you need to have to distribute the candies 
 to the children.

 Example 1:
 Input: ratings = [1,0,2]
 Output: 5
 Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

 Example 2:
 Input: ratings = [1,2,2]
 Output: 4
 Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
 The third child gets 1 candy because it only needs to satisfy the left neighbor.

 Example 3:
 Input: ratings = [1,3,2,2,1]
 Output: 7
 Explanation: Candy allocation: [1,2,1,2,1] → Total = 7

 Constraints:
 - n == ratings.length
 - 1 <= n <= 2 * 10^4
 - 0 <= ratings[i] <= 2 * 10^4
====================================================
*/


/* 
==========================================
 Approach 1: Brute Force - Iterative Adjustment
 -----------------------------------------
 💡 Idea:
 Start with 1 candy for each child. Repeatedly scan the array and adjust
 candies to satisfy the neighbor constraints until no more changes needed.

 🧩 Algorithm:
 1. Initialize each child with 1 candy.
 2. Repeat until no changes in one full iteration:
    - Scan left to right: if ratings[i] > ratings[i-1], ensure candies[i] > candies[i-1]
    - Scan right to left: if ratings[i] > ratings[i+1], ensure candies[i] > candies[i+1]
 3. Return sum of all candies.

 ⏱ Time Complexity: O(N^2) - may need multiple passes through array
 📦 Space Complexity: O(N) - candy allocation array
*/
int candyBruteForce(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1); // Start with 1 candy each
    bool changed = true;
    
    while (changed) {
        changed = false;
        
        // Left to right pass
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i-1] && candies[i] <= candies[i-1]) {
                candies[i] = candies[i-1] + 1;
                changed = true;
            }
        }
        
        // Right to left pass
        for (int i = n-2; i >= 0; i--) {
            if (ratings[i] > ratings[i+1] && candies[i] <= candies[i+1]) {
                candies[i] = candies[i+1] + 1;
                changed = true;
            }
        }
    }
    
    return accumulate(candies.begin(), candies.end(), 0);
}


/* 
==========================================
 Approach 2: Better - Two Pass with Arrays
 -----------------------------------------
 💡 Idea:
 Make two passes: left-to-right to handle ascending sequences,
 right-to-left to handle descending sequences. Take maximum at each position.

 🧩 Algorithm:
 1. Left pass: if ratings[i] > ratings[i-1], left[i] = left[i-1] + 1, else left[i] = 1
 2. Right pass: if ratings[i] > ratings[i+1], right[i] = right[i+1] + 1, else right[i] = 1
 3. For each position, take max(left[i], right[i]) to satisfy both constraints.
 4. Return sum of all candy allocations.

 ⏱ Time Complexity: O(N) - exactly two passes through array
 📦 Space Complexity: O(N) - two arrays for left and right passes
*/
int candyTwoPass(vector<int>& ratings) {
    int totalCandies = 0;
    int n = ratings.size();
    
    // Left pass: handle ascending sequences
    vector<int> left(n);
    left[0] = 1;
    for (int i = 1; i < n; i++) {
        left[i] = (ratings[i] > ratings[i-1]) ? left[i-1] + 1 : 1;
    }
    
    // Right pass: handle descending sequences
    vector<int> right(n);
    right[n-1] = 1;
    for (int i = n-2; i >= 0; i--) {
        right[i] = (ratings[i] > ratings[i+1]) ? right[i+1] + 1 : 1;
    }
    
    // Take maximum of both constraints at each position
    for (int i = 0; i < n; i++) {
        totalCandies += max(left[i], right[i]);
    }
    
    return totalCandies;
}


/* 
==========================================
 Approach 3: Optimal - Space Optimized Two Pass
 -----------------------------------------
 💡 Idea:
 Same logic as approach 2 but optimize space by combining the right pass
 with the final summation, eliminating the need for right array.

 🧩 Algorithm:
 1. Left pass: calculate left[i] as before.
 2. Combined right pass + summation:
    - Process from right to left
    - Maintain current right value instead of array
    - Add max(left[i], right_curr) to total directly
 3. Return total candies.

 ⏱ Time Complexity: O(N) - two passes through array
 📦 Space Complexity: O(N) - only left array needed
*/
int candySpaceOptimized(vector<int>& ratings) {
    int totalCandies = 0;
    int n = ratings.size();
    
    // Left pass: handle ascending sequences
    vector<int> left(n);
    left[0] = 1;
    for (int i = 1; i < n; i++) {
        left[i] = (ratings[i] > ratings[i-1]) ? left[i-1] + 1 : 1;
    }
    
    // Right pass + summation combined
    totalCandies += left[n-1]; // Add last element
    int curr = 1; // Current right pass value
    for (int i = n-2; i >= 0; i--) {
        if (ratings[i] > ratings[i+1]) {
            curr++;
        } else {
            curr = 1;
        }
        totalCandies += max(curr, left[i]);
    }
    
    return totalCandies;
}


/* 
==========================================
 Approach 4: Optimal - Single Pass (Peak-Valley)
 -----------------------------------------
 💡 Idea:
 Process the array in segments: handle equal ratings, ascending slopes,
 and descending slopes separately. Use mathematical formulas for slopes.

 🧩 Algorithm:
 1. Process equal consecutive ratings: give 1 candy each.
 2. Process ascending slope: give 1,2,3,... candies (arithmetic sum).
 3. Process descending slope: give n,n-1,n-2,... candies from bottom.
 4. Handle peak adjustment: if descending slope > ascending peak, adjust.
 5. Continue until entire array processed.

 ⏱ Time Complexity: O(N) - single pass through array
 📦 Space Complexity: O(1) - only using variables
*/
int candyOptimal(vector<int>& ratings) {
    int totalCandies = 1; // First child gets 1 candy
    int n = ratings.size();
    
    int peak, down, i = 1;
    while (i < n) {
        // Handle equal ratings
        while (i < n && ratings[i] == ratings[i-1]) {
            totalCandies += 1;
            i++;
        }
        
        // Handle ascending slope
        peak = 1;
        while (i < n && ratings[i] > ratings[i-1]) {
            peak++;
            totalCandies += peak;
            i++;
        }
        
        // Handle descending slope
        down = 1;
        while (i < n && ratings[i] < ratings[i-1]) {
            totalCandies += down;
            down++;
            i++;
        }
        
        // Adjust peak if descending slope is longer
        if (down > peak) {
            totalCandies += down - peak;
        }
    }
    
    return totalCandies;
}


/* Helper function to show candy distribution */
void showCandyDistribution(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> left(n), right(n);
    
    // Calculate left pass
    left[0] = 1;
    for (int i = 1; i < n; i++) {
        left[i] = (ratings[i] > ratings[i-1]) ? left[i-1] + 1 : 1;
    }
    
    // Calculate right pass
    right[n-1] = 1;
    for (int i = n-2; i >= 0; i--) {
        right[i] = (ratings[i] > ratings[i+1]) ? right[i+1] + 1 : 1;
    }
    
    cout << "Candy distribution analysis:\n";
    cout << "Ratings: [";
    for (int i = 0; i < n; i++) {
        cout << ratings[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
    
    cout << "Left:    [";
    for (int i = 0; i < n; i++) {
        cout << left[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
    
    cout << "Right:   [";
    for (int i = 0; i < n; i++) {
        cout << right[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
    
    cout << "Final:   [";
    int total = 0;
    for (int i = 0; i < n; i++) {
        int candies = max(left[i], right[i]);
        cout << candies;
        total += candies;
        if (i < n - 1) cout << ", ";
    }
    cout << "] → Total: " << total << "\n";
}


/* ========= MAIN FUNCTION ========= */
int main() {
    vector<vector<int>> testCases = {
        {1, 0, 2},
        {1, 2, 2},
        {1, 3, 2, 2, 1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {1, 3, 4, 5, 2},
        {1, 2, 87, 87, 87, 2, 1},
        {1},
        {1, 2},
        {2, 1}
    };

    cout << "=== Testing Candy Distribution Problem ===\n\n";
    
    for (int t = 0; t < testCases.size(); t++) {
        vector<int> ratings1 = testCases[t], ratings2 = testCases[t];
        vector<int> ratings3 = testCases[t], ratings4 = testCases[t];
        
        cout << "Test Case " << t + 1 << ":\n";
        cout << "Ratings: [";
        for (int i = 0; i < ratings1.size(); i++) {
            cout << ratings1[i];
            if (i < ratings1.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        int ans1 = candyBruteForce(ratings1);
        int ans2 = candyTwoPass(ratings2);
        int ans3 = candySpaceOptimized(ratings3);
        int ans4 = candyOptimal(ratings4);
        
        cout << " Brute Force:           " << ans1 << "\n";
        cout << " Two Pass:              " << ans2 << "\n";
        cout << " Space Optimized:       " << ans3 << "\n";
        cout << " Optimal Peak-Valley:   " << ans4 << "\n";
        
        showCandyDistribution(ratings1);
        cout << "------------------------\n";
    }

    /* ✅ Approach Overview */
    cout << "\n✅ Approach Overview:\n";
    cout << "1. Brute Force -> O(N^2) time, repeatedly adjusts until constraints satisfied.\n";
    cout << "2. Two Pass -> O(N) time, separate left/right passes with two arrays.\n";
    cout << "3. Space Optimized -> O(N) time, combines right pass with summation.\n";
    cout << "4. Optimal Peak-Valley -> O(N) time, O(1) space, single pass with math.\n";
    cout << "\nRecommendation: Your solutions showcase perfect algorithmic evolution! ✅\n";
    cout << "Key Insight: Each child's candies must satisfy both left and right constraints.\n";
    cout << "             Take maximum of what each constraint requires.\n";
    cout << "\nApproach Evolution:\n";
    cout << "1st Solution: Two arrays - clear and intuitive\n";
    cout << "2nd Solution: Space optimization - eliminates right array\n";
    cout << "3rd Solution: Peak-valley method - most advanced, O(1) space\n";
    cout << "\nAll three solutions you provided are excellent implementations! 🎯\n";
    cout << "The peak-valley approach is particularly impressive for its mathematical elegance.\n";

    return 0;
}
