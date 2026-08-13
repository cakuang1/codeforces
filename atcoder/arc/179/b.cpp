#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static const ll MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<int> X(M);
    for (int i = 0; i < M; i++) {
        cin >> X[i];
        --X[i];
    }

    int S = 1 << M;

    // unlock[v]:
    // when we place value v, every b with X[b] = v becomes usable again.
    vector<int> unlock(M, 0);

    for (int b = 0; b < M; b++) {
        if (X[b] != b) {
            unlock[X[b]] |= (1 << b);
        }
    }

    // dp[mask]:
    // number of sequences built so far where
    // bit b = 1 means b cannot currently be used.
    vector<ll> dp(S), ndp(S);
    dp[0] = 1;

    for (int pos = 0; pos < N; pos++) {
        fill(ndp.begin(), ndp.end(), 0);

        for (int mask = 0; mask < S; mask++) {
            if (dp[mask] == 0) continue;

            for (int v = 0; v < M; v++) {
                // v is currently forbidden
                if (mask & (1 << v)) continue;

                int nmask = mask;

                // Seeing v satisfies the waiting requirement
                // for every b such that X[b] = v.
                nmask &= ~unlock[v];

                // After placing v, another v requires X[v]
                // to appear first, unless X[v] = v.
                if (X[v] != v) {
                    nmask |= (1 << v);
                }

                ndp[nmask] += dp[mask];
                if (ndp[nmask] >= MOD) {
                    ndp[nmask] -= MOD;
                }
            }
        }

        dp.swap(ndp);
    }

    ll ans = 0;
    for (ll x : dp) {
        ans += x;
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans << '\n';
}
// ww rhosfsfhi iwor    