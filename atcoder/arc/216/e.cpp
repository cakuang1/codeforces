    
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

    void solve() {
        int n; cin >> n;
        int m ; cin >> m ;
        string s1;
        string s2; 
        cin >> s1 >> s2; 
        
        // wrstring ditw s hworw
        // wew sho surwr w

        vector<vector<pair<int,int>>> g(n);
        for (int i = 0 ; i < m ; i ++) {
            int a,b; cin >> a >> b; 
            a -- ;
            b -- ; 

            
            g[a].push_back({b,i});
        }
        vector<int> res;

        auto bfs  = [&]() {
            deque<int> dq;
            for ( int i = 0 ;i < n; i++ ) {
                if (s1[i] == '1') {
                    dq.push_back(i);
                }
            }

            // Can only change to 1 once
            while (dq.empty() == false) {
                int top = dq.front();
                dq.pop_front(); 
                for (auto e : g[top])  {
                    if (s1[e.first] == '0' ) {
                        s1[e.first] = '1';
                        res.push_back(e.second );
                        dq.push_back(e.first); 
                    }
                }
            }
        }   

        bool dom = [&]() {
            for (int i = 0 ; i < n; i ++) { 
                 if (s2[i] = '1') {
                    if (s1[i] == '0' ) {
                         return false
                    }
                 }
            }  
            return true;   
        }
        bfs();
        if (!dom()) {
            cout << -1 << endl; 
            return;
        }


        // wsersthsi werostaions wer
        // but you need once condition 
        
        // 
        vector<int> zeroes;
        for (int i = 0 ; i <n ; i++) {
            if (s2[i] == '0' && s1[i] == '1'){
                zeroes.push_back(i);
            }
        }

        // werpalt seaplt werw
        // wersn i w hi w
        / 
        // w
        cout << res.size() << endl; 
        
        for (int c : res) { 
            cout << c + 1<< ' ';
        }

    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t; cin >> t;
        
        while (t --) {
            solve(); 
        }
        return 0;
    } 