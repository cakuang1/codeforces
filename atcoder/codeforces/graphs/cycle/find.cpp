#include <bits/stdc++.h>
using namespace std;

const int N = 305;
const int INF = 1e9;

int g[N][N];
int d[N], vis[N], par[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // Read and preprocess adjacency matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
            if (g[i][j] == -1) 
                g[i][j] = INF;
        }
    }

    // For each vertex u, compute shortest simple cycle through u
    for (int u = 1; u <= n; u++) {
        // Dijkstra‐style initialization
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++) {
            d[i] = INF;
            par[i] = i;
        }
        d[u] = 0;
        par[u] = u;

        int ans = INF;

        // Main loop: extract min‐distance vertex cur
        while (true) {
            int cur = 0;
            for (int i = 1; i <= n; i++) {
                if (!vis[i] && d[i] < d[cur]) {
                    cur = i;
                }
            }
            if (cur == 0) break;
            vis[cur] = 1;

            // Option A: cycle u → ... → cur → u
            if (par[cur] != cur) {
                ans = min(ans, d[cur] + g[cur][u]);
            }

            // Relax edges and Option B: cycle via edge (cur,i)
            for (int i = 1; i <= n; i++) {
                if (i == u) continue;
                if (vis[i]) {
                    // both cur and i are finalized
                    if (par[cur] != par[i]) {
                        // their paths from u started on different neighbors
                        ans = min(ans, d[cur] + d[i] + g[cur][i]);
                    }
                } else {
                    // standard relaxation
                    if (d[cur] + g[cur][i] < d[i]) {
                        d[i] = d[cur] + g[cur][i];
                        par[i] = (cur == u ? i : par[cur]);
                    }
                }
            }
        }

        if (ans == INF) ans = -1;
        cout << ans << "\n";
    }

    return 0;
}
 
