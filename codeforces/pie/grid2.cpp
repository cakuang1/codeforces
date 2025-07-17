#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;

// Fast exponentiation mod
ll modexp(ll a, ll e = MOD-2) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, N;
    cin >> H >> W >> N;
    vector<pair<int,int>> blocked;
    blocked.reserve(N+1);
    for (int i = 0; i < N; i++) {
        int r, c;
        cin >> r >> c;
        blocked.emplace_back(r, c);
    }
    // add the destination as the "last block"
    blocked.emplace_back(H, W);

    // sort by row, then by column
    sort(blocked.begin(), blocked.end());

    // Precompute factorials up to H+W
    int LIM = H + W + 5;
    vector<ll> fact(LIM), invfact(LIM);
    fact[0] = 1;
    for (int i = 1; i < LIM; i++)
        fact[i] = fact[i-1] * i % MOD;
    invfact[LIM-1] = modexp(fact[LIM-1]);
    for (int i = LIM-1; i > 0; i--)
        invfact[i-1] = invfact[i] * i % MOD;

    auto choose = [&](int n, int k){
        if (k < 0 || k > n) return 0LL;
        return fact[n] * invfact[k] % MOD * invfact[n-k] % MOD;
    };

    int M = N + 1;  // total points including (H,W)
    vector<ll> dp(M);
    for (int i = 0; i < M; i++) {
        int r = blocked[i].first;
        int c = blocked[i].second;
        // ways from (1,1) to (r,c):
        // need (r-1) downs and (c-1) rights in any order
        ll ways = choose((r-1)+(c-1), r-1);
        // subtract paths that hit an earlier block
        for (int j = 0; j < i; j++) {
            int rj = blocked[j].first;
            int cj = blocked[j].second;
            if (rj <= r && cj <= c) {
                int dr = r - rj;
                int dc = c - cj;
                ll w2 = choose(dr+dc, dr);
                ways = (ways - dp[j] * w2) % MOD;
            }
        }
        dp[i] = (ways + MOD) % MOD;
    }

    // dp[M-1] is the number of valid paths to (H,W)
    cout << dp[M-1] << "\n";
    return 0;
}

