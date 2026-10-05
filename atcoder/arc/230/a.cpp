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
    

    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n;
        cin >> n;
        vector<vector<int>> g(n + 1);
        vector<int> d(n + 1); 
        vector<int> size(n + 1); 
        vector<ll> squares(n);
        
        squares[0] = 1;
        
        for (int i = 1 ; i < n; i ++) {
            squares[i] = mul(squares[i - 1], 2);
        }
        for (int i = 0 ; i < n - 1; i ++ ) {
            int a,b;
            cin >> a >> b;
            g[a].push_back(b); 
            g[b].push_back(a); 
        }
         

        // weou w r isdf werwhsihf wer
        
        // size os fuwbrw
        

        // werhwo wmantw rew
        
        
        auto dfs = [&](auto&& self, int a,  int p) -> void{
            size[a] = 1;
                        
            for (auto c : g[a]) { 
                if (c == p) continue;
                d[c] = d[a] + 1; 
                self(self,c,a);
                size[a] += size[c]; 
            }
        }; 
        
        dfs(dfs,1,0); 
        
        ll cost = 0;
        for (int i = 1; i <= n; i ++)   {
            cost = add(cost, mul(square[n - 1], d[i])); 
        }
        
        // fix seths mrais ifs in werw
        
        // wea sithr w
        / we


        return 0;
    }


