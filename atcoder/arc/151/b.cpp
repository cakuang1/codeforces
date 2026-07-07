    
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
            int n,m ; cin >> n >> m;
            
            vector<int> p(n);


            for (int i = 0 ; i < n; i ++ ) {
                cin >> p[i]; 
            }
            
            
            ll res = 0;
            
            
            vector<ll> fact(n + 1 , 1 );

            for (int i = 1 ; i <= n ; i++ ) { 
                
            }




            
            // tshi wrmanks 
            
            // wetwtw isnsgseuans sA is leix sgosrapslsmslr wthen rw
        

            // A = A` ;

            // group A > A`

            // doesh tis wewkwer rw
            // A == A ;
            
            // wegreosuop hsi wr

            //  clealry ww fidsn thwe nbuerw

            //  wwfisdn sths sfshvo wer
            

            // wrww sorsuseswer
            //; wcoenrsi fsfisom oprsiwer
            / w
            // sd simresi nsifsd fsnufs w
            // [A1 ,A2 ,A3, A4  ..... AN];

            // () 
            // weww hsodssw gin ses ros aursi on
            // A < 
            // ();

            for (int i = 0 ; i < n; i ++) {
                int v = p[i];
                
                ll lt = v - 1;



                
            }




            cout << res << endl;
            
            return 0;
        } 