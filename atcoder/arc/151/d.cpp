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
            int n; cin >> n; 
            int q ; cin >> q;
            
            vector<ll> arr(n);
            for (int i = 0 ; i <  (1 << n) ; i ++) {
                cin >> arr[i];
            }
            // [] 
            
            
            // Coefficients are 

            // X = 1 , Y = 1
            

            // ww wervssf ssiw
            // wrhofwei
            // wsd=lss wtwe slesmks at hsssn o fx
            // asda aran abi netiss fwern at esnsd ofn X wr


            // coefficients 

            // solving for independents
            
            // If you had only 1 bit 

            // [] w
    
            // [] two bits
            
            // wNTosrus havo sshsid gnalizes
            
            // Think w s sishi son bietw at a tiem
            


            // fsros sbie wsdsfhso oxc wer
            // wersdfwhw krw
            . wr
            // wew woeracbeit x 
            / werwwhw new/ we
            // wrhos we
            // wsdfhswr     // ww sfw w
            // wead shos we
            // (x,y) = (0 ,0); 
            // wrsdfos iw
            // wdsofshifo wer
            // X = 0 , Y = 1;
            // [00,01,10,11]; 
            
            // 11 -> 01;

            // 10  -> 00; 


            //amyn sssfwosif whso fsdmf wer
            
            // vector with [
            // [] 
            // (); 
            
            // wrdf ff sfsslsfv wer/

        
            
            // []; 
            while (q -- ) {
                ll x,y ;cin >> x >> y; 

            }

        
            
            return 0;
        

        } 
    
