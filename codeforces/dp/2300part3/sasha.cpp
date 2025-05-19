#include <bits/stdc++.h>
using namespace std;
 
// ---------- Global (per test case) structures ----------
 
const int LOGN = 18; // for n up to 1e5, 2^17 > 1e5
int n; 
vector<vector<int>> tree; // 1-indexed tree
vector<int> tin, tout, depth;
vector<vector<int>> up; // binary lifting table: up[v][i] is 2^i-th ancestor of v.
int timer;
 
// DFS to compute tin, tout, depth and up[.][0]
void dfsLCA(int v, int p, int d) {
    depth[v] = d;
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i < LOGN; i++) {
        up[v][i] = (up[v][i-1] == -1 ? -1 : up[ up[v][i-1] ][i-1]);
    }
    for (int u : tree[v]) {
        if (u == p) continue;
        dfsLCA(u, v, d+1);
    }
    tout[v] = ++timer;
}
 
// Check if u is ancestor of v (using tin/tout)
bool isAncestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}
 
// Standard LCA using binary lifting.
int lca(int a, int b) {
    if(isAncestor(a, b)) return a;
    if(isAncestor(b, a)) return b;
    for (int i = LOGN-1; i >= 0; i--) {
        if(up[a][i] != -1 && !isAncestor(up[a][i], b))
            a = up[a][i];
    }
    return up[a][0];
}
 
// ---------- Compressed (Virtual) Tree building ----------
 
// Given a set of vertices 'nodes' (must be unique) sorted by tin,
// build the virtual tree (compressed tree) over these nodes.
// Returns a vector of edges (u,v) in the virtual tree. Also returns the set of vertices used.
vector<pair<int,int>> buildVirtualTree(const vector<int>& nodes) {
    vector<pair<int,int>> vtreeEdges;
    vector<int> st;
    // Helper: push a vertex on stack, connecting with the previous if needed.
    auto addEdge = [&](int u, int v) {
        vtreeEdges.push_back({u, v});
    };
    for (int v : nodes) {
        if (st.empty()) {
            st.push_back(v);
            continue;
        }
        int curLCA = lca(v, st.back());
        // Pop until stack top has tin <= tin(curLCA)
        while(st.size() >= 2 && depth[ st[st.size()-2] ] >= depth[curLCA]) {
            addEdge(st[st.size()-2], st.back());
            st.pop_back();
        }
        if(st.back() != curLCA) {
            addEdge(curLCA, st.back());
            st.back() = curLCA; // replace top with LCA
        }
        st.push_back(v);
    }
    while(st.size() > 1) {
        addEdge(st[st.size()-2], st.back());
        st.pop_back();
    }
    return vtreeEdges;
}
 
// ---------- DP on subsets ----------
 
// Given a vector of masks (each mask is an integer with bits representing which pairs are covered by that edge),
// compute the minimum number of edges needed to cover all pairs (i.e. cover mask = (1<<k)-1).
int solveDP(const vector<int>& masks, int k) {
    int full = (1 << k) - 1;
    const int INF = 1e9;
    vector<int> dp(1 << k, INF);
    dp[0] = 0;
    for (int mask : masks) {
        // We iterate over current dp and try to add this edge.
        for (int cur = full; cur >= 0; cur--) {
            int nxt = cur | mask;
            dp[nxt] = min(dp[nxt], dp[cur] + 1);
        }
    }
    return dp[full];
}
 
// ---------- Main solution ----------
 
// For a given edge (u,v) with u as parent (i.e. tin[u] < tin[v]),
// determine the bitmask of pairs covered by this edge.
// For each pair j, edge (u,v) covers pair (a,b) if exactly one of a or b is in the subtree of v.
// (We use tin/tout arrays for that.)
int getMaskForEdge(int u, int v, const vector<pair<int,int>>& pairs) {
    int mask = 0;
    for (int j = 0; j < (int)pairs.size(); j++) {
        int a = pairs[j].first, b = pairs[j].second;
        bool inA = (tin[v] <= tin[a] && tin[a] < tout[v]);
        bool inB = (tin[v] <= tin[b] && tin[b] < tout[v]);
        // edge covers (a,b) if exactly one of a, b is in subtree of v.
        if(inA ^ inB)
            mask |= (1 << j);
    }
    return mask;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t; 
    cin >> t;
    while(t--) {
        cin >> n;
        tree.assign(n+1, {});
        for (int i = 1; i <= n-1; i++){
            int u, v;
            cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
 
        // Preprocess LCA, tin, tout, depth.
        tin.assign(n+1, 0);
        tout.assign(n+1, 0);
        depth.assign(n+1, 0);
        timer = 0;
        up.assign(n+1, vector<int>(LOGN, -1));
        dfsLCA(1, -1, 0);
 
        int k; 
        cin >> k;
        vector<pair<int,int>> pairs(k);
        // Also collect vertices from the pairs.
        set<int> S;
        for (int j = 0; j < k; j++){
            int a, b;
            cin >> a >> b;
            pairs[j] = {a, b};
            S.insert(a);
            S.insert(b);
        }
 
        // For each pair, add LCA(a,b) into S.
        for (int j = 0; j < k; j++){
            int L = lca(pairs[j].first, pairs[j].second);
            S.insert(L);
        }
 
        // Build vector of vertices from S and sort them by tin.
        vector<int> compNodes(S.begin(), S.end());
        sort(compNodes.begin(), compNodes.end(), [&](int a, int b){
            return tin[a] < tin[b];
        });
 
        // Build the compressed (virtual) tree.
        vector<pair<int,int>> vtreeEdges = buildVirtualTree(compNodes);
 
        // For each edge in the virtual tree, orient it so that parent is the one with smaller tin.
        // Also compute the mask for that edge.
        vector<int> masks;
        for (auto &e : vtreeEdges) {
            int u = e.first, v = e.second;
            if(tin[u] > tin[v]) swap(u, v); // now u is parent of v
            int mask = getMaskForEdge(u, v, pairs);
            // Only consider edges that cover at least one pair.
            if(mask) masks.push_back(mask);
        }
 
        // It is possible that no edge in the compressed tree covers any pair,
        // but since each pair must be covered, answer must be at least 1.
        int ans;
        if(masks.empty()) {
            ans = 1;
        } else {
            ans = solveDP(masks, k);
        }
 
        cout << ans << "\n";
    }
 
    return 0;
}
