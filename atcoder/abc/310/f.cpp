
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 998244353;

ll modExp(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll inv(ll a) {
    return modExp(a, MOD - 2);
}

ll dvd(ll a, ll b) {
    return mul(a, inv(b));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    const int FULL = 1 << 11;

    vector<ll> dp(FULL, 0);
    dp[1] = 1; // Only sum 0 is achievable

    ll t = 1;

    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;

        t = mul(t, a);

        vector<ll> ndp(FULL, 0);

        for (int mask = 0; mask < FULL; mask++) {
            if (dp[mask] == 0) continue;

            for (int v = 1; v <= min(10LL, a); v++) {
                int nxt = mask | (mask << v);
                nxt &= FULL - 1;

                ndp[nxt] = add(ndp[nxt], dp[mask]);
            }

            // Outcomes greater than 10 do not change the mask
            if (a > 10) {
                ndp[mask] = add(
                    ndp[mask],
                    mul(dp[mask], (a - 10) % MOD)
                );
            }
        }

        dp.swap(ndp);
    }

    ll s = 0;

    for (int mask = 0; mask < FULL; mask++) {
        if (mask & (1 << 10)) {
            s = add(s, dp[mask]);
        }
    }

    cout << dvd(s, t) << '\n';

    return 0;
}
