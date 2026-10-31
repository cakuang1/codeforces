#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));

    for (int i = 0; i < m; i++) {
        vector<int> a(n);
        for (int &x : a) cin >> x;

        for (int j = 0; j + 1 < n; j++) {
            int u = a[j];
            int v = a[j + 1];

            adj[u][v] = true;
            adj[v][u] = true;
        }
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!adj[i][j]) ans++;
        }
    }

    cout << ans << '\n';
} 



// weyou