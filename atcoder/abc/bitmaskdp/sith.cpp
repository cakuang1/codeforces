#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<double>> p(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> p[i][j];
        }
    }

    int N = 1 << n;
    vector<vector<double>> dp(N, vector<double>(n, 0.0));

    int full = N - 1;

    // Base case:
    // if everyone has already appeared, tournament is over.
    // dp[full][i] = 1 if i is Ivan (player 0), else 0.
    for (int i = 0; i < n; i++) {
        dp[full][i] = (i == 0 ? 1.0 : 0.0);
    }

    // Process masks from large to small
    for (int mask = full - 1; mask >= 0; mask--) {
        for (int i = 0; i < n; i++) {
            if (((mask >> i) & 1) == 0) continue; // i must already be in mask

            double best = 0.0;

            // Ivan chooses next unused fighter j optimally
            for (int j = 0; j < n; j++) {
                if ((mask >> j) & 1) continue; // j must be unused

                int nmask = mask | (1 << j);

                double cur =
                    p[i][j] * dp[nmask][i] +
                    p[j][i] * dp[nmask][j];

                best = max(best, cur);
            }

            dp[mask][i] = best;
        }
    }

    // Handle the first fight separately:
    // Ivan chooses any two starting fighters a, b.
    double ans = 0.0;

    if (n == 1) {
        ans = 1.0; // Ivan is the only participant
    } else {
        for (int a = 0; a < n; a++) {
            for (int b = a + 1; b < n; b++) {
                int mask = (1 << a) | (1 << b);

                double cur =
                    p[a][b] * dp[mask][a] +
                    p[b][a] * dp[mask][b];

                ans = max(ans, cur);
            }
        }
    }

    cout << fixed << setprecision(15) << ans << "\n";
    return 0;
}