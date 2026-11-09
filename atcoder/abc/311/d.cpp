
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> s(n);
    for (auto &row : s) cin >> row;

    vector<vector<bool>> seen(n, vector<bool>(m, false));
    vector<vector<bool>> touched(n, vector<bool>(m, false));

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    queue<pair<int,int>> q;
    q.push({1, 1});
    seen[1][1] = true;
    touched[1][1] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x, ny = y;

            while (s[nx + dx[d]][ny + dy[d]] == '.') {
                nx += dx[d];
                ny += dy[d];
                touched[nx][ny] = true;
            }

            if (!seen[nx][ny]) {
                seen[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans += touched[i][j];
        }
    }

    cout << ans << '\n';
}
