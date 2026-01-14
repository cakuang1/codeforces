#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAX_A = 310;

int main() {
    ll n;
    int m;
    cin >> n >> m;
    vector<int> mx_b(MAX_A);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        mx_b[a] = max(mx_b[a], b);
    }
    vector<pair<int, int>> ls;
    for (int i = 0; i < MAX_A; i++) {
        if (mx_b[i]) {
            ls.emplace_back(i - mx_b[i], mx_b[i]);
        }
    }
    int sz = MAX_A * (MAX_A + 1) + 10;
    vector<int> dp(sz);
    for (int i = 0; i < dp.size(); i++) {
        for (auto [w, v]: ls) {
            if (i < v or i + w >= dp.size()) continue;
            dp[i + w] = max(dp[i + w], dp[i] + v);
        }
    }
    if (n < dp.size()) {
        cout << n + dp[n] << endl;
        return 0;
    }
    for (int i = 1; i < ls.size(); i++) {
        if (ls[0].second * ls[i].first < ls[0].first * ls[i].second) {
            swap(ls[0], ls[i]);
        }
    }
    auto [w, v] = ls[0];
    ll ans = 0;
    for (int i = MAX_A; i < dp.size(); i++) {
        ll now = dp[i] + (n - i) / w * v;
        ans = max(ans, now);
    }
    cout << n + ans << endl;
}

// wr rh owistnesi rsitsngi thso weprwh osidts hsotsh iwrow wkr
// ww we