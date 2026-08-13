#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

ll modExp(ll base, ll power) {
    ll res = 1;
    while (power > 0) {
        if (power & 1) res = res * base % MOD;
        base = base * base % MOD;
        power >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return modExp(x, MOD - 2);
}

vector<ll> fac, ifac;

ll choose(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;

    vector<string> g(h);
    for (int i = 0; i < h; i++) cin >> g[i];

    int N = h + w + 5;
    fac.assign(N, 1);
    ifac.assign(N, 1);

    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[N - 1] = inv(fac[N - 1]);
    for (int i = N - 2; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

    vector<vector<ll>> paths(h, vector<ll>(w, 0));
    vector<vector<ll>> tsum(h, vector<ll>(w, 0));

    paths[0][0] = 1;

    ll res = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {

            // move down
            if (i + 1 < h) {
                bool yy = (g[i][j] == 'Y' && g[i + 1][j] == 'Y');

                if (yy) {
                    int ni = i + 1, nj = j;
                    ll suffix = choose((h - 1 - ni) + (w - 1 - nj), h - 1 - ni);

                    ll contribution = (paths[i][j] + 2 * tsum[i][j]) % MOD;
                    res = (res + contribution * suffix) % MOD;
                }

                paths[i + 1][j] = (paths[i + 1][j] + paths[i][j]) % MOD;
                tsum[i + 1][j] = (tsum[i + 1][j] + tsum[i][j]) % MOD;

                if (yy) {
                    tsum[i + 1][j] = (tsum[i + 1][j] + paths[i][j]) % MOD;
                }
            }

            // move right
            if (j + 1 < w) {
                bool yy = (g[i][j] == 'Y' && g[i][j + 1] == 'Y');

                if (yy) {
                    int ni = i, nj = j + 1;
                    ll suffix = choose((h - 1 - ni) + (w - 1 - nj), h - 1 - ni);

                    ll contribution = (paths[i][j] + 2 * tsum[i][j]) % MOD;
                    res = (res + contribution * suffix) % MOD;
                }

                paths[i][j + 1] = (paths[i][j + 1] + paths[i][j]) % MOD;
                tsum[i][j + 1] = (tsum[i][j + 1] + tsum[i][j]) % MOD;

                if (yy) {
                    tsum[i][j + 1] = (tsum[i][j + 1] + paths[i][j]) % MOD;
                }
            }
        }
    }

    cout << res % MOD << '\n';
    return 0;
} 


// we fws wurhuwrw

// ww
// we swr