#include <bits/stdc++.h>
using namespace std;

const int NMAX = 200005; // Maximum number of nodes
int n, maxLog;
vector<int> depth(NMAX);
vector<int> parent(NMAX);
vector<vector<int>> adj(NMAX);
vector<vector<int>> up(NMAX, vector<int>(22, 0)); // Assuming n <= 2e5, so 22 is safe

// DFS to compute parent and depth
void dfs(int u, int par) {
    parent[u] = par;
    depth[u] = (par == 0 ? 0 : depth[par] + 1);
    up[u][0] = par; // immediate parent
    for (int v : adj[u]) {
        if (v == par) continue;
        dfs(v, u);
    }
}

void buildBinaryLiftingTable(int n) {
    maxLog = floor(log2(n)) + 1;
    // Fill in the rest of the table using dynamic programming.
    for (int j = 1; j < maxLog; j++) {
        for (int i = 1; i <= n; i++) {
            int intermediate = up[i][j - 1];
            if (intermediate != 0)
                up[i][j] = up[intermediate][j - 1];
            else
                up[i][j] = 0;
        }
    }
}

// Function to "lift" node u by k levels
int kthAncestor(int u, int k) {
    for (int i = 0; i < maxLog; i++) {
        if (k & (1 << i)) {
            u = up[u][i];
            if (u == 0)
                break;
        }
    }
    return u;
}

// Function to find the LCA of nodes u and v
int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    // Lift u so that both nodes are at the same depth
    int diff = depth[u] - depth[v];
    u = kthAncestor(u, diff);
    
    if (u == v)
        return u;
    
    // Lift both nodes simultaneously until their ancestors differ
    for (int i = maxLog - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    
    // The parent of u (or v) is now the LCA
    return parent[u];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        // Build an undirected tree
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // Assume 1 is the root
    dfs(1, 0);
    buildBinaryLiftingTable(n);
    

for (int i = 0; i < q; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    // Compute distance between a and b.
    int d = depth[a] + depth[b] - 2 * depth[lca(a, b)];
    if (c >= d) {
        cout << b << "\n"; // enough energy to reach b
    } else {
        int dA = depth[a] - depth[lca(a, b)];
        if (c <= dA) {
            // Sloth stays on the a->LCA path.
            cout << kthAncestor(a, c) << "\n";
        } else {
            // Sloth goes up from a to LCA, then down toward b.
            // The remaining distance upward from b is (d - c).
            cout << kthAncestor(b, d - c) << "\n";
        }
    }
}

    
    return 0;
}
