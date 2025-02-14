#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1e9 + 7; 
const ll INF = 1e18;
const int MX = 1000001; // size for factorial arrays

ll modExp(ll base, ll power) {
    if (power == 0) {
        return 1;
    } else {
        ll cur = modExp(base, power / 2);
        cur = (cur * cur) % MOD;
        if (power % 2 == 1) cur = (cur * base) % MOD;
        return cur;
    }
}

ll inv(ll base) {
	return modExp(base, MOD-2);
}

ll mul(ll A, ll B) {
	return (A * B) % MOD;
}

ll add(ll A, ll B) {
	return (A + B) % MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

ll* facs = new ll[MX];
ll* facInvs = new ll[MX];

ll choose(ll a, ll b) {
    if (b > a) return 0;
    if (a < 0) return 0;
    if (b < 0) return 0;
    ll cur = facs[a];
    cur = mul(cur, facInvs[b]);
    cur = mul(cur, facInvs[a-b]);
    return cur;
}

void initFacs() {
    facs[0] = 1;
    facInvs[0] = 1;
    for (int i = 1; i < MX; i++) {  // Use MX here instead of MOD
        facs[i] = (facs[i-1] * i) % MOD;
        facInvs[i] = inv(facs[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);    
    
    initFacs();
    
    int n, k; 
    cin >> n >> k; 
    int mini = min(n, k); 
    ll res = 0; 

    // Use choose(n, i) instead of choose(mini, i)
    for (int i = 0; i <= mini; i++) {
        res = add(res, choose(n, i)); 
    }
    
    cout << res << endl; 
        
    return 0;
}
