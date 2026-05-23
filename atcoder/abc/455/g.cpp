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
        int n;
         cin >> n; 
         int k ;  cin >>k;
         vector<int> arr(n);
         for (int i = 0 ; i < n; i ++ ) {
            cin >> arr[i];
         }
         //  rando mslsina shagin fsodvsrabses. tsapce
         // w rsi sn sosmf svscestsp ace wehosf osd s
         // bk wesi weual o 0 fra l lalues
         // wsdshso wamksfsnf wer
         // dhdsofsfsmossusfls ssfsfshofssfhosfsfsfvossihssfshfvosdfsifesfsfsf
         // h(c) = 
         //w wrwhcxrs c = 0;
         
         // Dwthis sfhwaosk
         // wehososh wirw
         // wf wetsf wtwhi wr
         // rw hsdofos sishf iwrs

    
         // ars somslsisn s sfiswehos sdosh wrksd fwrksdf w
         int l = 0; 

            map<int,int> m;
            vector<int> lb(n); 
            for (int i = 0 ; i < n; i ++) {
                m[arr[i]] ++;
                while (m.rbegin().second > b) {
                    l ++; 
                }
                lb[i] = l;                
            }
            
            // w
            // all counts = 0 mod () 
            // /Thwfnw. hat
            //werwhoss hs wir 
            // Blocks w win tsissfmiwer
            //rwhsofwo r
            // 10^9 + 7
        
            // w[1] + w[2] + .... + w[bk] = 10^9 + 7
            
            

            // w wrshosfsf wr
            // ww whosf soshi ewr
            // sif a anf ontlw siftis ahs hblaue is 0 
            }
        }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t;cin >> t; 
        while (t -- ) {
            solve();
        }
        return 0;
    }