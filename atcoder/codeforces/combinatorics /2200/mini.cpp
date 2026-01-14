#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
// We'll use the modulo from the problem statement.
const int MOD = 998244353;
 
// Fast modular exponentiation (mod MOD).
ll modExp(ll base, ll exp) {
    ll res = 1;
    while(exp > 0) {
        if(exp & 1)
            res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    // Read n (number of digits), k (alphabet size), and m (unused in the easy version)
    int n, k, m;
    cin >> n >> k >> m;
 
    // Total number of tickets is k^n mod MOD.
    ll total = modExp(k, n);
 
    // We'll count the number of *unlucky* tickets:
    // A ticket is unlucky (non-surprising) if for its digit sum S (mod k) it does NOT contain any digit x with 2*x ≡ S (mod k).
    ll totalUnlucky = 0;
 
    // Try each candidate final sum S (from 0 to k-1)
    for (int S = 0; S < k; S++) {
        // Determine the forbidden digit for this candidate S.
        // (If there is no solution to 2*x ≡ S (mod k), then no digit is forbidden.)
        int forbidden = -1;
        bool exists = false;
        for (int x = 0; x < k; x++) {
            if ((2 * x) % k == S) {
                forbidden = x;
                exists = true;
                break;
            }
        }
 
        // dp[i][s] = number of ways to fill i digits so that the running sum mod k is s,
        // while never using the forbidden digit (if it exists).
        vector<vector<ll>> dp(n+1, vector<ll>(k, 0));
        dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int s = 0; s < k; s++) {
                if (dp[i][s] == 0) continue;
                for (int y = 0; y < k; y++) {
                    // If a forbidden digit exists, skip it.
                    if (exists && y == forbidden) continue;
                    int ns = (s + y) % k;
                    dp[i+1][ns] = (dp[i+1][ns] + dp[i][s]) % MOD;
                }
            }
        }
 
        // For the candidate S, the number of ways that yield total sum S mod k is dp[n][S].
        totalUnlucky = (totalUnlucky + dp[n][S]) % MOD;
    }
 
    // Lucky tickets = total tickets - unlucky tickets (mod MOD).
    ll lucky = (total - totalUnlucky + MOD) % MOD;
    cout << lucky << "\n";
     
    return 0;
}
