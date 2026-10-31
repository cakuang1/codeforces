#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = 1'000'000'000'000'000'000LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll x, y, z;
    cin >> x >> y >> z;

    string s;
    cin >> s;

    int n = s.size();

    vector<ll> dp(2, INF);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        char c = s[i];

        vector<ll> ndp(2, INF);

        if (c == 'a') {
            ndp[0] = min(dp[0] + x, dp[1] + z + x);
            ndp[1] = min(dp[1] + y, dp[0] + z + y);
        } else {
            ndp[0] = min(dp[0] + y, dp[1] + z + y);
            ndp[1] = min(dp[1] + x, dp[0] + z + x);
        }

        dp.swap(ndp);
    }

    cout << min(dp[0], dp[1]) << '\n';

    return 0;
}