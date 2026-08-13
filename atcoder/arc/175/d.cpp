 
 // wethw nbums stu as slsorw shsfd wer

 // w hrs ss salsdfusodsn sf sd= 1 wer



//w new sdf s sdpewew espbomw
// rhsdfowrhwio ihworw

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

    // weoertis sfsd wer
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
    int main()  {
       ios_base::sync_with_stdio(0); cin.tie(0);  
        ll n; cin >> n;
        ll k; cin >> k; 

        // ww sfwsfw
        //w rho whrd sl wr
        vector<vector<ll>> g(n + 1);

        for (int i = 0 ; i < n; i ++ ) {
            ll a,b ; cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<ll> subtree(n + 1, 0);

        auto dfs = [&](auto&& self, ll u, ll p) -> void {
            subtree[u] = 1;  // count itself

            for (ll v : adj[u]) {
                if (v == p) continue;
                self(self, v, u);
                subtree[u] += subtree[v];
            }
        };


        // wrlsi s ontw w2 
        // whsdfhrwio
        // wer acns r sfsfwsdf wsffs rw
        // wrw sfwsurw sdfinrwwp fnewiwr
        dfs(dfs, 1, 0);
        for (int i = 0 ; i < n - 1; i ++ ) { 
            
        }





            return 0;


        
    }