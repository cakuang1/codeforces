#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
const int MOD = 1000000007;
 
// fast exponentiation mod MOD
ll modexp(ll base, ll exp) {
    ll res = 1;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n; 
    cin >> n;
    vector<int> a(n);
    int maxA = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        maxA = max(maxA, a[i]);
    }
 
    // bit length needed (<= 20 for 1e6)
    int B = 0;
    while ((1 << B) <= maxA) B++;
    if (B < 20) B = 20; // safe upper bound
    int FULL = 1 << B;
 
    // Step 1: freq counts
    vector<int> cnt(FULL, 0);
    for (int x : a) cnt[x]++;
 
    // Step 2: superset DP
    // sup[mask] = number of elements that contain all bits in mask
    vector<int> sup = cnt;
    for (int b = 0; b < B; b++) {
        for (int mask = 0; mask < FULL; mask++) {
            if (!(mask & (1 << b))) {
                sup[mask] += sup[mask | (1 << b)];
            }
        }
    }
 
    // Step 3: g[mask] = total subsets (non-empty) whose AND ⊇ mask
    vector<ll> g(FULL, 0);
    for (int mask = 0; mask < FULL; mask++) {
        if (sup[mask] > 0) {
            g[mask] = (modexp(2, sup[mask]) - 1 + MOD) % MOD;
        }
    }
 
    // Step 4: Möbius inversion to get exact f[mask]
    vector<ll> f = g;
    for (int b = 0; b < B; b++) {
        for (int mask = 0; mask < FULL; mask++) {
            if (!(mask & (1 << b))) {
                f[mask] = (f[mask] - f[mask | (1 << b)] + MOD) % MOD;
            }
        }
    }
 
    // Step 5: answer = subsets whose AND = 0
    cout << f[0] % MOD << "\n";
    return 0;
}