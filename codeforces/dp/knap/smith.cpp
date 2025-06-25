 
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


        
    
    void initFacs() {
        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        } 
    }

    

    bool comp(auto &p1 , auto &p2) {
        return p1.first < p2.first; 
    }
    
            
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n; cin >> n; 
        int m ; cin >> m;
        vector<ll> a(n);
        vector<ll> b(n);
        vector<ll> c(m);
        vector<ll> d(n);
        
        
        vector<pair<ll,ll>> p(n); 
        ll m = 0; 

        
        for (int i = 0 ; i < n; i ++) {
            cin >> a[i]; 
            m = max(m , a[i]);
            p[i].first = a[i]; 
        }
        for (int i = 0 ; i < n; i ++) {
            cin >> b[i]; 
        }
        for (int i = 0 ; i < m ; i++) {
            cin >> c[i]; 
        }
        vector<ll> dp(m + 1, 0); 
        for (int i = 0 ; i < n; i ++) {
            d[i] =  a[i] - b[i];
            p[i].second = d;      
        }
        vector<ll> best(m + 1 , INF);
        for (int i = 0 ; i < n; i ++) {
            best[a[i]] = min(d ,best[a[i]]); 
        }

        for (int i = 1 ; i <= m ; i ++) {
            best[i] = min(best[i] ,best[i - 1]);
        }
        for (int i = 2  ;i < n; i ++) {
            int bjump = best[i];
            if (i - bjump >= 0) {
                dp[i] = dp[i - bjump] + 2; 
            }
        }
    
        ll res = 0; 
        for () 
        
        
        return 0;
    }
    