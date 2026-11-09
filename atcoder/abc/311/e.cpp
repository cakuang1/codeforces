
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w, n;
    cin >> h >> w >> n;

    vector<vector<int>> dp(h + 1, vector<int>(w + 1, 0));
    vector<vector<bool>> hole(h + 1, vector<bool>(w + 1, false));

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        hole[a][b] = true;
    }

    ll ans = 0;

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (hole[i][j]) continue;

            dp[i][j] = 1 + min({
                dp[i - 1][j],
                dp[i][j - 1],
                dp[i - 1][j - 1]
            });

            ans += dp[i][j];
        }
    }

    cout << ans << '\n';

    return 0;
}
