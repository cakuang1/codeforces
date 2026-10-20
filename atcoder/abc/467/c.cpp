
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


int dp[200001][3]; 
int main() { 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment if you need choose():
    // initFacs();
    int n,m ;
    cin >> n >> m;
    vector<int> a(n);    
    vector<int> b(n - 1);

    // define dp[i][m]
    vector<int> ma(n);


    for (int i = 0 ; i < n; i ++) {
        ma[i] = a[i] % m;
    }
    for (int i = 0 ; i < m ; i ++ ) {
        dp[0][i] = (i - ma[a]) % m;                
    }


    for (int i = 1 ; i < n; i ++ ) {
        
        for () {
             
        }
    }
    


    int res = __INT_MAX__;
    

    for (int i = 0 ; i < m ; i ++ ) {
        res = min(res , dp[n - 1][i]);
    }


    cout << res << endl;

            
    
    return 0;
} 