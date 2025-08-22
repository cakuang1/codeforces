#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<vector<int>> adj(N);
vector<int> in(N, 0), out(N, 0);
vector<int> path;

void dfs(int u) {
    while (!adj[u].empty()) {
        int v = adj[u].back();
        adj[u].pop_back();
        dfs(v);
    }
    path.push_back(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<multiset<int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        out[a]++;
        in[b]++;
    }

    // Check Eulerian path conditions
    if (out[1] != in[1] + 1 || in[n] != out[n] + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 2; i < n; ++i) {
        if (in[i] != out[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    dfs(1);

    if ((int)path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    reverse(path.begin(), path.end());
    for (int x : path) cout << x << ' ';
    cout << '\n';
    return 0;
}
