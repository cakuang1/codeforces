#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    // maximum possible inversions is n*(n-1)/2
    int maxInv = n*(n-1)/2;
    if(K > maxInv){
        cout << 0 << "\n";
        return 0;
    }

    // dp_prev[j] = dp[i-1][j], dp_cur[j] = dp[i][j]
    vector<int> dp_prev(K+1,0), dp_cur(K+1,0), pref(K+1,0);

    // base: one permutation of length 0 has 0 inversions
    dp_prev[0] = 1;

    // build up to length i=1..n
    for(int i = 1; i <= n; i++){
        // 1) prefix sums of dp_prev
        pref[0] = dp_prev[0];
        for(int j = 1; j <= K; j++){
            pref[j] = pref[j-1] + dp_prev[j];
            if(pref[j] >= MOD) pref[j] -= MOD;
        }
        // 2) compute dp_cur
        int maxJ = min(K, i*(i-1)/2);
        for(int j = 0; j <= K; j++){
            if(j > maxJ){
                dp_cur[j] = 0;
            } else {
                int x = pref[j];
                if(j >= i) {
                    x -= pref[j-i];
                    if(x < 0) x += MOD;
                }
                dp_cur[j] = x;
            }
        }
        // swap rows
        dp_prev.swap(dp_cur);
    }

    // answer for length n and exactly K inversions
    cout << dp_prev[K] << "\n";
    return 0;
}


// go up this path anddetemrin if there existswsom w