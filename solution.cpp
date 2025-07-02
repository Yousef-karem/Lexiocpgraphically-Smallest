#include <bits/stdc++.h>

using namespace std;


struct SuffixArray {
    string S;
    // sa is the suffix array with the empty suffix being sa[0]
    // lcp[i] holds the lcp between sa[i], sa[i - 1]
    vector<int> logs, sa, lcp, rank;
    vector<vector<int> > t1, t2;

    SuffixArray() {
    };

    SuffixArray(string &s, int lim = 256) {
        S = s;
        int n = s.size() + 1, k = 0, a, b;
        vector<int> c(s.begin(), s.end() + 1), tmp(n), frq(max(n, lim));
        c.back() = 0; //0 is less than any character
        sa = lcp = rank = tmp, iota(sa.begin(), sa.end(), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(tmp.begin(), tmp.end(), n - j);
            for (int i = 0; i < n; i++) {
                if (sa[i] >= j)
                    tmp[p++] = sa[i] - j;
            }

            fill(frq.begin(), frq.end(), 0);

            for (int i = 0; i < n; i++) frq[c[i]]++;
            for (int i = 1; i < lim; i++) frq[i] += frq[i - 1];
            for (int i = n; i--;) sa[--frq[c[tmp[i]]]] = tmp[i];

            swap(c, tmp), p = 1, c[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                a = sa[i - 1], b = sa[i], c[b] = (tmp[a] == tmp[b] && tmp[a + j] == tmp[b + j]) ? p - 1 : p++;
        }

        for (int i = 1; i < n; i++) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k && k--, j = sa[rank[i] - 1];
                 s[i + k] == s[j + k];
                 k++);
    }

    void preLcp() {
        int n = S.size() + 1;
        logs = vector<int>(n + 1);
        for (int i = 2; i <= n; ++i) {
            logs[i] = logs[i / 2] + 1;
        }

        t1 = vector<vector<int> >(n, vector<int>(logs[n] + 1));
        t2 = vector<vector<int> >(n, vector<int>(logs[n] + 1));
        for (int i = 0; i < n; ++i) {
            t1[i][0] = lcp[i];
            t2[i][0] = sa[i];
        }

        for (int j = 1; j <= logs[n]; ++j) {
            for (int i = 0; i <= n - (1 << j); ++i) {
                t1[i][j] = min(t1[i][j - 1], t1[i + (1 << (j - 1))][j - 1]);
                t2[i][j] = min(t2[i][j - 1], t2[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int queryLcp(int i, int j) {
        if (i == j)return (int) S.size() - sa[i];
        if (i > j)
            swap(i, j);
        i++;
        int len = logs[j - i + 1];
        return min(t1[i][len], t1[j - (1 << len) + 1][len]);
    }

    int queryMin(int i, int j) {
        int len = logs[j - i + 1];
        return min(t2[i][len], t2[j - (1 << len) + 1][len]);
    }
};

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    SuffixArray a(s);
    a.preLcp();
    int r = 0, cur = 0;
    for (int i = 1; i <= s.size(); ++i) {
        while (n - a.sa[cur] < i)cur++;
        r = max(r, cur);
        while (r + 1 <= s.size() && a.queryLcp(cur, r + 1) >= i)r++;
        while (a.queryLcp(cur, r) < i)r--;
        cout << a.queryMin(cur, r) + 1 << ' ';
    }
    cout << '\n';
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
