 
    #include <bits/stdc++.h>
    
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
    ll cielDiv(ll A , ll B) {
        return (A + B - 1)/B;
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


    ll l,r, k;
    ll dp[61][11][2][2];     

    ll solve(ll val) {
        vector<int> b;
        while (val) {
            if (val & 1) {
                b.push_back(1);
            } else {
                b.push_back(0); 
            } 
            val >>= 1; 
        }
        int n = b.size(); 
        reverse(b.begin(),b.end());
        // tight or not tight 
        dp[1][1][1][1] = 1; // started
        dp[1][0][0][0] = 1; // not started
        for (int pos = 1; pos < n; pos ++) {
            for (int used = 0 ; used <= k; used ++) {
                for (int tight = 0 ; tight <= 1 ; tight ++) {
                    for (int prev = 0 ; prev <= 1 ;prev ++) {
                            
                        if (dp[pos][used][tight][prev]) {
                            int v = dp[pos][used][tight][prev]; 
                            // add one 
                            
                            // add zero
                        }
                    }
                }
            }
        }
        ll res = 0;

        return res; 
        
    }
    void initFacs() {
        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }
    
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t; cin >> t; 
        while (t --) {
            cin >> l >> r >> k; 
            
            
        }
        return 0;
    }
    