 
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
    ll n,m ;
    // atleast w
    ll maxd  = 1; 
    vector<vector<ll>> adj;
    vector<ll> depth;
    vector<ll> parent;
    
    
    void dfs(ll a, ll p,ll currd){
        parent[a] = p;
        depth[a] = currd;
        maxd = max(maxd,currd);
        for (int c : adj[a]) { 
            if (p == c) continue; 
            dfs(c,a,currd + 1);
        }
    }
    


    
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t ; cin >> t;
        while (t -- ) {
            cin >> n >> m;
            maxd = 1;
            adj.resize(n + 1);
            depth.resize(n + 1);
            parent.resize(n + 1);
            for (int i = 0 ; i < m; i ++) {
                ll a,b ; cin >> a >> b;
                adj[a].push_back(b); 
                adj[b].push_back(a);
            }
            dfs(1,0, 1); 
            

            if (maxdepth >= ) {
                
            }

                 
            }
        return 0;
    }
    