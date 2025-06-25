#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll NEG_INF = -(ll)4e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<ll>> v(n);
    vector<int> sz(n);
    for(int i = 0; i < n; i++){
        cin >> sz[i];
        v[i].resize(sz[i]);
        for(int j = 0; j < sz[i]; j++){
            cin >> v[i][j];
        }
    }

    // 1) For each shelf i, precompute best[i][k] = max sum by taking exactly k items from its two ends.
    vector<vector<ll>> best(n, vector<ll>(101, NEG_INF));
    for(int i = 0; i < n; i++){
        int s = sz[i];
        // prefix sums from left, suffix sums from right
        vector<ll> pref(s+1, 0), suff(s+1, 0);
        for(int j = 1; j <= s; j++){
            pref[j] = pref[j-1] + v[i][j-1];
            suff[j] = suff[j-1] + v[i][s-j];
        }
        best[i][0] = 0;
        // try all splits: take L from left, R from right, L+R = k
        for(int k = 1; k <= s; k++){
            ll mx = 0;
            for(int L = 0; L <= k; L++){
                int R = k - L;
                if(R > s) continue;
                mx = max(mx, pref[L] + suff[R]);
            }
            best[i][k] = mx;
        }
    }

    vector<ll> dp(m+1, NEG_INF);
    dp[0] = 0;
    for(int i = 0; i < n; i++){
        // iterate backwards so we don't reuse shelf i more than once
        for(int used = m; used >= 0; used--){
            if(dp[used] == NEG_INF) continue;
            // try smashing k items from shelf i
            for(int k = 1; k <= sz[i] && used + k <= m; k++){
                dp[used + k] = max(dp[used + k],
                                   dp[used] + best[i][k]);
            }
        }
    }
    cout << dp[m] << "\n";
    return 0;
}
