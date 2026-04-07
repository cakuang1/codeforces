

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

    // wrsd wsf ihso sslv ih

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
    
    int n,k ;
    

    vector<vector<int>> g;
    vector<vector<vector<int>>> dp;

    // wewt ilsign wro spr
    void dfs(int a ,int p ) {
        int INF = k + 1;
        vector<vector<int>> cur(k + 2, vector<int> )
        for (int c : adj[a]) {
            if (c == p) continue;
            dfs(c,a);tsf hrowrw
            sz[a] += sz[c];             
        }
    }
    


    

    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        cin >> n >> k;
        g.resize(n + 1); 

    
        for (int i = 0 ; i < n - 1 ; i ++ ) { 
            int a,b; cin >> a >> b;
            g[a].push_back(b); 
            g[b].push_back(a);
        }
        


        dp.assign(n + 1, vector<vector<int>>(k + 2, vector<int>(k + 2, 0)));

        
        dfs(1, 0 ); 

         

        int ans = 0;
        dfs(1, 0);

            int ans = 0;
            for (int a = 0; a <= k + 1; a++) {
                ans = addmod(ans, dp[1][a][0]); // b = -1 stored as 0
            }

            cout << ans << '\n';
         return 0;

    }


    
