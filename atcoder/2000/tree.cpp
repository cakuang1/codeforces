#include <bits/stdc++.h>
using namespace std;

struct Basis {
    static const int LOG = 30;           // since ai <= 1e9
    int b[LOG];
    Basis() { memset(b, 0, sizeof(b)); }

    void insertVec(int x) {
        for (int i = LOG - 1; i >= 0; --i) {
            if (((x >> i) & 1) == 0) continue;
            if (!b[i]) { b[i] = x; return; }
            x ^= b[i];
        }
    }

    // merge other into this
    void mergeFrom(const Basis& other) {
        for (int i = 0; i < LOG; ++i) if (other.b[i]) insertVec(other.b[i]);
    }

    int maxXor() const {
        int res = 0;
        for (int i = LOG - 1; i >= 0; --i) {
            if (!b[i]) continue;
            res = max(res, res ^ b[i]);
        }
        return res;
    }
};

struct SegTree {
    int n;
    vector<Basis> st;
    SegTree() : n(0) {}
    SegTree(const vector<int>& arr) { build(arr); }

    void build(const vector<int>& arr) {
        n = (int)arr.size() - 1; // 1-indexed
        st.assign(4 * n + 5, Basis());
        build(1, 1, n, arr);
    }

    void build(int p, int l, int r, const vector<int>& arr) {
        if (l == r) {
            st[p] = Basis();
            st[p].insertVec(arr[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, arr);
        build(p << 1 | 1, m + 1, r, arr);
        st[p] = st[p << 1];
        st[p].mergeFrom(st[p << 1 | 1]);
    }

    Basis query(int L, int R) const {
        if (L > R) return Basis();
        return query(1, 1, n, L, R);
    }

    Basis query(int p, int l, int r, int L, int R) const {
        if (L <= l && r <= R) return st[p];
        int m = (l + r) >> 1;
        if (R <= m) return query(p << 1, l, m, L, R);
        if (L > m) return query(p << 1 | 1, m + 1, r, L, R);
        Basis left = query(p << 1, l, m, L, R);
        Basis right = query(p << 1 | 1, m + 1, r, L, R);
        left.mergeFrom(right);
        return left;
    }
};

static const int MAXLOG = 20; // since n <= 2e5, 2^18 > 2e5, so 20 is safe

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<vector<int>> g(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> tin(n + 1), tout(n + 1), depth(n + 1), euler(n + 1);
        vector<array<int, MAXLOG>> up(n + 1);
        int timer = 0;

        // iterative DFS to avoid recursion depth issues
        // stack: (u, p, state, iterator index)
        struct Frame { int u, p, it; };
        vector<int> parent(n + 1, 0);

        // root at 1
        int root = 1;
        parent[root] = root;
        depth[root] = 0;
        up[root].fill(root);

        vector<Frame> st;
        st.push_back({root, root, 0});
        tin[root] = ++timer;
        euler[timer] = root;

        // set up[root]
        up[root][0] = root;

        while (!st.empty()) {
            auto &fr = st.back();
            int u = fr.u;
            int p = fr.p;

            if (fr.it == 0) {
                // fill binary lifting for u
                up[u][0] = p;
                for (int k = 1; k < MAXLOG; k++) up[u][k] = up[ up[u][k-1] ][k-1];
            }

            if (fr.it < (int)g[u].size()) {
                int v = g[u][fr.it++];
                if (v == p) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;

                tin[v] = ++timer;
                euler[timer] = v;

                st.push_back({v, u, 0});
            } else {
                tout[u] = timer;
                st.pop_back();
            }
        }

        auto isAncestor = [&](int u, int v) -> bool {
            // u ancestor of v in root-1 tree?
            return tin[u] <= tin[v] && tout[v] <= tout[u];
        };

        auto jumpUp = [&](int v, int dist) -> int {
            for (int k = 0; k < MAXLOG; k++) {
                if (dist & (1 << k)) v = up[v][k];
            }
            return v;
        };

        // Build segtree over Euler array of values a[node]
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; i++) arr[i] = a[euler[i]];
        SegTree seg(arr);

        int q;
        cin >> q;
        while (q--) {
            int r, v;
            cin >> r >> v;

            Basis ansB;

            if (!isAncestor(v, r)) {
                // r not in subtree(v): subtree_r(v) == subtree_1(v)
                ansB = seg.query(tin[v], tout[v]);
            } else {
                // r in subtree(v): subtree_r(v) == all nodes minus subtree(child c on path v->r)
                if (v == r) {
                    // whole tree
                    ansB = seg.query(1, n);
                } else {
                    int dist = depth[r] - depth[v] - 1;
                    int c = jumpUp(r, dist); // child of v on path to r
                    // c should have parent v
                    // complement of subtree(c)
                    Basis left = seg.query(1, tin[c] - 1);
                    Basis right = seg.query(tout[c] + 1, n);
                    left.mergeFrom(right);
                    ansB = left;
                }
            }

            cout << ansB.maxXor() << "\n";
        }
    }
    return 0;
}

// we sdoshtso owrw w rwobusods ghsos ostais snfw hsdtshfo iwer
// wrw IVna rew sdf anr wbitw