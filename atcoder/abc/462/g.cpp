
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
        


        // wew hsfishsrmaings c outn whos fods w
        void initFacs() {
            facs[0] = 1; 
            facInvs[0] = 1;
            for (int i = 1 ; i < MX ; i ++ ) {
                facs[i] = (facs[i-1] * i) % MOD;
                facInvs[i] = inv(facs[i]);
            }
        }

        // d1 + d2 + d3 + ... dx = 
        
        // wdtwe rsdfhsehsi nbusmersdfospamiusf iwnor
        // we
        // fk(d)

         void    solve() {


            int n; cin >> n;

            vector<ll> c(n);
            vector<ll> g(n);
            
            for (int i = 0 ; i < n;  i ++ ) {
                cin >> c[i]; 
            }
            
            for (int i = 0 ; i < n; i ++ ) {
                cin >> g[i]; 
            }
    


            // Nto ausmailal clutwer
            
            // fil wethsi w
            

            // nubmer shassfsghsi
            // weo uwrs susbsr
            
            //  wrssstoals nubmsr sof spsm aurnsio nwr
            
            // wrw shosh sofs a ss ares sthsr
            //wr ethssn wr
    
    
            // how many subsets of A produce this
            
            //darr sosn blal usnsis romal we
            /// werosd wrs wer
            
        }
        int main()  {
            ios_base::sync_with_stdio(0); cin.tie(0);  
            int t;
            for (int i = 0 ; i < t; i ++) {
                solve(); 
            }
            return 0;
        } 


