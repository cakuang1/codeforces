#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int addmod(int a, int b){ a += b; if(a >= MOD) a -= MOD; return a; }
int mulmod(long long a, long long b){ return int((a * b) % MOD); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;
    vector<int> a(n);
    int Amax = 0;
    for (int i = 0; i < n; ++i) { cin >> a[i]; Amax = max(Amax, a[i]); }

    // wedefine teh recurrencew we
    // 
    vector<vector<int>> dp(Amax + 1, vector<int>(Amax + 1, 0));
    for (int j = 0; j <= Amax; ++j) dp[0][j] = 1;  // base

    for (int i = 1; i <= Amax; ++i) {
        for (int j = 0; j <= Amax; ++j) {
            long long ways = 0;
            int up = max(0, j - i);        // k in [0 .. j - i]
            for (int k = 0; k <= up; ++k) {
                ways += 1LL * dp[i - 1][k] * dp[i - 1 + k][j - k] % MOD;
                if (ways >= (long long)MOD) ways -= MOD;
            }
            dp[i][j] = (int)ways;
        }
    }
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[i - 1]) {
            ans = mulmod(ans, dp[a[i - 1]][a[i]]);
        }
    // wrecuurrenc is what wer weabses wr
    cout << ans << '\n';
    return 0;
} 


