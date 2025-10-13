#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev; int cap; };
    int N, s, t;
    vector<vector<Edge>> g;
    vector<int> level, it;

    Dinic(int n): N(n), g(n), level(n), it(n) {}

    void add_edge(int u, int v, int c) {
        Edge a{v, (int)g[v].size(), c};
        Edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
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
            Edge &e = g[v][i];
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

    int flow(int S, int T) {
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
    cin >> n >> m;
    vector<int> p(n), c(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) cin >> c[i];

    int d; cin >> d;
    vector<int> leave(d);
    vector<int> alive(n, 1);
    for (int i = 0; i < d; i++) {
        cin >> leave[i];
        --leave[i];
        alive[leave[i]] = 0;
    }

    int P = m + 1, C = m;
    int S = 0;
    auto pot_idx  = [&](int pv){ return 1 + pv; };
    auto club_idx = [&](int cv){ return 1 + P + (cv - 1); };
    int T = 1 + P + C;

    Dinic din(T + 1);

    for (int cv = 1; cv <= m; ++cv)
        din.add_edge(club_idx(cv), T, 1);

    for (int i = 0; i < n; ++i)
        if (alive[i] && 0 <= p[i] && p[i] <= m)
            din.add_edge(pot_idx(p[i]), club_idx(c[i]), 1);

    int cur_mex = 0;
    din.add_edge(S, pot_idx(0), 1);

    // Extend mex initially
    while (cur_mex <= m) {
        int add = din.flow(S, T);
        if (add == 0) break;
        ++cur_mex;
        if (cur_mex <= m) din.add_edge(S, pot_idx(cur_mex), 1);
    }

    vector<int> ans(d);

    for (int i = d - 1; i >= 0; --i) {
        ans[i] = cur_mex;  // record BEFORE adding this student back
        int id = leave[i];
        if (0 <= p[id] && p[id] <= m)
            din.add_edge(pot_idx(p[id]), club_idx(c[id]), 1);

        while (cur_mex <= m) {
            int add = din.flow(S, T);
            if (add == 0) break;
            ++cur_mex;
            if (cur_mex <= m)
                din.add_edge(S, pot_idx(cur_mex), 1);
        }
    }

    for (int x : ans) cout << x << '\n';
}




