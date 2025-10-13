#include <bits/stdc++.h>
using namespace std;

struct MCMF {
    struct Edge { int to, rev, cap; long long cost; };
    int n;
    vector<vector<Edge>> g;
    vector<long long> dist, pot;
    vector<int> pv, pe;

    MCMF(int n): n(n), g(n), dist(n), pot(n), pv(n), pe(n) {}

    void add_edge(int u, int v, int cap, long long cost) {
        Edge a = {v, (int)g[v].size(), cap, cost};
        Edge b = {u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a); g[v].push_back(b);
    }

    pair<int,long long> max_cost_flow(int s, int t, int maxf) {
        long long flow=0, cost=0;
        fill(pot.begin(), pot.end(), 0);
        while (flow < maxf) {
            fill(dist.begin(), dist.end(), LLONG_MIN);
            dist[s] = 0;
            typedef pair<long long,int> pli;
            priority_queue<pli> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top(); pq.pop();
                d = -d;
                if (d < dist[v]) continue;
                for (int i=0;i<(int)g[v].size();++i) {
                    Edge &e = g[v][i];
                    if (e.cap <= 0) continue;
                    long long nd = dist[v] + e.cost - pot[e.to] + pot[v];
                    if (nd > dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = v; pe[e.to] = i;
                        pq.push({-nd, e.to});
                    }
                }
            }
            if (dist[t] == LLONG_MIN) break;
            for (int i=0;i<n;++i)
                if (dist[i] > LLONG_MIN)
                    pot[i] += dist[i];
            int addf = maxf - flow;
            for (int v=t; v!=s; v=pv[v])
                addf = min(addf, g[pv[v]][pe[v]].cap);
            flow += addf;
            cost += 1LL * addf * pot[t];
            for (int v=t; v!=s; v=pv[v]) {
                Edge &e = g[pv[v]][pe[v]];
                e.cap -= addf;
                g[v][e.rev].cap += addf;
            }
        }
        return {(int)flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    int S = 2*n, T = S+1;
    MCMF mcmf(T+1);

    for (int i=0;i<n;i++) {
        int in = 2*i, out = 2*i+1;
        mcmf.add_edge(in, out, 1, 1); // taking note i adds +1 profit
        mcmf.add_edge(S, in, 1, 0);   // can start here
        mcmf.add_edge(out, T, 1, 0);  // can end here
    }

    // connect melody transitions
    for (int i=0;i<n;i++) {
        for (int j=i+1;j<n;j++) {
            if (abs(a[i]-a[j])==1 || a[i]%7==a[j]%7)
                mcmf.add_edge(2*i+1, 2*j, 1, 0);
        }
    }

    auto [flow, cost] = mcmf.max_cost_flow(S, T, 4);
    cout << cost << "\n";
}



// wsreuylw thsi shosudlwtnw or