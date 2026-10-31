#include <bits/stdc++.h>
using namespace std;

struct RollbackDSU {
    struct Change {
        int u, v;
        int oldSize;
        bool oldCyclic;
        int oldAns;
    };
    
    vector<int> parent, sz;
    vector<bool> cyclic;
    vector<Change> history;
    int ans = 0;

    RollbackDSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
        sz.assign(n + 1, 1);
        cyclic.assign(n + 1, false);
    }

    int find(int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }

    int snapshot() {
        return history.size();
    }

    void addEdge(int a, int b) {
        int u = find(a);
        int v = find(b);

        if (u == v) {
            history.push_back({u, -1, sz[u], cyclic[u], ans});

            if (!cyclic[u]) {
                cyclic[u] = true;
                ans++;
            }
            return;
        }

        if (sz[u] < sz[v]) swap(u, v);

        history.push_back({u, v, sz[u], cyclic[u], ans});

        if (!(cyclic[u] && cyclic[v]))
            ans++;

        parent[v] = u;
        sz[u] += sz[v];
        cyclic[u] = cyclic[u] || cyclic[v];
    }

    void rollback(int snap) {
        while ((int)history.size() > snap) {
            auto c = history.back();
            history.pop_back();

            ans = c.oldAns;
            cyclic[c.u] = c.oldCyclic;
            sz[c.u] = c.oldSize;

            if (c.v != -1)
                parent[c.v] = c.v;
        }
    }
};


struct Event {
    int v, p, type, snap;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    RollbackDSU dsu(n);
    vector<int> answer(n + 1);

    stack<Event> st;
    st.push({1, 0, 0, 0});

    while (!st.empty()) {
        auto [v, p, type, snap] = st.top();
        st.pop();

        if (type == 1) {
            dsu.rollback(snap);
            continue;
        }

        int curSnap = dsu.snapshot();

        dsu.addEdge(a[v], b[v]);
        answer[v] = dsu.ans;

        st.push({v, p, 1, curSnap});

        for (int u : g[v]) {
            if (u != p)
                st.push({u, v, 0, 0});
        }
    }

    for (int i = 2; i <= n; i++)
        cout << answer[i] << (i == n ? '\n' : ' ');
}

