#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct MCMF {
    struct Edge { int to, rev, cap; ll cost; };
    int N;
    vector<vector<Edge>> G;
    vector<ll> dist, pot;
    vector<int> prevv, preve;

    MCMF(int n): N(n), G(n), dist(n), pot(n), prevv(n), preve(n) {}

    void addEdge(int from, int to, int cap, ll cost) {
        G[from].push_back({to, (int)G[to].size(), cap, cost});
        G[to].push_back({from, (int)G[from].size()-1, 0, -cost});
    }

    pair<int,ll> minCostFlow(int s, int t, int maxf) {
        int flow = 0; ll cost = 0;
        fill(pot.begin(), pot.end(), 0);
        while (flow < maxf) {
            priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
            fill(dist.begin(), dist.end(), LLONG_MAX);
            dist[s] = 0; pq.push({0,s});
            while (!pq.empty()) {
                auto [d,v] = pq.top(); pq.pop();
                if (dist[v] < d) continue;
                for (int i=0; i<(int)G[v].size(); i++) {
                    Edge &e = G[v][i];
                    if (e.cap > 0 && dist[e.to] > d + e.cost + pot[v] - pot[e.to]) {
                        dist[e.to] = d + e.cost + pot[v] - pot[e.to];
                        prevv[e.to] = v; preve[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }
            if (dist[t] == LLONG_MAX) break;
            for (int v=0; v<N; v++) if (dist[v] < LLONG_MAX) pot[v] += dist[v];
            int addf = maxf - flow;
            for (int v=t; v!=s; v=prevv[v]) {
                addf = min(addf, G[prevv[v]][preve[v]].cap);
            }
            flow += addf;
            cost += (ll)addf * pot[t];
            for (int v=t; v!=s; v=prevv[v]) {
                Edge &e = G[prevv[v]][preve[v]];
                e.cap -= addf;
                G[v][e.rev].cap += addf;
            }
        }
        return {flow,cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,k; cin >> n >> m >> k;
    MCMF g(n);
    for (int i=0;i<m;i++) {
        int a,b,r,c; cin >> a >> b >> r >> c;
        --a; --b;
        g.addEdge(a,b,r,c); // directed edge only!
    }
    auto [flow,cost] = g.minCostFlow(0,n-1,k);
    if (flow < k) cout << -1 << "\n";
    else cout << cost << "\n";
}

// 