#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, w;
    cin >> n >> w;

    vector<ll> dp(w + 1, 0); // FIX: Initialized to 0, meaning "no items taken"

    for (int i = 0; i < n; i++) {
        ll weight, value;
        cin >> weight >> value;

        for (int curr = w; curr >= weight; curr--) { // FIX: Backward loop to avoid reuse
            dp[curr] = max(dp[curr], dp[curr - weight] + value);
        }
    }

    ll ans = *max_element(dp.begin(), dp.end());
    cout << ans << endl;

    return 0;
}


// 