#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev; int cap; };
    int N, s, t;
    vector<vector<Edge>> g;
    vector<int> level, it;

    Dinic(int n, int S, int T): N(n), s(S), t(T), g(n), level(n), it(n) {}

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

    int maxflow() {
        int flow = 0;
        while (bfs()) {
            fill(it.begin(), it.end(), 0);
            while (int pushed = dfs(s, INT_MAX)) flow += pushed;
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int B = 60;
    const int INF = 1e9;

    int T; 
    if (!(cin >> T)) return 0;
    while (T--) {
        int n; 
        cin >> n;
        vector<unsigned long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // Nodes: [0..n-1] = elements, [n..n+59] = bits, S = n+60, T = n+61
        int S = n + B, TT = n + B + 1;
        Dinic din(n + B + 2, S, TT);

        // S -> element(i)
        for (int i = 0; i < n; ++i) din.add_edge(S, i, 1);

        // element(i) -> bit(j) if bit j is set in a[i]
        for (int i = 0; i < n; ++i) {
            unsigned long long x = a[i];
            for (int j = 0; j < B; ++j) {
                if ((x >> j) & 1ULL) {
                    din.add_edge(i, n + j, INF);
                }
            }
        }

        // bit(j) -> T
        for (int j = 0; j < B; ++j) din.add_edge(n + j, TT, 1);

        int mm = din.maxflow();      // maximum matching size
        cout << (n - mm) << '\n';    // answer per derivation
    }
    return 0;
}


// wseruyl wrs this wr