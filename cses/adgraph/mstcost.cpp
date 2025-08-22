#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100000;
const int LOG  = 17; // since 2^17 = 131072 > 100000

struct DSU {
    vector<int> p;
    DSU(int n = 0) : p(n+1, -1) {}
    int find(int x) {
        return p[x] < 0 ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a,b); // p[x] is negative size
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};

int n, m;
int U[MAXN], V[MAXN], W[MAXN];
bool inMST[MAXN];

vector<pair<int,int>> adj[MAXN+1];
// up[k][v] = 2^k‑ancestor of v
// maxUp[k][v] = maximum edge weight on the path from v up to its 2^k‑ancestor
int up[LOG+1][MAXN+1];
int maxUp[LOG+1][MAXN+1];
int depth[MAXN+1];
ll mstCost = 0;

// DFS to set depth[], up[0][], maxUp[0][]
void dfs(int u, int p) {
    for (auto &e : adj[u]) {
        int v = e.first, w = e.second;
        if (v == p) continue;
        depth[v]    = depth[u] + 1;
        up[0][v]    = u;
        maxUp[0][v] = w;
        dfs(v, u);
    }
}

// Return the maximum edge weight on the path u -- v in the tree
int queryMax(int u, int v){
    if (depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    int ans = 0;
    // lift u up to depth v
    for (int k = 0; k <= LOG; k++){
        if (diff & (1<<k)) {
            ans = max(ans, maxUp[k][u]);
            u = up[k][u];
        }
    }
    if (u == v) return ans;
    // binary‑lift both up until parents match
    for (int k = LOG; k >= 0; k--){
        if (up[k][u] != up[k][v]) {
            ans = max(ans, maxUp[k][u]);
            ans = max(ans, maxUp[k][v]);
            u = up[k][u];
            v = up[k][v];
        }
    }
    // one more step to reach LCA
    ans = max(ans, maxUp[0][u]);
    ans = max(ans, maxUp[0][v]);
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> U[i] >> V[i] >> W[i];
    }
    // Build a list of edges (w, u, v, idx) for sorting
    vector<tuple<int,int,int,int>> E;
    E.reserve(m);
    for (int i = 0; i < m; i++){
        E.emplace_back(W[i], U[i], V[i], i);
    }
    sort(E.begin(), E.end(),
         [](const tuple<int,int,int,int> &A,
            const tuple<int,int,int,int> &B){
             return get<0>(A) < get<0>(B);
         });

    // Kruskal
    DSU dsu(n);
    for (auto &t : E){
        int w,u,v,idx;
        tie(w,u,v,idx) = t;
        if (dsu.unite(u,v)){
            inMST[idx] = true;
            mstCost += w;
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
    }

    // Root MST at node 1
    depth[1] = 0;
    up[0][1] = 1;
    maxUp[0][1] = 0;
    dfs(1, 0);

    // Build binary lifting tables
    for (int k = 1; k <= LOG; k++){
        for (int v = 1; v <= n; v++){
            up[k][v]    = up[k-1][ up[k-1][v] ];
            maxUp[k][v] = max(maxUp[k-1][v],
                              maxUp[k-1][ up[k-1][v] ]);
        }
    }

    vector<ll> answer(m);
    for (int i = 0; i < m; i++){
        if (inMST[i]){
            answer[i] = mstCost;
        } else {
            int wmax = queryMax(U[i], V[i]);
            answer[i] = mstCost + W[i] - wmax;
        }
    }

    // Print
    for (int i = 0; i < m; i++){
        cout << answer[i] << "\n";
    }
    return 0;
}
