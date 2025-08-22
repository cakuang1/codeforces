#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a;
    cin >> n >> a;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
        y[i] = x[i] - a;
    }

    int max_sum = 0, min_sum = 0;
    for(int v : y){
        if(v > 0) max_sum += v;
        else       min_sum += v;
    }
    int offset = -min_sum;
    int S = max_sum - min_sum + 1;

    vector<int> dp(S, 0), ndp(S);
    dp[offset] = 1;
    int cur_min = 0, cur_max = 0;

    for(int v : y){
        ndp = dp;
        if(v >= 0){
            for(int s = cur_max; s >= cur_min; s--){
                ndp[s + v + offset] = (ndp[s + v + offset] + dp[s + offset]) % MOD;
            }
            cur_max += v;
        } else {
            for(int s = cur_min; s <= cur_max; s++){
                ndp[s + v + offset] = (ndp[s + v + offset] + dp[s + offset]) % MOD;
            }
            cur_min += v;
        }
        dp.swap(ndp);
    }

    int ans = dp[offset] - 1;
    if(ans < 0) ans += MOD;
    cout << ans << "\n";
    return 0;
}
//  wezeor wedoe shti wwhat erand how d oyu wse ehtw