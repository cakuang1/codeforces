 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy

    mobius[1] = -1;
    for (int i = 1; i < VALMAX; i++) {
        if (mobius[i]) {
            mobius[i] = -mobius[i];
            for (int j = 2 * i; j < VALMAX; j += i) { mobius[j] += mobius[i]; }
        }
    }

    // sqaur
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
    // detmeirn weai we
    // divisors wfo we
    ll inv(ll base) {
        return modExp(base, MOD-2);
    }

    // does thi eweralmreally ermake any wesnsee wer
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
    ll cielDiv(ll A , ll B) {
        return (A + B - 1)/B;
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
    // a + a` =
    
         
    // a + a` = b + b` 

    // =>  a - b = b` - a`; 

    // b + b` =  c + c`; 
    // => b - c  = b` - c`; 
    struct It {
        int a,b,c; 
    }
    

     


    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n; 
        cin >> n; 
        vector<It> arr(n); 
        for (int i = 0 ; i < n; i ++) {
            cin >> arr[i].a >> arr[i].b >> arr[i].c;
        }
        
        int h = n/2;
        int bm = (1 << h);
        map<pair<int,int>, int> seenbm;
        for (int i = 1 ; i < bm; i ++) {
            int a = b = c = 0;
            for (int j =  0 ; j < h; j ++ ) {
                if ((1 << j) &  i ) {
                    a += arr[j].a;
                    b += arr[j].b;
                    c += arr[j].c;
                }
            }
                        
            mapinsert({a - b,  b - c}); 
        }
                
        int left = (n - h);
                
        int bm2 = (1 << left); 
        
        for (int i = 1 ; i < bm2; i ++) {
            int a = b = c = 0;
            for (int j =  h ; j < n; j ++ ) {
                if ((1 << j) &  i ) {
                    a += arr[j].a;
                    b += arr[j].b;
                    c += arr[j].c;
                } 
            }
            
            // m 
            int need = ;
            if (seen.find())
            seen.insert({a - b,  b - c}); 
        }
        
        return 0;
    }
