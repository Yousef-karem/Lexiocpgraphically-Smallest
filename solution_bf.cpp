#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 1; i <= n; ++i) {
        string cur = s.substr(0, i);
        int best = 0;
        for (int j = 1; j <= n - i; ++j) {
            if (s.substr(j, i) < cur) {
                cur = s.substr(j, i);
                best = j;
            }
        }
        cout << best + 1 << ' ';
    }
    cout << endl;
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
