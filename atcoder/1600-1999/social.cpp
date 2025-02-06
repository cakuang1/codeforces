#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

bool isBipartite(int n, const vector<vector<pair<int, int>>>& adj, vector<int>& color) {
    queue<int> q;
    for (int start = 1; start <= n; ++start) {
        if (color[start] == -1) {
            color[start] = 0;
            q.push(start);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (auto [v, w] : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false; // Not bipartite
                    }
                }
            }
        }
    }
    return true;
}

bool check(int x, int n, const vector<Edge>& edges) {
    vector<vector<pair<int, int>>> adj(n + 1);
    for (const auto& edge : edges) {
        if (edge.w < x) {
            adj[edge.u].emplace_back(edge.v, edge.w);
            adj[edge.v].emplace_back(edge.u, edge.w);
        }
    }

    vector<int> color(n + 1, -1);
    if (!isBipartite(n, adj, color)) return false;

    // Check minimum weight of two-edge paths in the bipartite graph
    for (const auto& edge : edges) {
        if (edge.w >= x) continue;
        if (color[edge.u] == color[edge.v]) return false;
    }

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // Binary search on X
    int left = 1, right = 1e9, result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid, n, edges)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << result << endl;
    return 0;
}
