#include <bits/stdc++.h>
using namespace std; 
 
const int md = 998244353;
 




void solve(){
    int n, k;
    cin >> n >> k;
    int dp[n + 1][k + 1] = {};
    int ans = 0;    
    fill(dp[0] + 1, dp[0] + k + 1, 1);
 
    for (int sum = 1; sum <= n; sum++){
        for (int cur = 1; cur <= k; cur++){
            for (int prv = 1; cur * prv <= sum and cur + prv - 1 <= k; prv++)
                dp[sum][cur] = (dp[sum][cur] + dp[sum - cur * prv][prv]) % md;
 
            if (sum == n)
                ans = (ans + dp[sum][cur]) % md;
        }
    }
    cout<<ans<<"\n";
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); 
    int tc; 
    cin >> tc;
 
    while (tc--)
        solve();
}