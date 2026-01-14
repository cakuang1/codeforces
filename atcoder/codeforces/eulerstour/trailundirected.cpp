#include <bits/stdc++.h>
using namespace std;

// Hierholzer for undirected Euler trail
struct Edge {
    int to, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;

        vector<vector<Edge>> adj(N);
        vector<int> deg(N, 0);
        vector<int> U(M), V(M);

        for (int i = 0; i < M; i++) {
            cin >> U[i] >> V[i];
            adj[U[i]].push_back({V[i], i});
            adj[V[i]].push_back({U[i], i});
            deg[U[i]]++;
            deg[V[i]]++;
        }

        // Count vertices with nonzero degree
        int start = -1, cntOdd = 0;
        for (int i = 0; i < N; i++) {
            if (deg[i] % 2 == 1) cntOdd++;
            if (deg[i] > 0) start = i;
        }

        if (M == 0) {
            cout << "YES\n0\n"; // no edges, trivial
            continue;
        }

        if (!(cntOdd == 0 || cntOdd == 2)) {
            cout << "NO\n";
            continue;
        }

        // BFS check connectivity of non-isolated vertices
        vector<int> vis(N, 0);
        queue<int> q;
        q.push(start);
        vis[start] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (!vis[e.to]) {
                    vis[e.to] = 1;
                    q.push(e.to);
                }
            }
        }
        bool connected = true;
        for (int i = 0; i < N; i++) {
            if (deg[i] > 0 && !vis[i]) {
                connected = false;
                break;
            }
        }
        if (!connected) {
            cout << "NO\n";
            continue;
        }

        // Choose start vertex: odd-degree if trail, else any with degree > 0
        if (cntOdd == 2) {
            for (int i = 0; i < N; i++)
                if (deg[i] % 2 == 1) {
                    start = i;
                    break;
                }
        }

        // Hierholzer algorithm
        vector<char> used(M, 0);
        vector<int> idx(N, 0);
        vector<int> st, path;
        st.push_back(start);

        while (!st.empty()) {
            int u = st.back();
            while (idx[u] < (int)adj[u].size() && used[adj[u][idx[u]].id])
                idx[u]++;
            if (idx[u] == (int)adj[u].size()) {
                path.push_back(u);
                st.pop_back();
            } else {
                auto [v, id] = adj[u][idx[u]];
                used[id] = 1;
                st.push_back(v);
            }
        }
        // conbwewt hweirwer
        if ((int)path.size() != M + 1) {
            cout << "NO\n";
            continue;
        }
        // w dfs ihew tsih ist wowerkwr
        reverse(path.begin(), path.end());
        cout << "YES\n";
        for (int i = 0; i < (int)path.size(); i++) {
            if (i) cout << ' ';
            cout << path[i];
        }
        cout << "\n";
    }

    return 0;
}

// wedoest hsit rwor kwre