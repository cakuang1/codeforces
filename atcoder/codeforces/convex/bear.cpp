#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct LiChao {
    struct Line { ll m, b; };
    int n;
    vector<Line> st;
    vector<ll> xs;
    LiChao(const vector<ll>& _xs) {
        xs = _xs;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = xs.size();
        st.assign(4*n, {0, (ll)4e18});
    }
    ll eval(const Line &ln, ll x) const {
        return ln.m * x + ln.b;
    }
    void add_line(Line nw, int p, int l, int r) {
        int m = (l + r) >> 1;
        ll xl = xs[l], xm = xs[m];
        bool lef = eval(nw, xl) < eval(st[p], xl);
        bool mid = eval(nw, xm) < eval(st[p], xm);
        if (mid) swap(nw, st[p]);
        if (r - l == 1) return;
        if (lef != mid) add_line(nw, p<<1,   l,  m);
        else            add_line(nw, p<<1|1, m,  r);
    }
    void add_line(ll m, ll b) {
        add_line({m,b}, 1, 0, n);
    }
    ll query(ll xq, int p, int l, int r) const {
        ll res = eval(st[p], xq);
        if (r - l == 1) return res;
        int m = (l + r) >> 1;
        if (xq < xs[m]) return min(res, query(xq, p<<1,   l,  m));
        else            return min(res, query(xq, p<<1|1, m,  r));
    }
    ll query(ll xq) const {
        return query(xq, 1, 0, n);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];

    // Prefix sums P and Q
    vector<ll> P(n+1,0), Q(n+1,0);
    for(int i=1;i<=n;i++){
        P[i] = P[i-1] + a[i];
        Q[i] = Q[i-1] + a[i]*i;
    }

    // Build Li Chao over all P[i]
    LiChao lct(P);

    ll ans = 0;
    // initial line for k=0: m=0, C[0]=Q[0]-0*P[0]=0
    lct.add_line(0, 0);
    
    // you shift wthis up we w
    for(int r=1;r<=n;r++){
        // Query best k for x = P[r]
        ll best = lct.query(P[r]);
        // dp[r] = Q[r] - (k*P[r] + C[k]) = Q[r] - best
        ll cur = Q[r] - best;
        ans = max(ans, cur);
        // Insert new line for k=r => m = r, b = C[r] = Q[r] - r*P[r]
        ll C = Q[r] - r * P[r];
        lct.add_line(r, C);
    }

    cout << ans << "\n";
    return 0;
}
