#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll NEG_INF = -(ll)4e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, x;
    cin >> n >> k >> x;
    vector<ll> a(n+1);
    for(int i = 1; i <= n; i++) 
        cin >> a[i];

    // dp[i][j] = max sum using exactly j picks, with the j-th pick at position i
    static ll dp[201][201];
    for(int i = 0; i <= n; i++)
      for(int j = 0; j <= x; j++)
        dp[i][j] = NEG_INF;

    dp[0][0] = 0;  // “0 picks, ending at position 0” = 0 sum

    // Build up
    for(int i = 1; i <= n; i++){
      for(int j = 1; j <= x; j++){
        ll bestPrev = NEG_INF;
        // Try picking a[i] as the j-th repost, previous pick was at t = i - d
        for(int d = 1; d <= k && i - d >= 0; d++){
          bestPrev = max(bestPrev, dp[i - d][j - 1]);
        }
        if(bestPrev > NEG_INF)
          dp[i][j] = bestPrev + a[i];
      }
    }

    // Now your last pick must be within the last k positions: i in [n-k+1 .. n]
    ll ans = NEG_INF;
    for(int i = n - k + 1; i <= n; i++){
      ans = max(ans, dp[i][x]);
    }
    if(ans < 0) ans = -1;
    cout << ans << "\n";
    return 0;
}
