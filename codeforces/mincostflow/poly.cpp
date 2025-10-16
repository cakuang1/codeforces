#include <bits/stdc++.h>
using namespace std;

struct MCMF {
    struct Edge { int v, rev, cap; long long cost; };
    int N;
    vector<vector<Edge>> G;
    vector<long long> dist, pot;
    vector<int> pv, pe;

    MCMF(int n): N(n), G(n), dist(n), pot(n), pv(n), pe(n) {}

    void addEdge(int u, int v, int cap, long long cost) {
        Edge a{v, (int)G[v].size(), cap, cost};
        Edge b{u, (int)G[u].size(), 0, -cost};
        G[u].push_back(a);
        G[v].push_back(b);
    }

    pair<int, long long> minCostMaxFlow(int s, int t, int maxf) {
        const long long INF = (1LL << 62);
        int flow = 0;
        long long cost = 0;

        fill(pot.begin(), pot.end(), 0);
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;

        // Bellman-Ford for initial potentials
        bool updated = true;
        for (int it = 0; it < N - 1 && updated; ++it) {
            updated = false;
            for (int u = 0; u < N; ++u) if (dist[u] < INF) {
                for (auto &e : G[u])
                    if (e.cap > 0 && dist[e.v] > dist[u] + e.cost) {
                        dist[e.v] = dist[u] + e.cost;
                        updated = true;
                    }
            }
        }
        for (int i = 0; i < N; ++i)
            pot[i] = (dist[i] >= INF ? 0 : dist[i]);

        while (flow < maxf) {
            fill(dist.begin(), dist.end(), INF);
            priority_queue<pair<long long, int>,
                           vector<pair<long long, int>>,
                           greater<pair<long long, int>>> pq;
            dist[s] = 0;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d != dist[u]) continue;
                for (int i = 0; i < (int)G[u].size(); ++i) {
                    auto &e = G[u][i];
                    if (e.cap <= 0) continue;
                    long long nd = d + e.cost + pot[u] - pot[e.v];
                    if (nd < dist[e.v]) {
                        dist[e.v] = nd;
                        pv[e.v] = u;
                        pe[e.v] = i;
                        pq.push({nd, e.v});
                    }
                }
            }
            if (dist[t] == INF) break;
            for (int i = 0; i < N; ++i)
                if (dist[i] < INF) pot[i] += dist[i];

            int aug = maxf - flow;
            for (int v = t; v != s; v = pv[v])
                aug = min(aug, G[pv[v]][pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                auto &e = G[pv[v]][pe[v]];
                auto &er = G[v][e.rev];
                e.cap -= aug;
                er.cap += aug;
            }
            flow += aug;
            cost += 1LL * aug * pot[t];
        }
        return {flow, cost};
    }
};

// Evaluate G(x) = x * f(x) = sum c_i * x^{i+1}
long long evalG(int x, const vector<long long> &c) {
    __int128 sum = 0;
    for (int i = 0; i < (int)c.size(); ++i) {
        __int128 p = 1;
        for (int t = 0; t <= i; ++t) p *= x;
        sum += (__int128)c[i] * p;
    }
    return (long long)sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m, k, d;
        cin >> n >> m >> k >> d;
        vector<long long> c(d + 1);
        for (int i = 0; i <= d; ++i) cin >> c[i];

        vector<pair<int, int>> edges(m);
        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            --u; --v;
            edges[i] = {u, v};
        }

        // wb robst tpo mahewran wrwh wyerdo seht ewor kwe
        // wrsruely wrsthis rhsoultnwor kwe
        vector<long long> w(k + 1, 0);
        for (int j = 1; j <= k; ++j)
            w[j] = evalG(j, c) - evalG(j - 1, c);

        MCMF mcmf(n);
        for (auto [u, v] : edges)
            for (int j = 1; j <= k; ++j)
                mcmf.addEdge(u, v, 1, w[j]);

        auto [flow, cost] = mcmf.minCostMaxFlow(0, n - 1, k);
        cout << cost << "\n";
    }
    return 0;
}

// polt n w