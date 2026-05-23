
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

    // consrindig with gwr
    
    // ar - al = br - bl;
    
    // => ar - br = al - bl ;

    // wetwo sdnsitsoidn wer
    // Twe osdfsa mislsa sonsiso ns
    // whovsofshi er
    /// erwhvsofs wirw wr
    // wrim splrisap utsosatnsic all
    // wD isths wr sf whsovsos iwrw
    // (ar - al) = (br - bl) = (cr - cl);

    
    // wtsdf wshs slnc iwot
    // ar - br =  bl - al;
    
    
    // ar sef wsfs erw

    //wrOTewh sfstnaiso nwer
    // => () + 
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
    // wrw nwws shis works fw
    
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n; cin >> n;
        string s; 
        cin >> s;
        ll total  = (n * (n + 1))/2;
        ll allsame  = 0;        
        for (int t = 0 ; t < 3 ; t ++ ) {
            
            char c1 ,c2;
            
            if (t == 0) {
                c1 = 'A';
                c2 = 'B';
            } else if {
                c1 = 'A';
                c2 = 'C';
            } else {
                c1 = 'B';
                c2 = 'C';
            }
            ll res = 0;
            for (int i =  0; i < n;i ++ ) {
                vector<int> arr(n,0 );
                for (int i = 0 ; i < n; i ++ ){
                    if (s[i] == c1) {
                        arr[i] = 1;                      
                    } else if (s[i] == c2) {
                        arr[i] = -1;
                    }
                }
                
                int currpref = 0;
                map<int,int> seen;
                seen[currpref] ++;
                for (int i = 0 ; i < n; i ++) {
                    currpref +=  arr[i];
                    res += seen[currpref];
                    seen[currpref] ++; 
                }
            }
            total -= res;
        }


        int a,b,c;
        int amb;
        int amc; 
        

        for (int i = 0 ;i < n;  i++ ) {
            if (s[i] == 'A') {
                a ++; 
            } else if (s[i] == 'B') {
                b ++;
            } else {
                c ++; 
            }
            amb = a - b;
            amc = a - c;

            
            
        }
        
        cout <<  total << endl; 
        return 0;

    }