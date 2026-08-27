#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll L, R;
    cin >> N >> L >> R;

    vector<ll> A(N + 1), B(N + 1);

    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) cin >> B[i];

    vector<ll> PA(N + 1, 0), PB(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        PA[i] = PA[i - 1] + A[i];
        PB[i] = PB[i - 1] + B[i];
    }

    auto solve = [&](ll X) -> ll {
        if (X < 0) return 0;

        ll K = PA[N] - PB[N] + X;

        vector<ll> dp(N + 1, 0);

        dp[0] = 1;

        for (int a = 0; a <= N; a++) {
            for (int b = 0; b <= a; b++) {

                // (0,0) already initialized
                if (a == 0 && b == 0) {
                    if (PA[0] - PB[0] > K)
                        dp[0] = 0;
                    continue;
                }

                // Forbidden cell
                if (PA[a] - PB[b] > K) {
                    dp[b] = 0;
                    continue;
                }

                ll ways = 0;

                // From (a-1, b)
                // dp[b] still stores previous row here.
                if (a > 0)
                    ways += dp[b];

                // From (a, b-1)
                if (b > 0)
                    ways += dp[b - 1];

                dp[b] = ways % MOD;
            }

            // States b > a aren't legal anyway.
            if (a + 1 <= N)
                dp[a + 1] = 0;
        }

        return dp[N];
    };

    ll ans = (solve(R) - solve(L - 1) + MOD) % MOD;

    cout << ans << '\n';
} 
