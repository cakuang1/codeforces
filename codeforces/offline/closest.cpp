 
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
    struct SegTreeMin {
        int n;
        vector<long long> t;
        SegTreeMin(int _n): n(_n) {
            t.assign(4*n, INF);
        }
    
        // Set position idx (1≤idx≤n) to value v
        void update(int idx, long long v) {
            update(1, 1, n, idx, v);
        }
    
        // Query minimum on [l..r]
        long long query(int l, int r) {
            return query(1, 1, n, l, r);
        }
    
    private:
        void update(int node, int nl, int nr, int idx, long long v) {
            if (nl == nr) {
                t[node] = v;
                return;
            }
            int mid = (nl + nr) >> 1;
            if (idx <= mid)
                update(node<<1, nl, mid, idx, v);
            else
                update(node<<1|1, mid+1, nr, idx, v);
            t[node] = min(t[node<<1], t[node<<1|1]);
        }
    
        long long query(int node, int nl, int nr, int l, int r) {
            if (r < nl || nr < l) 
                return INF;            // outside → return +∞
            if (l <= nl && nr <= r)
                return t[node];        // fully inside
            int mid = (nl + nr) >> 1;
            return min(
                query(node<<1,    nl,   mid, l, r),
                query(node<<1|1, mid+1, nr, l, r)
            );
        }
    };

    
    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
    
        int n, m;
        cin >> n >> m;
        SegTreeMin st(n + 1);
        vector<ll> arr(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
    
        vector<vector<pair<ll,int>>> q(n + 1);
        vector<ll> res(m);
        for (int i = 0; i < m; i++) {
            int l, r;
            cin >> l >> r;
            q[r].push_back({l, i});
        }
    
        map<ll,int> prev;
        for (int i = 1; i <= n; i++) {
            ll val = arr[i];
            if (prev.count(val)) {
                int p = prev[val];
                ll old = st.query(p, p);
                ll newdist = i - p;
                if (old > newdist) {
                    st.update(p, newdist);
                }
            }
    
            for (auto [l, idx] : q[i]) {
                ll ans = st.query(l, i);
                res[idx] = (ans == INF ? -1 : ans);
            }
            prev[val] = i;
        }
    
        for (int i = 0; i < m; i++) {
            cout << res[i] << "\n";
        }
        return 0;
    }
    