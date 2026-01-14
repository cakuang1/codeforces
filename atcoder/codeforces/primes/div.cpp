 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy



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
         
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        ll n; cin >> n;
        
        ll res = 0;
        ll c = n;
        for (ll p = 2; p * p <= c; ++p) {
            if (c % p == 0) {
                int a = 0;
                while (c % p == 0) {
                    ++a;
                    c /= p;
                }
                // maximum distinct e summing <= a:
                ll t = (ll)floor((sqrt(8.0*a + 1) - 1)/2);
                res += t;
            }
        }
        if (c > 1) {
            // one last prime factor with exponent a=1
            res += 1;  
        }
        cout << res << "\n";
        
        return 0;
    }

    // solve for  
    //  we
    
    // 1 + 2 + 3 + 4 <= n 
    
    

