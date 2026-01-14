#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll)-4e18;

// encode a 10‐vector of counts c[0..9], each ∈[0,2], into
// mask = sum_{d=0..9} c[d]*3^d
static int pow3[10];
constexpr int M = 59049;  // 3^10

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // precompute 3^i
    pow3[0] = 1;
    for(int i = 1; i < 10; i++) 
        pow3[i] = pow3[i-1] * 3;

    int T; 
    cin >> T;
    while (T--){
        int n; 
        cin >> n;
        vector<ll> w(n);
        for(int i = 0; i < n; i++) 
            cin >> w[i];

        static ll dp[M];
        fill(dp, dp+M, INF);
        dp[0] = 0;

        // process each plate
        for(int i = 0; i < n; i++){
            ll x = w[i];
            int cnt[10] = {0};
            while (x){
                cnt[x%10]++;
                x /= 10;
            }
            bool ok = true;
            for(int d = 0; d < 10; d++){
                if (cnt[d] > 2) { ok = false; break; }
            }
            if (!ok) continue;

            // 0/1‐knapsack step
            for(int mask = M-1; mask >= 0; mask--){
                ll cur = dp[mask];
                if (cur < 0) continue;
                int tmp = mask, newMask = mask;
                bool can = true;
                for(int d = 0; d < 10; d++){
                    int have = tmp % 3; tmp /= 3;
                    if (have + cnt[d] > 2) { can = false; break; }
                    newMask += cnt[d] * pow3[d];
                }
                if (!can) continue;
                dp[newMask] = max(dp[newMask], cur + w[i]);
            }

        ll ans = 0;
        for(int mask = 0; mask < M; mask++){
            ans = max(ans, dp[mask]);
        }
        cout << ans << "\n";
    }
    return 0;
}
