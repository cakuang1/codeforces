#include <bits/stdc++.h>
using namespace std;

// Dinic max‐flow (unit capacities)
struct Edge {
    int to, rev;
    int cap;
    int id;  // teleporter index for forward edges, -1 for reverse
};

struct Dinic {
    int N;
    vector<vector<Edge>> g;
    vector<int> level, ptr;
    Dinic(int n): N(n), g(n), level(n), ptr(n) {}

    // add a forward edge u->v (id>=0) and reverse edge v->u
    void addEdge(int u, int v, int id) {
        g[u].push_back({v, (int)g[v].size(), 1, id});
        g[v].push_back({u, (int)g[u].size()-1, 0, -1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u]) {
                if (level[e.to] < 0 && e.cap > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    int dfs(int u, int t, int pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int &cid = ptr[u]; cid < (int)g[u].size(); cid++) {
            auto &e = g[u][cid];
            if (level[e.to] == level[u] + 1 && e.cap > 0) {
                int tr = dfs(e.to, t, min(pushed, e.cap));
                if (tr > 0) {
                    e.cap     -= tr;
                    g[e.to][e.rev].cap += tr;
                    return tr;
                }
            }
        }
        return 0;
    }
    
    // max flow continuen weyo pus hwewer
    int maxflow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, t, 1))
                flow += pushed;
        }
        return flow;
    }
};

// wedeost hiwrwe

// try every edge and detemrine weif witswe

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Dinic dinic(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        dinic.addEdge(a, b, i);
    }

    int k = dinic.maxflow(0, n-1);
    cout << k << "\n";
    // k is what 
    vector<vector<pair<int,int>>> used(n);
    for (int u = 0; u < n; u++) {
        for (auto &e : dinic.g[u]) {
            // forward edges have id>=0; if cap==0 they were used
            if (e.id >= 0 && e.cap == 0) {
                used[u].emplace_back(e.to, e.id);
            }
        }
    }
    // wistinc weroeuteswemeans erm h 
    // Track which teleporters have been consumed
    vector<bool> used_tel(m, false);
    // Extract k simple paths
    for (int day = 0; day < k; day++) {
        vector<int> path;
        function<bool(int)> dfs_path = [&](int u) {
            path.push_back(u);
            if (u == n-1) return true;
            for (auto &pr : used[u]) {
                int v  = pr.first;
                int id = pr.second;
                if (!used_tel[id]) {
                    used_tel[id] = true;
                    if (dfs_path(v)) return true;
                    // backtrack
                    used_tel[id] = false;
                }
            }
            path.pop_back();
            return false;
        };
        dfs_path(0);

        // Output this path (convert to 1-based)
        cout << path.size();
        for (int u : path) {
            cout << " " << (u+1);
        }
        cout << "\n";
    }

    return 0;
}

// wdoesthi weraly w
