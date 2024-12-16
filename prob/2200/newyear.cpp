#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll mod = 1e9 + 7;

ll k, pa, pb, inva, invb, invab;
ll dp[1010][1010];

// Modular exponentiation
ll ksm(ll x, ll y) {
    ll sum = 1;
    x %= mod;
    while (y) {
        if (y & 1) sum = sum * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return sum;
}

// Top-down DP function
ll topdown(ll i, ll j) {
    // Base case: if i + j >= k, compute the closed-form solution
    if (i + j >= k) return (i + j + pa * invb % mod) % mod;

    // Memoized value
    if (dp[i][j] != -1) return dp[i][j];

    // Recursive transitions
    ll res = 0;
    res = (res + topdown(i + 1, j) * pa % mod * invab % mod) % mod; // Add 'a'
    res = (res + topdown(i, i + j) * pb % mod * invab % mod) % mod; // Add 'b'

    return dp[i][j] = res;
}
// steps of logic 

// ivnerse transitio ns  erw
int main() {
    // Input
    cin >> k >> pa >> pb;

    // Precompute modular inverses
    inva = ksm(pa, mod - 2);   // pa^{-1} % mod
    invb = ksm(pb, mod - 2);   // pb^{-1} % mod
    invab = ksm(pa + pb, mod - 2); // (pa + pb)^{-1} % mod

    // Initialize DP table
    memset(dp, -1, sizeof(dp));

    // Compute the result starting from state (1, 0)
    cout << topdown(1, 0) << endl;

    return 0;
}
