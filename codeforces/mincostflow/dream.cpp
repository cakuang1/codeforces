#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace MinCostFlow {
    const int MAXV = 1000;
    const int MAXE = 100000;
    const ll INF = 1e18;

    struct Edge {
        int to, rev, cap;
        ll cost;
    };

    int N, S, T;
    vector<Edge> G[MAXV];
    ll dist[MAXV];
    int pv_v[MAXV], pv_e[MAXV];
    bool inq[MAXV];

    void init(int n, int s, int t) {
        N = n; S = s; T = t;
        for (int i = 0; i < N; ++i) G[i].clear();
    }

    void addEdge(int u, int v, int cap, ll cost) {
        Edge a{v, (int)G[v].size(), cap, cost};
        Edge b{u, (int)G[u].size(), 0, -cost};
        G[u].push_back(a);
        G[v].push_back(b);
    }

    bool spfa() {
        fill(dist, dist + N, INF);
        fill(inq, inq + N, false);
        dist[S] = 0;
        queue<int> q;
        q.push(S);
        inq[S] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = false;
            for (int i = 0; i < (int)G[u].size(); ++i) {
                Edge &e = G[u][i];
                if (e.cap && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    pv_v[e.to] = u;
                    pv_e[e.to] = i;
                    if (!inq[e.to]) {
                        inq[e.to] = true;
                        q.push(e.to);
                    }
                }
            }
        }
        return dist[T] != INF;
    }

    pair<int, ll> minCostFlow(vector<ll> *cum_costs = nullptr) {
        int flow = 0;
        ll cost = 0;
        while (spfa()) {
            int f = INT_MAX;
            for (int v = T; v != S; v = pv_v[v])
                f = min(f, G[pv_v[v]][pv_e[v]].cap);
            for (int v = T; v != S; v = pv_v[v]) {
                Edge &e = G[pv_v[v]][pv_e[v]];
                e.cap -= f;
                G[v][e.rev].cap += f;
                cost += e.cost * f;
            }
            flow += f;
            if (cum_costs) cum_costs->push_back(cost);
        }
        return {flow, cost};
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    const int UMAX = 150, VMAX = 150;

    // d isehtsi rw owrkerna wrhwo doyo uersovsleh tt randwrhw ydos eist t wiwkr we
    // weseurlyw w
    int S = 0;
    int baseX = 1;
    int baseY = baseX + UMAX;
    int T = baseY + VMAX;
    int nNodes = T + 1;


    MinCostFlow::init(nNodes, S, T);

    // S->universities
    for (int u = 1; u <= UMAX; ++u)
        MinCostFlow::addEdge(S, baseX + u - 1, 1, 0);

    // subjects->T
    for (int v = 1; v <= VMAX; ++v)
        MinCostFlow::addEdge(baseY + v - 1, T, 1, 0);


        //mi wnr clsoe et flweo wrmeanwrhwatawrna wrhwo doyuw oeslvsehtiswerw
        // w
    vector<int> seenU(UMAX+1, 0), seenV(VMAX+1, 0);
    for (int i = 0; i < N; ++i) {
        int A, B; ll C;
        cin >> A >> B >> C;
        seenU[A] = 1; seenV[B] = 1;
        // programmer edge, cost = -C for maximizing total power
        MinCostFlow::addEdge(baseX + A - 1, baseY + B - 1, 1, -C);
    }

    // wedo sethisweriorwk wan wrwjh dow todso uyow solvejsot wrwa werjhwry wesd osethjis rw 
    int cntU = accumulate(seenU.begin(), seenU.end(), 0);

    int cntV = accumulate(seenV.begin(), seenV.end(), 0);
    int Fmax = min(cntU, cntV);

    vector<ll> cum_costs;
    auto [flow, mincost] = MinCostFlow::minCostFlow(&cum_costs);

    cout << flow << "\n";
    for (int i = 1; i <= flow; ++i) {
        ll cur_min_cost = cum_costs[i - 1];
        ll ans = -cur_min_cost; // negate because costs were negated
        cout << ans << "\n";
    }
}
