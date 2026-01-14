 
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
    struct Line {
        mutable ll k, m, p;
        bool operator<(const Line& o) const { return k < o.k; }
        bool operator<(ll x)        const { return p < x; }
    };
    
    struct LineContainer : multiset<Line, less<>> {
        static const ll inf = LLONG_MAX;
        // floored division
        ll div(ll a, ll b) {
            return a/b - ((a^b)<0 && a%b);
        }
        // intersects x with next line y; returns true if y is made obsolete
        bool isect(iterator x, iterator y) {
            if (y == end()) { 
                x->p = inf; 
                return false; 
            }
            if (x->k == y->k) 
                x->p = x->m > y->m ? inf : -inf;
            else 
                x->p = div(y->m - x->m, x->k - y->k);
            return x->p >= y->p;
        }
        void add(ll k, ll m) {
            auto z = insert({k,m,0}), y = z++, x = y;
            while (isect(y,z))          z = erase(z);
            if (x!=begin() && isect(--x,y))
                isect(x, y = erase(y));
            while ((y = x)!=begin() && (--x)->p >= y->p)
                isect(x, erase(y));
        }
        // returns max(k*x + m)
        ll query(ll x) {
            assert(!empty());
            auto l = *lower_bound(x);
            return l.k*x + l.m;
        }
    };
    
        
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n; cin >> n; 
        vector<ll> a(n);
        vector<ll> b(n);
        for (int i = 0 ;i < n; i ++ ) {
            cin >> a[i]; 
        }
        for (int i = 0 ; i < n; i ++ ) {
            cin >> b[i];
        }
        vector<ll> dp(n , INT_MAX); 
        LineContainer l;         
        dp[0] =  0;
        l.add(-b[0],-dp[0]);
        for (int i = 1; i < n ; i++ )  {
            ll q = -l.query(a[i]); 
            dp[i] = q; 
            l.add(-b[i],-dp[i]); 
        }
        cout << dp[n - 1] << endl; 
        return 0;
    }
    
    // minimum sum after deploying 