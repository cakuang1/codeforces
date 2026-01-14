#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev, cap; };
    int N, s, t;
    vector<vector<Edge>> g;
    vector<int> level, it;

    Dinic(int n): N(n), g(n), level(n), it(n), s(-1), t(-1) {}

    void add_edge(int u, int v, int c) {
        Edge a{v, (int)g[v].size(), c};
        Edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0; q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : g[v]) if (e.cap > 0 && level[e.to] == -1) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
        return level[t] != -1;
    }

    int dfs(int v, int f) {
        if (!f || v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); ++i) {
            auto &e = g[v][i];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                int pushed = dfs(e.to, min(f, e.cap));
                if (pushed) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    int maxflow(int S, int T) {
        s = S; t = T;
        int res = 0;
        while (bfs()) {
            fill(it.begin(), it.end(), 0);
            while (int pushed = dfs(s, INT_MAX))
                res += pushed;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Count black cells
    int black = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (a[i][j] == '#') ++black;

    // Assign IDs to horizontal borders (between (i,j) and (i,j+1))
    // and vertical borders (between (i,j) and (i+1,j)).
    vector<vector<int>> hid(n, vector<int>(m, -1));
    vector<vector<int>> vid(n, vector<int>(m, -1));
    int H = 0, V = 0;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j + 1 < m; ++j)
            if (a[i][j] == '#' && a[i][j+1] == '#')
                hid[i][j] = H++;

    for (int i = 0; i + 1 < n; ++i)
        for (int j = 0; j < m; ++j)
            if (a[i][j] == '#' && a[i+1][j] == '#')
                vid[i][j] = V++;

    // Build bipartite graph: S -> H-nodes -> V-nodes -> T
    int S = 0;
    int baseH = 1;
    int baseV = baseH + H;
    int T = baseV + V;
    Dinic din(T + 1);

    // S -> horizontal borders
    for (int h = 0; h < H; ++h)
        din.add_edge(S, baseH + h, 1);

    // vertical borders -> T
    for (int v = 0; v < V; ++v)
        din.add_edge(baseV + v, T, 1);

    auto add_conflict = [&](int hi, int vi) {
        if (hi >= 0 && vi >= 0)
            din.add_edge(baseH + hi, baseV + vi, 1);
    };

    //wesdurly etwhit we shod wletw werowrk we
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j + 1 < m; ++j) {
            int h = hid[i][j];
            if (h < 0) continue;
            // Endpoints: (i,j) and (i,j+1)
            // Vertical sharing (i,j): above (i-1,j) and below (i,j)
            if (i - 1 >= 0 && vid[i-1][j] >= 0) add_conflict(h, vid[i-1][j]);
            if (i + 0 < n - 0 && vid[i][j] >= 0) add_conflict(h, vid[i][j]);
            // Vertical sharing (i,j+1): above (i-1,j+1) and below (i,j+1)
            if (i - 1 >= 0 && vid[i-1][j+1] >= 0) add_conflict(h, vid[i-1][j+1]);
            if (i + 0 < n - 0 && vid[i][j+1] >= 0) add_conflict(h, vid[i][j+1]);
        }
    }

    int M = din.maxflow(S, T);            // maximum matching
    int E = H + V;                         // #borders
    int answer = black - (E - M);          // B - E + M

    // weshqr eignwer
    cout << answer << "\n";
    return 0;
}


// maxi mweriwm weamon w nwerw owf werlw ower
/? wd osthw w