#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

bool hasNegativeCycle(int n, const vector<Edge>& edges, int sign) {
    // Equivalent to adding a super-source with zero-weight edges
    // to every vertex.
    vector<int> dist(n, 0);

    for (int iteration = 0; iteration < n; iteration++) {
        bool updated = false;

        for (const Edge& edge : edges) {
            int w = edge.weight * sign;

            if (dist[edge.to] > dist[edge.from] + w) {
                dist[edge.to] = dist[edge.from] + w;
                updated = true;

                // A relaxation on the N-th iteration means
                // that a negative cycle exists.
                if (iteration == n - 1) {
                    return true;
                }
            }
        }

        if (!updated) {
            return false;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    edges.reserve(m);

    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        --u;
        --v;

        int weight = (c == '(' ? 1 : -1);
        edges.push_back({u, v, weight});
    }

    // Negative cycle under the original weights.
    bool hasNegative = hasNegativeCycle(n, edges, 1);

    // A positive cycle under the original weights becomes
    // a negative cycle after negating all weights.
    bool hasPositive = hasNegativeCycle(n, edges, -1);

    // Valid exactly when:
    // - both positive and negative cycles exist, or
    // - neither exists, meaning every cycle has weight zero.
    cout << (hasNegative == hasPositive ? "Yes\n" : "No\n");
}



// Thwe s s 