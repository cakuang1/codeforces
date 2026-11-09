#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1000000007;
const int MOD2 = 998244353;
const ll INF = 1'000'000'000'000'000'000LL;
const int MX = 1000001; // Valid factorial indices: 0 ... MX-1

ll modExp(ll base, ll power) {
    base %= MOD;
    if (base < 0) base += MOD;

    ll result = 1;
    while (power > 0) {
        if (power & 1) result = result * base % MOD;
        base = base * base % MOD;
        power >>= 1;
    }
    return result;
}


// webiwet. s ssorw rw




ll inv(ll base) {
    // Requires base != 0 (mod MOD), and MOD prime.
    return modExp(base, MOD - 2);
}

// These helpers assume 0 <= A, B < MOD.
ll mul(ll A, ll B) {
    return A * B % MOD;
}

ll add(ll A, ll B) {
    return (A + B) % MOD;
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll facs[MX], facInvs[MX];

void initFacs() {
    facs[0] = 1;
    for (int i = 1; i < MX; ++i) {
        facs[i] = mul(facs[i - 1], i);
    }

    facInvs[MX - 1] = inv(facs[MX - 1]);
    for (int i = MX - 1; i >= 1; --i) {
        facInvs[i - 1] = mul(facInvs[i], i);
    }
}

ll choose(ll a, ll b) {
    if (a < 0 || b < 0 || b > a) return 0;

    // Requires a < MX and initFacs() called beforehand.
    return mul(facs[a], mul(facInvs[b], facInvs[a - b]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    map<ll,pair<ll,ll>> m ;

    for (int i = 0 ; i < n; i ++ ) {
        ll a,b,c; cin >> a >> b >> c;
        m[a].push_back({b,c});
    }   
    

    for (auto &v : m) {
        sort(v.begin(),v.end());
    }

    bool res = false;
    

    int f = 0 ;
    int s = 0 ; 
    auto it = v.begin();
    for (auto p : *it) {
        f = max(p.first,f); 
        s = max(p.second,s ); 
    } 
    it ++; 
    while (it !=  m.end()) {
        
        for (auto &p : *it) {
            if (p.first > f && p.second > s ){
                res = true; 
            }
        }
        for (auto &p : *it) {
            f  = max(f,p.first );
            s  = max(s,p.second);
        } 
    }
    
    if (res) {
        cout << "Yes";
    } else {
        cout << "No";
    }


    return 0;
}  

 