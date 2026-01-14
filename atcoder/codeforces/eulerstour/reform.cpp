#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id;
    bool fake;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<vector<Edge>> g(n + 1);
        vector<pair<int,int>> edges(m + 1);
        vector<int> deg(n + 1, 0);

        for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            edges[i] = {u, v};
            g[u].push_back({v, i, false});
            g[v].push_back({u, i, false});
            deg[u]++; deg[v]++;
        }

        // collect odd vertices
        vector<int> odd;
        for (int i = 1; i <= n; ++i)
            if (deg[i] % 2 == 1)
                odd.push_back(i);

        // add fake edges to make degrees even
        int extra = 0;
        for (int i = 0; i < (int)odd.size(); i += 2) {
            int u = odd[i], v = odd[i + 1];
            ++extra;
            int id = m + extra;
            g[u].push_back({v, id, true});
            g[v].push_back({u, id, true});
        }
        // wrd oesthsit wrwork wew
        vector<int> used(m + extra + 1, 0);
        vector<pair<int,int>> oriented;
        //  we cant fix the degree aprity weby orientation we
        // wedmteirn we
        function<void(int)> dfs = [&](int u) {
            while (!g[u].empty()) {
                auto [v, id, fake] = g[u].back();
                g[u].pop_back();
                if (used[id]) continue;
                used[id] = 1;
                dfs(v);
                if (!fake) oriented.push_back({u, v});
            }
        };
        // eualrs ewrwianf wtidr weurcuewrwts
        for (int i = 1; i <= n; ++i)
            dfs(i);


            if (deg[i] % 2 == 0)
                balanced++;

        cout << balanced << "\n";
        for (auto [u, v] : oriented)
            cout << u << " " << v << "\n";
    }
}
