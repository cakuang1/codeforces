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



// how cmssscuslwweis wrw


// werhow sus isl wrw

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // wernsti wrw s so wer
  // Uncomment if you need choose():
    // initFacs();

    // witw rg a bi wrw bi w
    ll n , k; cin >> n >> k;
    vector<ll> a(n + 1);
    vector<ll> b(n + 1); 
    

    // components are what 

    
    for (int i = 1 ; i <= n; i ++) {
        cin >> a[i]; 
    }
    
    
    for (int i = 1 ;i <= n; i ++ ) {
        cin >> b[i];
    }
    

    // -> -> -> cycle <- <-
    
    vector<int> ind(n + 1 ,0);
    
    

    
    for (int i = 1 ; i <= n ; i ++) {
        ind[a[i]] ++; 
    }

    // cycles entracnes ind = 2
     

    vector<int> starts;
    

    for (int i = 1 ; i <= n; i ++ ) {
        if (ind[i] == 0) {
            starts.push_back(i);
        }
    }
    
    // from each comp what do i need? 
    
    // cycle size

    
    // comp size

    // brute force approach into all cycles 
    
    // wes witso sms shisf wrwr


    // wregi ss skh sf v sa shsf spvls tis aidghs ark hfsih wr


    
    // wvwertsdi fss psssi fsv w buwetw hwi wr

    
    // solve this per component? 

    
    // branch contribution 
    // push up until they are all within werthe cycles e

    
    // cycle size 
    
    for () {
        
    }


    // ind == 2? 

    // ind = 0? star

     

    vector<int>  
    for (int i = 0 ; i < n; i ++) {
        
    }
     

    for (int i = 1 ; i <= n; i ++ ) {
        cout << res[i] << ' '; 
    }

    
    return 0;
} 