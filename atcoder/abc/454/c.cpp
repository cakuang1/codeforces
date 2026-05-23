#include <bits/stdc++.h>
using namespace std;

vector<int> adj[300001];
bool seen[300001];

void dfs(int a) {
    seen[a] = true;
    for (int c : adj[a]) {
        if (!seen[c]) dfs(c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b); // directed: give item a, receive item b
    }

    dfs(1);

    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (seen[i]) res++;
    }

    cout << res << "\n";
    return 0;
}