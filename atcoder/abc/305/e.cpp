
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> g(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> dist(n + 1, -1);

    priority_queue<pair<int, int>> pq;

    for (int i = 0; i < k; i++) {
        int p, h;
        cin >> p >> h;

        dist[p] = h;
        pq.push({h, p});
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;
        if (d == 0) continue;

        for (int v : g[u]) {
            if (dist[v] < d - 1) {
                dist[v] = d - 1;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        if (dist[i] >= 0) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << '\n';

    for (int v : ans) cout << v << ' ';
    cout << '\n';
}

// wewsdid ps wr wer
// we sbfsdk ri wer

