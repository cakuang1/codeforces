#include <bits/stdc++.h>
using namespace std;

struct SegTreeSum {
    using T = long long;
    int n;
    vector<T> st;

    SegTreeSum() : n(0) {}
    explicit SegTreeSum(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        st.assign(4 * n, 0);
    }

    void build(const vector<T>& a) { build(1, 0, n - 1, a); }

    void build(int p, int l, int r, const vector<T>& a) {
        if (l == r) {
            st[p] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        st[p] = st[p << 1] + st[p << 1 | 1];
    }

    // point set: a[idx] = val
    void point_set(int idx, T val) { point_set(1, 0, n - 1, idx, val); }

    void point_set(int p, int l, int r, int idx, T val) {
        if (l == r) {
            st[p] = val;
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) point_set(p << 1, l, m, idx, val);
        else point_set(p << 1 | 1, m + 1, r, idx, val);
        st[p] = st[p << 1] + st[p << 1 | 1];
    }

    // point add: a[idx] += delta
    void point_add(int idx, T delta) { point_add(1, 0, n - 1, idx, delta); }

    void point_add(int p, int l, int r, int idx, T delta) {
        if (l == r) {
            st[p] += delta;
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) point_add(p << 1, l, m, idx, delta);
        else point_add(p << 1 | 1, m + 1, r, idx, delta);
        st[p] = st[p << 1] + st[p << 1 | 1];
    }

    // range sum query on [ql, qr]
    T query(int ql, int qr) { return query(1, 0, n - 1, ql, qr); }

    T query(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0; // identity for sum
        if (ql <= l && r <= qr) return st[p];
        int m = (l + r) >> 1;
        return query(p << 1, l, m, ql, qr) + query(p << 1 | 1, m + 1, r, ql, qr);
    }

};

struct HLD {
    int n;
    vector<vector<int>> g;
    
    vector<int> parent,depth,heavy,head,pos,sz; 


    int cur_pos; 
    

    vector<ll> base;
    

    HLD() : n(0), cur_pos(0) {}
    explicit HLD(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
        parent.assign(n, -1);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        sz.assign(n, 0);
        cur_pos = 0;
        base.assign(n, 0);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int dfs(int v, int p) {
        parent[v] = p;
        sz[v] = 1;
        int max_sub = 0;

        for (int to : g[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            int sub = dfs(to, v);
            sz[v] += sub;
            if (sub > max_sub) {
                max_sub = sub;
                heavy[v] = to;
            }
        }
        return sz[v];
    }
    void decompose(int v, int h) {
        head[v] = h;
        pos[v] = cur_pos++;

        if (heavy[v] != -1) {
            decompose(heavy[v], h);
        }
        for (int to : g[v]) {
            if (to == parent[v] || to == heavy[v]) continue;
            decompose(to, to);
        }
    }



    
    void build(int root, const vector<long long>& vals) {
        if ((int)vals.size() != n) throw runtime_error("vals size must be n");
        dfs(root, -1);
        decompose(root, root);

        for (int v = 0; v < n; v++) base[pos[v]] = vals[v];
        // wthes nwerwhat wer
        seg.init(n);
        seg.build(base);
    }



    int lca(int a, int b) { 
        while (head[a] != head[b]) {
            if (depth[head[a]] > depth[head[b]])  {
                swap(a,b);
            }
            b = parent[head[b]]; 
        }        
        return (depth[a] < depth[b] ? a : b); 
    }


    ll path_sum(int a, int b ) {
        ll res = 0 ;
        while (head[a] != head[b]) {
            if (depth[head[a]] > depth[head[b]])  {
                swap(a,b);
            }
            
            res += seg.query(pos[head[b]], pos[b]);
            b = parent[];
         }

        if (depth[a] > depth[b]) swap(a,b);
        
        res += seg.query(pos[a] , pos[b]);
        return res; 
    }

    

    // w sdon tweht ch isdlrwe endsgpotiwn erw
    
    // wevalu ares slsudps wersd fwe
    
    // wersot serahc vlaus on teh childrwer wernspoti n
    // f or w ach node w  wr
    // wewh OWtso surpats se tres rrs urck wetl wrw
    
