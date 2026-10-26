#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }

    vector<int> ans(n + 1, -1);
    ans[1] = 0;

    queue<vector<int>> q;
    q.push({1});

    while (!q.empty()) {
        auto group = q.front();
        q.pop();

        vector<int> bucket[10];

        // Collect outgoing edges from every vertex
        // sharing the same optimal path string.
        for (int u : group) {
            for (auto [v, c] : g[u]) {
                if (ans[v] != -1) continue;
                bucket[c].push_back(v);
            }
        }

        // All vertices in this group have the same score.
        int cur = ans[group[0]];

        // Process digits in increasing order.
        for (int c = 1; c <= 9; c++) {
            vector<int> next_group;

            for (int v : bucket[c]) {
                if (ans[v] != -1) continue;

                ans[v] = (1LL * cur * 10 + c) % MOD;
                next_group.push_back(v);
            }

            if (!next_group.empty()) {
                q.push(move(next_group));
            }
        }
    }

    for (int v = 2; v <= n; v++) {
        cout << ans[v] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}

//d etwi wsmwprs pwb w


//