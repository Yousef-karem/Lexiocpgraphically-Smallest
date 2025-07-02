#include <bits/stdc++.h>
using namespace std;

// Compare two substrings s[a..a+len) and s[b..b+len)
int minStartIndex(const string &s, int a, int b, int len) {
    for (int i = 0; i < len; ++i) {
        if (s[a + i] < s[b + i]) return a;
        if (s[a + i] > s[b + i]) return b;
    }
    return a; // equal, return the earlier index
}

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> ans(n);
        for (int l = 1; l <= n; ++l) {
            int best_idx = 0;
            for (int i = 1; i <= n - l; ++i) {
                best_idx = minStartIndex(s, best_idx, i, l);
            }
            ans[l - 1] = best_idx;
        }

        for (int idx : ans) {
            cout << idx << " ";
        }
        cout << "\n";
    }
}
