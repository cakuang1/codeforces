
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> X(N), Y(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
    }

    const int K = 28;
    const double INF = 1e100;

    vector<vector<double>> dp(N, vector<double>(K + 1, INF));

    dp[0][0] = 0;

    for (int i = 1; i < N; i++) {
        for (int j = max(0, i - K - 1); j < i; j++) {
            int skip = i - j - 1;

            double dist = hypot(X[i] - X[j], Y[i] - Y[j]);

            for (int k = skip; k <= K; k++) {
                dp[i][k] = min(
                    dp[i][k],
                    dp[j][k - skip] + dist
                );
            }
        }
    }

    double ans = INF;

    for (int k = 0; k <= K; k++) {
        double penalty = (k == 0 ? 0.0 : (double)(1LL << (k - 1)));

        ans = min(ans, dp[N - 1][k] + penalty);
    }

    cout << fixed << setprecision(15) << ans << '\n';

    return 0;
}

/// wweifnis fnsf wer

// werleairn asdofsgosin e uwrw
