#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 998244353;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;

    // We never reach odd-numbered rows.
    if (H % 2 == 0) {
        cout << 0 << '\n';
        return 0;
    }

    // Need combinations up to 2H.
    int M = 2 * H;

    vector<ll> fac(M + 1), ifac(M + 1);

    fac[0] = 1;
    for (int i = 1; i <= M; i++)
        fac[i] = fac[i - 1] * i % MOD;

    ifac[M] = modpow(fac[M], MOD - 2);

    for (int i = M; i >= 1; i--)
        ifac[i - 1] = ifac[i] * i % MOD;

    auto C = [&](int n, int k) -> ll {
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
    };

    ll ans = 0;

    // -----------------------------------------
    // W odd
    // -----------------------------------------
    if (W % 2 == 1) {
        /*
            Choose k of the H moves to be +1.

            Net horizontal shift after H moves:

                s = k - (H-k)
                  = 2k - H

            Repeating this block visits every column iff

                gcd(s, W) = 1.
        */

        for (int k = 0; k <= H; k++) {
            int s = abs(2 * k - H);

            if (std::gcd(s, W) == 1) {
                ans += C(H, k);
                if (ans >= MOD) ans -= MOD;
            }
        }
    }

    // -----------------------------------------
    // W even
    // -----------------------------------------
    else {
        /*
            For even W, one H-step block switches
            column parity.

            So we look at 2H moves at once.

            After the reduction in the editorial,
            let d be the effective displacement.

            We need:

                gcd(d, W/2) = 1.

            Number of ways to obtain |d| is:

                C(2H, H + |d|)

            We consider d = -H ... H.
        */

        int m = W / 2;

        for (int d = -H; d <= H; d++) {
            if (std::gcd(abs(d), m) == 1) {
                ans += C(2 * H, H + abs(d));
                if (ans >= MOD) ans -= MOD;
            }
        }
    }

    cout << ans % MOD << '\n';
}

// we w sn fisiehsf si mv li erw