#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
// We'll use a very small number for -infinity.
const ll NEG_INF = -1000000000000000000LL; // -1e18, safely lower than any achievable value.
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<int> col(n);
    for (int i = 0; i < n; i++){
        cin >> col[i];
    }
    
    // For each query:
    while(q--){
        ll a, b;
        cin >> a >> b;
        
        // best[color]: best achievable value for a subsequence ending with a ball of that color.
        // Note: ball colors are given as integers from 1 to n.
        vector<ll> best(n+1, NEG_INF);
        // overall best and second best overall value
        ll overall = 0, second = 0;
        int bestColor = -1;
        
        // Process the balls in order.
        for (int i = 0; i < n; i++){
            int c = col[i];
            ll cur = v[i];
            
            // Option 1: Extend subsequence ending with the same color.
            ll candidate = best[c] + cur * a;
            // Option 2: Start a new block (or extend a subsequence ending with a different color).
            // If the overall best is from the same color, use second best.
            if(c == bestColor) {
                candidate = max(candidate, second + cur * b);
            } else {
                candidate = max(candidate, overall + cur * b);
            }
            // Also, starting a new subsequence from scratch is covered by overall = 0.
            
            // Update best for this color.
            best[c] = max(best[c], candidate);
            
            // Update overall best and second best:
            if(candidate > overall) {
                // If the color of candidate is different from bestColor, update second best.
                if(c != bestColor) {
                    second = overall;
                }
                overall = candidate;
                bestColor = c;
            } else if(c != bestColor && candidate > second) {
                second = candidate;
            }
        }
        
        cout << overall << "\n";
    }
    
    return 0;
}
