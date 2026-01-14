
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
        if (a < 0)45 return 0;
        if (b < 0) return 0;
        ll cur = facs[a];
        cur = mul(cur, facInvs[b]);
        cur = mul(cur, facInvs[a-b]);
        return cur;
    }



    void initFacs() {
        facs[0] = 1;
        facInvs[0] = 1;
        for (int i = 1 ; i < MOD ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }
    ll  dp[100001][2]; 

    // the number 
    
    // all paths need to be even
    // place casino or dont place 
    
    void dfs(int v, int p , auto & adj ) {
        ll evendontpaint = 1;
        ll odddontpaint = 1;
        for (int a : adj[v]) {
            if (a == p) continue; 
            dfs(a,v ,adj); 
            evendontpoint *= dp[a][0];
            odddontpaint *= dp

        }


        // withthe last w



        dp[v][0] = even;
        dp[v][1] = odd; 

        
        
        
    }
    
    int main() {
        ios_base::sync_with_stdio(0); cin.tie(0);    
        int n ; cin >> n;
        vector<vector<int>> dp(n + 1);
        for (int i = 0 ; i < n- 1; i ++) {
            int a , b ; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        } 

        
        return 0;
    }
     

    // doesn t    