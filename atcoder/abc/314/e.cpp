
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> cost(n), p(n);
    vector<vector<int>> r(n);

    for (int i = 0; i < n; i++) {
        cin >> cost[i] >> p[i];

        r[i].resize(p[i]);

        for (int j = 0; j < p[i]; j++) {
            cin >> r[i][j];
        }
    }

    vector<double> dp(m + 1, 1e18);
    dp[m] = 0.0;

    for (int i = m - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            double res = 1.0 * cost[j] * p[j];
            int nonzero = 0;

            for (int k = 0; k < p[j]; k++) {
                int points = r[j][k];

                if (points == 0) continue;

                nonzero++;

                int nxt = min(m, i + points);
                res += dp[nxt];
            }

            res /= nonzero;

            dp[i] = min(dp[i], res);
        }
    }

    cout << fixed << setprecision(15) << dp[0] << '\n';

    return 0;
}

// wecosen sohswe

// weruspfsthsi wer