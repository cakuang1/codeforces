#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // 1) Compute total XOR
    ll total = 0;
    for (int i = 1; i <= n; i++) total ^= a[i];
    // 2) If total == 0, we can always make at least 2 pieces of XOR = 0 by one cut
    if (total == 0) {
        cout << "YES\n";
        return;
    }
    // 3) If k < 3, we cannot form 3 pieces => NO
    if (k < 3) {
        cout << "NO\n";
        return;
    }
    // 4) Otherwise we need at least two disjoint subtrees with subtree-xor == total
    //    We'll do an iterative DFS to get a post-order.
    vector<int> parent(n+1, 0), order;
    order.reserve(n);
    // stack for DFS preorder
    stack<int> st;
    st.push(1);
    parent[1] = 0;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            st.push(v);
        }
    }
    // Now order[] is a preorder; process in reverse for postorder:
    vector<ll> subxor(n+1);
    int cuts = 0;
    for (int idx = n-1; idx >= 0; idx--) {
        int u = order[idx];
        // start with own value
        subxor[u] = a[u];
        // accumulate children
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            subxor[u] ^= subxor[v];
        }
        // if this subtree has XOR == total, and it's not the entire tree,
        // we can “cut” it off as one piece, and zero it out so its parent
        // won't see it.
        if (subxor[u] == total && u != 1) {
            cuts++;
            subxor[u] = 0;
        }
    }
    // If we found at least two such cuts, we can form 3 pieces of XOR = total
    cout << (cuts >= 2 ? "YES\n" : "NO\n");
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

