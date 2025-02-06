#include<bits/stdc++.h>

using namespace std;

const int inf = 1 << 30;

void chmin(int &a, int b) { a = min(a, b); }

int main() {
    int n, m;
    cin >> n >> m;
    vector d(n, vector<int>(n, inf));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        d[u][v] = w;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] == inf or d[k][j] == inf) continue;
                chmin(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    vector dp(1 << n, vector<int>(n, inf));
    for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
    for (int bit = 1; bit < (1 << n) - 1; bit++) {
        for (int i = 0; i < n; i++) {
            if (~bit >> i & 1) continue;
            if (dp[bit][i] == inf) continue;
            for (int j = 0; j < n; j++) {
                if (bit >> j & 1) continue;
                if (d[i][j] == inf) continue;
                chmin(dp[bit | 1 << j][j], dp[bit][i] + d[i][j]);
            }
        }
    }
    int ans = inf;
    for (int i = 0; i < n; i++) {
        chmin(ans, dp[(1 << n) - 1][i]);
    }
    if (ans == inf) cout << "No" << endl;
    else cout << ans << endl;
}
