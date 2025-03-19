#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int a, b, w, index;
};

const int MAXN = 200005;
int p[MAXN], rnk[MAXN];

// DSU find with path compression.
int find(int a) {
    if (p[a] != a)
        p[a] = find(p[a]);
    return p[a];
}

// DSU union by rank.
void unionSet(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            p[a] = b;
        else if (rnk[a] > rnk[b])
            p[b] = a;
        else {
            p[b] = a;
            rnk[a]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = {a, b, c, i};
    }
    
    // DSU initialization.
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        rnk[i] = 1;
    }
    
    // Sort edges by weight (for Kruskal's algorithm).
    sort(edges.begin(), edges.end(), [](const Edge &e1, const Edge &e2) {
        return e1.w < e2.w;
    });
    
    long long mst_weight = 0;
    vector<Edge> mst;       // Store edges that are in the MST.
    vector<int> used(m, -1); // Mark whether an edge (by its original index) is used in the MST.
    
    // Kruskal: Build MST.
    for (int i = 0; i < m; i++) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w, index = edges[i].index;
        if (find(a) != find(b)) {
            unionSet(a, b);
            mst_weight += w;
            used[index] = 1;  // Mark edge as part of the MST.
            mst.push_back(edges[i]);
        }
    }
    
    // Build the adjacency list for the MST.
    // Each element is a pair: (neighbor, edge weight).
    vector<vector<pair<int,int>>> tree(n+1);
    for (auto &edge : mst) {
        tree[edge.a].push_back({edge.b, edge.w});
        tree[edge.b].push_back({edge.a, edge.w});
    }
    
    // Binary lifting parameters.
    int maxLOG = floor(log2(n)) + 1;
    // bin[v][j] will be the 2^j-th ancestor of node v.
    vector<vector<int>> bin(n+1, vector<int>(maxLOG, -1));
    // maxEdge[v][j] stores the maximum edge weight on the jump from v to bin[v][j].
    // For nodes without an ancestor, we use 0.
    vector<vector<int>> maxEdge(n+1, vector<int>(maxLOG, 0));
    vector<int> depth(n+1, 0);
    
    // DFS to initialize the binary lifting table (first ancestor) and maxEdge for the immediate parent.
    function<void(int, int)> dfs = [&](int v, int parent) {
        bin[v][0] = parent;
        for (auto &edge : tree[v]) {
            int u = edge.first, w = edge.second;
            if (u == parent)
                continue;
            depth[u] = depth[v] + 1;
            maxEdge[u][0] = w;  // The edge from v (parent) to u.
            dfs(u, v);
        }
    };
    
    // Run DFS from an arbitrary root (node 1).
    dfs(1, -1);
    
    // Build the complete binary lifting table.
    for (int j = 1; j < maxLOG; j++) {
        for (int i = 1; i <= n; i++) {
            if (bin[i][j-1] != -1) {
                bin[i][j] = bin[bin[i][j-1]][j-1];
                maxEdge[i][j] = max(maxEdge[i][j-1], maxEdge[bin[i][j-1]][j-1]);
            }
        }
    }
    
    // Query function: Returns the maximum edge weight on the path between nodes u and v in the MST.
    auto queryMaxEdge = [&](int u, int v) -> int {
        int ans = 0;
        if (depth[u] < depth[v])
            swap(u, v);
        
        // Lift u to the same depth as v.
        int diff = depth[u] - depth[v];
        for (int j = 0; diff; j++) {
            if (diff & 1) {
                ans = max(ans, maxEdge[u][j]);
                u = bin[u][j];
            }
            diff >>= 1;
        }
        
        if (u == v)
            return ans;
        
        // Lift both u and v until their ancestors diverge.
        for (int j = maxLOG - 1; j >= 0; j--) {
            if (bin[u][j] != bin[v][j]) {
                ans = max(ans, maxEdge[u][j]);
                ans = max(ans, maxEdge[v][j]);
                u = bin[u][j];
                v = bin[v][j];
            }
        }
        
        // One final update: consider the edge connecting to the LCA.
        ans = max(ans, maxEdge[u][0]);
        ans = max(ans, maxEdge[v][0]);
        return ans;
    };
    
    // Prepare the answer for each edge in the original input order.
    // For an edge that is already in the MST, answer = mst_weight.
    // For an edge not in the MST, answer = mst_weight + e.w - (maximum edge on the path between e.a and e.b).
    vector<long long> ans(m, 0);
    for (int i = 0; i < m; i++) {
        Edge e = edges[i];
        if (used[e.index] == 1) {
            ans[e.index] = mst_weight;
        } else {
            int maxE = queryMaxEdge(e.a, e.b);
            ans[e.index] = mst_weight + e.w - maxE;
        }
    }
    
    // Output the answer for each edge in input order.
    for (int i = 0; i < m; i++)
        cout << ans[i] << "\n";
    
    return 0;
}
