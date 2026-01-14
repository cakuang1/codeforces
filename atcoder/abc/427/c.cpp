#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<pair<int,int>> edges;
    edges.reserve(M);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        edges.emplace_back(u, v);
    }

    int ans = M;

    // mask encodes a 2-coloring: color(i) = (mask >> i) & 1
    for (int mask = 0; mask < (1 << N); mask++) {
        int bad = 0;
        for (auto [u, v] : edges) {
            int cu = (mask >> u) & 1;
            int cv = (mask >> v) & 1;
            if (cu == cv) bad++;
        }
        ans = min(ans, bad);
    }

    cout << ans << '\n';
    return 0;
}


// thsi rmaksets ser