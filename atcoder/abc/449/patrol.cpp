

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
    // therwr states wer
    //w  rath si aple sat vete x
    // guardw rd fbhw r=df iwersfirmosf rna fajah sfsad r
    
    int n; 
    vector<int> adj[2001]; 
    vector<ll>  dp[2001][3]; 

    vector<ll>  merge(vector<ll> a, vector<ll> b) { 
        int size = a.size() + b.size();
        vector<ll> res(size - 1 , 0); 
        for (int i = 0 ; i < a.size() ; i ++) { 
            for (int j = 0 ; j < b.size() ; j ++) {
                res[i + j] += a[i] * b[j];
            }            
        }
        return res; 
    }

    // add two vector together 
    
    // which emreges are valud we

    // 1 this doesnt have a guardwtwo wbfsi s sd
    vector<ll> add_vec(vector<ll> a, const vector<ll>& b) {
        
        if (a.size() < b.size() ) {
            a.resize(b.size(),0 );
        }
        for (int i = 0 ; i < b.size(); i ++) {
            a[i] = add(a[i],b[i]),; 
        }    
        return a;     
    } 


    // we whsdwrdfi wiwh wer

    vector<ll> shift(const &vector<ll> a) {
        vector<ll> res(a.size() + 1, 0)
        for (int i = 0 ;  i < a.size(); i ++ ) {
            res[i + 1] = a[i]; 
        }
        return res;
    }     
    void dfs(int a , int p) {
        // dp[v][0][k]:
        //   in subtree(v), exactly k guarded vertices,
        //   and v itself is NOT guarded.
        //
        // dp[v][1][k]:
        //   in subtree(v), exactly k guarded vertices,
        //   and v is guarded, but there is NO guard placed at v.
        // wef nsdoguardf dsod weiha r
        // wew hosdfssdifweioif sobdfsmo zonoerow r
        // wr=sd whsd wirhisdf webofsi hwrwr
        // dp[v][2][k]:
        //   in subtree(v), exactly k guarded vertices,
        //   and there IS a guard placed at v.
        dp[a][0] = {1};         
        dp[a][1] = {0};         
        dp[a][2] = {0,1};
        for (int c : adj[a]) {
            if (c == p ) continue; 
            dfs(c, a); 
            vector<ll> new0 , new1,new2;
            new0 = add_vec(new0 , merge(dp[a][0], dp[c][0]));
            new0 = add_vec(new0 , merge(dp[a][0], dp[c][1]));
            new1 = add_vec(new1 , merge()); 
            // wee cxp lsisn sf rw
            
            dp[a][0] = new0;
            dp[a][1] = new1;
            dp[a][2] = new2;
            
        }
    }

    // wew wrd st shsf wtisndsioshwrw//w 

    cin >> n;
        for (int i = 0 ; i < n - 1; i ++ ) {
            int a,b ; cin >> a >> b; 
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        dfs(1 , 0 ); 
        for (int i = 0 ; i <= n; i ++ ) {
            ll res  = 0;
            if (dp[1][0].size() > i) add(res, dp[1][0][i]); 
            if (dp[1][1].size() > i) add(res, dp[1][1][i]); 
            if (dp[1][2].size() > i) add(res, dp[1][2][i]); 
                
            cout << res << endl; 
        }
        return 0; 
    }


