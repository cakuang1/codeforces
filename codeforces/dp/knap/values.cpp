#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;
const int MX = 1000001;

ll modExp(ll base, ll power) {
    if (power == 0) return 1;
    ll cur = modExp(base, power / 2);
    cur = (cur * cur) % MOD;
    if (power % 2) cur = (cur * base) % MOD;
    return cur;
}
ll inv(ll x) { return modExp(x, MOD - 2); }
ll mul(ll A, ll B) { return (A * B) % MOD; }
ll add(ll A, ll B) { return (A + B) % MOD; }
ll sub(ll A, ll B) { return (A - B + MOD) % MOD; }

bool dp[501][501][501];




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    dp[0][0][0] = true;
    // dp[i][j][k]  = true if there exists some subset sum of j that also includes w    
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 0; i < n; i++) {
    
        for (int a  = 0 ; a <=  k ; a  ++) {
            for (int b  = 0 ; b <=  k ; b  ++) {
                 if (dp[i][a][b]) {
                    int val = arr[i]; 
                    dp[i + 1][a][b] = true; 
                    if (a + val <= k) {
                        dp[i + 1][a + val][b] = true; 
                        if (b + val <= k) {
                            dp[i + 1 ][a + val][b + val] = true;
                        }
                    }
                }
            }
    }
}
    vector<int> res;
    for (int i = 0  ; i <= k ; i ++) {
        if (dp[n][k][i]) {
            res.push_back(i);
        } 
    }    
    cout << res.size() << endl;
    for (int i = 0 ; i < res.size() ; i ++) {
        cout << res[i] << ' '; 
    }
     return 0;
}
