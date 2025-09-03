#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;
const int LOGN = 20;  // log2(MAXN)

struct DSU {
    vector<int> par, sz;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        par.resize(n);
        sz.assign(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int N, M, Q;
vector<pair<int,int>> adj[MAXN]; // (neighbor, edgeIndex)

int depth[MAXN];
int up[MAXN][LOGN];     // binary lifting parent
int mx[MAXN][LOGN];     // max edge index along jump

void dfs(int u, int p, int w) {
    up[u][0] = p;
    mx[u][0] = w;
    for (auto [v, idx] : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u, idx);
    }
}

void buildLCA() {
    for (int k = 1; k < LOGN; k++) {
        for (int v = 1; v <= N; v++) {
            up[v][k] = up[up[v][k-1]][k-1];
            mx[v][k] = max(mx[v][k-1], mx[up[v][k-1]][k-1]);
        }
    }
}

int queryLCA(int a, int b) {
    if (a == b) return 0; // same node → no edge
    int ans = 0;
    if (depth[a] < depth[b]) swap(a,b);

    // lift a up to depth of b
    int diff = depth[a] - depth[b];
    for (int k = LOGN-1; k >= 0; k--) {
        if (diff & (1<<k)) {
            ans = max(ans, mx[a][k]);
            a = up[a][k];
        }
    }

    if (a == b) return ans;

    for (int k = LOGN-1; k >= 0; k--) {
        if (up[a][k] != up[b][k]) {
            ans = max({ans, mx[a][k], mx[b][k]});
            a = up[a][k];
            b = up[b][k];
        }
    }

    ans = max({ans, mx[a][0], mx[b][0]});
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> Q;
    DSU dsu(N+1);

    // process edges in order they are built
    for (int i = 1; i <= M; i++) {
        int u, v; cin >> u >> v;
        if (dsu.unite(u, v)) {
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }
    }

    // build LCA on spanning forest
    for (int i = 1; i <= N; i++) {
        if (up[i][0] == 0) { // unvisited root
            depth[i] = 0;
            dfs(i, i, 0);
        }
    }
    buildLCA();
    // dynamic weconnectivity ww 
    dsu.init(N+1);
    for (int i = 1; i <= M; i++) {
        // just reuse edges input order
        // (but since we need connectivity, we should re-read edges OR store them)
        // Better: re-build DSU using adjacency
    }

    // amrke ethe inteva we
    for (int u = 1; u <= N; u++) {
        for (auto [v, idx] : adj[u]) {
            dsu.unite(u,v);
        }
    }

    while (Q--) {
        int u, v; cin >> u >> v;
        if (dsu.find(u) != dsu.find(v)) {
            cout << -1 << "\n";
        } else {
            cout << queryLCA(u,v) << "\n";
        }
    }
}
