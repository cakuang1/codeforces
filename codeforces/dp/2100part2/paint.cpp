

    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD2 =  998244353; 
    const int MOD = 1000000007;
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
        for (int i = 1 ; i < MOD ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }
    
    // flag is zero? we are choosing k children
    
    // flag is one?, we are choosing  k - 1 children, and the rest   
    void solve2(int node, ,int parent , vector<vector<pair<int,int>>> &adj,vector<vector<int>> &dp )  {
        vector<int> dp1;
        vector<int> dp2;
        for (auto c : adj[node]) {
            if (c.first == parent) {
                continue;
            }           
            solve(c.first, node, adj ,dp);  
            dp0.push_back(dp[c][0]);
            dp1.push_back(dp[c][1]);
        }

        

        for (int )
    }
    void solve()  {
       int n,k; cin >> n >>k ;
        vector<vector<pair<int,int>> adj(n + 1);
        for (int i = 0 ; i < n - 1;  i ++) {
            int a,b,c ; cin >> a >> b >>c;
            adj[a].push_back({b,c});
            adj[b].push_back({a,c});
        } 
        vector<vector<int>> dp(n + 1 , vector<int> )
        solve(1, 0, -1 ,adj , dp); 


            
    }




    int main() {
        ios_base::sync_with_stdio(0); cin.tie(0);    
        int q; cin >> q;

        while (q --) {
            solve(); 
        }
        

        return 0;
    }
    

