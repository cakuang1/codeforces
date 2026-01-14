#include <bits/stdc++.h>
using namespace std;

struct MCMF {
    struct Edge {
        int to, rev, cap;
        long long cost;
    };

    int n;
    vector<vector<Edge> > g;
    vector<long long> dist, pot;
    vector<int> parent_v, parent_e;

    MCMF(int n) {
        this->n = n;
        g.assign(n, vector<Edge>());
        dist.resize(n);
        pot.resize(n);
        parent_v.resize(n);
        parent_e.resize(n);
    }

    void add_edge(int u, int v, int cap, long long cost) {
        Edge a = {v, (int)g[v].size(), cap, cost};
        Edge b = {u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    pair<long long, long long> min_cost_max_flow(int s, int t, int maxf) {
        long long flow = 0, cost = 0;
        fill(pot.begin(), pot.end(), 0);

        while (flow < maxf) {
            fill(dist.begin(), dist.end(), LLONG_MAX);
            dist[s] = 0;
            typedef pair<long long,int> pli;
            priority_queue<pli, vector<pli>, greater<pli> > pq;
            pq.push(make_pair(0LL, s));

            while (!pq.empty()) {
                pli top = pq.top();
                pq.pop();
                long long d = top.first;
                int v = top.second;
                if (d != dist[v]) continue;

                for (int i = 0; i < (int)g[v].size(); ++i) {
                    Edge &e = g[v][i];
                    if (e.cap <= 0) continue;
                    long long nd = d + e.cost + pot[v] - pot[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        parent_v[e.to] = v;
                        parent_e[e.to] = i;
                        pq.push(make_pair(nd, e.to));
                    }
                }
            }

            if (dist[t] == LLONG_MAX) break;
            for (int i = 0; i < n; ++i)
                if (dist[i] < LLONG_MAX)
                    pot[i] += dist[i];

            int addf = maxf - flow;
            for (int v = t; v != s; v = parent_v[v])
                addf = min(addf, g[parent_v[v]][parent_e[v]].cap);

            flow += addf;
            cost += 1LL * addf * pot[t];
            for (int v = t; v != s; v = parent_v[v]) {
                Edge &e = g[parent_v[v]][parent_e[v]];
                e.cap -= addf;
                g[v][e.rev].cap += addf;
            }
        }
        return make_pair(flow, cost);
    }
};


// 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int j = 0; j < n; ++j) cin >> b[j];

    vector<vector<int> > c(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> c[i][j];

            //w e w
            int S = 2 * n;
    int T = S + 1;
    MCMF mcmf(T + 1);
    
    // demtiern wecapitwyw wr
    for (int i = 0; i < n; ++i)
        mcmf.add_edge(S, i, a[i], 0);
    for (int j = 0; j < n; ++j)
        mcmf.add_edge(n + j, T, b[j], 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mcmf.add_edge(i, n + j, 1, -c[i][j]);

    int total = 0;
    for (int i = 0; i < n; ++i) total += a[i];

    pair<long long, long long> res = mcmf.min_cost_max_flow(S, T, total);
    long long flow = res.first;
    long long cost = res.second;

    if (flow < total) {
        cout << -1 << "\n";
        return 0;
    }

    cout << -cost << "\n";

    vector<string> grid(n, string(n, '.'));
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < (int)mcmf.g[i].size(); ++k) {
            MCMF::Edge e = mcmf.g[i][k];
            if (e.to >= n && e.to < 2 * n && e.cap == 0)
                grid[i][e.to - n] = 'X';
        }

    for (int i = 0; i < n; ++i)
        cout << grid[i] << "\n";

    return 0;
}

 

// minc c w