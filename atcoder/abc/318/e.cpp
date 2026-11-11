
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    pair<int, int> S, G;

    for (int i = 0; i < H; i++) {
        cin >> grid[i];

        for (int j = 0; j < W; j++) {
            if (grid[i][j] == 'S') S = {i, j};
            if (grid[i][j] == 'G') G = {i, j};
        }
    }

    vector<vector<bool>> unsafe(H, vector<bool>(W, false));

    auto isPerson = [&](char c) {
        return c == '>' || c == '<' || c == '^' || c == 'v';
    };

    // Left -> Right: vision from '>'
    for (int i = 0; i < H; i++) {
        bool watching = false;

        for (int j = 0; j < W; j++) {
            char c = grid[i][j];

            if (c == '#' || isPerson(c)) {
                watching = (c == '>');
            } else if (watching) {
                unsafe[i][j] = true;
            }
        }
    }

    // Right -> Left: vision from '<'
    for (int i = 0; i < H; i++) {
        bool watching = false;

        for (int j = W - 1; j >= 0; j--) {
            char c = grid[i][j];

            if (c == '#' || isPerson(c)) {
                watching = (c == '<');
            } else if (watching) {
                unsafe[i][j] = true;
            }
        }
    }

    // Top -> Bottom: vision from 'v'
    for (int j = 0; j < W; j++) {
        bool watching = false;

        for (int i = 0; i < H; i++) {
            char c = grid[i][j];

            if (c == '#' || isPerson(c)) {
                watching = (c == 'v');
            } else if (watching) {
                unsafe[i][j] = true;
            }
        }
    }

    // Bottom -> Top: vision from '^'
    for (int j = 0; j < W; j++) {
        bool watching = false;

        for (int i = H - 1; i >= 0; i--) {
            char c = grid[i][j];

            if (c == '#' || isPerson(c)) {
                watching = (c == '^');
            } else if (watching) {
                unsafe[i][j] = true;
            }
        }
    }

    // BFS
    vector<vector<int>> dist(H, vector<int>(W, -1));
    queue<pair<int, int>> q;

    q.push(S);
    dist[S.first][S.second] = 0;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (make_pair(x, y) == G) {
            cout << dist[x][y] << '\n';
            return 0;
        }

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                continue;

            if (grid[nx][ny] != '.' && grid[nx][ny] != 'G')
                continue;

            if (unsafe[nx][ny] || dist[nx][ny] != -1)
                continue;

            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }

    cout << -1 << '\n';
    return 0;
}
