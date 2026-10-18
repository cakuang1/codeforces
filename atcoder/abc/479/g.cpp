    
    //  rpd rs sos ein wer
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

// rw wsdfwriw so rwid wr

// wwsdf wlriwnw


// wfiw wesom lsisen 


// 

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

        return 0;
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
    

    // wrss sse slf heow lsisn wr
    
    //w erthsi ssh ower ewlrsidn ewr
    //w ershwts fslfsinw
    
    // woewtwe arewor sginalr spotiwn w

    // (a1 .... an);
    // (); 

    // 

    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n;
        cin >> n;
        vector<int> a(n); 
        vector<int> b(n);
        
        for (int i = 0 ; i < n; i ++ ) {
            cin >> a[i]; 
        }

        // fixes the arisos wer
    
        // werwehtsi srsintis fnset fit in some lien 

        
        // 
        // weridsn wersdi lbnapd iwornw

        // wadsdso rso i sisf welru w
        
        // werwhsd ewrsd iwern sdf wer welruw
        



    
        // x = [a1 + c1 ..... an + cn];
        // y = [b1 + d1 ..... w];

        //  adj surs erpais wrw
        // tis mrakwkew ew

    
        // wrw ssf werls owprw
        
        / this msrskns rew
        
        //w dsots wi wemr wer
        // xiyj = xjyi;  
        // c[]
        for () { 
        }
        return 0;
    }
