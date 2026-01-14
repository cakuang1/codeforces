#include <bits/stdc++.h>
using namespace std;

/*
ABC435 D - Reachability Query 2

Idea:
- Compute SCCs of the original directed graph.
- Compress into SCC DAG (condensation graph).
- Maintain good[c] = whether SCC c can reach some black SCC.
- When a vertex v is colored black, let c = comp[v]. If good[c] is false, set it true and
  propagate backwards on the SCC DAG using reverse edges (revDAG), marking all ancestors good.
- For query type 2, answer good[comp[v]].

Total: O(N+M+Q) after SCC (which is O(N+M)).
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> g(N), gr(N);
    g.reserve(N); gr.reserve(N);

    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        g[x].push_back(y);
        gr[y].push_back(x);
    }

    // Kosaraju: 1st pass order
    vector<int> order;
    order.reserve(N);
    vector<char> vis(N, 0);

    for (int s = 0; s < N; s++) if (!vis[s]) {
        // iterative DFS to avoid recursion limit
        vector<pair<int,int>> st;
        st.push_back({s, 0});
        vis[s] = 1;
        while (!st.empty()) {
            int v = st.back().first;
            int &it = st.back().second;
            if (it < (int)g[v].size()) {
                int to = g[v][it++];
                if (!vis[to]) {
                    vis[to] = 1;
                    st.push_back({to, 0});
                }
            } else {
                order.push_back(v);
                st.pop_back();
            }
        }
    }

    // 2nd pass assign components on reversed graph
    vector<int> comp(N, -1);
    int C = 0;
    for (int i = N - 1; i >= 0; i--) {
        int s = order[i];
        if (comp[s] != -1) continue;
        // BFS/DFS on gr
        vector<int> st;
        st.push_back(s);
        comp[s] = C;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (int to : gr[v]) {
                if (comp[to] == -1) {
                    comp[to] = C;
                    st.push_back(to);
                }
            }
        }
        C++;
    }

    // Build SCC DAG reverse edges (we only need reverse propagation)
    vector<vector<int>> revDAG(C);
    revDAG.reserve(C);

    // Deduplicate edges between components: use hash set per component (lightweight)
    // Total edges up to M, so global hash set is fine.
    unordered_set<long long> seen;
    seen.reserve((size_t)M * 2 + 10);
    seen.max_load_factor(0.7f);

    auto key = [&](int a, int b) -> long long {
        return (long long)a * (long long)C + b;
    };

    for (int v = 0; v < N; v++) {
        int cv = comp[v];
        for (int to : g[v]) {
            int cu = comp[to];
            if (cv == cu) continue;
            long long k = key(cv, cu);
            if (seen.insert(k).second) {
                // edge cv -> cu in DAG, so reverse edge cu -> cv
                revDAG[cu].push_back(cv);
            }
        }
    }

    int Q;
    cin >> Q;

    vector<char> good(C, 0);
    deque<int> dq;

    while (Q--) {
        int t, v;
        cin >> t >> v;
        --v;
        int c = comp[v];

        if (t == 1) {
            if (!good[c]) {
                good[c] = 1;
                dq.push_back(c);
                while (!dq.empty()) {
                    int x = dq.front();
                    dq.pop_front();
                    for (int p : revDAG[x]) {
                        if (!good[p]) {
                            good[p] = 1;
                            dq.push_back(p);
                        }
                    }
                }
            }
        } else {
            cout << (good[c] ? "Yes\n" : "No\n");
        }
    }

    return 0;
}

