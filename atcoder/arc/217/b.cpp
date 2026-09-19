// wew werotsus rw sfwsdistha wer


// /we wwhw smasih smsts

// werwthaeri hwp rob wer

// werin al l equqllst sdlstiw kwpermsunation
// w

// wrw nwwer 
    //w fsits pobwirtlw wrw
using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy


    ll modExp(ll base, ll power) {
        if (power == 0) {
            return 1;
        } else {
            ll cur = modExp(base, power / 2); cur = cur * cur; cur = cur % MOD;
            if (power % 2 == 1) cur = cur * base;
            cur = cur % MOD;
            return cur;
        }
    }

         
    ll inv(ll base) {
        return modExp(base, MOD-2);
    }


    ll mul(ll A, ll B) {
        return (A*B)%MOD;
    }

    ll add(ll A, ll B) {
        return (A+B)%MOD;
    }
    
    ll dvd(ll A, ll B) {
        return mul(A, inv(B));
    }

    ll sub(ll A, ll B) {
        return (A-B+MOD)%MOD;
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
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }

    void solve() {
        int n ; cin >> n;
        int k ; cin >> k; 
        vector<int> arr(k); 
        for (int i = 0 ;i < k ; i ++) {
            cin >> arr[i];
        }
         

        // wrw s ferobisltssjsowrs wew hsirwer

            
        }        
        
    
    // wr osndfssin ssh wurw        

    }

    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t; cin >> t;
        while (t --) {
            solve();
        }
        return 0;
    }
    
    // wtwh ares lsstis opsi nwr
    / w

    / w era#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 998244353;
const int MAXN = 500000 + 5;

ll fact[MAXN];
ll invv[MAXN];
ll pw2[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // factorials
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    // modular inverses 1/i
    invv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        invv[i] =
            MOD - (ll)(MOD / i) * invv[MOD % i] % MOD;
    }

    // powers of 2
    pw2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pw2[i] = pw2[i - 1] * 2 % MOD;
    }

    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<int> A(K);

        for (int &x : A) {
            cin >> x;
        }

        int M = N - K;
        ll ways = fact[M];

        /*
            Sum of S(P) over all completions, where

              S(P) = sum_{x high} 2^(x-1)

            We'll first compute it WITHOUT the common M! factor.
        */

        ll highSum = 0;

        // --------------------------------------------------------
        // 1. Fixed prefix values.
        //
        // A[i] is high iff it is a prefix maximum.
        // If so, it is high in every completion.
        // --------------------------------------------------------

        int mx = 0;

        for (int x : A) {
            if (x > mx) {
                highSum += pw2[x - 1];

                if (highSum >= MOD)
                    highSum -= MOD;

                mx = x;
            }
        }

        /*
            mx = maximum fixed value.

            Any unfixed x < mx can NEVER be high,
            because mx occurs before it.

            Every x > mx is necessarily unfixed
            (since mx is the largest fixed value).
        */

        // --------------------------------------------------------
        // 2. Unfixed values x > mx.
        //
        // x is high iff x appears before:
        //
        //       x+1, x+2, ..., N
        //
        // among the suffix.
        //
        // Probability = 1 / (N-x+1).
        //
        // So contribution after removing common M! is:
        //
        //       2^(x-1) / (N-x+1)
        // --------------------------------------------------------

        for (int x = mx + 1; x <= N; x++) {
            ll contribution =
                pw2[x - 1] * invv[N - x + 1] % MOD;

            highSum += contribution;

            if (highSum >= MOD)
                highSum -= MOD;
        }

        /*
            For each permutation:

                f(P) = (2^N - 1) - S(P)

            There are M! permutations.

            Therefore:

                answer
                = M! * (2^N - 1)
                  - sum_P S(P)

            We factored M! out of highSum, so:

                answer
                = M! * ((2^N - 1) - highSum)
        */

        ll total = (pw2[N] - 1 + MOD) % MOD;

        ll ans = (total - highSum + MOD) % MOD;
        ans = ans * ways % MOD;

        cout << ans << '\n';
    }

    return 0;
}



//w ewresdf wrsf ew