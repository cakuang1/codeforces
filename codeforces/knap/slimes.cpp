#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // prefix sums
    vector<ll> prefix(n+1, 0);
    for (int i = 1; i <= n; i++) prefix[i] = prefix[i-1] + a[i];

    auto rangeSum = [&](int l, int r) {
        return prefix[r] - prefix[l-1];
    };

    // dp[l][r] = min cost to merge slimes l..r
    vector<vector<ll>> dp(n+1, vector<ll>(n+1, 0));

    // length of interval
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = LLONG_MAX;
            for (int m = l; m < r; m++) {
                dp[l][r] = min(dp[l][r],
                               dp[l][m] + dp[m+1][r] + rangeSum(l, r));
            }
        }
    }

    cout << dp[1][n] << "\n";
    return 0;
}
