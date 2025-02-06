#include<bits/stdc++.h>

using namespace std;

const int inf = 1000000000;

bool chmin(int &a, int b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

// Makes a table of distances from (si, sj)
// Gives inf if it is unreachable
vector<vector<int>> dist(int h, int w, const vector<string> &a, int si, int sj) {
    vector res(h, vector<int>(w, inf));
    res[si][sj] = 0;
    queue<pair<int, int>> q;
    q.emplace(si, sj);
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if (ni < 0 or ni >= h or nj < 0 or nj >= w) continue;
            if (a[ni][nj] == '#') continue;
            if (chmin(res[ni][nj], res[i][j] + 1)) q.emplace(ni, nj);
        }
    }
    return res;
}

int main() {
    int h, w, t;
    cin >> h >> w >> t;
    vector<string> a(h);
    int si, sj, gi, gj;
    vector<pair<int, int>> ls;
    for (int i = 0; i < h; i++) {
        cin >> a[i];
        for (int j = 0; j < w; j++) {
            if (a[i][j] == 'S') si = i, sj = j;
            if (a[i][j] == 'G') gi = i, gj = j;
            if (a[i][j] == 'o') ls.emplace_back(i, j);
        }
    }
    int cnt = ls.size();
    
    vector d(cnt, vector<vector<int>>()); // d[i] : distance table starting from the i-th candy square
    for (int i = 0; i < cnt; i++) d[i] = dist(h, w, a, ls[i].first, ls[i].second);
    
    vector dp(1 << cnt, vector<int>(cnt, inf));
    for (int i = 0; i < cnt; i++) dp[1 << i][i] = d[i][si][sj];
    for (int s = 1; s < (1 << cnt); s++) {
        for (int last = 0; last < cnt; last++) {
            if (dp[s][last] == inf) continue;
            for (int nx = 0; nx < cnt; nx++) {
                if (s >> nx & 1) continue;
                chmin(dp[s | 1 << nx][nx], dp[s][last] + d[last][ls[nx].first][ls[nx].second]);
            }
        }
    }
    
    int ans = -1;
    if (dist(h, w, a, si, sj)[gi][gj] <= t) ans = 0;
    for (int s = 1; s < (1 << cnt); s++) {
        for (int last = 0; last < cnt; last++) {
            if (dp[s][last] + d[last][gi][gj] <= t) {
                int now = 0;
                for (int i = 0; i < cnt; i++) if (s >> i & 1) ++now;
                ans = max(ans, now);
            }
        }
    }
    cout << ans << endl;
}


// does hits make wany wsens weat erall w