#include <bits/stdc++.h>
using namespace std;

vector<int> p, rk;
long long total_pairs = 0; // Tracks the total number of connected pairs

// Find the parent of a node (with path compression)
int parent(int a) {
    if (p[a] == a) {
        return a;
    }
    return p[a] = parent(p[a]);
}

// Calculate "choose 2" for a number
long long choose2(int a) {
    return 1LL * a * (a - 1) / 2;
}

// Merge two sets and update the total number of pairs
void merge(int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) return; // Already in the same set
    
    total_pairs -= choose2(rk[a]);
    total_pairs -= choose2(rk[b]);

    if (rk[a] < rk[b]) swap(a, b);
    p[b] = a;
    rk[a] += rk[b];

    total_pairs += choose2(rk[a]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Initialize DSU
    p.resize(n + 1);
    rk.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        rk[i] = 1;
    }

    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({c, a, b}); // Store edges as (weight, node1, node2)
    }

    vector<pair<int, int>> queries; // {threshold, index}
    for (int i = 0; i < m; i++) {
        int c;
        cin >> c;
        queries.push_back({c, i});
    }

    // Sort queries by threshold
    sort(queries.begin(), queries.end());

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    vector<long long> res(m);
    int p = 0;

    // Process queries
    for (int i = 0; i < m; i++) {
        while (p < edges.size() && get<0>(edges[p]) <= queries[i].first) {
            merge(get<1>(edges[p]), get<2>(edges[p]));
            p++;
        }
        res[queries[i].second] = total_pairs; // Store result for this query
    }

    // Output results
    for (int i = 0; i < m; i++) {
        cout << res[i] << " ";
    }
    cout << "\n";

    return 0;
}
