#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<set<int>> adj(n + 1);
    vector<int> deg(n + 1, 0);

    int ans = n;

    while (q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int u, v;
            cin >> u >> v;

            if (deg[u] == 0) ans--;
            if (deg[v] == 0) ans--;

            adj[u].insert(v);
            adj[v].insert(u);

            deg[u]++;
            deg[v]++;
        } else {
            int v;
            cin >> v;

            if (deg[v] > 0) ans++;

            for (int u : adj[v]) {
                adj[u].erase(v);
                deg[u]--;

                if (deg[u] == 0) ans++;
            }

            adj[v].clear();
            deg[v] = 0;
        }

        cout << ans << '\n';
    }
}