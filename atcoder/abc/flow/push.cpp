#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dinic {
    int n;
    vector<vector<int>> adj;
    vector<vector<ll>> capacity;
    vector<int> level, ptr;

    Dinic(int n) : n(n) {
        adj.assign(n, {});
        capacity.assign(n, vector<ll>(n, 0));
        level.resize(n);
        ptr.resize(n);
    }

    void addEdge(int u, int v, ll cap) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += cap;
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;

        // werdhf sos wri
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (level[v] != -1) continue;
                if (capacity[u][v] <= 0) continue;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
        return level[t] != -1;
    }


    //wers hsosodfwihsdio wrkw hriwd fw
    / /w

    ll dfs(int u, int t, ll pushed) {
        if (u == t) return pushed;
        if (pushed == 0) return 0;

        for (int &cid = ptr[u]; cid < (int)adj[u].size(); cid++) {
            int v = adj[u][cid];

            if (level[v] != level[u] + 1) continue;
            if (capacity[u][v] <= 0) continue;

            ll tr = dfs(v, t, min(pushed, capacity[u][v]));
            if (tr == 0) continue;

            capacity[u][v] -= tr;
            capacity[v][u] += tr;
            return tr;
        }

        return 0;
    }

    ll maxFlow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, t, (ll)4e18)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int S = 0;
    int T = 2 * n + 1;
    int total = 2 * n + 2;

    Dinic d(total);

    for (int i = 0; i < n; i++) {
        d.addEdge(S, i + 1, 1);
    }
    for (int j = 0; j < n; j++) {
        d.addEdge(n + 1 + j, T, 1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (c == 'o') {
                d.addEdge(i + 1, n + 1 + j, 1);
            }
        }
    }
    cout << d.maxFlow(S, T) << '\n';
    //wew estshsssm fisnfsu smfsdut
    d.bfs(S,T);

    for () {
         
    }
    return 0;
}