#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;
static const int TABLE = 300000;

long long fac[TABLE + 1], finv[TABLE + 1];

long long modpow(long long a, long long e) {
    long long r = 1;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

void init_comb() {
    fac[0] = 1;
    for (int i = 1; i <= TABLE; i++) fac[i] = fac[i - 1] * i % MOD;

    finv[TABLE] = modpow(fac[TABLE], MOD - 2);
    for (int i = TABLE; i >= 1; i--) {
        finv[i - 1] = finv[i] * i % MOD;
    }
}


long long binom(long long n, long long k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return fac[n] * finv[k] % MOD * finv[n - k] % MOD;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_comb();

    int N, D;
    cin >> N >> D;
    vector<int> A(N);
    int mx = 0;
    for (int &x : A) {
        cin >> x;
        mx = max(mx, x);
    }

    vector<int> cnt(mx + 1, 0);
    for (int x : A) cnt[x]++;

    long long ans = 1;
    long long s = 0;

    for (int v = 0; v <= mx; v++) {
        s += cnt[v];
        ans = ans * binom(s, cnt[v]) % MOD;

        if (v >= D) s -= cnt[v - D];
    }

    cout << ans << "\n";
    return 0;
}
