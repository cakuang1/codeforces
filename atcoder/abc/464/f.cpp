
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

        
        // total sum 
        
        

        // wus coutwn su wmr
        

        // size of subse
        // wrhos cfosh sfsfirw

        //E Epxcsatiosn fwis hwt
        
        // cnt 
        // pretty werinsan ewr
        // ww wbsersfsifuwrw;
        
        // wfro sosm esusbtes
        


        // cnt sum

        // lef tsids weris hwtw
        
        // prifx sfovsnsussiower
        // contributsio nwris hww
    
        // 
        // cnt[]
        void  initFacs() {
            facs[0] = 1; 
            facInvs[0] = 1;
            for (int i = 1 ; i < MX ; i ++ ) {
                facs[i] = (facs[i-1] * i) % MOD;
                facInvs[i] = inv(facs[i]);
            } 
        }
        int main()  {
            ios_base::sync_with_stdio(0); cin.tie(0);  
            int n, x; cin >> n >> x; 
            vector<ll> a(n);
        
            for (int i = 0  ;i < n; i ++ ) {
                 cin >> a[i];
            }


            // [] ene wrodd wanthwoso hfwk w
            
            int left = n/2;
            int right = n - left;
            
            
                                
            map<ll,ll> freqleft;
            map<ll ,ll> freqright;
            map<ll ,ll> freqtotal;



            for (int i = 0 ; i < (1 << left); i ++ ) {
                ll s = 0;
                for (int j = 0 ;  j < left ; j ++ ) { 
                    if ((1 << j) & i) {
                        s += a[j];                        
                    }     
                }
                freqleft[s] ++;
            }

            for  (int i = 0 ; i < (1 << right); i ++ ) {
                ll s = 0;
                for (int j = 0 ;  j < right ; j ++ ) { 
                    if ((1 << j) & i) {
                        s += a[left + j];                        
                    }     
                }
                freqright[s] ++;                  
            }
            for (auto p : freqleft) { 

            }



            // proboalitwwo fths susbet is what 
            
            // find the total number of permuatiosn wr

            // wharsd wrpbslersi wer
        

            // pbialrists hif whsis sifwhwt
            

            // how mansy sepresmsaanonai hses sathesi persix ser
            

            // contrubsieton wer
            
            // Enumerate the number of subsets with sum < x;
            

            




            return 0;

    
        } 