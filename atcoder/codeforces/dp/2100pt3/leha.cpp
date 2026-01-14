#include <bits/stdc++.h>
using namespace std;
 
// We'll use 0-indexing for vertices internally, but note that the input edges are numbered starting at 1.
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // Read the desired parity for each vertex.
    // d[i] can be 0 (even), 1 (odd), or -1 (flexible).
    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    
    // Build the graph. We'll store for each vertex a list of (neighbor, edge index) pairs.
    vector<vector<pair<int,int>>> adj(n);
    vector<pair<int,int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // convert to 0-indexed
        edges.push_back({u, v});
        // store edge index as i+1 so that when we output it, it matches the input numbering.
        adj[u].push_back({v, i+1});
        adj[v].push_back({u, i+1});
    }
    
    // Step 1: Adjust flexible vertices.
    // Compute the sum of the fixed values and count the flexible ones.
    int fixedSum = 0;
    int flexibleCount = 0;
    vector<int> flexibleIndices;
    for (int i = 0; i < n; i++) {
        if (d[i] != -1) {
            fixedSum += d[i];
        } else {
            flexibleCount++;
            flexibleIndices.push_back(i);
        }
    }
    
    // The overall sum of desired parities must be even.
    // If fixedSum is odd, we need to assign one flexible vertex to 1, and the rest to 0.
    // Otherwise, assign all flexible vertices to 0.
    if (fixedSum % 2 != 0) {
        if (flexibleCount == 0) {
            cout << -1 << "\n";
            return 0;
        }
        bool assignedOne = false;
        for (int i : flexibleIndices) {
            if (!assignedOne) {
                d[i] = 1;
                assignedOne = true;
            } else {
                d[i] = 0;
            }
        }
    } else {
        for (int i : flexibleIndices) {
            d[i] = 0;
        }
    }
    
    // Now the sum of desired parities is even.
    
    // Step 2: Build a spanning tree via DFS.
    vector<int> parent(n, -1);
    vector<int> parentEdge(n, -1); // records the edge index connecting a vertex to its parent.
    vector<bool> visited(n, false);
    vector<int> postorder; // will store vertices in postorder (children before parent)
    
    function<void(int, int)> dfs = [&](int u, int par) {
        visited[u] = true;
        parent[u] = par;
        for (auto &p : adj[u]) {
            int v = p.first;
            int edgeIndex = p.second;
            if (v == par) continue;
            if (!visited[v]) {
                parentEdge[v] = edgeIndex;
                dfs(v, u);
            }
        }
        postorder.push_back(u);
    };
    
    dfs(0, -1); // root the tree at vertex 0.
    
    // Step 3: Process vertices in postorder (from leaves upward).
    vector<int> ans;
    for (int u : postorder) {
        if (u == 0) continue; // skip the root
        if (d[u] == 1) {
            // To achieve an odd degree at u, we must include the edge connecting u to its parent.
            ans.push_back(parentEdge[u]);
            // Including this edge contributes 1 to the parent's degree, so we flip parent's desired parity.
            if (parent[u] != -1) {
                d[parent[u]] = 1 - d[parent[u]];
            }
        }
    }
    
    // After processing, the root's desired parity should be 0.
    if (d[0] == 1) {
        cout << -1 << "\n";
        return 0;
    }
    // spannign wetee w
    cout << ans.size() << "\n";
    for (int edgeIndex : ans) {
        cout << edgeIndex << "\n";
    }
    
    return 0;
}
