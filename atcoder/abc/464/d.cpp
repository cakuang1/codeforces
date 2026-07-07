#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 60);
const ll M = 1000000000LL;

int digit_sum(ll x) {
    int res = 0;
    while (x > 0) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> A(N + 1), B(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) cin >> B[i];

    const int S = 1 << 9;

    vector<array<ll, 2>> dp(S), ndp(S);
    vector<ll> R(S), nR(S);

    for (int s = 0; s < S; s++) {
        dp[s][0] = dp[s][1] = INF;
        R[s] = -1;
    }

    // X_0 = 0, so L = 0, R = 0
    dp[0][0] = 0; // digitSum(L)
    dp[0][1] = 1; // digitSum(L + 1)
    R[0] = 0;

    vector<ll> ans(N + 1);

    for (int i = 1; i <= N; i++) {
        for (int s = 0; s < S; s++) {
            ndp[s][0] = ndp[s][1] = INF;
            nR[s] = -1;
        }

        for (int s = 0; s < S; s++) {
            if (dp[s][0] == INF) continue;

            for (int b = 0; b < 2; b++) {
                ll c = (b == 0 ? A[i] : B[i]);

                int ns = ((s << 1) & (S - 1)) | b;

                ll val = 10 * R[s] + c;
                ll q = val / M;      // amount entering upper digits
                ll nr = val % M;     // new lower 9 digits

                nR[ns] = nr;

                for (int x = 0; x <= 1; x++) {
                    ll add = q + x;

                    ll cand;
                    if (add < 10) {
                        cand = dp[s][0] + add;
                    } else {
                        cand = dp[s][1] + (add - 10);
                    }

                    ndp[ns][x] = min(ndp[ns][x], cand);
                }
            }
        }

        dp.swap(ndp);
        R.swap(nR);

        ll best = INF;

        for (int s = 0; s < S; s++) {
            if (dp[s][0] == INF) continue;
            best = min(best, dp[s][0] + digit_sum(R[s]));
        }

        ans[i] = best;
    }

    for (int i = 1; i <= N; i++) {
        if (i > 1) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
//