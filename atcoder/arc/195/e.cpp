#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 998244353;

ll modpow(ll a, ll e) {
    ll r = 1;
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

    int N, Q;
    cin >> N >> Q;

    vector<ll> A(N + 1);
    for (int i = 2; i <= N; i++) {
        cin >> A[i];
        A[i] %= MOD;
    }

    // inv[i] = modular inverse of i
    vector<ll> inv(N + 1);
    inv[1] = 1;
    for (int i = 2; i <= N; i++) {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    }

    // E[i] = expected distance from root 1 to vertex i
    vector<ll> E(N + 1);
    ll sumE = 0;

    E[1] = 0;

    for (int i = 2; i <= N; i++) {
        // E[i] = A[i] + (E[1] + ... + E[i-1]) / (i-1)
        E[i] = (A[i] + sumE * inv[i - 1]) % MOD;
        sumE += E[i];
        sumE %= MOD;
    }

    // L[i] = expected depth of LCA(i, v), for ANY v > i
    //
    // L[i] = (E[i] + L[1] + ... + L[i-1]) / i
    vector<ll> L(N + 1);
    ll sumL = 0;

    for (int i = 1; i <= N - 1; i++) {
        L[i] = (E[i] + sumL) % MOD * inv[i] % MOD;

        sumL += L[i];
        sumL %= MOD;
    }

    // Number of possible parent sequences = (N-1)!
    ll fact = 1;
    for (int i = 1; i <= N - 1; i++) {
        fact = fact * i % MOD;
    }

    while (Q--) {
        int u, v;
        cin >> u >> v;

        // Expected distance:
        //
        // E[u] + E[v] - 2 * L[u]
        ll expected = (E[u] + E[v] - 2 * L[u]) % MOD;
        if (expected < 0) expected += MOD;

        // Problem asks for SUM over all trees,
        // not the expected value.
        ll ans = expected * fact % MOD;

        cout << ans << '\n';
    }

    return 0;

} 