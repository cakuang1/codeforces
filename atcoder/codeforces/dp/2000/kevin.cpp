#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> b(m);
        for (int j = 0; j < m; j++){
            cin >> b[j];
        }
        
        // We'll store all possible marginal reductions from each a[i]
        vector<int> reductions;
        // Also compute initial sum of a's
        ll totalSum = 0;
        for (int i = 0; i < n; i++){
            totalSum += a[i];
            
            // dp[x] will be the minimum value after x operations on a[i]
            // Because the operations are AND, using the same magic twice is redundant.
            // So we only need to consider at most m operations.
            vector<int> dp(m+1, 0);
            dp[0] = a[i];
            for (int x = 1; x <= m; x++){
                int best = dp[x-1]; // start with current value (if none of the operations help)
                // try each magic type
                for (int j = 0; j < m; j++){
                    int candidate = dp[x-1] & b[j];
                    best = min(best, candidate);
                }
                dp[x] = best;
            }
            // Compute marginal reductions:
            // reduction for the x-th operation is: dp[x-1] - dp[x]
            for (int x = 1; x <= m; x++){
                int red = dp[x-1] - dp[x];
                // Only add if reduction is positive (if it is 0, no point in using that operation)
                if(red > 0)
                    reductions.push_back(red);
            }
        }
                
        sort(reductions.begin(), reductions.end(), greater<int>());
        ll totalReduction = 0;
        for (int i = 0; i < k && i < (int)reductions.size(); i++){
            totalReduction += reductions[i];
        }
        
        ll answer = totalSum - totalReduction;
        cout << answer << "\n";
    }
    
    return 0;
}
