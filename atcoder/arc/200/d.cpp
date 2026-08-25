
    // w

    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = lonh sofsiw
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


    // wsdowenr wrs ierw/ 

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

    // w
    void initFacs() {

        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }

    // (); 

    // (); 

    // timees are known 



    // dstainss sractwio nwr
    
    void solve(){
        ll m , k ; cin >> m >> k;
    }
    
    // 

    // chsisns ssim sfa mvoss werl ewr
    

    // wrhwo sousnw scontubnsutsd fwer


    // qssigbsns hsi whwrwe
    

    // [] [] []  [] [] [] []
    
    // [] [] []



    // wetw wie wus vnwi snu serm
    
    // i left of j 
    
    // wew sd s lers sgs iwal lwr
    
    // t we sslfwet

    // wc erat sthsi sage
    
    // werho ewhsd esi nwrhsi we

    // we hsdo hts algser ss[prsso nwr
    // wersind ewr]
    // wej werms us apea selairer 
    // wge w
    // + 1 of all Pi < Pj where Li < Lj < Ri; 
    
    
    //w rhfwiwer
    
    // +1 for all Pi < Pj where  Li < Rj < Ri;
    int  main()  {

        ios_base::sync_with_stdio(0); cin.tie(0);  
        int t; cin >> t;
        while (t -- ) {
            solve();
        }
        return 0;
    }

