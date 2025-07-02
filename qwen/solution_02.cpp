#include <bits/stdc++.h>
using namespace std;

// Function to compute answer for one string
vector<int> computeMinSubstrings(const string& s) {
    int n = s.size();
    vector<int> res(n, 0); // res[i] = start index of min substring of length i+1

    for (int l = 1; l <= n; ++l) {
        int i = 0, j = 1, k = 0;
        while (i < n && j < n && k < l) {
            if (s[(i + k) % n] == s[(j + k) % n]) {
                ++k;
            } else {
                if (s[(i + k) % n] > s[(j + k) % n])
                    i = i + k + 1;
                else
                    j = j + k + 1;
                if (i == j)
                    ++j;
                k = 0;
            }
        }
        res[l - 1] = min(i, j);
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> ans = computeMinSubstrings(s);

        for (int x : ans)
            cout << x << " ";
        cout << "\n";
    }

    return 0;
}
