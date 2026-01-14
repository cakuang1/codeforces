#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
const int MOD = 998244353;
const ll INF = 1e18;
 
// ---------- modular helpers ----------
ll modExp(ll base, ll power) {
    if (power == 0) return 1;
    ll cur = modExp(base, power / 2);
    cur = (cur * cur) % MOD;
    if (power % 2) cur = (cur * base) % MOD;
    return cur;
}
 
ll inv(ll base) { return modExp(base, MOD - 2); }
ll mul(ll A, ll B) { return (A * B) % MOD; }
ll add(ll A, ll B) { return (A + B) % MOD; }
ll sub(ll A, ll B) { return (A - B + MOD) % MOD; }
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int n;
    cin >> n;
    vector<string> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
 
    // character counts for each string
    vector<vector<ll>> counts(n, vector<ll>(26, 0));
    for (int i = 0; i < n; i++) {
        for (char c : arr[i]) counts[i][c - 'a']++;
    }
 
    // Step 1. Compute H[mask] = subsequences common to all strings in mask
    vector<ll> H(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<ll> mincounts(26, INF);
        bool emptyMask = true;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                emptyMask = false;
                for (int j = 0; j < 26; j++) {
                    mincounts[j] = min(mincounts[j], counts[i][j]);
                }
            }
        }
        ll res = 1;
        if (emptyMask) {
            // H[0] should equal the "union" of all strings:
            for (int j = 0; j < 26; j++) {
                ll maxCount = 0;
                for (int i = 0; i < n; i++) maxCount = max(maxCount, counts[i][j]);
                res = mul(res, maxCount + 1);
            }
        } else {
            for (int j = 0; j < 26; j++) {
                if (mincounts[j] == INF) continue;
                res = mul(res, mincounts[j] + 1);
            }
        }
        H[mask] = res;
    }

    // recursive wroll aac e
    // Step 2. Möbius inversion to get G from H (superset inversion)
    vector<ll> G = H;
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (!(mask & (1 << i))) {
                G[mask] = sub(G[mask], G[mask | (1 << i)]);
            }
        }
    }
 
    ll total = 0;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        total = add(total, G[mask]);
    }
 
    // Step 4. SOS DP over submasks to get sumG[mask] = sum_{x ⊆ mask} G[x]
    vector<ll> sumG = G;
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i)) {
                sumG[mask] = add(sumG[mask], sumG[mask ^ (1 << i)]);
            }
        }
    }
 
    //
    // Step 5. Compute f[S] for each subset
    vector<ll> f(1 << n, 0);
    for (int S = 0; S < (1 << n); S++) {
        int comp = ((1 << n) - 1) ^ S;
        f[S] = sub(total, sumG[comp]);
    }
    
    unsigned long long ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int k = __builtin_popcount(mask);
        if (k == 0) continue;
        int sumIdx = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) sumIdx += (i + 1);
        }
        // f[mask] is already modulo 998244353, but we do NOT reduce after multiplying
        unsigned long long contrib = (unsigned long long)f[mask] * k * sumIdx;
        ans ^= contrib;
    }
 
    cout << ans << "\n";
    return 0;
}
