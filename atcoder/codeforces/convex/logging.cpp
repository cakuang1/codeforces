#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = LLONG_MAX/4;

// A line y = m*x + c
struct Line {
    ll m, c;
    ll eval(ll x) const { return m*x + c; }
};

// Li Chao tree over a fixed set of x-coordinates (the a[i]s)
struct LiChao {
    int n;                  // number of distinct x’s
    vector<ll> xs;          // sorted, unique a[i]
    vector<Line> seg;       // size = 4*n
    LiChao(vector<ll> const &coords) {
        xs = coords;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        
        // 
        n = xs.size();
        seg.assign(4*n, {0, INF});
    }
    
    
    void insert(Line nw, int o, int l, int r) {
        int m = (l + r) >> 1;
        ll xm = xs[m];
        // keep in seg[o] the line that is *smaller* at xm
        if (nw.eval(xm) < seg[o].eval(xm))
            swap(nw, seg[o]);
        if (r - l == 1) return;
        ll xl = xs[l], xr = xs[r-1];
        // the loser `nw` might still win on one half
        if (nw.eval(xl) < seg[o].eval(xl))
            insert(nw, 2*o+1, l, m);
        else if (nw.eval(xr) < seg[o].eval(xr))
            insert(nw, 2*o+2, m, r);
    }
    
    
    // erase wand hwo do yuwo e
    ll query(ll x0, int o, int l, int r) const {
        // find the index of x0 in xs
        int idx = int(lower_bound(xs.begin(), xs.end(), x0) - xs.begin());
        ll res = seg[o].eval(x0);
        if (r - l == 1) return res;
        int m = (l + r) >> 1;
        if (idx < m)
            return min(res, query(x0, 2*o+1, l, m));
        else
            return min(res, query(x0, 2*o+2, m, r));
    }
    
    void insert(Line nw) { insert(nw, 0, 0, n); }
    ll query(ll x0) const { return query(x0, 0, 0, n); }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n), b(n); 
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    LiChao lichao(a);

    vector<ll> dp(n, INF);
    dp[0] = 0;
    lichao.insert({ b[0], dp[0]});

    for(int i = 1; i < n; i++){
        dp[i] = lichao.query(a[i]);
        lichao.insert({ b[i], dp[i]});
    }

    cout << dp[n-1] << "\n";
    return 0;
}

