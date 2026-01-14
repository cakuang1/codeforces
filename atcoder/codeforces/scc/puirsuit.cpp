#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

const int MAXN = 500000 + 5;
const int MAXM = 500000 + 5;

int n, m;
struct Edge { int u, v, z; };
vector<Edge> edges;
vector<vector<pii>> adj;      // adj[u] = list of (v, edge_id)

bool isBridge[MAXM];
int disc[MAXN], low[MAXN], Timer = 1;

// 1) Find all bridges via lowlink
void dfs_br(int u, int pe) {
    disc[u] = low[u] = Timer++;
    for (auto [v, eid] : adj[u]) {
        if (eid == pe) continue;
        if (!disc[v]) {
            dfs_br(v, eid);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u]) {
                isBridge[eid] = true;
            }
        } else {
            // back-edge
            low[u] = min(low[u], disc[v]);
        }
    }
}

int comp[MAXN], compCnt = 0;
// 2) Label edge-biconnected components by DFS over non-bridge edges
void dfs_comp(int u) {
    comp[u] = compCnt;
    for (auto [v, eid] : adj[u]) {
        if (!comp[v] && !isBridge[eid]) {
            dfs_comp(v);
        }
    }
}


    
vector<vector<pii>> tree;  // tree[c] = list of (c2, artifact_on_bridge)
vector<bool> good;         // good[c] = true if component c has an internal artifact

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    edges.resize(m);
    adj.assign(n+1, {});
    for (int i = 0; i < m; i++) {
        int u, v, z;
        cin >> u >> v >> z;
        edges[i] = {u, v, z};
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    int A, B;
    cin >> A >> B;

    // 1) Find bridges
    for (int i = 1; i <= n; i++) {
        if (!disc[i]) dfs_br(i, -1);
    }

    // 2) Build EBCCs
    for (int i = 1; i <= n; i++) {
        if (!comp[i]) {
            ++compCnt;
            dfs_comp(i);
        }
    }

    // prepare tree and good[]
    tree.assign(compCnt+1, {});
    good.assign(compCnt+1, false);

    // 3) Populate tree edges and internal-artifact flags
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v, z = edges[i].z;
        int cu = comp[u], cv = comp[v];
        if (cu == cv) {
            // internal edge
            if (z == 1) good[cu] = true;
        } else {
            // bridge-edge in original => tree-edge here
            tree[cu].push_back({cv, z});
            tree[cv].push_back({cu, z});
        }
    }

    // 4) BFS on the component-tree to recover the unique path from comp[A] to comp[B]
    int cA = comp[A], cB = comp[B];
    vector<int> parent(compCnt+1, -1), parEdge(compCnt+1, 0);
    queue<int> q;
    parent[cA] = cA;
    q.push(cA);
    while(!q.empty() && parent[cB] == -1) {
        int u = q.front(); q.pop();
        for (auto [v, w] : tree[u]) {
            if (parent[v] == -1) {
                parent[v] = u;
                parEdge[v] = w;
                q.push(v);
            }
        }
    }

    // 5) Walk back from cB to cA, checking artifacts
    bool ans = false;
    int cur = cB;
    while (true) {
        if (good[cur]) ans = true;
        if (cur == cA) break;
        if (parEdge[cur] == 1) ans = true;
        cur = parent[cur];
    }

    cout << (ans ? "YES\n" : "NO\n");
    return 0;
}
