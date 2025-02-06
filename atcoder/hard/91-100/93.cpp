#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 1000001;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--; // Convert to 0-based
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    int queries, k;
    cin >> queries >> k;
    k--; // Convert K to 0-based

    // BFS to compute shortest distances from node K
    vector<ll> dist(n, INF);
    queue<int> q;
    q.push(k);
    dist[k] = 0;

    while (!q.empty()) {
        int top = q.front();
        q.pop();
        for (pair<int, int> u : adj[top]) {
            if (dist[u.first] == INF) {
                dist[u.first] = dist[top] + u.second;
                q.push(u.first);
            }
        }
    }

    // Answer queries in O(1)
    while (queries--) {
        int v1, v2;
        cin >> v1 >> v2;
        v1--, v2--; // Convert to 0-based
        cout << dist[v1] + dist[v2] << '\n';
    }

    return 0;
}
