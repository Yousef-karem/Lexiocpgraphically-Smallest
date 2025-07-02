#include <bits/stdc++.h>
using namespace std;

// Manber-Myers suffix array algorithm (O(n log n))
vector<int> buildSuffixArray(const string &s) {
    int n = s.size();
    vector<int> sa(n), rank(n + 1), cnt(max(n, 256)), tmp(n + 1);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            int ra = (a + k < n ? rank[a + k] : -1);
            int rb = (b + k < n ? rank[b + k] : -1);
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);

        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rank = tmp;

        if (tmp[sa.back()] == n - 1) break;
    }
    return sa;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        // Step 1: Build suffix array
        vector<int> sa = buildSuffixArray(s);

        // Step 2: Initialize result array with max values
        vector<int> res(n, -1);

        // Step 3: For each suffix in SA, update min index for each possible substring length
        for (int idx : sa) {
            // For length l = 1 to n - idx
            // We want to fill res[l-1] with the smallest index found so far
            int max_len = n - idx;
            for (int l = 1; l <= max_len; ++l) {
                if (res[l - 1] == -1)
                    res[l - 1] = idx;
                else
                    break; // since we process SA in increasing lex order, no need to go further
            }
        }

        // Step 4: Print result
        for (int i = 0; i < n; ++i)
            cout << res[i] << " ";
        cout << "\n";
    }
}
