
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();

    vector<ll> dp(n + 1, 0), ndp(n + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        fill(ndp.begin(), ndp.end(), 0);

        for (int j = 0; j <= n; j++) {
            if (dp[j] == 0) continue;

            // Add an opening bracket
            if ((s[i] == '(' || s[i] == '?') && j + 1 <= n) {
                ndp[j + 1] = (ndp[j + 1] + dp[j]) % MOD;
            }

            // Add a closing bracket
            if ((s[i] == ')' || s[i] == '?') && j > 0) {
                ndp[j - 1] = (ndp[j - 1] + dp[j]) % MOD;
            }
        }

        dp.swap(ndp);
    }

    cout << dp[0] << '\n';

    return 0;
}
