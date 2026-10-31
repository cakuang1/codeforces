#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> s(n);
    for (auto &x : s) cin >> x;

    vector<vector<bool>> adj(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int diff = 0;

            for (int k = 0; k < m; k++) {
                if (s[i][k] != s[j][k]) {
                    diff++;
                }
            }

            adj[i][j] = (diff == 1);
        }
    }

    int FULL = 1 << n;
    vector<vector<bool>> dp(FULL, vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = true;
    }

    for (int mask = 1; mask < FULL; mask++) {
        for (int last = 0; last < n; last++) {
            if (!dp[mask][last]) continue;

            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) continue;
                if (!adj[last][j]) continue;

                dp[mask | (1 << j)][j] = true;
            }
        }
    }

    for (int last = 0; last < n; last++) {
        if (dp[FULL - 1][last]) {
            cout << "Yes\n";
            return 0;
        }
    }

    cout << "No\n";
}