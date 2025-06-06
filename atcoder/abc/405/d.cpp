 
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

    struct Dir {
        int first, second ;
        char c; 
    };
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        
        int h, w ; cin >> h >> w; 
        vector<string> grid(h);
        
        deque<pair<int,int>> q; 
        
        for (int i = 0 ; i <h ; i ++){
            cin >> grid[i];
        }
        for (int i = 0 ; i < h; i ++) {
             for (int j = 0 ; j < w ; j ++) {
                if (grid[i][j] == 'E') {
                    q.push_front({i,j}); 
                }
             }
        }        

    // correct dir‐table:
    vector<Dir> dir = {
        { 1,  0, '^' },
        {-1,  0, 'v' },
        { 0,  1, '<' },
        { 0, -1, '>' }
    };        
    while (!q.empty()) {
            int s = q.size();
            for (int i = 0 ; i < s ; i ++ ) {
                auto f = q.front(); 
                q.pop_front(); 
                for (auto d : dir) {
                    int newx = d.first + f.first;
                    int newy = d.second + f.second;
                    bool withinx = (newx >= 0 && newx < h);
                    bool withiny = (newy >= 0 && newy < w);
                    if (withinx && withiny && grid[newx][newy] == '.') {
                        grid[newx][newy] = d.c; 
                        q.push_back({newx,newy}); 
                    }
                    
                }
            }
        }
        
        // surely 
        for (int i = 0 ; i < h ; i ++) {
            cout << grid[i] << endl;
        }
        
        return 0;
    }
    