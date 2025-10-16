#include <bits/stdc++.h>
using namespace std;

// Hierholzer for directed Euler trail
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;

    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<int> U(M), V(M);
        for (int i = 0; i < M; ++i) {
            cin >> U[i] >> V[i];
        }

        // Quick accept for M==0: any single vertex works
        if (M == 0) {
            cout << "YES\n";
            cout << 0 << "\n"; // single-vertex trail
            continue;
        }

        // Build directed adjacency with edge IDs
        vector<vector<pair<int,int>>> adj(N);
        vector<int> indeg(N, 0), outdeg(N, 0);
        vector<int> degUndir(N, 0);

        for (int i = 0; i < M; ++i) {
            adj[U[i]].push_back({V[i], i});
            outdeg[U[i]]++;
            indeg[V[i]]++;
            degUndir[U[i]]++;
            degUndir[V[i]]++;
        }

        // Check weak connectivity among vertices with deg>0
        int startConn = -1;
        int nonzero = 0;
        for (int i = 0; i < N; ++i) {
            if (degUndir[i] > 0) {
                nonzero++;
                if (startConn == -1) startConn = i;
            }
        }
        if (nonzero == 0) {
            // No edges: already handled M==0; shouldn't happen here
            cout << "YES\n";
            cout << 0 << "\n";
            continue;
        }
        vector<vector<int>> und(N);
        und.reserve(N);
        for (int i = 0; i < M; ++i) {
            und[U[i]].push_back(V[i]);
            und[V[i]].push_back(U[i]);
        }
        vector<int> vis(N, 0);
        {
            queue<int> q;
            q.push(startConn);
            vis[startConn] = 1;
            int seen = 1;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int w : und[u]) if (!vis[w]) {
                    vis[w] = 1; q.push(w); seen++;
                }
            }
            int countReach = 0;
            for (int i = 0; i < N; ++i) if (degUndir[i] > 0 && vis[i]) countReach++;
            if (countReach != nonzero) {
                cout << "NO\n";
                continue;
            }
        }

        // Degree conditions for Euler trail (directed)
        int start = -1, end = -1;
        bool bad = false;
        for (int i = 0; i < N; ++i) {
            int d = outdeg[i] - indeg[i];
            if (d == 1) {
                if (start == -1) start = i;
                else bad = true;
            } else if (d == -1) {
                if (end == -1) end = i;
                else bad = true;
            } else if (d != 0) {
                bad = true;
            }
        }
        if (bad) {
            cout << "NO\n";
            continue;
        }

        // Choose start vertex:
        // if trail (start exists) start there; else circuit: any with outdeg>0
        if (start == -1) {
            for (int i = 0; i < N; ++i) if (outdeg[i] > 0) { start = i; break; }
        }
        if (start == -1) {
            // Shouldn't happen (M>0), but guard
            cout << "NO\n";
            continue;
        }

        // Hierholzer: iterative
        vector<int> it(N, 0);
        vector<char> used(M, 0);
        vector<int> st;
        st.reserve(M + 5);
        vector<int> trail; trail.reserve(M + 1);

        st.push_back(start);
        while (!st.empty()) {
            int u = st.back();
            auto &vec = adj[u];
            while (it[u] < (int)vec.size() && used[vec[it[u]].second]) it[u]++;
            if (it[u] == (int)vec.size()) {
                // no more outgoing unused edges
                trail.push_back(u);
                st.pop_back();
            } else {
                auto [v, id] = vec[it[u]];
                used[id] = 1;
                st.push_back(v);
            }
        }

        if ((int)trail.size() != M + 1) {
            cout << "NO\n";
            continue;
        }
        reverse(trail.begin(), trail.end());

        cout << "YES\n";
        for (int i = 0; i < (int)trail.size(); ++i) {
            if (i) cout << ' ';
            cout << trail[i];
        }
        cout << "\n";
    }

    return 0;
}

// ww wer werhiw 