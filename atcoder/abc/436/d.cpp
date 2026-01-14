#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;

    vector<string> S(H);
    for (int i = 0; i < H; i++) cin >> S[i];

    // Store warp positions for each letter
    vector<vector<pair<int,int>>> warp(26);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if ('a' <= S[i][j] && S[i][j] <= 'z') {
                warp[S[i][j] - 'a'].push_back({i, j});
            }
        }
    }

    const int INF = 1e9;
    vector<vector<int>> dist(H, vector<int>(W, INF));
    queue<pair<int,int>> q;

    dist[0][0] = 0;
    q.push({0, 0});

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        int d = dist[x][y];

        // Walk
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (S[nx][ny] == '#') continue;
            if (dist[nx][ny] > d + 1) {
                dist[nx][ny] = d + 1;
                q.push({nx, ny});
            }
        }

        // Warp
        if ('a' <= S[x][y] && S[x][y] <= 'z') {
            int c = S[x][y] - 'a';
            for (auto [nx, ny] : warp[c]) {
                if (dist[nx][ny] > d + 1) {
                    dist[nx][ny] = d + 1;
                    q.push({nx, ny});
                }
            }
            // Important: prevent reuse
            warp[c].clear();
        }
    }

    int ans = dist[H-1][W-1];
    cout << (ans == INF ? -1 : ans) << "\n";
    return 0;
}


// wesm iwnerw sifssawp w
// wyeou ars ive. ian itnngss seuqncspP we

