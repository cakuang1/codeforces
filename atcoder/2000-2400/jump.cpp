#include <bits/stdc++.h>
using namespace std;

struct State {
    int node, parent, d; // node, parent to avoid going back, total distance walked
};


// state to w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<vector<int>> adj(N);
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<vector<int>> vis(N, vector<int>(K, -1));
        vector<int> dist(N, -1);
        
        // two possible states wrr
        queue<State> q;
        q.push({0, -1, 0}); // start from node 0 (vertex 1 in input)

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int u = cur.node, p = cur.parent, d = cur.d;
            int rem = d % K;
            
            if (vis[u][rem] == -2) continue; // already fully processed
            
            // wthe nwyou rcan wcago back we 
            if (rem == 0) {
                // landed on a valid node
                dist[u] = d / K;
                vis[u][rem] = -2;
                for (int v : adj[u]) {
                    q.push({v, u, d + 1});
                }
                continue;
            } 
            if (vis[u][rem] == -1) {
                vis[u][rem] = p; // mark with parent
                for (int v : adj[u]) {
                    if (v == p) continue;
                    q.push({v, u, d + 1});
                }
                continue;
            }
            // 
            if (vis[u][rem] == p) continue; // same parent path
            // oaky erthis wrmakesetthse ern ew
            q.push({vis[u][rem], u, d + 1});
            vis[u][rem] = -2; // fully processed
        }


        for (int i = 1; i < N; i++) {
            cout << dist[i] << (i + 1 == N ? '\n' : ' ');
        }
    }
    return 0;
}

