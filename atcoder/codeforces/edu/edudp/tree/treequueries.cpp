#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 200005;

vector<int> adj[N];
int tin[N], tout[N], p[N], d[N];
int timer = 1, n, m;

void dfs(int curr, int parent, int depth) {
    p[curr] = parent;
    d[curr] = depth;
    tin[curr] = timer++;

    for (int child : adj[curr]) {
        if (child == parent) continue;
        dfs(child, curr, depth + 1);
    }

    tout[curr] = timer++;
}

bool isAncestor(int x, int y) {
    return tin[x] <= tin[y] && tout[x] >= tout[y];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1, 1);

    while (m--) {
        int k;
        cin >> k;
        vector<int> s(k);

        int maxdepth = 0, curr = -1;
        for (int i = 0; i < k; i++) {
            cin >> s[i];
            if (d[s[i]] > maxdepth) {
                maxdepth = d[s[i]];
                curr = s[i];
            }
        }
        // 
        // Convert all nodes to their parents (except the root)
        for (int i = 0; i < k; i++) {
            if (s[i] != 1) s[i] = p[s[i]];
        }

        // Check if all nodes are in the subtree of curr
        bool valid = true;
        for (int i = 0; i < k; i++) {
            if (!isAncestor(s[i], curr)) {
                valid = false;
                break;
            }
        }

        cout << (valid ? "YES" : "NO") << '\n';
    }

    return 0;
}
