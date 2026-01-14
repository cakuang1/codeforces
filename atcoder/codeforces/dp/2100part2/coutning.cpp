#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> arr(n);
    int maxA = 0;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        maxA = max(maxA, arr[i]);
    }
    
    // Build frequency array: cnt[x] = number of occurrences of x.
    vector<ll> cnt(maxA+1, 0);
    for (int i = 0; i < n; i++){
        cnt[arr[i]]++;
    }
    
    // dp[g] will hold the number of pairs whose gcd is exactly g.
    vector<ll> dp(maxA+1, 0);
    
    // Process candidate g values from maxA down to 1.
    for (int g = maxA; g >= 1; g--){
        ll s = 0;
        // Sum the frequency of numbers divisible by g.
        for (int multiple = g; multiple <= maxA; multiple += g) {
            s += cnt[multiple];
        }
        // All pairs among these numbers.
        dp[g] = s * (s - 1) / 2;
        // Subtract the pairs already counted for multiples of g.
        for (int multiple = 2 * g; multiple <= maxA; multiple += g) {
            dp[g] -= dp[multiple];
        }
    }
    
    // Mark g values that are "not suitable". For every number x that appears in the array,
    // mark all multiples of x as unsuitable.
    vector<bool> suitable(maxA+1, true);
    for (int x = 1; x <= maxA; x++){
        if (cnt[x] > 0){
            for (int g = x; g <= maxA; g += x){
                suitable[g] = false;
            }
        }
    }
    
    // Sum the dp[g] for all g that are suitable.
    ll ans = 0;
    for (int g = 1; g <= maxA; g++){
        if (suitable[g]){
            ans += dp[g];
        }
    }
    //minimu m wamount of w
    cout << ans << "\n";
    return 0;
}


