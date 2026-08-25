#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    const ll NEG = -(1LL << 60);

    // dp[p] = maximum sum where the last kept index has parity p.
    //
    // We pretend index 0 is already kept.
    // Its parity is even and contributes 0.
    ll dp[2] = {0, NEG};

    for (int i = 1; i <= N; i++) {
        int p = i & 1;

        // To keep i, the previous kept index must have
        // opposite parity, because their difference must be odd.
        dp[p] = max(dp[p], dp[p ^ 1] + A[i]);
    }

    // We also pretend N+1 is kept.
    // The last real kept index must differ from N+1 by an odd number,
    // so its parity must be the same as N.
    cout << dp[N & 1] << '\n';
}