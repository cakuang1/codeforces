#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

static const int64 MOD = 998244353;

int64 mod_pow(int64 a, int64 e) {
    int64 r = 1;
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

    int N;
    int64 M;
    cin >> N >> M;

    // H_N = 1 + 1/2 + ... + 1/N mod MOD
    int64 H = 0;

    for (int i = 1; i <= N; i++) {
        H += mod_pow(i, MOD - 2);
        H %= MOD;
    }

    // answer = M^2 * (2 * N * H_N - 1)
    int64 m2 = (M % MOD) * (M % MOD) % MOD;

    int64 inside = 2LL * N % MOD * H % MOD;
    inside = (inside - 1 + MOD) % MOD;

    int64 ans = m2 * inside % MOD;
    cout << ans << '\n';


    
    //  w xiwhe
    return 0;
} 