#include <bits/stdc++.h>
using namespace std;

/*
Problem Title: Accounts Merge
Problem Link: https://leetcode.com/problems/accounts-merge/

Problem Statement:
Given a list of accounts where each account is represented as a list of strings,
the first string is the person's name, and the rest are the person's email addresses.

We need to merge accounts that refer to the same person.
Two accounts belong to the same person if they share at least one common email address.
Return the accounts after merging, where the first element is the name
and the rest are unique email addresses sorted lexicographically.

Example:
Input:
accounts = [
  ["John","johnsmith@mail.com","john_newyork@mail.com"],
  ["John","johnsmith@mail.com","john00@mail.com"],
  ["Mary","mary@mail.com"],
  ["John","johnnybravo@mail.com"]
]

Output:
[
  ["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
  ["Mary","mary@mail.com"],
  ["John","johnnybravo@mail.com"]
]
*/


// Disjoint Set Union (Union by Size + Path Compression)
class DSU {
public:
    vector<int> par, size;

    DSU(int n) {
        par.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int findP(int x) {
        if (par[x] == x) return x;
        return par[x] = findP(par[x]);
    }

    void unionSet(int u, int v) {
        int up = findP(u);
        int vp = findP(v);
        if (up == vp) return;

        if (size[up] < size[vp]) {
            par[up] = vp;
            size[vp] += size[up];
        } else {
            par[vp] = up;
            size[up] += size[vp];
        }
    }
};


// Approach: Disjoint Set Union (Union-Find)
// 💡 Idea:
// Treat each account as a separate node. If two accounts share any email, unite them.
// Then collect all emails belonging to the same ultimate parent (connected component).
//
// 🧩 Algorithm:
// 1. For each account, assign its index as representative in DSU.
// 2. For every email, store the first occurrence; if seen again, union its DSU set.
// 3. Traverse all emails, group them under the ultimate parent.
// 4. Gather sorted emails + name and produce final output.
//
// ⏱ Time Complexity: O(N * M * log(M)) where N = accounts count, M = avg emails per account
// 📦 Space Complexity: O(N * M)

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DSU d(n);

        unordered_map<string, int> emailMap;

        // Step 1: Map each email to its representative account index
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string mail = accounts[i][j];
                if (emailMap.find(mail) == emailMap.end())
                    emailMap[mail] = i;
                else
                    d.unionSet(emailMap[mail], i);
            }
        }

        // Step 2: Group emails based on their root representative
        vector<vector<string>> groupedEmails(n);
        for (auto& it : emailMap) {
            string mail = it.first;
            int root = d.findP(it.second);
            groupedEmails[root].push_back(mail);
        }

        // Step 3: Build final merged result
        vector<vector<string>> result;
        for (int i = 0; i < n; i++) {
            if (groupedEmails[i].empty()) continue;
            sort(groupedEmails[i].begin(), groupedEmails[i].end());
            vector<string> mergedAccount;
            mergedAccount.push_back(accounts[i][0]);
            for (string& mail : groupedEmails[i])
                mergedAccount.push_back(mail);
            result.push_back(mergedAccount);
        }

        return result;
    }
};


int main() {
    Solution s;
    
    vector<vector<string>> accounts = {
        {"John","johnsmith@mail.com","john_newyork@mail.com"},
        {"John","johnsmith@mail.com","john00@mail.com"},
        {"Mary","mary@mail.com"},
        {"John","johnnybravo@mail.com"}
    };

    vector<vector<string>> result = s.accountsMerge(accounts);

    cout << "Merged Accounts:\n";
    for (auto& acc : result) {
        for (auto& s : acc)
            cout << s << " ";
        cout << "\n";
    }

    return 0;
}

/*
✅ Approach Overview:
| Step | Description |
|------|-------------|
| 1.   | Use DSU to connect accounts sharing common emails |
| 2.   | Each group’s root represents a merged account     |
| 3.   | Collect & sort emails per root + attach name      |

| Approach | Time Complexity | Space Complexity | Key Feature |
|-----------|----------------|------------------|--------------|
| DSU (Union-Find) | O(N * M * log M) | O(N * M) | Merges transitive connections efficiently |

This is the optimized, standard DSU-based solution for **LeetCode 721: Accounts Merge**.
*/
