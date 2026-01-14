#include <bits/stdc++.h>
using namespace std;

struct MCMF {
    struct Edge {
        int to, rev, cap;
        int cost;
    };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> dist, pot, par_v, par_e;
    vector<char> inq;

    MCMF(int n) : n(n), g(n), dist(n), pot(n), par_v(n), par_e(n), inq(n) {}

    void add_edge(int u, int v, int cap, int cost) {
        Edge a{v, (int)g[v].size(), cap, cost};
        Edge b{u, (int)g[u].size(), 0,  -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    // successive shortest augmenting paths with Johnson potentials
    pair<int,long long> min_cost_max_flow(int S, int T, int need_flow) {
        s = S; t = T;
        fill(pot.begin(), pot.end(), 0);
        int flow = 0;
        long long cost = 0;

        while (flow < need_flow) {
            const int INF = 0x3f3f3f3f;
            fill(dist.begin(), dist.end(), INF);
            fill(inq.begin(), inq.end(), 0);
            dist[s] = 0;

            // Dijkstra with potentials
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top(); pq.pop();
                if (d != dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); ++i) {
                    Edge &e = g[v][i];
                    if (e.cap <= 0) continue;
                    int nd = d + e.cost + pot[v] - pot[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        par_v[e.to] = v;
                        par_e[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }
            if (dist[t] == INF) break;
            for (int i = 0; i < n; ++i) if (dist[i] < INF) pot[i] += dist[i];

            int aug = need_flow - flow;
            for (int v = t; v != s; v = par_v[v]) {
                Edge &e = g[par_v[v]][par_e[v]];
                aug = min(aug, e.cap);
            }
            flow += aug;
            cost += 1LL * aug * pot[t];
            for (int v = t; v != s; v = par_v[v]) {
                Edge &e = g[par_v[v]][par_e[v]];
                e.cap -= aug;
                g[v][e.rev].cap += aug;
            }
        }
        return {flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Node mapping:
    // for each i: i_in = 2*i, i_out = 2*i+1
    // S = 2*n, T = 2*n+1
    int S = 2*n, T = 2*n+1;
    MCMF mf(2*n + 2);

    // S -> i_in (start at any note), cap 1, cost 0
    for (int i = 0; i < n; ++i) mf.add_edge(S, 2*i, 1, 0);

    // i_in -> i_out (select note i), cap 1, cost -1 (gain +1)
    for (int i = 0; i < n; ++i) mf.add_edge(2*i, 2*i+1, 1, -1);

    // i_out -> T (end a melody at i), cap 1, cost 0
    for (int i = 0; i < n; ++i) mf.add_edge(2*i+1, T, 1, 0);

    // Build transition edges i_out -> j_in if j>i and valid:
    //  - |a[i]-a[j]| == 1  OR  a[i]%7 == a[j]%7
    // Use value buckets and modulo-7 buckets to avoid full O(n^2)
    unordered_map<int, vector<int>> by_value;
    by_value.reserve(n * 2);
    vector<int> by_mod[7];

    for (int i = 0; i < n; ++i) {
        by_value[a[i]].push_back(i);
        by_mod[a[i] % 7].push_back(i);
    }

    auto add_transitions = [&](const vector<int> &vec) {
        // Connect all later j>i in this vector (kept sorted by i increasing)
        // Edge: i_out -> j_in (cap 1, cost 0)
        // This is the potentially large part; but summed over residue classes
        // it's ~O(n^2/14) in worst case, which is fine in 1 GB memory limits.
        for (int idx = 0; idx < (int)vec.size(); ++idx) {
            int i = vec[idx];
            int ui = 2*i+1;
            for (int jdx = idx+1; jdx < (int)vec.size(); ++jdx) {
                int j = vec[jdx];
                mf.add_edge(ui, 2*j, 1, 0);
            }
        }
    };

    // same modulo 7 transitions
    for (int m = 0; m < 7; ++m) add_transitions(by_mod[m]);

    // value ±1 transitions
    // We need all pairs (i,j) with j > i and a[j] == a[i] ± 1.
    // Do it by iterating values present.
    for (auto &kv : by_value) {
        int val = kv.first;
        auto itm = by_value.find(val + 1);
        if (itm != by_value.end()) {
            const auto &L = kv.second;       // positions with value = val
            const auto &R = itm->second;     // positions with value = val+1
            // Two-finger merge: add i_out -> j_in for i in L, j in R with j>i
            int p = 0;
            for (int i : L) {
                int ui = 2*i+1;
                while (p < (int)R.size() && R[p] <= i) ++p;
                for (int q = p; q < (int)R.size(); ++q) {
                    int j = R[q];
                    mf.add_edge(ui, 2*j, 1, 0);
                }
            }
        }
        itm = by_value.find(val - 1);
        if (itm != by_value.end()) {
            const auto &L = kv.second;       // value = val
            const auto &R = itm->second;     // value = val-1
            int p = 0;
            for (int i : L) {
                int ui = 2*i+1;
                while (p < (int)R.size() && R[p] <= i) ++p;
                for (int q = p; q < (int)R.size(); ++q) {
                    int j = R[q];
                    mf.add_edge(ui, 2*j, 1, 0);
                }
            }
        }
    }
    // da wr ad ad wa wand w wehowt wovsl
    auto res = mf.min_cost_max_flow(S, T, 4);
    cout << -res.second << "\n";
    return 0;
} 

// wr wgroupskiilgin we dosthi wra hat w