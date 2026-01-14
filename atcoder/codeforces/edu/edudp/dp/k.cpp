#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

// You had "add", "mul" helpers; here's just inline:
inline long long addmod(long long a, long long b) {
    return (a + b) % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    // 1) Fix the syntax for divisors:
    vector<vector<long long>> divisors(n+1);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= i; j++){
            if(i % j == 0) {
                divisors[i].push_back(j);
            }
        }
    }

    // 2) dp dimensions: dp[length from 0..k][value from 0..n]
    vector<vector<long long>> dp(k+1, vector<long long>(n+1, 0));

    // 3) base case
    dp[0][1] = 1;

    // 4) fill
    for(int length = 1; length <= k; length++){
        for(int curr = 1; curr <= n; curr++){
            for(long long d : divisors[curr]){
                dp[length][curr] = addmod(dp[length][curr], dp[length-1][d]);
            }
        }
    }

    // 5) sum up answers
    long long ans = 0;
    for(int v = 1; v <= n; v++){
        ans = addmod(ans, dp[k][v]);
    }
    cout << ans << "\n";

    return 0;
}
