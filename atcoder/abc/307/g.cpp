#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n + 1);
    ll sum = 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    ll L = sum / n;
    if (sum % n < 0) L--;

    int R = sum - L * n;

    const ll INF = (1LL << 62);

    vector<ll> dp(R + 1, INF);
    dp[0] = 0;

    ll pref = 0;

    for (int i = 1; i <= n; i++) {
        pref += a[i];

        // Descending order allows in-place DP
        for (int k = min(i, R); k >= 0; k--) {
            ll best = dp[k];

            if (k > 0) {
                best = min(best, dp[k - 1]);
            }

            dp[k] = best + abs(pref - (L * i + k));
        }
    }

    cout << dp[R] << '\n';

    return 0;
} 



// we wepl wnrwweh wr