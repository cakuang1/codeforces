#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev; long long cap; };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> lvl, it;

    Dinic(int n): n(n), g(n), lvl(n), it(n) {}

    void add_edge(int u, int v, long long c) {
        Edge a{v, (int)g[v].size(), c};
        Edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs() {
        fill(lvl.begin(), lvl.end(), -1);
        queue<int> q; q.push(s);
        lvl[s] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : g[v]) if (e.cap > 0 && lvl[e.to] == -1) {
                lvl[e.to] = lvl[v] + 1;
                q.push(e.to);
            }
        }
        return lvl[t] != -1;
    }

    long long dfs(int v, long long f) {
        if (!f || v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); ++i) {
            auto &e = g[v][i];
            if (e.cap > 0 && lvl[e.to] == lvl[v] + 1) {
                long long pushed = dfs(e.to, min(f, e.cap));
                if (pushed) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long long maxflow(int S, int T) {
        s = S; t = T;
        long long res = 0;
        while (bfs()) {
            fill(it.begin(), it.end(), 0);
            while (long long pushed = dfs(s, LLONG_MAX))
                res += pushed;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    vector<long long> a(N + 1);
    for (int i = 1; i <= N; ++i) cin >> a[i];

    // Nodes: 0 = S, 1..N = items, N+1 = T
    int S = 0, T = N + 1;
    Dinic din(N + 2);

    const long long INF = (long long)4e18; // big enough

    long long P = 0; // sum of positives
    for (int i = 1; i <= N; ++i) {
        if (a[i] > 0) {
            P += a[i];
            din.add_edge(S, i, a[i]);
        } else if (a[i] < 0) {
            din.add_edge(i, T, -a[i]);
        }
    }

    // Closure edges: if we keep j, we must keep every divisor d of j
    for (int j = 1; j <= N; ++j) {
        for (int d = 1; d * d <= j; ++d) {
            if (j % d == 0) {
                int d1 = d;
                int d2 = j / d;
                if (d1 < j) din.add_edge(j, d1, INF);
                if (d2 != d1 && d2 < j) din.add_edge(j, d2, INF);
            }
        }
    }

    long long C = din.maxflow(S, T);
    cout << (P - C) << "\n";
    return 0;
}



// what w sdods thsi t wemans wer we
// wcapcitww eis what we

// ai + bj w
// 0 weci wej we
// wd osthis rworwkt w

// 
// wflwoer ocontains wew

// MCF cannot wesend tht muc hwrlfwo erits imposible otuput wr- 1
// otherwise it will send exactly wrthat many wredges w
// Each edge Ri -> wCj wwiwth wflower w1 w

// chosen cell we 

// 


// d osethiw rwr rwtask weassignemnt wrsi what erw 
// w