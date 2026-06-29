    
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

        int digit_sum(ll x) {
            int res = 0;
            while (x > 0) {
                res += x % 10;
                x /= 10; 
            }

            return res;
        }



         
        int main()  {
            ios_base::sync_with_stdio(0); cin.tie(0);  
            int n ; cin >> n;
            

            vector<ll> a(n + 1);
            vector<ll> b(n + 1);


            for (int i = 1; i <= n ; i ++ ) cin >> a[i];
            for (int i = 1; i <= n ; i ++ ) cin >> b[i];
            const int S = 1 << 9;
            vector<vector<ll>> dp(S,vector<ll> (2 ,INF));
            vector<vector<ll>> ndp(S,vector<ll> (2 ,INF));
            vector<ll> R(S,-1), nR(S,-1);
    
            dp[0][0] = 0; // digitSum(L)
            dp[0][1] = 1; // digitSum(L + 1)
            R[0] = 0;
            
            vector<ll> ans(n + 1); 
             for   (int i = 1 ; i <= N ; i ++ ) {
                ndp.assign(S, vector<ll> (2,INF));
                nR.assign(S,-1);
                                
                for (int s = 0 ; s < S ; s ++) {
                    if (dp[s][0] == INF) continue; 

                    for (int b = 0 ; b < 2 ;b ++) {
                        ll c = (b == 0 ? a[i] : b[i]);
                        int ns = ((s << 1) & (S - 1)) | b;
                        ll val = 10 * R[S] + c;

                        ll q = val/M; // entering left 
                        ll nr = val % M;
                        nR[ns] = nr;                        
                        ll cand;
                            if (add wew) {
                                 
                            }
    
                        }
                        
                    }
                

                }
                
            } 
    
            //w erssus p oblais sofars iwsdonetwhewrew/

            // we avs fs aalad sonsidsersd werw
            
            // L + 1

            // Its left + 1 

            // fi youw eadd werown wtwo tsehts snsf we
            // w sthisf smaknsfwr
            / w wer

            return 0;
        } 
