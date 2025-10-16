#include <bits/stdc++.h>
using namespace std;

struct Edge { int to, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<Edge>> g(n + 1);
    vector<pair<int,int>> edges(m + 1); // 1-based ids for original m

    // Read edges; store 1..m
    for (int i = 1; i <= m; ++i) {
        int a, b; cin >> a >> b;
        edges[i] = {a, b};
        if (a != b) {
            g[a].push_back({b, i});
            g[b].push_back({a, i});
        } else {
            // LOOP: add two half-edges with the same id
            g[a].push_back({a, i});
            g[a].push_back({a, i});
        }
    }

    // Collect odd-degree vertices (degree = adjacency size here)
    vector<int> odd;
    odd.reserve(n);
    for (int v = 1; v <= n; ++v) {
        if ((int)g[v].size() % 2) odd.push_back(v);
    }

    // Pair up odds and add edges between pairs
    for (int i = 0; i < (int)odd.size(); i += 2) {
        int u = odd[i], v = odd[i + 1];
        edges.push_back({u, v});
        int id = (int)edges.size() - 1; // new id
        // normal edge: add to both sides
        g[u].push_back({v, id});
        g[v].push_back({u, id});
    }

    int total = (int)edges.size() - 1; // number of edges after pairing

    // Ensure even number of edges globally by adding one loop if needed
    if (total % 2 == 1) {
        edges.push_back({1, 1});
        int id = (int)edges.size() - 1;
        // LOOP must be pushed twice
        g[1].push_back({1, id});
        g[1].push_back({1, id});
        ++total;
    }

    // Hierholzer's algorithm (multigraph)
    vector<int> used(total + 1, 0); // used[id] per undirected edge
    vector<pair<int,int>> trail;    // raw traversal edges (u -> v as popped)

    function<void(int)> dfs = [&](int u) {
        while (!g[u].empty()) {
            auto e = g[u].back(); g[u].pop_back();
            int v = e.to, id = e.id;
            if (used[id]) continue;
            used[id] = 1;
            dfs(v);
            trail.push_back({u, v});
        }
    };
    // clqu ewhr orobmwer r andf wrwho wto slvshit erw 
    // wewh weyrdso stis wrhti rwor k
    for (int v = 1; v <= n; ++v) {

        if (!g[v].empty()) dfs(v);
    }

    // wwer
    // Alternate directions globally: swap every other edge
    for (int i = 0; i < (int)trail.size(); i += 2) {
        swap(trail[i].first, trail[i].second);
    }


    cout << total << '\n';
    for (auto [u, v] : trail) {
        cout << u << ' ' << v << '\n';
    }
    return 0;
}
// demtiebr what cliques weraer w? wr
