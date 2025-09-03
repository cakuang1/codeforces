#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> arr(n);

    int max5 = 0;  // total possible factors of 5 across all numbers

    for (int i = 0; i < n; i++) {
        ll a; cin >> a;
        int count2 = 0, count5 = 0;
        while (a % 2 == 0) { a /= 2; count2++; }
        while (a % 5 == 0) { a /= 5; count5++; }
        arr[i] = {count2, count5};
        max5 += count5;
    }

    // dp[j][f] = max number of 2's achievable with j items and f fives
    // initialize with -1 (unreachable)
    vector<vector<int>> dp(k+1, vector<int>(max5+1, -1));
    dp[0][0] = 0;

    for (auto [two, five] : arr) {
        // iterate backwards to avoid double counting
        for (int j = k-1; j >= 0; j--) {
            for (int f = 0; f <= max5; f++) {
                if (dp[j][f] < 0) continue;
                int nf = min(max5, f + five);
                dp[j+1][nf] = max(dp[j+1][nf], dp[j][f] + two);
            }
        }
    }

    int res = 0;
    for (int f = 0; f <= max5; f++) {
        if (dp[k][f] >= 0) {
            res = max(res, min(f, dp[k][f]));
        }
    }

    cout << res << "\n";
    return 0;
}
