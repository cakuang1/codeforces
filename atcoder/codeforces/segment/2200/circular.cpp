 
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

    struct LazySeg {
        int n;
        vector<ll> st, lz;
        
        LazySeg(int _n): n(_n), st(4*n, INF), lz(4*n, 0) {}
    
        // Build from 0‐indexed array `a` of length n
        void build(int v, int tl, int tr, const vector<ll> &a) {
            if (tl == tr) {
                st[v] = a[tl];
            } else {
                int tm = (tl + tr) >> 1;
                build(v<<1,   tl,   tm, a);
                build(v<<1|1, tm+1, tr, a);
                st[v] = min(st[v<<1], st[v<<1|1]);
            }
        }
    
        // Push lazy tag at v down to its children
        void push(int v) {
            ll &lzv = lz[v];
            if (lzv != 0) {
                // apply to children
                for (int u : {v<<1, v<<1|1}) {
                    st[u] += lzv;
                    lz[u] += lzv;
                }
                lzv = 0;
            }
        }
    
        // Range‐add `val` on [l..r]
        void update(int v, int tl, int tr, int l, int r, ll val) {
            if (l > r) return;
            if (l <= tl && tr <= r) {
                st[v] += val;
                lz[v] += val;
            } else {
                push(v);
                int tm = (tl + tr) >> 1;
                if (l <= tm) update(v<<1,   tl,   tm,   l, min(r,tm), val);
                if (r >  tm) update(v<<1|1, tm+1, tr, max(l,tm+1), r, val);
                st[v] = min(st[v<<1], st[v<<1|1]);
            }
        }
    
        // Range‐min on [l..r]
        ll query(int v, int tl, int tr, int l, int r) {
            if (l > r) return INF;
            if (l <= tl && tr <= r) {
                return st[v];
            }
            push(v);
            int tm = (tl + tr) >> 1;
            ll ans = INF;
            if (l <= tm) ans = min(ans, query(v<<1,   tl,   tm,   l, min(r,tm)));
            if (r >  tm) ans = min(ans, query(v<<1|1, tm+1, tr, max(l,tm+1), r));
            return ans;
        }
    };
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  

        int n; cin >> n; 
        vector<ll> arr(n);
        for (int i = 0 ; i < n; i ++) {
            cin >> arr[i]; 
        }
        LazySeg seg(n);
        seg.build(1, 0, n-1, arr);
        int q;
        cin >> q; 
        string line;
        getline(cin, line); 
        while (q  -- ) {
            getline(cin , line);
            stringstream ss(line);
            vector<ll> tok; 
            int x; 
            while (ss >> x) {
                tok.push_back(x); 
            }
            if (tok.size() == 2) {
                if (tok[1] < tok[0]) {
                    int one = seg.query(1,0,n - 1, tok[0] , n - 1);
                    int two = seg.query(1,0,n - 1, 0 , tok[1]);
                    cout << min(one,two) << endl;
                } else {
                    cout << seg.query(1,0,n - 1, tok[0] , tok[1]) << endl;
                }
            } else {
                if (tok[1] < tok[0]) {
                    seg.update(1,0,n - 1, tok[0] , n - 1,tok[2]);
                    seg.update(1,0,n - 1, 0 , tok[1],tok[2]);
                } else {
                    seg.update(1,0,n - 1, tok[0] , tok[1],tok[2]);
                }
            }
        }
        // does this work 
        return 0;
    }
    