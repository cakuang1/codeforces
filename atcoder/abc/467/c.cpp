#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<int> a(n), b(n - 1);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;
    
    vector<ll> dp(m, INF);

    // Choose the final remainder of the first element.
    for (int r = 0; r < m; ++r) {
        dp[r] = (r - a[0] + m) % m;
    }

    for (int i = 1; i < n; ++i) {
        vector<ll> newdp(m, INF);

        for (int prev = 0; prev < m; ++prev) {
            if (dp[prev] == INF) continue;

            int curr = (b[i - 1] - prev + m) % m;
            ll cost = (curr - a[i] + m) % m;

            newdp[curr] = min(newdp[curr], dp[prev] + cost);
        }

        dp.swap(newdp);
    }

    cout << *min_element(dp.begin(), dp.end()) << '\n';
}