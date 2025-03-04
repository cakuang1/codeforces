#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
const int MOD = 1000000007;
 
// Fast modular exponentiation.
ll modExp(ll base, ll power) {
    ll res = 1;
    base %= MOD;
    while (power > 0) {
        if (power & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        power >>= 1;
    }
    return res;
}
 
// Compute modular inverse.
ll inv(ll a) {
    return modExp(a, MOD-2);
}
 
// Compute nCr modulo MOD using multiplicative formula.
ll nCr(ll n, ll r) {
    if(r < 0 || r > n) return 0;
    ll res = 1;
    for (ll i = 1; i <= r; i++) {
        res = (res * (n - i + 1)) % MOD;
        res = (res * inv(i)) % MOD;
    }
    return res;
}
 
// Total ways to distribute extra length among 3 sticks (da+db+dc <= l).
ll totalWays(ll l) {
    // Number of solutions = C(l+3, 3)
    return nCr(l+3, 3);
}
 
// Function F(T, l): number of solutions (da,db,dc) with da+db+dc = S (for S from 0 to l)
// and da - (db+dc) >= T.
ll F(ll T, ll l) {
    ll res = 0;
    for (ll S = 0; S <= l; S++) {
        ll ways = 0;
        if (T <= 0) {
            // No restriction: there are S+1 solutions.
            ways = S + 1;
        } else {
            // We need X = da >= ceil((S+T)/2).
            ll Xmin = (S + T + 1) / 2;  // this gives ceiling((S+T)/2)
            if (Xmin <= S) {
                ll L = S - Xmin + 1; // number of valid X
                // Sum_{r=1}^{L} r = L*(L+1)/2.
                ways = (L * (L + 1) / 2) % MOD;
            }
        }
        res = (res + ways) % MOD;
    }
    return res;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b, c;
    ll l;
    cin >> a >> b >> c >> l;
    
    // Total ways to assign extra lengths.
    ll tot = totalWays(l);
    
    // For each side, degenerate occurs if that side (after extension) is at least the sum of the other two.
    // For side a, degenerate if: a+da >= (b+db)+(c+dc) <=> da - (db+dc) >= (b+c - a).
    ll dA = F(b + c - a, l);
    ll dB = F(a + c - b, l);
    ll dC = F(a + b - c, l);
    
    // The degenerate assignments are the ones where any one of these conditions holds.
    // (It turns out that at most one can hold, so we can simply subtract their sum.)
    ll degenerate = (dA + dB + dC) % MOD;
    
    ll ans = (tot - degenerate + MOD) % MOD;
    cout << ans << "\n";
    return 0;
}
