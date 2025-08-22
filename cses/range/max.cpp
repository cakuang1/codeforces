#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll sum, pref, suff, best;
};

int n, q;
vector<ll> x;
vector<Node> seg;  // size 4*n

Node merge(const Node &L, const Node &R) {
    Node P;
    P.sum  = L.sum + R.sum;
    P.pref = max(L.pref, L.sum + R.pref);
    P.suff = max(R.suff, R.sum + L.suff);
    P.best = max({ L.best, R.best, L.suff + R.pref });
    return P;
}

void build(int idx, int l, int r) {
    if (l == r) {
        ll v = x[l];
        seg[idx] = { v, max(0LL,v), max(0LL,v), max(0LL,v) };
    } else {
        int m = (l+r)/2;
        build(idx*2,   l, m);
        build(idx*2+1, m+1, r);
        seg[idx] = merge(seg[idx*2], seg[idx*2+1]);
    }
}

// query on [ql..qr], current node covers [l..r]
Node query(int idx, int l, int r, int ql, int qr) {
    if (ql<=l && r<=qr) {
        return seg[idx];
    }
    int m = (l+r)/2;
    if (qr <= m) return query(idx*2,   l, m, ql, qr);
    if (ql >  m) return query(idx*2+1, m+1, r, ql, qr);
    Node L = query(idx*2,   l, m,   ql, qr);
    Node R = query(idx*2+1, m+1, r, ql, qr);
    return merge(L,R);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    x.resize(n+1);
    for(int i = 1; i <= n; i++){
        cin >> x[i];
    }

    seg.resize(4*n);
    build(1, 1, n);

    while(q--){
        int a, b;
        cin >> a >> b;
        Node ans = query(1, 1, n, a, b);
        cout << ans.best << "\n";
    }
    return 0;
}
