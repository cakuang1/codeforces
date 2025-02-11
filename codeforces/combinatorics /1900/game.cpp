#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 998244353; 
const int MX = 1000001; // size for factorial arrays
const int MAXN = 1000001; // maximum number for sieve (must be defined before use)

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
    return modExp(base, MOD - 2);
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
    cur = mul(cur, facInvs[a - b]);
    return cur;
}

void initFacs() {
    facs[0] = 1;
    facInvs[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        facs[i] = (facs[i - 1] * i) % MOD;
        facInvs[i] = inv(facs[i]);
    }
}

bool primes[MX];

void sieve() {
    fill(primes, primes + MX, true);
    primes[0] = primes[1] = false;
    for (int i = 2; i * i < MX; i++) {
        if (primes[i]) {
            for (int curr = i * i; curr < MX; curr += i) {
                primes[curr] = false;
            }
        }
    }
}


// direct   

void solve() {
    int n; cin >> n;
    // what will the graph look like    
    vector<
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);    
     
    int t;

    
    // what can you 

    while (t --) {
        solve(); 
    }
    return 0;
}
