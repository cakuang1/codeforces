#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NEG_INF = -(1LL << 60);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<pair<int,ll>> arr(n); // {color, value}
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }

    // dp[j][0] = {best value, last color}
    // dp[j][1] = {second best, last color}
    vector<vector<pair<ll,int>>> dp(k+1, vector<pair<ll,int>>(2, {NEG_INF,-1}));
    dp[0][0] = {0, -1}; // no removals, sum = 0, no last color

    for (int i = 0; i < n; i++) {
        int C = arr[i].first;
        ll V = arr[i].second;

        vector<vector<pair<ll,int>>> ndp(k+1, vector<pair<ll,int>>(2, {NEG_INF,-1}));

        for (int j = 0; j <= k; j++) {
            // try to keep this ball
            if (dp[j][0].first > NEG_INF) {
                ll val;
                if (dp[j][0].second != C) {
                    val = dp[j][0].first + V;
                } else {
                    val = (dp[j][1].first > NEG_INF ? dp[j][1].first + V : NEG_INF);
                }
                if (val > NEG_INF) {
                    // insert into ndp[j]
                    if (val > ndp[j][0].first) {
                        if (ndp[j][0].second != C) {
                            ndp[j][1] = ndp[j][0];
                        }
                        ndp[j][0] = {val, C};
                    } else if (val > ndp[j][1].first && ndp[j][0].second != C) {
                        ndp[j][1] = {val, C};
                    }
                }
            }

            // try to remove this ball
            if (j < k) {
                for (int t = 0; t < 2; t++) {
                    if (dp[j][t].first > NEG_INF) {
                        ll val = dp[j][t].first;
                        int col = dp[j][t].second;
                        if (val > ndp[j+1][0].first) {
                            if (ndp[j+1][0].second != col) {
                                ndp[j+1][1] = ndp[j+1][0];
                            }
                            ndp[j+1][0] = {val, col};
                        } else if (val > ndp[j+1][1].first && ndp[j+1][0].second != col) {
                            ndp[j+1][1] = {val, col};
                        }
                    }
                }
            }
        }
    
        // sqrt wm wrrwposointe andwerwhowd oeosthsi rework
        dp.swap(ndp);
    }
    ll ans = dp[k][0].first;
    if (ans < 0) ans = -1;
    cout << ans << "\n";

    return 0;
}
 
