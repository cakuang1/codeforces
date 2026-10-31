#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, T;
    cin >> H >> W >> T;

    vector<string> a(H);
    for (auto &s : a) cin >> s;

    pair<int,int> S, G;
    vector<pair<int,int>> candy;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (a[i][j] == 'S') S = {i, j};
            if (a[i][j] == 'G') G = {i, j};
            if (a[i][j] == 'o') candy.push_back({i, j});
        }
    }

    int K = candy.size();

    // Important nodes: candies [0..K-1], S=K, G=K+1
    vector<pair<int,int>> p = candy;
    p.push_back(S);
    p.push_back(G);

    int M = K + 2;
    vector<vector<int>> dist(M, vector<int>(M, INF));

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int s = 0; s < M; s++) {
        vector<vector<int>> d(H, vector<int>(W, INF));
        queue<pair<int,int>> q;

        auto [sx, sy] = p[s];
        d[sx][sy] = 0;
        q.push({sx, sy});

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int z = 0; z < 4; z++) {
                int nx = x + dx[z];
                int ny = y + dy[z];

                if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                    continue;

                if (a[nx][ny] == '#') continue;
                if (d[nx][ny] != INF) continue;

                d[nx][ny] = d[x][y] + 1;
                q.push({nx, ny});
            }
        }

        for (int j = 0; j < M; j++) {
            auto [x, y] = p[j];
            dist[s][j] = d[x][y];
        }
    }

    int start = K, goal = K + 1;

    if (dist[start][goal] > T) {
        cout << -1 << '\n';
        return 0;
    }

    int ans = 0;

    int FULL = 1 << K;
    vector<vector<int>> dp(FULL, vector<int>(K, INF));

    for (int i = 0; i < K; i++) {
        dp[1 << i][i] = dist[start][i];
    }

    for (int mask = 1; mask < FULL; mask++) {
        for (int i = 0; i < K; i++) {
            if (!(mask & (1 << i))) continue;
            if (dp[mask][i] == INF) continue;

            // Finish at G
            if (dp[mask][i] + dist[i][goal] <= T) {
                ans = max(ans, __builtin_popcount((unsigned)mask));
            }

            // Visit another candy
            for (int j = 0; j < K; j++) {
                if (mask & (1 << j)) continue;
                if (dist[i][j] == INF) continue;

                int nmask = mask | (1 << j);

                dp[nmask][j] = min(
                    dp[nmask][j],
                    dp[mask][i] + dist[i][j]
                );
            }
        }
    }

    cout << ans << '\n';
}