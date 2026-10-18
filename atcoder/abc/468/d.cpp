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

bool p[10001][10001][2]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; 
    cin >> s; 
    int n = s.size();
        
    vector<vector<int>> palin(n,vector<int> (n ,false)) 
    for (int i = 0  ; i < n; i ++ ) {
        p[i][i][0] = true; 
    } 
    int res = 0;
    
    for (int i = n - 2 ; i >= 0 ; i --) {
        for (int j = i + 1 ; j < n ; j ++) {
            if (j - i  == 1) {
                p[i][j][0] = a[i] == a[j];
                p[i][j][1] = true; 
            } else {
                p[i][j][0] = p[i + 1][j - 1][0] && a[i] == a[j];  
                p[i][j][1] = p[i + 1][j - 1][0];
            }
            if (p[i][j][0] || p[i][j][1]) {
                res ++; 
            }
        }    
    }


    cout << res << endl;
    
        
        
    return 0;
} 