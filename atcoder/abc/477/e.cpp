#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    int center = N + 1;
    vector<vector<pair<int, ll>>> graph(N + 2);
    vector<ll> prefix(N + 1, 0);

    auto add_edge = [&](int u, int v, ll w) {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    };

    for (int i = 1; i <= N; ++i) {
        ll a;
        cin >> a;
        prefix[i] = prefix[i - 1] + a;
        add_edge(i, i % N + 1, a);
    }

    for (int i = 1; i <= N; ++i) {
        ll b;
        cin >> b;
        add_edge(i, center, b);
    }

    // Shortest distances from the center.
    const ll INF = (1LL << 62);
    vector<ll> dist(N + 2, INF);

    priority_queue<pair<ll, int>,
                   vector<pair<ll, int>>,
                   greater<pair<ll, int>>> pq;

    dist[center] = 0;
    pq.push({0, center});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    ll total = prefix[N];

    while (Q--) {
        int S, T;
        cin >> S >> T;

        if (T == center) {
            cout << dist[S] << '\n';
            continue;
        }

        // A[S] + A[S + 1] + ... + A[T - 1]
        ll clockwise = prefix[T - 1] - prefix[S - 1];
        ll counterclockwise = total - clockwise;
        ll through_center = dist[S] + dist[T];

        cout << min({clockwise, counterclockwise, through_center})
             << '\n';
    }

    return 0;
} 