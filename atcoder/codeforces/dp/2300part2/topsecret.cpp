#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
 
typedef long long ll;
const ll INF = 1e18;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    ll s;
    cin >> n >> k >> s;
    vector<int> q(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> q[i];
    }
    
    // Maximum possible swap cost needed is when the chosen soldiers are as far right as possible.
    // For a chosen subsequence of length k, maximum cost = k*(n - k)
    int maxCost = k * (n - k);
    int cap = min((ll)maxCost, s);
    
    // dp[j][c] = minimal sum of loquacity for choosing j soldiers with total cost exactly c.
    vector<vector<ll>> dp(k + 1, vector<ll>(cap + 1, INF));
    dp[0][0] = 0;
    
    // Process soldiers one by one.
    for (int i = 1; i <= n; i++){
        // We iterate j from min(i, k) down to 1 to avoid reusing soldier i.
        for (int j = min(i, k); j >= 1; j--){
            int costToAdd = i - j; // cost for placing soldier i as the j-th chosen
            for (int c = 0; c <= cap - costToAdd; c++){
                if (dp[j - 1][c] != INF) {
                    int newCost = c + costToAdd;
                    if (newCost <= cap) {
                        dp[j][newCost] = min(dp[j][newCost], dp[j - 1][c] + q[i]);
                    }
                }
            }
        }
    }
    
    ll ans = INF;
    // Look for the best sum among all ways to choose k soldiers with total cost at most s.
    for (int c = 0; c <= cap; c++){
        if(c <= s){
            ans = min(ans, dp[k][c]);
        }
    }
         
    cout << ans << "\n";
    return 0;
}


 