#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// ---- Lazy‐Segment‐Tree for range‐assign + range‐OR‐query/popcount ----
struct SegTree {
    int n;
    vector<ull> seg, lazy;
    vector<bool> marked;
    SegTree(int _n): n(_n) {
        seg.assign(4*n, 0);
        lazy.assign(4*n, 0);
        marked.assign(4*n, false);
    }
    void push(int v, int l, int r) {
        if (!marked[v]) return;
        seg[v] = lazy[v];
        if (l < r) {
            for (int c : {v<<1, v<<1|1}) {
                marked[c] = true;
                lazy[c]   = lazy[v];
            }
        }
        marked[v] = false;
    }
    void build(int v, int l, int r, vector<ull> &flat) {
        if (l == r) {
            seg[v] = flat[l];
            return;
        }
        int m = (l+r)>>1;
        build(v<<1,   l, m, flat);
        build(v<<1|1, m+1, r, flat);
        seg[v] = seg[v<<1] | seg[v<<1|1];
    }
    void upd(int v, int l, int r, int ql, int qr, ull mask) {
        push(v,l,r);
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            marked[v] = true;
            lazy[v]   = mask;
            push(v,l,r);
            return;
        }
        int m = (l+r)>>1;
        upd(v<<1,   l, m, ql, qr, mask);
        upd(v<<1|1, m+1, r, ql, qr, mask);
        seg[v] = seg[v<<1] | seg[v<<1|1];
    }
    ull qry(int v, int l, int r, int ql, int qr) {
        push(v,l,r);
        if (qr < l || r < ql) return 0ULL;
        if (ql <= l && r <= qr) return seg[v];
        int m = (l+r)>>1;
        return qry(v<<1,   l, m, ql, qr)
             | qry(v<<1|1, m+1, r, ql, qr);
    }
    // wrappers:
    void build(vector<ull> &flat) { build(1,1,n,flat); }
    void update(int l, int r, ull mask) { upd(1,1,n,l,r,mask); }
    int query_popcount(int l, int r) {
        ull x = qry(1,1,n,l,r);
        return __builtin_popcountll(x);
    }
};

// ---- Euler Tour flattening ----
static const int MAXN = 400000;
vector<int> adj[MAXN+1];
int n, m;
int tin[MAXN+1], tout[MAXN+1];
ull arr_val[MAXN+1];
int timer = 0;
vector<ull> flat; // 1..n

void dfs(int u, int p) {
    tin[u] = ++timer;
    flat[timer] = arr_val[u];
    for (int v: adj[u]) {
        if (v == p) continue;
        dfs(v,u);
    }
    tout[u] = timer;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    // read initial bitsets
    for(int i = 1; i <= n; i++){
        int c; 
        cin >> c;
        arr_val[i] = (1ULL << c);
    }
    // read tree edges
    for(int i = 0; i < n-1; i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    flat.assign(n+1, 0ULL);
    dfs(1, 0);

    // 2) Build lazy‐segtree on flat[1..n]
    SegTree st(n);
    st.build(flat);

    // 3) Process m operations:
    //    Format (example): 
    //      type=1:   1 u newColor    (assign subtree u to mask=(1<<newColor))
    //      type=2:   2 u              (query popcount over subtree u)
    while(m--){
        int type; 
        cin >> type;
        if(type == 1){
            int u, c;
            cin >> u >> c;
            ull mask = (1ULL << c);
            st.update(tin[u], tout[u], mask);
        } else {
            int u; 
            cin >> u;
            int ans = st.query_popcount(tin[u], tout[u]);
            cout << ans << "\n";
        }
    }
    
    return 0;
}
