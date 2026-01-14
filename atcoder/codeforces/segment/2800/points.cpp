#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// sentinel for “empty bucket”
static constexpr int NEG_INF = -1;

struct SegTree {
    int n;
    vector<int> t;   // t[v] = max y in this node’s [tl..tr] buckets, or NEG_INF

    SegTree(int _n): n(_n), t(4*_n, NEG_INF) {}

    // point-update bucket `pos` to new maximum `val` (or NEG_INF if empty)
    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) >> 1;
            if (pos <= tm) update(v<<1,   tl,   tm, pos, val);
            else          update(v<<1|1, tm+1, tr, pos, val);
            t[v] = max(t[v<<1], t[v<<1|1]);
        }
    }

    // find the leftmost index >= L whose t[..] > y0, or -1 if none
    int find_first(int v, int tl, int tr, int L, int y0) {
        if (tr < L || t[v] <= y0) return -1;           // no candidate here
        if (tl == tr)           return tl;             // leaf with t[v] > y0
        int tm = (tl + tr) >> 1;
        int res = find_first(v<<1,   tl,   tm,   L, y0);
        if (res != -1) return res;
        return find_first(v<<1|1, tm+1, tr,   L, y0);
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    struct Query { string type; int a, b; };
    vector<Query> qs(q);
    set<int> xs;
    for (int i = 0; i < q; i++) {
        cin >> qs[i].type >> qs[i].a >> qs[i].b;
        xs.insert(qs[i].a);
    }

    // compress x → [0..N-1], and build inverse map
    int N = xs.size();
    unordered_map<int,int> comp; comp.reserve(N);
    vector<int> inv(N);
    int idx = 0;
    for (int x : xs) {
        comp[x]  = idx;
        inv[idx] = x;
        idx++;
    }

    // per-x bucket of y's
    vector< set<int> > ys(N);
    SegTree st(N);

    for (auto &Q : qs) {
        int xi = comp[Q.a];
        if (Q.type == "add") {
            ys[xi].insert(Q.b);
            int mx = *ys[xi].rbegin();
            st.update(1, 0, N-1, xi, mx);
        }
        
        else if (Q.type == "remove") {
            ys[xi].erase(Q.b);
            int mx = ys[xi].empty() ? NEG_INF : *ys[xi].rbegin();
            st.update(1, 0, N-1, xi, mx);
        }
        else {  // find
            // 1) find first bucket > xi whose max y > Q.b
            int bi = st.find_first(1, 0, N-1, xi+1, Q.b);
            if (bi == -1) {
                cout << -1 << "\n";
            } else {
                int orig_x = inv[bi];
                // 2) within that bucket, pick the smallest y > Q.b
                auto it = ys[bi].upper_bound(Q.b);
                // guaranteed it != end() since t[bi] > Q.b
                cout << orig_x << " " << *it << "\n";
            }
        }
    }

    return 0;
}
