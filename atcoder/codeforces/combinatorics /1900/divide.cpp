#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353; 
const int MX = 300001; // We'll precompute factorials up to 300000

// Iterative modular exponentiation: computes base^power mod MOD
ll modExp(ll base, ll power) {
    ll res = 1;
    base %= MOD;
    while (power > 0) {
        if (power & 1) 
            res = (res * base) % MOD;
        base = (base * base) % MOD;
        power >>= 1;
    }
    return res;
}

// Modular inverse using Fermat's little theorem
ll inv(ll base) {
    return modExp(base, MOD - 2);
}

ll* facs = new ll[MX];
ll* facInvs = new ll[MX];

// Precompute factorials and their modular inverses up to MX-1
void initFacs() {
    facs[0] = 1;
    facInvs[0] = 1;
    for (int i = 1; i < MX; i++) {
        facs[i] = (facs[i - 1] * i) % MOD;
        facInvs[i] = inv(facs[i]);
    }
}

// Compute n choose k modulo MOD
ll choose(ll n, ll k) {
    if (k > n || n < 0 || k < 0) return 0;
    ll cur = facs[n];
    cur = (cur * facInvs[k]) % MOD;
    cur = (cur * facInvs[n - k]) % MOD;
    return cur;
}

void solve() {
    int n; 
    cin >> n;
    int len = 2 * n;
    vector<ll> a(len);
    for (int i = 0; i < len; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    
    ll sumLeft = 0, sumRight = 0;
    for (int i = 0; i < n; i++) {
        sumLeft = (sumLeft + a[i]) % MOD;
    }
    for (int i = n; i < len; i++) {
        sumRight = (sumRight + a[i]) % MOD;
    }
    
    ll diff = (sumRight - sumLeft) % MOD;
    if(diff < 0) diff += MOD;
    ll ways = choose(2 * n, n);
    ll ans = (ways * diff) % MOD;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    initFacs();
    solve(); 
    return 0;
}
