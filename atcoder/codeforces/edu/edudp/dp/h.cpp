#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;

    vector<ll> fonts(n), costs(n);
    for (int i = 0; i < n; i++) {
        cin >> fonts[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> costs[i];
    }

    // dp[k][i] = minimum cost of a strictly increasing subsequence of length k
    // ending *exactly* at index i.
    static ll dp[4][3005];
    for (int k = 0; k < 4; k++) {
        for (int i = 0; i < 3005; i++) {
            dp[k][i] = INF;
        }
    }

    // For length = 1, if a subsequence ends at i, cost is just costs[i].
    for (int i = 0; i < n; i++) {
        dp[1][i] = costs[i];
    }

    // For length = 2.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (fonts[j] < fonts[i]) {
                // We extend the subsequence of length 1 at j with element i.
                dp[2][i] = min(dp[2][i], dp[1][j] + costs[i]);
            }
        }
    }

    // For length = 3.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (fonts[j] < fonts[i]) {
                // Extend the subsequence of length 2 at j with element i.
                dp[3][i] = min(dp[3][i], dp[2][j] + costs[i]);
            }
        }
    }

    // Answer is the minimum dp[3][i] over all i.
    ll ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[3][i]);
    }

    if (ans == INF) {
        ans = -1;
    }
    cout << ans << "\n";

    return 0;
}
