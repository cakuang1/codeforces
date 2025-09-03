#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}
ll inv(ll x) { return modpow(x, MOD - 2); }
ll add(ll a, ll b) { return (a + b) % MOD; }
ll sub(ll a, ll b) { return (a - b + MOD) % MOD; }
ll mul(ll a, ll b) { return (a * b) % MOD; }
ll dvd(ll a, ll b) { return mul(a, inv(b)); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, C;
    cin >> N >> C;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    C--;
    A[C]++; // add initial sock

    // Build frequency of counts
    vector<int> memo(3005, 0);
    ll sum = 0;
    for (int i = 0; i < N; i++) {
        memo[A[i]]++;
        sum += A[i];
    }

    vector<ll> dp(3005, 0);
    ll csum = sum;

    for (int i = 3004; i >= 1; i--) {
        if (memo[i] == 0) continue;

        // base contribution
        ll si = (i - 1 + sum - csum) % MOD;
        ll bo = (sum - 1) % MOD;
        dp[i] = dvd(bo, si);

        // contributions from larger counts
        ll invbo = inv((sum - csum + i - 1) % MOD);
        for (int j = i + 1; j <= 3004; j++) {
            if (memo[j] > 0) {
                dp[i] = add(dp[i], mul(dp[j], mul(invbo, (1LL * j * memo[j]) % MOD)));
            }
        }

        csum -= 1LL * memo[i] * i;
    }

    cout << dp[A[C]] % MOD << "\n";
    return 0;
}

// weflu wer wrowor wcol we2 ea s wrw
