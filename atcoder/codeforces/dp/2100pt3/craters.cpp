 
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
    const int maxm = 4005; 
    int n;
    int id[maxm][maxm];
    int dp[maxm][maxm];
    int vis[maxm][maxm];
    vector<int> gl[maxm];
    int dfs(int l, int r) {
        if (l >=r ) {
            return 0;
        }  
        if (dp[l][r] != -1) {
            return dp[l][r]; 
        }
        dp[l][r] = dfs(l + 1, r);
        for (int nr : gl[l]) {
            if (nr < r) {
                if (dp[l][r] < dfs(l,nr ) + dfs(nr,r)) {
                    dp[l][r] = dfs(l,nr ) +  dfs(nr,r); 
                    vis[l][r] = nr; 
                } 
            }
        }
            
        
        return dp[l][r] += (id[l][r] != -1 ? 1 : 0); 
    }
    


    void output(int l , int r ) {
        if (l >= r) {
            return; 
        }
        if (id[l][r] != -1) {
            cout << id[l][r] << ' ';  
        } 
        if (vis[l][r] == -1) {
            output(l + 1, r);
        } else{
            output(l,vis[l][r]);
            output(vis[l][r],r);
        }
    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        cin >> n; 
        memset(id, -1, sizeof(id)); 
        memset(dp, -1, sizeof(dp)); 
        memset(vis, -1, sizeof(vis)); 
        int c = 0;
        vector<int> s;
        vector<pair<int,int>> p(n);
        for (int i = 0 ; i < n; i ++) {
            int c ,d ; cin >> c >> d;
            int a =  c - d;
            int  b = c + d; 
            s.push_back(a);
            s.push_back(b);
            p[i].first = a;
            p[i].second = b;
        }
        sort(s.begin() , s.end()); 
        auto it = unique(s.begin(), s.end());
        s.erase(it,s.end());
        int u = s.size(); 
        map<int,int> m;
        for (int i = 1 ; i <= u  ; i ++) {
            m[s[i - 1]] = i;  
        }
        for (int i = 0 ;i < n; i ++) {
            p[i].first = m[p[i].first];
            p[i].second= m[p[i].second];
            gl[p[i].first].push_back(p[i].second); 
            id[p[i].first][p[i].second] = i + 1; 
        }
        cout << dfs(1,u) << endl; 
        output(1,u);
        return 0;
    }
    