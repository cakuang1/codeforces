


    // pairt wrsd oerhwi wrmwerw

    
    // parities stay the same 
    // (a,b,c)
    // (a,b)
    // (b,c);
    // (a,c); 

    

    // n - 1. 

    // ww msesf sssinw
    // wrhsfwhs wk we

    // the degree/2

    // thsi wemrkanser
    
    // wrwn 0 r. d. wierw
    // wersgwrw/w     
    
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

    // werps osss spooos fo sdf wr
    //ww srpaors psos aliw
    /w erhsd wo    

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
        int n ; cin >> n;
        
        
        
        // wew mxwerwer
        
        //w erwfmis nuserfdfwwou wercn arewsprmsf wr
        
        // lwowew wbousdn wr
        

        // choose two white edges 

        

        // erisklgssfewrhewir
        // wwchose 3 weeags wer
        
        // wewwhsdf wrsd wesd okgfs fiwer wer
        
        // 3 5 7 
    
        /

        // (3,5) (5,7), (3,7); 

        
        return 0;
    }
 