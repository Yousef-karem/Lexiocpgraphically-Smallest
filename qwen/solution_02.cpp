#include<bits/stdc++.h>
using namespace std;
#define ll  long long
#define all(d) d.begin(),d.end()
#define test int t;cin>>t;while(t--)
#define ones(n) __builtin_popcountll(n)
#define last(n) __builtin_clz(len)
const int dx8[8] = {1, 0, -1, 0, -1, -1, 1, 1};
const int dy8[8] = {0, 1, 0, -1, -1, 1, -1, 1};
int dx[] = {+0, +0, +1, -1};
int dy[] = {+1, -1, +0, +0};
char di[] = {'R', 'L', 'D', 'U'};

void JOO() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}



const int N =1e6+5, M = 26, LOG = 20, inf = 1e9;
int MOD = 998244353;
ll infLL = 0x3f3f3f3f3f3f3f3f;

vector <int> go, divs, alls;

void get_divs(int n) {
    divs.assign(1, 1);
    go.assign(1, 1);
    while (n > 1) {
        int k = spf[n];
        int mx = 0;
        int cur = 1, sz = divs.size();
        while (n % k == 0) {
            n /= k;
            mx++;
        }

        for (int cc= 1; cc <= mx; cc++){
            cur *= k;
            for (int i = 0; i < sz; i++) {
                divs.push_back(divs[i] * cur);
                alls.push_back(divs[i] * cur);
            }
            if (cc == mx / 2 + 1)
            {
                int sz = go.size();
                for (int i = 0; i < sz; i++) {
                    go.push_back(-go[i] * cur);
                }
            }
        }

    }
}
void solve() {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end(), greater<int>());

        vector<pair<int,int>> vals;
        vals.reserve(n);
        for(int i = 0; i < n; ){
            int x = a[i];
            int j = i+1;
            while(j < n && a[j]==x) j++;
            vals.emplace_back(x, j - i);
            i = j;
        }

        ll total_pairs = 0;
        ll total_bad   = 0;
        ll processed_count = 0;
        vector<int> used_divs;
        used_divs.reserve(n * 10);

        auto factor = [&](int x){
            vector<pair<int,int>> f;
            while(x > 1){
                int p = spf[x], e = 0;
                while(x % p == 0){
                    x /= p;
                    e++;
                }
                f.emplace_back(p,e);
            }
            return f;
        };

        for(auto & [x,freq] : vals){
            total_pairs += ll(freq) * processed_count;
            auto F = factor(x);
            vector<int> P;
            P.reserve(F.size());
            for(auto & pe : F){
                int p = pe.first, e = pe.second;
                int need = e/2 + 1;
                int pw = 1;
                while(need--) pw *= p;
                P.push_back(pw);
            }
            int k = (int)P.size();
            ll bad_for_one = 0;
            for(int mask = 1; mask < (1<<k); mask++){
                int d = 1, bits = 0;
                for(int b = 0; b < k; b++){
                    if(mask & (1<<b)){
                        d *= P[b];
                        bits++;
                    }
                }
                int sgn = (bits & 1) ? +1 : -1;
                bad_for_one += sgn * counter_div[d];
            }
            total_bad += bad_for_one * freq;
            processed_count += freq;
            vector<int> divisors = {1};
            for(auto & pe : F){
                int p = pe.first, e = pe.second;
                int sz = divisors.size();
                int pp = 1;
                for(int ee = 1; ee <= e; ee++){
                    pp *= p;
                    for(int i = 0; i < sz; i++){
                        divisors.push_back(divisors[i] * pp);
                    }
                }
            }
            for(int d : divisors){
                if(counter_div[d] == 0) used_divs.push_back(d);
                counter_div[d] += freq;
            }
        }

        ll cnt1 = 0;
        if(!vals.empty() && vals.back().first == 1){
            cnt1 = vals.back().second;
        }
        ll self_ones = cnt1 * (cnt1 + 1) / 2;

        ll ans = total_pairs - total_bad + self_ones;
        cout << ans << "\n";
        for(int d : used_divs){
            counter_div[d] = 0;
        }
}

signed main() {
    JOO();
    //    int cnt=1;
    test {
        //        cout << "Case " << "#" << cnt++ << ": ";
        solve();
    }
}