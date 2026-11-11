
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, ll>>> adj(N);

    for (int i = 0; i < M; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        --a;
        --b;

        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    ll ans = 0;
    vector<bool> visited(N, false);

    auto dfs = [&](auto&& self, int u, ll dist) -> void {
        ans = max(ans, dist);

        for (auto [v, w] : adj[u]) {
            if (visited[v]) continue;

            visited[v] = true;
            self(self, v, dist + w);
            visited[v] = false;
        }
    };

    for (int start = 0; start < N; start++) {
        visited[start] = true;
        dfs(dfs, start, 0);
        visited[start] = false;
    }

    cout << ans << '\n';
}
