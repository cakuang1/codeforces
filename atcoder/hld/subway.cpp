#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1000000007;
const ll INF = (ll)4e18;

// -------------------- (optional) mod / combinatorics helpers --------------------
ll modExp(ll base, ll power) {
    ll res = 1 % MOD;
    base %= MOD;
    while (power > 0) {
        if (power & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        power >>= 1;
    }
    return res;
}
ll inv(ll base) { return modExp(base, MOD - 2); }

ll mul(ll A, ll B) { return (A * B) % MOD; }
ll addm(ll A, ll B) { return (A + B) % MOD; }
ll subm(ll A, ll B) { return (A - B + MOD) % MOD; }
ll dvd(ll A, ll B) { return mul(A, inv(B)); }

// If you don't need combinatorics, you can delete this whole section.
const int MX = 1000001;
static ll facs[MX];
static ll facInvs[MX];

ll choose(ll a, ll b) {
    if (b > a || a < 0 || b < 0) return 0;
    ll cur = facs[a];
    cur = mul(cur, facInvs[b]);
    cur = mul(cur, facInvs[a - b]);
    return cur;
}
void initFacs() {
    facs[0] = 1;
    facInvs[0] = 1;
    for (int i = 1; i < MX; i++) {
        facs[i] = (facs[i - 1] * i) % MOD;
        facInvs[i] = inv(facs[i]);
    }
}

// -------------------- HLD + Lazy SegTree --------------------
static const int MAXN = 100000 + 5;

int n, q;
vector<int> g[MAXN];

int parentArr[MAXN], heavy[MAXN], head[MAXN], pos[MAXN], depthArr[MAXN];
int sz[MAXN];
int cur_pos = 1;

void dfs_sz(int root) {
    // iterative parent/depth + order
    vector<int> st;
    st.reserve(n);
    st.push_back(root);
    parentArr[root] = 0;
    depthArr[root] = 1;

    vector<int> order;
    order.reserve(n);

    while (!st.empty()) {
        int v = st.back();
        st.pop_back();
        order.push_back(v);
        for (int to : g[v]) {
            if (to == parentArr[v]) continue;
            parentArr[to] = v;
            depthArr[to] = depthArr[v] + 1;
            st.push_back(to);
        }
    }

    // postorder for subtree sizes + heavy child
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int v = order[i];
        sz[v] = 1;
        heavy[v] = -1;
        int best = 0;
        for (int to : g[v]) {
            if (to == parentArr[v]) continue;
            sz[v] += sz[to];
            if (sz[to] > best) {
                best = sz[to];
                heavy[v] = to;
            }
        }
    }
}

void decompose(int root) {
    // iterative decomposition:
    // walk heavy paths assigning positions, push light children as new heads
    vector<pair<int,int>> st;
    st.reserve(n);
    st.push_back({root, root}); // (node, head)

    while (!st.empty()) {
        auto [v, h] = st.back();
        st.pop_back();

        int cur = v;
        int curHead = h;
        while (cur != -1) {
            head[cur] = curHead;
            pos[cur] = cur_pos++;

            // push light children as separate chains
            for (int to : g[cur]) {
                if (to == parentArr[cur] || to == heavy[cur]) continue;
                st.push_back({to, to});
            }

            cur = heavy[cur];
        }
    }
}

struct LazySegTree {
    int n;
    vector<long long> seg, lazy;

    LazySegTree(int n = 0) : n(n) {
        seg.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);
    }

    void build(int p, int l, int r, const vector<long long> &base) {
        if (l == r) {
            seg[p] = base[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, base);
        build(p << 1 | 1, m + 1, r, base);
        seg[p] = seg[p << 1] + seg[p << 1 | 1];
    }

    inline void apply(int p, int l, int r, long long v) {
        seg[p] += (r - l + 1) * v;
        lazy[p] += v;
    }

    void push(int p, int l, int r) {
        if (lazy[p] == 0 || l == r) return;
        int m = (l + r) >> 1;
        apply(p << 1, l, m, lazy[p]);
        apply(p << 1 | 1, m + 1, r, lazy[p]);
        lazy[p] = 0;
    }

    void range_add(int p, int l, int r, int ql, int qr, long long v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(p, l, r, v);
            return;
        }
        push(p, l, r);
        int m = (l + r) >> 1;
        range_add(p << 1, l, m, ql, qr, v);
        range_add(p << 1 | 1, m + 1, r, ql, qr, v);
        seg[p] = seg[p << 1] + seg[p << 1 | 1];
    }

    long long range_sum(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return seg[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        return range_sum(p << 1, l, m, ql, qr)
             + range_sum(p << 1 | 1, m + 1, r, ql, qr);
    }
};

void path_add(int u, int v, long long x, LazySegTree &seg) {
    while (head[u] != head[v]) {
        if (depthArr[head[u]] < depthArr[head[v]]) swap(u, v);
        int h = head[u];
        seg.range_add(1, 1, n, pos[h], pos[u], x);
        u = parentArr[h];
    }
    if (depthArr[u] > depthArr[v]) swap(u, v);
    seg.range_add(1, 1, n, pos[u], pos[v], x);
}

long long path_sum(int u, int v, LazySegTree &seg) {
    long long res = 0;
    while (head[u] != head[v]) {
        if (depthArr[head[u]] < depthArr[head[v]]) swap(u, v);
        int h = head[u];
        res += seg.range_sum(1, 1, n, pos[h], pos[u]);
        u = parentArr[h];
    }
    if (depthArr[u] > depthArr[v]) swap(u, v);
    res += seg.range_sum(1, 1, n, pos[u], pos[v]);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // build HLD
    cur_pos = 1;
    dfs_sz(1);
    decompose(1);

    // segtree over positions [1..n]
    vector<ll> base(n + 1, 0);
    LazySegTree seg(n);
    seg.build(1, 1, n, base);

    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        path_add(a, b, 1, seg);
        cout << path_sum(c, d, seg) << '\n';
        path_add(a, b, -1, seg);
    }

    return 0;
}


// sd osths weprwo jww sdf wheorwrwer