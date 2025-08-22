#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Segment‑tree for range‑min, with point‑update
struct SegmentTree {
    int n;
    vector<int> st;
    SegmentTree(int _n=0): n(_n), st(4*_n+4, INT_MAX) {}
    void build(int node, int l, int r, const vector<int>& a) {
        if (l == r) {
            st[node] = a[l];
        } else {
            int m = (l+r)>>1;
            build(node<<1, l, m, a);
            build(node<<1|1, m+1, r, a);
            st[node] = min(st[node<<1], st[node<<1|1]);
        }
    }
    void update(int node, int l, int r, int pos, int val) {
        if (l == r) {
            st[node] = val;
        } else {
            int m = (l+r)>>1;
            if (pos <= m) update(node<<1, l, m, pos, val);
            else          update(node<<1|1, m+1, r, pos, val);
            st[node] = min(st[node<<1], st[node<<1|1]);
        }
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return INT_MAX;
        if (ql <= l && r <= qr) return st[node];
        int m = (l+r)>>1;
        return min(
          query(node<<1,   l, m, ql, qr),
          query(node<<1|1, m+1, r, ql, qr)
        );
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<ll> x(n+1);
    for(int i = 1; i <= n; i++){
        cin >> x[i];
    }

    // For each value v, keep a sorted set of its positions + sentinel (n+1)
    unordered_map<ll, set<int>> pos;
    pos.reserve(n*2);
    for(int i = 1; i <= n; i++){
        pos[x[i]].insert(i);
    }
    for(auto &kv : pos){
        kv.second.insert(n+1);
    }

    // Build next[i] = next occurrence of x[i], or n+1
    vector<int> nxt(n+1);
    for(auto &kv : pos){
        auto &s = kv.second;
        int prev = -1;
        for(int idx : s){
            if (prev != -1 && prev <= n){
                nxt[prev] = idx;
            }
            prev = idx;
        }
    }
    
    // wdoetmeirn wrranges w
    SegmentTree st(n);
    st.build(1, 1, n, nxt);

    while(q--){
        int type;
        cin >> type;
        if (type == 1){
            // update: set x[k] = u
            int k; ll u;
            cin >> k >> u;
            ll old = x[k];
            if (old == u) continue;

            // --- remove k from old's set, fix prev_old → next_old
            {
                auto &s = pos[old];
                auto it = s.find(k);
                auto itn = next(it);
                auto itp = (it == s.begin() ? s.end() : prev(it));
                int nxt_old = *itn;
                if (itp != s.end()){
                    int prev_old = *itp;
                    nxt[prev_old] = nxt_old;
                    st.update(1, 1, n, prev_old, nxt_old);
                }
                s.erase(it);
            }

            // --- insert k into new u's set, fix prev_new → k and k → next_new
            {
                auto &s = pos[u];
                if (s.empty()) s.insert(n+1);
                auto itn = s.lower_bound(k);
                int nxt_new = *itn;
                auto itp = (itn == s.begin() ? s.end() : prev(itn));
                int prev_new = (itp == s.end() ? -1 : *itp);

                nxt[k] = nxt_new;
                st.update(1, 1, n, k, nxt_new);

                if (prev_new != -1 && prev_new <= n){
                    nxt[prev_new] = k;
                    st.update(1, 1, n, prev_new, k);
                }
                s.insert(k);
            }

            x[k] = u;
        }
        else {
            // type 2: query [a,b] distinct?
            int a, b;
            cin >> a >> b;
            // if the minimum next-occurrence in [a,b] is > b, all are distinct
            int mn = st.query(1, 1, n, a, b);
            cout << (mn > b ? "YES\n" : "NO\n");
        }
    }
     
    return 0;
}
