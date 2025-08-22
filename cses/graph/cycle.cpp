#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<char> used, inStack;
vector<int> parent, cycle;

bool dfs(int u) {
    used[u] = inStack[u] = 1;
    for (int v : adj[u]) {
        if (!used[v]) {
            parent[v] = u;
            if (dfs(v)) 
                return true;
        } 
        else if (inStack[v]) {
            // found a back‐edge u -> v; reconstruct the cycle
            cycle.clear();
            cycle.push_back(v);
            for (int x = u; x != v; x = parent[x]) 
                cycle.push_back(x);
            cycle.push_back(v);
            reverse(cycle.begin(), cycle.end());
            return true;
        }
    }
    inStack[u] = 0;
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.assign(n+1, {});
    for (int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
    }

    used.assign(n+1, 0);
    inStack.assign(n+1, 0);
    parent.assign(n+1, -1);

    // try to find a cycle starting from each unvisited node
    for (int i = 1; i <= n; i++) {
        if (!used[i] && dfs(i)) {
            // we found 'cycle'
            cout << cycle.size() << "\n";
            for (int x : cycle) 
                cout << x << " ";
            cout << "\n";
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
