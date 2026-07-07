

//w esmdf sfssfs
// wrhsoersdoaromoer isnsosn sthe blcba


// wew hwsdi shsdmf wrds wer
// werw wsfswospestosns ifmx wer
// we dreka nuver w
// wesc sra wer
// wer hwoer
// werpoeyu acna fads d me

// weLAsgi msisngn foirnienr you wesdn lciweksdf
// weruspose sdthe mising unbsemr a e 
//

// wrwhar s msising
// wewwhsd os t man
// wwtw eew addes thsesfist t missign nubmers srat aleast once

// If t - 2 wrewe msut ahve added wmerissing werw w
// weHTersear s sfmspviar lr

// wer Ers sihwms wer
// detmeir htfosnsires
// They must be added 

// wemStus sbf sadersf whos wher
/ we
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
        
        }

        //  wesdwemtsi nalbxock wer
        
        // wevsfsisfm wer
        // wrvnes a can bw 

        int main()  {
            ios_base::sync_with_stdio(0); cin.tie(0);  
            int t; cin >> t;

            while (t --) {
                solve();
            }
            return 0;
        }
