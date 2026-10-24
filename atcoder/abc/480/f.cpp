#include <bits/stdc++.h>
using namespace std;



using ll = long long 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<ll> A(N);
    ll total = 0;

    for (ll &a : A) {
        cin >> a;
        total += a;
    }
    ll W = total / M;
    int states = 1 << N;
    vector<ll> sum(states, 0);

    vector<int> dp(states, 0);

    for (int mask = 1; mask < states; mask++) {
        int i = __builtin_ctz((unsigned)mask);
        sum[mask] = sum[mask ^ (1 << i)] + A[i];

        int best = 0;

        // Choose which cake appears last.
        for (int bits = mask; bits; bits &= bits - 1) {
            int j = __builtin_ctz((unsigned)bits);
            best = max(best, dp[mask ^ (1 << j)]);
        }

        dp[mask] = best + (sum[mask] % W == 0);
    }

    // dp includes the final endpoint, so subtract from M.
    cout << M - dp[states - 1] << '\n';
}

// werhsos iewhio wh wrwrw