#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    ll W;
    cin >> n >> W;

    vector<pair<ll,ll>> items(n);
    ll maxvalue = 0;
    for (int i = 0; i < n; i++) {
        cin >> items[i].first >> items[i].second; // weight, value
        maxvalue += items[i].second;
    }

    // dp[v] = minimum weight needed to achieve total value v
    vector<ll> dp(maxvalue + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        ll weight = items[i].first;
        ll value  = items[i].second;
        for (ll v = maxvalue; v >= value; v--) {
            dp[v] = min(dp[v], dp[v - value] + weight);
        }
    }

    ll res = 0;
    for (int v = 0; v <= maxvalue; v++) {
        if (dp[v] <= W) {
            res = v;
        }
    }

    cout << res << "\n";
    return 0;
}
