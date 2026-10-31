#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + m + 1);

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;

        for (int j = 0; j < a; j++) {
            int x;
            cin >> x;

            // Element vertex: x
            // Set vertex: m + i
            g[x].push_back(m + i);
            g[m + i].push_back(x);
        }
    }

    vector<int> dist(n + m + 1, -1);
    queue<int> q;

    dist[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : g[v]) {
            if (dist[u] != -1) continue;

            dist[u] = dist[v] + 1;
            q.push(u);
        }
    }

    if (dist[m] == -1) {
        cout << -1 << '\n';
    } else {
        cout << dist[m] / 2 - 1 << '\n';
    }
} 

