
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD =  998244353; 
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

    // uoinwerfproblem we 
    //  woe
    void initFacs() {

        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }
    // wionsan re
    // moboisu transform we wer
    // wemous erinveriosn ris whatwe wall subsmask war ewhat e    
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n ; cin >> n ;
        vector<string> arr(n); 
        for (int i =  0 ; i < n; i ++) {
             cin >> arr[i]; 
        }
        

        // doeos thsi w wor ka wner whow douy wler=sove thsi we we w
        vector<vector<ll>> counts(n, vector<int> (26,0));
        for (int i = 0 ; i < n; i ++ ) {
            for (char c : arr[i]) {
                 int val = int(c - 'a');
                counts[i][val] ++;                  
            }
        }
        vector<ll> H(1 << n , 0);
        vector<ll> F(1 << n , 0);
        for (int mask = 0 ;mask  < (1 << n) ;  mask  ++) {
            vector<ll> mincounts(26,INF); 
            
            for (int i = 0 ; i < n; i ++) {
                if ((1 << i) &  mask) { 
                    for (int j = 0 ; j < 26 ;j ++) {
                        mincounts[j] = min(mincounts[j], counts[i][j]); 
                    }
                }
            }
            ll res = 1; 
            for (int i = 0 ; i < 26 ; i ++) { 
                res = mul(res, mincounts[i] + 1);                
            }
            H[mask] =  res;
        }        

        vector<ll> G = H;
                
        for (int i = 0 ; i < n ; i ++) {
            for (int mask = 0 ; mask < (1 << n); mask ++ ) {
                if (!((1 << n) & mask)) { 
                    G[mask] = add(G[mask],G[mask | (1 << n)] ); 
                }
            }
        }

        ll total = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            total = add(total, G[mask]);
        }

        vector<ll> sumg = G:
        vector<ll> F(1 << n , 0); 
        /
        ll res = 0;
        return 0;
    }
    