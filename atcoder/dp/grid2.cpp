#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 200005; // Large enough for factorials

ll modExp(ll base, ll power) {
    if (power == 0) return 1;
    ll cur = modExp(base, power / 2);
    cur = (cur * cur) % MOD;
    if (power % 2 == 1) cur = (cur * base) % MOD;
    return cur;
}

ll inv(ll base) {
    return modExp(base, MOD - 2);
}

ll mul(ll A, ll B) {
    return (A * B) % MOD;
}

ll add(ll A, ll B) {
    return (A + B) % MOD;
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

ll facs[MX], facInvs[MX];

ll choose(ll a, ll b) {
    if (b > a || a < 0 || b < 0) return 0;
    return mul(mul(facs[a], facInvs[b]), facInvs[a - b]);
}

void initFacs(int maxN) {
    facs[0] = 1;
    facInvs[0] = 1;
    for (int i = 1; i <= maxN; i++) {
        facs[i] = mul(facs[i - 1], i);
        facInvs[i] = inv(facs[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll H, W, N;
    cin >> H >> W >> N;

    vector<pair<ll, ll>> walls(N);
    
    for (int i = 0; i < N; i++) {
        cin >> walls[i].first >> walls[i].second;
    }

    // Include (H, W) as a valid endpoint
    walls.push_back({H, W});
    N++; // We have N+1 points now

    // Sort walls by (row, column)
    sort(walls.begin(), walls.end());

    // Initialize factorials for large values
    initFacs(H + W);

    vector<ll> dp(N, 0);

    for (int i = 0; i < N; i++) {
        ll x = walls[i].first;
        ll y = walls[i].second;
        ll paths = choose(x + y - 2, x - 1);  // Ways to reach (x, y) from (1,1)

        for (int j = 0; j < i; j++) {
            ll x2 = walls[j].first;
            ll y2 = walls[j].second;
            if (x2 <= x && y2 <= y) {
                ll subPaths = choose((x - x2) + (y - y2), x - x2); // Ways from (x2, y2) to (x, y)
                paths = sub(paths, mul(dp[j], subPaths));
            }
        }
                
        dp[i] = paths;
    }

    cout << dp[N - 1] << '\n'; // Output the number of ways to reach (H, W)
    return 0;
}
