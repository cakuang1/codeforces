 
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
    int n; 
    const int MAXN = 100001;
    vector<int> adj[MAXN]; 
    int col[MAXN]; 
    map<int,int> m[MAXN]; 
    int domcount[MAXN];
    int domsum[MAXN];
    
    void dfs(int a,int p){
        // 1) recurse into children first
        for(int c: adj[a]){
            if(c==p) continue;
            dfs(c,a);
        }
    
        // 2) start m[a] with just your own color
        m[a].clear();
        m[a].insert({ col[a], 1 });
        domcount[a] = 1;
        domsum[a]   = col[a];
    
        // 3) merge each child with small-to-large
        for(int c: adj[a]){
            if(c==p) continue;
            if(m[c].size() > m[a].size())
                m[a].swap(m[c]);
            for(auto &kv : m[c]){
                int color = kv.first, freq = kv.second;
                int &newf = m[a][color];
                newf += freq;
    
                if(newf == domcount[a]) {
                    domsum[a] += color;
                }
                else if(newf > domcount[a]) {
                    domcount[a] = newf;
                    domsum[a]   = color;
                }
            } 
            
            // optional: free m[c] if you won't revisit it
            // m[c].clear();
        }
    }

    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        cin >> n; 
        for (int i = 1 ; i <=  n; i ++) {
            cin >> col[i]; 
        }
        
        for (int i = 0 ; i < n -1 ; i ++) {
            int a,b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        dfs(1,0);
        
        for(int i=1;i<=n;i++){
            cout << domsum[i] << " ";
        }
         
        return 0;
    }
    