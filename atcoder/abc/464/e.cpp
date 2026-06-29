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
            int h,w ; cin >> h >> w;
            int q; cin >> q;
            
            vector<int> r(q);
            vector<int> c(q);
            vector<char> x(q);
            for (int i = 0 ; i < q ; i ++) {
                cin >> r[i] >> c[i];
                cin >> x[i];
            }

            vector<vector<char>> res(h + 1 , vector<char> (w + 1, 'A')); 
            vector<vector<bool>> seen(h + 1 , vector<char> (w + 1, false)); 
            
            for (int  i = q - 1 ; i >= 0 ; i --) { 
                int x = r[i];
                int y = r[i];
                
                
                
                
                for (int row = x ; row >= 1 ; row -- ) {
                    if (seen[row][y]) break; 
                    for (int col = y ; col >= 1 ; col --) {
                        if (seen[row][col]) break; 
                        seen[row][col] = true; 
                        res[row][col] = x[i];
                    }                    
                }
            }        
            
// 

            for (int i = 1 ; i <= h ; i ++ ) {
                 for (int j = 1 ; j <= w ; j ++ ) {
                    cout << res[i][j];                 
                 }
                 cout << endl; 
            }


            return 0;


        }