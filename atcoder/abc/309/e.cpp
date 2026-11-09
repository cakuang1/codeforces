
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> p(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
    }

    vector<int> dp(n + 1, -1);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        dp[x] = max(dp[x], y);
    }

    for (int i = 2; i <= n; i++) {
        dp[i] = max(dp[i], dp[p[i]] - 1);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] >= 0) ans++;
    }

    cout << ans << '\n';
}
