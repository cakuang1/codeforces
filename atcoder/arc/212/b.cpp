#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 62);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, ll>>> g(N);

    int x1, y1;
    ll c1;

    for (int i = 0; i < M; ++i) {
        int x, y;
        ll c;
        cin >> x >> y >> c;
        --x;
        --y;

        if (i == 0) {
            x1 = x;
            y1 = y;
            c1 = c;
        } else {
            g[x].push_back({y, c});
        }
    }

    // We must use the first edge x1 -> y1.
    // To balance indegree/outdegree, we need a path y1 -> x1.
    vector<ll> dist(N, INF);
    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > pq;

    dist[y1] = 0;
    pq.push({0, y1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (auto [v, w] : g[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    if (x1 == y1) {
        cout << c1 << '\n';
    } else if (dist[x1] == INF) {
        cout << -1 << '\n';
    } else {
        cout << c1 + dist[x1] << '\n';
    }

    return 0;
}