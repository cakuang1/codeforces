#include <bits/stdc++.h>
using namespace std;

static const int INF = 1 << 30;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int h, w;
        cin >> h >> w;

        vector<string> s(h);
        for (int i = 0; i < h; i++) cin >> s[i];

        // dp[x][y][dir]
        vector<vector<array<int,4>>> dp(h, vector<array<int,4>>(w, {INF, INF, INF, INF}));

        deque<array<int,4>> dq;  
        // Start from "pre-pos" = (0, -1) entering from direction 1 (right)
        dq.push_back({0, 0, -1, 1});

        // Map mirrors A,B,C
        unordered_map<char,int> d = {{'A',0},{'B',1},{'C',3}};

        while (!dq.empty()) {
            auto [cost, px, py, dir] = dq.front();
            dq.pop_front();

            int x = px + dx[dir];
            int y = py + dy[dir];

            if (!(0 <= x && x < h && 0 <= y && y < w))
                continue;

            for (int ndir = 0; ndir < 4; ndir++) {
                // disallow reverse direction
                if ((dir ^ ndir) == 2) continue;

                int zero_cost_cond = d[s[x][y]];
                int ncost = cost + (((dir ^ ndir) == zero_cost_cond) ? 0 : 1);

                if (ncost < dp[x][y][ndir]) {
                    dp[x][y][ndir] = ncost;

                    if (ncost == cost) {
                        dq.push_front({ncost, x, y, ndir});
                    } else {
                        dq.push_back({ncost, x, y, ndir});
                    }
                }
            }
        }

        cout << dp[h-1][w-1][1] << "\n";
    }
    return 0;
}
