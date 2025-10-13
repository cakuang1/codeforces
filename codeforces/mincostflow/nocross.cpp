#include <bits/stdc++.h>
using namespace std;

struct MinCostMaxFlow {
    struct Edge {
        int to, rev;
        int cap;
        long long cost;
    };

    int N;
    vector<vector<Edge>> G;
    vector<long long> dist, pot;
    vector<int> prevv, preve;

    MinCostMaxFlow(int n) : N(n), G(n), dist(n), pot(n), prevv(n), preve(n) {}

    void add_edge(int from, int to, int cap, long long cost) {
        G[from].push_back({to, (int)G[to].size(), cap, cost});
        G[to].push_back({from, (int)G[from].size() - 1, 0, -cost});
    }

    // returns {flow, cost}
    pair<int, long long> min_cost_flow(int s, int t, int maxf) {
        const long long INF = LLONG_MAX / 4;
        int flow = 0;
        long long cost = 0;
        fill(pot.begin(), pot.end(), 0);

        // Bellman-Ford init (optional for negative costs)
        {
            vector<long long> d(N, INF);
            d[s] = 0;
            bool upd = true;
            while (upd) {
                upd = false;
                for (int v = 0; v < N; ++v) {
                    if (d[v] == INF) continue;
                    for (auto &e : G[v]) {
                        if (e.cap > 0 && d[e.to] > d[v] + e.cost) {
                            d[e.to] = d[v] + e.cost;
                            upd = true;
                        }
                    }
                }
            }
            for (int v = 0; v < N; ++v)
                if (d[v] < INF) pot[v] = d[v];
        }

        while (flow < maxf) {
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (dist[v] < d) continue;
                for (int i = 0; i < (int)G[v].size(); ++i) {
                    auto &e = G[v][i];
                    if (e.cap > 0) {
                        long long nd = d + e.cost + pot[v] - pot[e.to];
                        if (nd < dist[e.to]) {
                            dist[e.to] = nd;
                            prevv[e.to] = v;
                            preve[e.to] = i;
                            pq.push({nd, e.to});
                        }
                    }
                }
            }

            if (dist[t] == INF) break; // cannot send more flow

            for (int v = 0; v < N; ++v)
                if (dist[v] < INF)
                    pot[v] += dist[v];

            int addf = maxf - flow;
            for (int v = t; v != s; v = prevv[v])
                addf = min(addf, G[prevv[v]][preve[v]].cap);

            flow += addf;
            cost += (long long)addf * pot[t];
            for (int v = t; v != s; v = prevv[v]) {
                auto &e = G[prevv[v]][preve[v]];
                e.cap -= addf;
                G[v][e.rev].cap += addf;
            }
        }
        return {flow, cost};
    }
};



// edwerblue grabv w wis hwat e
// www rdo ses htiswor kwe
// how do youwe rmode wtweh contrians? we
//
// rwmodel ain fora. red vetex we
// 
// red verteicse web werwe.
// w w
// different xconaitn ewr
// net. color we
// w

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<long long> Ax(N), Ay(N), Cx(N), Cy(N);
    for (int i = 0; i < N; ++i) cin >> Ax[i] >> Ay[i];
    for (int i = 0; i < N; ++i) cin >> Cx[i] >> Cy[i];

    const long double SCALE = 1.5e12L; // scaling to preserve precision
    int S = 2 * N, T = S + 1;
    MinCostMaxFlow mcmf(T + 1);

    // Build graph
    for (int i = 0; i < N; ++i) {
        mcmf.add_edge(S, i, 1, 0);          // source to P_i
        mcmf.add_edge(N + i, T, 1, 0);      // Q_i to sink
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            long double dx = Ax[i] - Cx[j];
            long double dy = Ay[i] - Cy[j];
            long double dist = sqrtl(dx * dx + dy * dy);
            long long cost = (long long)(dist * SCALE + 0.5L);
            mcmf.add_edge(i, N + j, 1, cost);
        }
    }


    // 
    auto [flow, cost] = mcmf.min_cost_flow(S, T, N);
    if (flow < N) {
        cout << -1 << "\n";
        return 0;
    }
    vector<int> ans(N, -1);
    for (int i = 0; i < N; ++i) {
        for (auto &e : mcmf.G[i]) {
            if (e.to >= N && e.to < 2 * N && e.cap == 0) {
                ans[i] = e.to - N + 1;
                break;
            }
        }
    }


    for (int i = 0; i < N; ++i)
        cout << ans[i] << (i + 1 == N ? '\n' : ' ');
}


// wwtw wis thi r// w