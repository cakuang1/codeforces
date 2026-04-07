#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1000000007;
const int MX = 200005; // h+w is at most 2e5

ll modExp(ll base, ll power) {
    ll res = 1;
    while (power > 0) {
        if (power & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        power >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return modExp(x, MOD - 2);
}

ll mul(ll a, ll b) {
    return (a * b) % MOD;
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll subb(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll facs[MX], facInvs[MX];

void initFacs() {
    facs[0] = 1;
    for (int i = 1; i < MX; i++) facs[i] = mul(facs[i - 1], i);

    facInvs[MX - 1] = inv(facs[MX - 1]);
    for (int i = MX - 2; i >= 0; i--) facInvs[i] = mul(facInvs[i + 1], i + 1);
}

ll choose(int a, int b) {
    if (b < 0 || b > a) return 0;
    return mul(facs[a], mul(facInvs[b], facInvs[a - b]));
}

struct Cell {
    int r, c;

    bool operator<(const Cell& other) const {
        if (r != other.r) return r < other.r;
        return c < other.c;
    }
};

ll ways(Cell a, Cell b) {
    if (a.r > b.r || a.c > b.c) return 0;
    int dr = b.r - a.r;
    int dc = b.c - a.c;
    return choose(dr + dc, dr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    initFacs();

    int h, w, n;
    cin >> h >> w >> n;

    vector<Cell> arr(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].r >> arr[i].c;
    }

    arr[n] = {h, w}; // treat destination as final point
    sort(arr.begin(), arr.end());

    vector<ll> dp(n + 1, 0);

    Cell start = {1, 1};

    for (int i = 0; i <= n; i++) {
        dp[i] = ways(start, arr[i]);

        for (int j = 0; j < i; j++) {
            ll through_j = mul(dp[j], ways(arr[j], arr[i]));
            dp[i] = subb(dp[i], through_j);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}


// wew nostss hd