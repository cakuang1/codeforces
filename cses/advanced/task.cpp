#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct MCMF {
    struct Edge {
        int to, rev, cap;
        ll cost;
    };
    int N;
    vector<vector<Edge>> G;
    MCMF(int N) : N(N), G(N) {}

    void addEdge(int u, int v, int cap, ll cost) {
        Edge a{v, (int)G[v].size(), cap, cost};
        Edge b{u, (int)G[u].size(), 0, -cost};
        G[u].push_back(a);
        G[v].push_back(b);
    }

    pair<ll, int> minCostMaxFlow(int s, int t, int maxf) {
        ll flowCost = 0;
        int flow = 0;
        vector<ll> dist(N), pot(N);
        vector<int> pv(N), pe(N);

        while (flow < maxf) {
            fill(dist.begin(), dist.end(), LLONG_MAX);
            dist[s] = 0;
            priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
            pq.push({0,s});
            while (!pq.empty()) {
                auto [d,u] = pq.top(); pq.pop();
                if (d != dist[u]) continue;
                for (int i=0; i<(int)G[u].size(); i++) {
                    auto &e = G[u][i];
                    if (e.cap > 0) {
                        ll nd = d + e.cost + pot[u] - pot[e.to];
                        if (nd < dist[e.to]) {
                            dist[e.to] = nd;
                            pv[e.to] = u;
                            pe[e.to] = i;
                            pq.push({nd,e.to});
                        }
                    }
                }
            }
            if (dist[t] == LLONG_MAX) break;
            for (int i=0; i<N; i++) if (dist[i] < LLONG_MAX) pot[i] += dist[i];
            int aug = maxf - flow;
            for (int v=t; v!=s; v=pv[v]) {
                aug = min(aug, G[pv[v]][pe[v]].cap);
            }
            flow += aug;
            flowCost += (ll)aug * pot[t];
            for (int v=t; v!=s; v=pv[v]) {
                auto &e = G[pv[v]][pe[v]];
                e.cap -= aug;
                G[v][e.rev].cap += aug;
            }
        }
        return {flowCost, flow};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i=0; i<n; i++) 
        for (int j=0; j<n; j++) 
            cin >> cost[i][j];

    int S = 2*n, T = 2*n+1;
    MCMF mcmf(2*n+2);

    // source to employees
    for (int i=0; i<n; i++) mcmf.addEdge(S, i, 1, 0);
    // tasks to sink
    for (int j=0; j<n; j++) mcmf.addEdge(n+j, T, 1, 0);
    // employee i to task j
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            mcmf.addEdge(i, n+j, 1, cost[i][j]);
        }
    }

    auto [ans, flow] = mcmf.minCostMaxFlow(S, T, n);
    cout << ans << "\n";

    // recover assignment
    vector<pair<int,int>> assignment;
    for (int i=0; i<n; i++) {
        for (auto &e : mcmf.G[i]) {
            if (e.to >= n && e.to < 2*n && e.cap == 0) {
                assignment.push_back({i+1, e.to-n+1});
            }
        }
    }
    for (auto [emp, task] : assignment) {
        cout << emp << " " << task << "\n";
    }
}
