#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static const int MOD = 998244353;

ll mod_pow(ll a, ll e) {
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

    int N, M;
    cin >> N >> M;

    // If M > N, at least one box must have |ai-bi| = 0
    // in every configuration, so every product is 0.
    if (M > N) {
        cout << 0 << '\n';
        return 0;
    }

    int LIM = N + M;

    // int is enough because values are always modulo MOD.
    vector<int> fac(LIM + 1), ifac(LIM + 1);

    fac[0] = 1;
    for (int i = 1; i <= LIM; ++i) {
        fac[i] = (ll)fac[i - 1] * i % MOD;
    }

    ifac[LIM] = mod_pow(fac[LIM], MOD - 2);

    for (int i = LIM; i >= 1; --i) {
        ifac[i - 1] = (ll)ifac[i] * i % MOD;
    }

    auto C = [&](int n, int r) -> ll {
        if (r < 0 || r > n) return 0;
        return (ll)fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
    };

    ll ans = 0;

    // k = total number of "unbalanced" balls.
    // N-k must be even.
    //
    // Start from k having same parity as N and >= M.
    int k = M;
    if ((k & 1) != (N & 1))
        ++k;

    for (; k <= N; k += 2) {
        int pairs = (N - k) / 2;

        ll waysPairs =
            C(pairs + M - 1, M - 1);

        ll weightedExtras =
            C(k + M - 1, 2 * M - 1);

        ans += waysPairs * weightedExtras % MOD;

        if (ans >= MOD)
            ans -= MOD;
    }

    ans = ans * mod_pow(2, M) % MOD;

    cout << ans << '\n';
    return 0;
}


//T werc sds sfixsk wers
/w