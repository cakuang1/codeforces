#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 17; // log2(MAXN) + 1
vector<int> tree[MAXN];
int up[MAXN][LOG];  // Binary lifting table
int depth[MAXN];    // Depth of each node

// DFS to preprocess depth and the first ancestor (up[node][0])
void dfs(int node, int parent) {
    up[node][0] = parent; // Direct parent
    for (int j = 1; j < LOG; j++) {
        if (up[node][j - 1] != -1) {
            up[node][j] = up[up[node][j - 1]][j - 1];
        } else {
            up[node][j] = -1; // No ancestor at this level
        }
    }
    for (int neighbor : tree[node]) {
        if (neighbor != parent) {
            depth[neighbor] = depth[node] + 1;
            dfs(neighbor, node);
        }
    }
}

// Lift a node to a target depth
int liftNode(int node, int k) {
    for (int j = LOG - 1; j >= 0; j--) {
        if (k & (1 << j)) {
            node = up[node][j];
            if (node == -1) break;
        }
    }
    return node;
}

// Find LCA of two nodes
int findLCA(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    // Lift u to the same depth as v
    u = liftNode(u, depth[u] - depth[v]);
    if (u == v) return u;

    // Binary jump to find LCA
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }

    // Return the parent of u (or v)
    return up[u][0];
}


// precompute paths  wfind the number of paths woerf gifxe dlenhth 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n ; 
    cin >> n; 
    // Input the tree
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    memset(up, -1, sizeof(up));
    depth[1] = 0;
    dfs(1, -1);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << findLCA(u, v) << "\n";
    }


    return 0;
}
