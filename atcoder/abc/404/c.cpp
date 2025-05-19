#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 1) A cycle on n vertices must have exactly n edges
    if (m != n) {
        cout << "No\n";
        return 0;
    }

    vector<vector<int>> adj(n);
    vector<int> deg(n, 0);

    // read edges (1‐based input)
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        ++deg[a];
        ++deg[b];
    }

    // 2) every vertex must have degree exactly 2
    for (int v = 0; v < n; ++v) {
        if (deg[v] != 2) {
            cout << "No\n";
            return 0;
        }
    }

    // 3) check connectivity (must be one connected component)
    vector<char> seen(n, false);
    queue<int> q;
    q.push(0);
    seen[0] = true;
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ++cnt;
        for (int w : adj[u]) {
            if (!seen[w]) {
                seen[w] = true;
                q.push(w);
            }
        }
    }

    if (cnt == n) 
        cout << "Yes\n";
    else 
        cout << "No\n";

    return 0;
}
