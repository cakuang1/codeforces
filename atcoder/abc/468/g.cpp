#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 998244353;
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
     
    initFacs();
    int n;
    cin >> n;
    string s;
     cin >> s;
     vector<int> os;
    
     
     for (int i = 1 ; i <= n; i ++ ) {
        if (s[i - 1] == 'o' ) {
            os.push_back(i)
        } 
    }

    
    if (s[0] == 'x'  || s[n - 1] == 'x') {
        cout << 0;
        return 0; 
     }

    
    
    reverse(os.begin(), os.end());

    ll res = 1; 
    ll length = n; 
    
    for (int i = 0 ; i < os.size() ; i ++) {
        int outside = length - os[i];

        ll placeoutside = facs[outside]; 
        res = mul(res, mul(placeoutside ,outside));
        length = os[i];
    }  

 c c    
        /// wwths sthsi srd slok li w
        
        // cant wrw iav estism is si. wrw

        // 
        // [1...5] 678 
        
        // place this

        // build thsi wew wrmo l wtwer o ihwerwe r

        ///w erwhin ko s ewsl ew         
        // place thsif rw

        // gaps 

        // arrange tehs es w 

        // oxo ? impossible no? 
        

            
        // between gaps oxxxo
        
        // wecna tw hsv werw
    // [] 
    
    // oxxxxo    

    
    cout << res ; 
    return 0;
}
