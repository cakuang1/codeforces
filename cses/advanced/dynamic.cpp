#include <bits/stdc++.h>
using namespace std;

// Rollback DSU (Union-Find with undo)
struct RollbackDSU {
    vector<int> parent, sz;
    stack<pair<int,int>> history;
    int components;

    RollbackDSU(int n) {
        parent.resize(n+1);
        sz.assign(n+1, 1);
        iota(parent.begin(), parent.end(), 0);
        components = n;
    }

    int find(int x) {
        while (x != parent[x]) x = parent[x];
        return x;
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) {
            history.push({-1,-1}); // dummy
            return false;
        }
        if (sz[a] < sz[b]) swap(a,b);
        history.push({b, sz[a]});
        parent[b] = a;
        sz[a] += sz[b];
        components--;
        return true;
    }

    void rollback() {
        auto [b, old_size] = history.top();
        history.pop();
        if (b == -1) return; // dummy
        int a = parent[b];
        parent[b] = b;
        sz[a] = old_size;
        components++;
    }
};

// Segment tree over time for edge intervals
struct SegTree {
    int n;
    vector<vector<pair<int,int>>> edges; // edges stored per node
    SegTree(int n): n(n) { edges.resize(4*n); }

    void addEdge(int node, int l, int r, int ql, int qr, pair<int,int> e) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            edges[node].push_back(e);
            return;
        }
        int mid = (l+r)/2;
        addEdge(node*2, l, mid, ql, qr, e);
        addEdge(node*2+1, mid+1, r, ql, qr, e);
    }

    void dfs(int node, int l, int r, RollbackDSU &dsu, vector<int> &ans) {
        int before = 0;
        // add edges in this interval
        for (auto [u,v] : edges[node]) {
            dsu.unite(u,v);
            before++;
        }

        if (l == r) {
            ans[l] = dsu.components;
        } else {
            int mid = (l+r)/2;
            dfs(node*2, l, mid, dsu, ans);
            dfs(node*2+1, mid+1, r, dsu, ans);
        }

        // rollback all edges added here
        for (int i=0;i<before;i++) dsu.rollback();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    // Read initial edges
    vector<pair<int,int>> init_edges(m);
    for (int i=0;i<m;i++) {
        int a,b; cin >> a >> b;
        if (a>b) swap(a,b);
        init_edges[i] = {a,b};
    }

    // Process events
    vector<tuple<int,int,int>> events(k+1); // 1-indexed
    map<pair<int,int>, int> active; // edge -> start time
    for (int i=1;i<=k;i++) {
        int t,a,b; cin >> t >> a >> b;
        if (a>b) swap(a,b);
        events[i] = {t,a,b};
    }

    SegTree st(k);

    // Initial edges: active from time 0 to end
    for (auto [a,b] : init_edges) {
        active[{a,b}] = 0;
    }

    // Events
    for (int i=1;i<=k;i++) {
        auto [t,a,b] = events[i];
        if (t == 1) {
            active[{a,b}] = i;
        } else {
            int start = active[{a,b}];
            st.addEdge(1, 0, k, start, i-1, {a,b});
            active.erase({a,b});
        }
    }
    // Remaining active edges until end
    for (auto [e,start] : active) {
        st.addEdge(1, 0, k, start, k, e);
    }

    // Solve with rollback DSU
    RollbackDSU dsu(n);
    vector<int> ans(k+1);
    st.dfs(1,0,k,dsu,ans);

    for (int i=0;i<=k;i++) cout << ans[i] << " ";
    cout << "\n";
}
