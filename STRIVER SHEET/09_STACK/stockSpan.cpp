#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
Problem Title: Stock Span Problem (Online Stock Span)
Problem Link: LeetCode #901 (https://leetcode.com/problems/online-stock-span/)

Problem Statement:
Design an algorithm that collects daily stock prices and returns the "span" of 
that stock's price for the current day.

The "span" of the stock's price today is defined as the maximum number of 
consecutive days (starting from today and going backward) for which the stock 
price was less than or equal to today's price.

------------------------------------------------------------
Example:
Input sequence of prices: [100, 80, 60, 70, 60, 75, 85]

Output spans:
- Day 1, price=100 → span=1
- Day 2, price=80  → span=1
- Day 3, price=60  → span=1
- Day 4, price=70  → span=2 (60 < 70)
- Day 5, price=60  → span=1
- Day 6, price=75  → span=4 (70,60,80 < 75)
- Day 7, price=85  → span=6

Final result: [1, 1, 1, 2, 1, 4, 6]

------------------------------------------------------------
Constraints:
- At most 10^4 calls to next().
- Price of each stock: 1 ≤ price ≤ 10^5
------------------------------------------------------------
*/

/*
==================================================================
Approach 1: Brute Force (O(n^2))
==================================================================
💡 Idea:
- Store prices in an array.
- For each new price:
   - Scan backward until a larger price is found.
   - Count consecutive smaller/equal prices.

🧩 Algorithm:
1. Append new price into array.
2. Start with span=1.
3. Traverse backward until a greater price appears.
4. Return span.

⏱ Time Complexity: O(n^2) (worst case: strictly increasing sequence)
📦 Space Complexity: O(n)
*/

class StockSpannerBrute {
    vector<int> prices;
public:
    StockSpannerBrute() {}

    int next(int price) {
        int span = 1;
        for (int i = prices.size()-1; i >= 0; i--) {
            if (prices[i] > price) break;
            span++;
        }
        prices.push_back(price);
        return span;
    }
};

/*
==================================================================
Approach 2: Monotonic Stack (Optimal O(n))
==================================================================
💡 Idea:
- Use stack to store pairs {price, span}.
- When new price arrives:
   - While stack top price ≤ current price, pop it and add its span.
   - Push {current price, total span}.
- Ensures every element is popped at most once → amortized O(1).

🧩 Algorithm:
1. If stack empty, push {price,1}.
2. If stack top price ≤ current price:
   - Pop and accumulate spans.
3. Push {price, accumulatedSpan}.
4. Return span at top.

⏱ Time Complexity: Amortized O(1) per query (O(n) for n calls).
📦 Space Complexity: O(n)
*/

class StockSpannerOptimal {
    stack<pair<int,int>> st; // {price, span}
public:
    StockSpannerOptimal() {}

    int next(int price) {
        int span = 1;
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second;
            st.pop();
        }
        st.push({price, span});
        return span;
    }
};

/*
==================================================================
main() function
==================================================================
*/

int main() {
    cout << "=== Brute Force Approach ===" << endl;
    StockSpannerBrute sp1;
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    for (int p : prices) cout << sp1.next(p) << " ";
    cout << endl;

    cout << "=== Optimal Monotone Stack Approach ===" << endl;
    StockSpannerOptimal sp2;
    for (int p : prices) cout << sp2.next(p) << " ";
    cout << endl;

    /*
    Expected Output:
    Brute:   1 1 1 2 1 4 6
    Optimal: 1 1 1 2 1 4 6
    */
    return 0;
}

/*
==================================================================
✅ Approach Overview
==================================================================
1. Brute Force:
   - O(n) per query in worst case.
   - Simple but too slow for 10^4 operations.
   - Complexity → O(n^2).

2. Monotonic Stack:
   - Uses stack of {price, span}.
   - Each price is pushed & popped once → amortized O(1).
   - Complexity → O(n) overall.
   - Perfect for interviews and large inputs.

👉 Use **Monotonic Stack approach** in interviews (clean, efficient).
==================================================================
*/
