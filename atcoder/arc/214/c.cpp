#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> P(N);
    int S = 0;

    for (int i = 0; i < N; i++) {
        cin >> P[i];
        S += P[i];
    }

    // If A=B and C=D, then
    // S = 2*A + 2*C, so S must be even.
    if (S % 2) {
        cout << 0 << '\n';
        return 0;
    }

    int H = S / 2;

    // dp[s] = number of subsets whose total strength is s
    vector<ll> dp(H + 1, 0);
    dp[0] = 1;

    for (int p : P) {
        for (int s = H; s >= p; s--) {
            dp[s] += dp[s - p];
            if (dp[s] >= MOD) dp[s] -= MOD;
        }
    }

    ll X = dp[H];

    /*
        X = number of subsets U with sum S/2.

        Pick ordered pair (U, V), both half-sum subsets.

        This gives:
            A = U ∩ V
            C = U \ V
            D = V \ U
            B = outside U ∪ V

        So there are X^2 balanced assignments if empty teams are allowed.


    // thse serbusehf wrw wsf ienwi wer
    /w e

        2. V = complement(U)
           => A and B are empty.
           There are X su   ch pairs.

        Therefore:
            answer = X^2 - 2X
    */

    ll ans = X * X % MOD;
    ans = (ans - 2 * X) % MOD;

    if (ans < 0) ans += MOD;

    cout << ans << '\n';

    return 0;
}

// werhdo hwro