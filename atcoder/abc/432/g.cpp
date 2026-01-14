#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int C = 500010;

mint fac[C + 1];
mint ifac[C + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fac[0] = 1;
    for (int i = 0; i < C; i++) fac[i + 1] = fac[i] * (i + 1);
    ifac[C] = fac[C].inv();
    for (int i = C - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1);

    int n, m;
    cin >> n >> m;
    vector<int> ca(C), cb(C);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        ++ca[a];
    }
    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        ++cb[b];
    }

    vector<mint> f(C), g(C);
    for (int i = 0; i < C; i++) {
        f[i] = ifac[i] * cb[i];
        g[i] = ifac[i];
    }
    auto h = convolution(f, g);
    mint ans = 0;
    for (int i = 0; i < C; i++) {
        ans += h[i] * fac[i] * ca[i];
    }
    cout << ans.val() << endl;
}

