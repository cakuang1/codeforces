#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

long long modpow(long long a, long long e) {
    long long r = 1;
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

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> fac(k + 1), ifac(k + 1);
    fac[0] = 1;
    for (int i = 1; i <= k; ++i) fac[i] = fac[i - 1] * i % MOD;
    ifac[k] = modpow(fac[k], MOD - 2);
    for (int i = k; i >= 1; --i) ifac[i - 1] = ifac[i] * i % MOD;

    auto C = [&](int a, int b) -> long long {
        if (b < 0 || b > a) return 0;
        return fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
    };

    long long ans = 0;
    for (int i = 0; i <= k; ++i) {
        long long term = C(k, i) * modpow(k - i, n) % MOD;
        if (i & 1) ans = (ans - term + MOD) % MOD;
        else       ans = (ans + term) % MOD;
    }

    cout << ans << '\n';
    return 0;
}

// determien wrthe possible evalues 