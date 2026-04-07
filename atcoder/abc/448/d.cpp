

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
    int n;
            
    vector<int> g[200005]; 
    int a[200005];
    string res[200005];
    map<int,int> m;
    int duplicates = 0; 
    void dfs(int curr , int p ) {

        m[a[curr]] ++;
        if (m[a[curr]] == 2) {
            duplicates ++;
        }

        if (duplicates) {
            res[a] = "Yes";
        } else {
            res[a] = "No"; 
        }
        for (int c  : adj[curr]) {
            if (c == p) continue;
            dfs(c);
        }
        m[a[curr]] --; 
        if (m[a[curr]] == 1) {
            duplicates --; 
        }
    } 
    int main()  {
      
        ios_base::sync_with_stdio(0); cin.tie(0);  
        cin >> n;
        for (int i = 1 ; i <= n; i ++) {
            cin >> a[i];
        }        

        for (int i = 0 ; i < (n - 1) ; i ++) { 
            int a, b; cin >> a >> b; 
            g[a].push_back(b);  
            g[b].push_back(a);  
        }

        dfs(1,0); 

        for (int i = 1 ; i <= n ; i ++) {
            cout << res[i] << endl;              
        }
        return 0;
    }


