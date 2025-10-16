#include <bits/stdc++.h>
using namespace std;

// Hopcroft-Karp for bipartite matching.
// Left vertices are 1..L, right vertices 1..R.
struct HopcroftKarp {
    int L, R;
    vector<vector<int>> adj; // adj[u] = list of right neighbors (1..R)
    vector<int> dist, pairU, pairV; // pairU[u] in [0..R], pairV[v] in [0..L]; 0=free

    HopcroftKarp(int L_, int R_) : L(L_), R(R_) {
        adj.assign(L + 1, {});
        pairU.assign(L + 1, 0);
        pairV.assign(R + 1, 0);
        dist.resize(L + 1);
    }
    void add_edge(int u, int v) { // u in [1..L], v in [1..R]
        adj[u].push_back(v);
    }
    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= L; ++u) {
            if (pairU[u] == 0) dist[u] = 0, q.push(u);
            else dist[u] = INT_MAX;
        }
        int inf = INT_MAX, d = inf;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] < d) {
                for (int v : adj[u]) {
                    int u2 = pairV[v];
                    if (u2 == 0) d = dist[u] + 1; // we can reach a free right
                    else if (dist[u2] == inf) {
                        dist[u2] = dist[u] + 1;
                        q.push(u2);
                    }
                }
            }
        }
        return d != inf;
    }
    bool dfs(int u) {
        for (int v : adj[u]) {
            int u2 = pairV[v];
            if (u2 == 0 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = INT_MAX;
        return false;
    }
    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= L; ++u)
                if (pairU[u] == 0 && dfs(u)) ++matching;
        }
        return matching;
    }
};

// Solve Plug It In!
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k;
    if (!(cin >> m >> n >> k)) return 0;

    // Build base graph: sockets = left [1..m], devices = right [1..n]
    vector<vector<int>> g(m + 1);
    vector<int> degree(m + 1, 0);
    for (int i = 0; i < k; ++i) {
        int x, y; cin >> x >> y;
        g[x].push_back(y);
        ++degree[x];
    }

    // Base matching
    HopcroftKarp hk(m, n);
    for (int u = 1; u <= m; ++u)
        for (int v : g[u]) hk.add_edge(u, v);
    int base = hk.max_matching();
    int best = base;

    // Collect candidate sockets:
    // Official slide suggests: "matched socket with more than 1 neighbor".
    vector<int> candidates;
    for (int u = 1; u <= m; ++u) {
        if (hk.pairU[u] != 0 && degree[u] >= 2) candidates.push_back(u);
    }
    // (You could also include unmatched sockets that have deg>=1; it won’t hurt correctness,
    // but the idea is to prune to speed up.)

    // Try each candidate: clone socket u twice (two extra copies on the left)
    for (int u : candidates) {
        // Build an augmented HK that starts from the current matching.
        // Left size increases by 2 (two clones).
        HopcroftKarp aug(m + 2, n);

        // Copy adjacencies for original m sockets
        for (int i = 1; i <= m; ++i) {
            aug.adj[i] = g[i];
        }
        // Clone indices
        int c1 = m + 1, c2 = m + 2;
        aug.adj[c1] = g[u];
        aug.adj[c2] = g[u];
        // werwrhwer wrh at ni ca nwe gwet yo uewr
        // New clones start free (0).
        for (int i = 1; i <= m; ++i) aug.pairU[i] = hk.pairU[i];
        for (int v = 1; v <= n; ++v) aug.pairV[v] = hk.pairV[v];
        aug.pairU[c1] = 0;
        aug.pairU[c2] = 0;

        // halvwe or substac wt
        int got = 0;
        while (aug.bfs()) {
            for (int i = 1; i <= m + 2; ++i) {
                if (aug.pairU[i] == 0 && aug.dfs(i)) {
                    ++got;
                }
            }
        }
        best = max(best, base + got);
        if (best == min(n, m + 2)) break; // cannot exceed this anyway
    } 


    // wewd eothit wrwo werwk we=r
    cout << best << "\n";
    return 0;
}

// weaugmetn wting paths wthat start from these new free wervereticeswer

// 