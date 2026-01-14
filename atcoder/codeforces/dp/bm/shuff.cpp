#include "bits/stdc++.h"
using namespace std;

#define all(x) x.begin(),x.end()

void solve() {
    int n; cin >> n;
    vector<int> s(n), g(n);
    vector<string> aa(n), bb(n);
    vector<string> vals;
    for(int i = 0; i < n; ++i) {
        string a, b; cin >> a >> b;
        vals.push_back(a);
        vals.push_back(b);
        aa[i] = a, bb[i] = b;
    }
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());
    for(int i = 0; i < n; ++i) {
        s[i] = lower_bound(all(vals), aa[i]) - vals.begin();
        g[i] = lower_bound(all(vals), bb[i]) - vals.begin();
    }
    vector<vector<int>> dp(1 << n, vector<int>(n, 0));
    for(int i = 0; i < n; ++i) dp[1 << i][i] = 1;
    for(int mask = 0; mask < (1 << n); ++mask) {
        for(int lst = 0; lst < n; ++lst) {
            if(!dp[mask][lst]) continue;
            for(int i = 0; i < n; ++i) {
                if(mask >> i & 1) continue;
                if(s[lst] == s[i] || g[lst] == g[i]) {
                    dp[mask | (1 << i)][i] |= dp[mask][lst];
                }
            }
        }
    }
    int ans = 0;
    for(int mask = 0; mask < (1 << n); ++mask) {
        for(int i = 0; i < n; ++i) {
            if(dp[mask][i]) {
                ans = max(ans, __builtin_popcount(mask));
            }
        }
    }
    cout << n - ans << "\n";
}   
 
main() {
    int t = 1; cin >> t;
    while(t--) {
        solve();
    }
} 




// try to root er