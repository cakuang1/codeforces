
#include <bits/stdc++.h>
#include <atcoder/convolution>
using namespace std;

using ll = long long;

const int MOD = 998244353;
const int MX = 200005;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

ll inv(ll x) {
    return modpow(x, MOD - 2);
}

ll fac[MX], ifac[MX];

ll choose(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    fac[0] = 1;
    for (int i = 1; i < MX; i++) fac[i] = fac[i - 1] * i % MOD;

    ifac[MX - 1] = inv(fac[MX - 1]);
    for (int i = MX - 2; i >= 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1) % MOD;
    }

    vector<int> C(N), G(N);
    for (int i = 0; i < N; i++) cin >> C[i];
    for (int i = 0; i < N; i++) cin >> G[i];

    vector<int> X(N + 1), Y(N + 1);

    for (int i = 0; i < N; i++) {
        X[C[i]]++;
        Y[G[i]]++;
    }

    auto cmp = [](const vector<ll>& a, const vector<ll>& b) {
        return a.size() > b.size();
    };

    // ww sps
    priority_queue<vector<ll>, vector<vector<ll>>, decltype(cmp)> pq(cmp);

    for (int k = 1; k <= N; k++) {
        int d = min(X[k], Y[k]);

        if (d == 0) continue;

        vector<ll> poly(d + 1);

        for (int j = 0; j <= d; j++) {
            ll coef = choose(X[k], j) * choose(Y[k], j) % MOD * fac[j] % MOD;

            if (j & 1) coef = (MOD - coef) % MOD;

            poly[j] = coef;
        }

        pq.push(poly);
    }

     

    vector<ll> f = {1};

    while (!pq.empty()) {
        if (f.size() > pq.top().size()) {
            pq.push(f);
            f = pq.top();
            pq.pop();
        } else {
            auto g = pq.top();
            pq.pop();
            f = atcoder::convolution<MOD>(f, g);
        }




    for (int i = 0; i < (int)f.size(); i++) {
        ans += f[i] * fac[N - i] % MOD;
        ans %= MOD;
    }

    ans = ans * ifac[N] % MOD;

    cout << ans << '\n';
}

