#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n+1), b(m+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int j = 1; j <= m; j++) cin >> b[j];

    // dp[i][j] = LCS length of a[1..i], b[1..j]
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    int length = dp[n][m];
    cout << length << "\n";

    // Reconstruct one LCS by backtracking
    vector<int> lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i] == b[j]) {
            lcs.push_back(a[i]);
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(lcs.begin(), lcs.end());

    for (int x : lcs) 
        cout << x << " ";
    cout << "\n";

    return 0;
}
