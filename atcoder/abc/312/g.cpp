
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Root the tree at vertex 0
    vector<int> parent(n, -1), order;
    order.reserve(n);

    parent[0] = 0;
    order.push_back(0);

    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];

        for (int u : adj[v]) {
            if (u == parent[v]) continue;

            parent[u] = v;
            order.push_back(u);
        }
    }

    // Calculate subtree sizes
    vector<ll> sz(n, 1);

    for (int i = n - 1; i > 0; i--) {
        int v = order[i];
        sz[parent[v]] += sz[v];
    }

    // Sum of distances over all unordered pairs
    ll distSum = 0;

    for (int v = 1; v < n; v++) {
        distSum += sz[v] * (n - sz[v]);
    }

    ll total = 1LL * n * (n - 1) * (n - 2) / 6;
    ll pairs = 1LL * n * (n - 1) / 2;

    // Triples lying on one simple path
    ll invalid = distSum - pairs;

    cout << total - invalid << '\n';

    return 0;
}
 
 
// wrwrw