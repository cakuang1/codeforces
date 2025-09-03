#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct MCMF {
    struct Edge {
        int to, rev, cap, orig_cap;
        ll cost;
    };
    int N;
    vector<vector<Edge>> G;
    vector<ll> dist, pot;
    vector<int> prevv, preve;

    MCMF(int n): N(n), G(n), dist(n), pot(n), prevv(n), preve(n) {}

    void addEdge(int from, int to, int cap, ll cost) {
        G[from].push_back({to, (int)G[to].size(), cap, cap, cost});
        G[to].push_back({from, (int)G[from].size()-1, 0, 0, -cost});
    }

    pair<int,ll> minCostFlow(int s, int t, int maxf) {
        int flow = 0;
        ll cost = 0;
        fill(pot.begin(), pot.end(), 0);

        while (flow < maxf) {
            priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
            fill(dist.begin(), dist.end(), LLONG_MAX);
            dist[s] = 0;
            pq.push({0,s});
            while (!pq.empty()) {
                auto [d,v] = pq.top(); pq.pop();
                if (dist[v] < d) continue;
                for (int i=0; i<(int)G[v].size(); i++) {
                    Edge &e = G[v][i];
                    if (e.cap > 0 && dist[e.to] > d + e.cost + pot[v] - pot[e.to]) {
                        dist[e.to] = d + e.cost + pot[v] - pot[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
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

    vector<vector<int>> extractPaths(int s, int t, int k) {
        vector<vector<int>> paths;
        for (int run=0; run<k; run++) {
            vector<int> path;
            int v = s;
            path.push_back(v);
            while (v != t) {
                bool moved = false;
                for (auto &e : G[v]) {
                    // flow used this edge if orig_cap==1 and cap==0
                    if (e.orig_cap == 1 && e.cap == 0) {
                        e.cap = 1; // mark as consumed
                        v = e.to;
                        path.push_back(v);
                        moved = true;
                        break;
                    }
                }
                if (!moved) break; // shouldn't happen if flow==k
            }
            paths.push_back(path);
        }
        return paths;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    MCMF g(n);

    for (int i=0; i<m; i++) {
        int a,b;
        cin >> a >> b;
        --a; --b;
        g.addEdge(a,b,1,1);
    }

    auto [flow,cost] = g.minCostFlow(0,n-1,k);
    if (flow < k) {
        cout << -1 << "\n";
        return 0;
    }
    cout << cost << "\n";

    auto paths = g.extractPaths(0,n-1,k);
    for (auto &p : paths) {
        cout << p.size() << "\n";
        for (int v : p) cout << v+1 << " ";
        cout << "\n";
    }
}

