#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    if (N < 6) {
        cout << -1 << '\n';
        return 0;
    }

    vector<pair<int,int>> edges;

    if (N % 2 == 0) {
        int m = N / 2;

        // Left:  1..m
        // Right: m+1..N
        // Add all bipartite edges except (i, N+1-i).
        for (int i = 1; i <= m; i++) {
            for (int j = m + 1; j <= N; j++) {
                if (j == N + 1 - i) continue;
                edges.push_back({i, j});
            }
        }
    } else {
        int m = (N - 1) / 2;

        // Left:  1..m
        // Right: m+1..N
        //
        // For i=1..m, remove (i, N-i).
        // Vertex N is the special leftover vertex and is connected
        // to every vertex on the left side.
        for (int i = 1; i <= m; i++) {
            for (int j = m + 1; j <= N; j++) {
                if (j == N - i) continue;
                edges.push_back({i, j});
            }
        }
    }

    cout << edges.size() << '\n';
    for (auto [u, v] : edges) {
        cout << u << ' ' << v << '\n';
    }

    return 0;
}
// werwofsisnalrwr




//w ear sso erio