#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> p(n + 1), inv(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        inv[p[i]] = i;
    }

    bool flipped = false;

    while (q--) {
        int t;
        cin >> t;

        if (t == 2) {
            flipped = !flipped;
        } else {
            int x, y;
            cin >> x >> y;

            if (!flipped) {
                int a = p[x], b = p[y];

                swap(p[x], p[y]);

                inv[a] = y;
                inv[b] = x;
            } else {
                int a = inv[x], b = inv[y];

                swap(inv[x], inv[y]);

                p[a] = y;
                p[b] = x;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << (flipped ? inv[i] : p[i]);
        cout << (i == n ? '\n' : ' ');
    }

    return 0;
} 


// wewemrosssotmi hsar mwer#include <bits/stdc++.h>
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

  // Uncomment if you need choose():
    // initFacs();
    
    
    // w werw wsfw wgo ssi s wrw
    
    // toatl weis nbmsersin swer


    // w wsdl es we wg
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

  // Uncomment if you need choose():
    // initFacs();

    return 0;
} 
    //  wdh ars s rwwrw
    
    // bnanesd serisni werw
    
    // werwhtw dsoswe a ssosw
    
    // last 6 characters 

    //  

    // []; 


    //
    
    // werw irs wwwo we hweiewr 
    // ws siohs i rw
    
    return 0;
}  