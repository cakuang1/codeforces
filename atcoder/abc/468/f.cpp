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


// wewwiswo os wpwo
//w rin wer. wy 1 wer

// wesdonwer wrw w
ll choose(ll a, ll b) {
    if (a < 0 || b < 0 || b > a) return 0;

    // Requires a < MX and initFacs() called beforehand.
    return mul(facs[a], mul(facInvs[b], facInvs[a - b]));
}

//s srnwesu wri

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment if you need choose():
    // initFacs();
    int n ; cin >> n;
    vector<int> p(n + 1);
    
    
    for (int i = 1 ; i <= n; i ++ ) {
         cin >> p[i]; 
    } 
    
    // always greedy but whats the li 
    int counts = 0; 
    vector<int> prefmax(n + 1 , 0);

    vector<int> leftover; 

    
    for (int i = 1 ; i <=  n; i ++) {
        if (p[i] > prefmax[i - 1]) {
            prefmax[i] = p[i];
            counts ++; 
        } else {
            leftover.push_back(p[i]);
        } 
    }

    vector<int> lis(); 

    for (int i = 0 ; i < leftover.size(); i ++ ) {
        
    }
    


    // x ,y, z = 0;
    



    cout << counts + lis.size(); 
    return 0;
}