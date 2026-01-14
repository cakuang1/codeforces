#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    const int MAX = 1e6 + 5;
    vector<int> dp(MAX, 0), has(MAX, 0);
    for (int x : a) has[x] = 1;

    int ans = 1;
    for (int x : a) {
        dp[x] = max(dp[x], 1);
        // Try to extend the chain to multiples of x
        for (int y = 2*x; y < MAX; y += x)
            if (has[y])
                dp[y] = max(dp[y], dp[x] + 1);
        ans = max(ans, dp[x]);
    }

    cout << ans << "\n";
}


// eww weran wei chain we
// werwdilworss rr wethero woemr sd ser