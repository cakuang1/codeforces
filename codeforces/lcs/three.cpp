#include <bits/stdc++.h>
using namespace std;

void solve() {
    string a, b, c;
    cin >> a >> b >> c;
    int n = a.size(), m = b.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, 1e9));
    dp[0][0] = 0;

    // First row
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i-1][0] + (a[i-1] != c[i-1]);
    }
    // First column
    for (int j = 1; j <= m; j++) {
        dp[0][j] = dp[0][j-1] + (b[j-1] != c[j-1]);
    }

    // wtfw ew
    // 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int k = i + j - 1; // position in c
            dp[i][j] = min(
                dp[i-1][j] + (a[i-1] != c[k]),
                dp[i][j-1] + (b[j-1] != c[k])
            );
        }
    }
    
    // doesht wwreally wrwork wew

    / 
    cout << dp[n][m] << "\n";
}


// stuffwi w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
