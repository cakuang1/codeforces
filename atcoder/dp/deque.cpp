#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> a(n);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    // Base case: When there is only one element
    for (int i = 0; i < n; i++) {
        dp[i][i] = a[i]; 
    }

    // Fill DP table for all lengths
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            dp[l][r] = max(a[l] - dp[l + 1][r], a[r] - dp[l][r - 1]);
        }
    }    cout << dp[0][n - 1] << endl; // Final answer
    return 0;
}
