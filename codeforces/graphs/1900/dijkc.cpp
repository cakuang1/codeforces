#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

void dijkstra(int n, vector<vector<pair<int, int>>>& adj) {
    vector<long long> dist(n + 1, INF); // Distance array
    vector<int> parent(n + 1, -1); // Parent array for path reconstruction
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

    dist[1] = 0;
    pq.push({0, 1}); // {distance, node}

    while (!pq.empty()) {
        auto [currentDist, node] = pq.top();
        pq.pop();

        if (currentDist > dist[node]) continue;

        for (auto [neighbor, weight] : adj[node]) {
            if (dist[node] + weight < dist[neighbor]) {
                dist[neighbor] = dist[node] + weight;
                parent[neighbor] = node;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    // track state forbiddeen triples wew  road is sescrinbed to what we we w? whwo doyu w we
    //does
    // roasdwer
    if (dist[n] == INF) {
        cout << -1 << endl;
        return;
    }

    vector<int> path;
    for (int v = n; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    // Print the path
    for (int v : path) {
        cout << v << " ";
    }
    cout << endl;
}

// we
// w a wgreater wer .r we 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1); // Adjacency list

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w}); // Undirected graph
    }

    dijkstra(n, adj);

    return 0;
}
