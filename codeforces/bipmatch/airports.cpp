#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<vector<long long>> t(n, vector<long long>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> t[i][j];

    struct Flight { int s, f; long long start; };
    vector<Flight> flights(m);
    for (int i = 0; i < m; ++i) {
        int si, fi; long long ti;
        cin >> si >> fi >> ti;
        --si; --fi;
        flights[i] = {si, fi, ti};
    }

    // 1) Build transfer graph with weights w(u->v) = t[u][v] + p[v]
    const long long INF = (1LL<<60);
    vector<vector<long long>> D(n, vector<long long>(n, INF));
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u == v) D[u][v] = 0; // no hop -> no extra inspection (already accounted at previous landing)
            else D[u][v] = t[u][v] + p[v];
        }
    }
    // Floyd–Warshall to allow multi-hop deadhead with inspections at every landing
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            if (D[i][k] < INF)
                for (int j = 0; j < n; ++j)
                    if (D[k][j] < INF)
                        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

    // 2) Sort flights by start time (DAG ordering)
    sort(flights.begin(), flights.end(),
         [](const Flight& a, const Flight& b){ return a.start < b.start; });

    // 3) Build DAG edges: i -> j if feasible to chain
    vector<vector<int>> adj(m);
    for (int i = 0; i < m; ++i) {
        long long arrive = flights[i].start + t[flights[i].s][flights[i].f];
        long long ready  = arrive + p[flights[i].f];
        for (int j = i+1; j < m; ++j) {
            if (ready > flights[j].start) continue; // early prune
            long long transfer = D[flights[i].f][flights[j].s];
            if (transfer >= INF) continue;          // unreachable (shouldn't happen if graph is connected enough)
            if (ready + transfer <= flights[j].start)
                adj[i].push_back(j);
        }
    }

    // 4) Maximum bipartite matching (Hopcroft–Karp) on DAG’s bipartite expansion
    vector<int> matchL(m, -1), matchR(m, -1), dist(m);
    auto bfs = [&](){
        queue<int> q;
        for (int i = 0; i < m; ++i) {
            if (matchL[i] == -1) { dist[i] = 0; q.push(i); }
            else dist[i] = -1;
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int w = matchR[v];
                if (w == -1) found = true;
                else if (dist[w] == -1) { dist[w] = dist[u] + 1; q.push(w); }
            }
        }
        return found;
    };
    function<bool(int)> dfs = [&](int u){
        for (int v : adj[u]) {
            int w = matchR[v];
            if (w == -1 || (dist[w] == dist[u] + 1 && dfs(w))) {
                matchL[u] = v; matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    };
    int matching = 0;
    while (bfs())
        for (int i = 0; i < m; ++i)
            if (matchL[i] == -1 && dfs(i))
                ++matching;

    cout << (m - matching) << "\n";
    return 0;
}


// wwwher werwoen flihthwcna woflwe rantoerhw e
// we