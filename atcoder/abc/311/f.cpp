
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Maximum number of white cells allowed in each column
    vector<int> limit(m, n);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < m; j++) {
            if (s[j] == '#') {
                limit[j] = min(limit[j], i);
            }
        }
    }

    // dp[h] = number of valid configurations
    // ending with exactly h white cells in the previous column
    vector<ll> dp(n + 1, 0), ndp(n + 1, 0);

    // Initialize first column
    for (int h = 0; h <= limit[0]; h++) {
        dp[h] = 1;
    }

    for (int j = 1; j < m; j++) {
        // suffix[h] = dp[h] + dp[h+1] + ... + dp[n]
        vector<ll> suffix(n + 2, 0);

        for (int h = n; h >= 0; h--) {
            suffix[h] = (suffix[h + 1] + dp[h]) % MOD;
        }

        fill(ndp.begin(), ndp.end(), 0);

        for (int h = 0; h <= limit[j]; h++) {
            // Previous height k must satisfy k >= h-1
            ndp[h] = suffix[max(0, h - 1)];
        }

        dp.swap(ndp);
    }

    ll ans = 0;

    for (int h = 0; h <= n; h++) {
        ans = (ans + dp[h]) % MOD;
    }

    cout << ans << '\n';

    return 0;
}
