#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int h, w;
    cin >> h >> w;
    vector a(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> p(h + w - 1);
    for (int &i: p) cin >> i;
    vector dp(h, vector<ll>(w, 1e18));
    dp[h - 1][w - 1] = 0;
    for (int i = h - 1; i >= 0; i--) {
        for (int j = w - 1; j >= 0; j--) {
            if (i + 1 < h) dp[i][j] = min(dp[i][j], dp[i + 1][j]);
            if (j + 1 < w) dp[i][j] = min(dp[i][j], dp[i][j + 1]);
            dp[i][j] += p[i + j] - a[i][j];
            dp[i][j] = max(dp[i][j], 0LL);
        }
    }
    cout << dp[0][0] << endl;
}