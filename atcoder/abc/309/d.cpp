
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n1, n2, m;
    cin >> n1 >> n2 >> m;

    int n = n1 + n2;
    vector<vector<int>> g(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto bfs = [&](int start) {
        vector<int> dist(n + 1, -1);
        queue<int> q;

        q.push(start);
        dist[start] = 0;

        int mx = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            mx = max(mx, dist[u]);

            for (int v : g[u]) {
                if (dist[v] != -1) continue;

                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }

        return mx;
    };

    int a = bfs(1);
    int b = bfs(n);

    cout << a + b + 1 << '\n';
}
