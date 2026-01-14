#include <bits/stdc++.h>
using namespace std;

// Simple Kuhn's algorithm for bipartite matching
struct BipartiteMatcher {
    int n, m;
    vector<vector<int>> adj;
    vector<int> matchR, vis;

    BipartiteMatcher(int n, int m): n(n), m(m), adj(n), matchR(m, -1), vis(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool dfs(int u) {
        if (vis[u]) return false;
        vis[u] = 1;
        for (int v : adj[u]) {
            if (matchR[v] == -1 || dfs(matchR[v])) {
                matchR[v] = u;
                return true;
            }
        }
        return false;
    }

    int maxMatching() {
        int res = 0;
        for (int u = 0; u < n; u++) {
            fill(vis.begin(), vis.end(), 0);
            if (dfs(u)) res++;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n+1), b(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    // --- Step 1: find cycles in permutation a ---
    vector<int> cycA(n+1, -1), cycB(n+1, -1);
    vector<vector<int>> cyclesA, cyclesB;
    vector<int> vis(n+1, 0);

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vector<int> cycle;
            int x = i;
            while (!vis[x]) {
                vis[x] = 1;
                cycle.push_back(x);
                x = a[x];
            }
            for (int v : cycle) cycA[v] = (int)cyclesA.size();
            cyclesA.push_back(cycle);
        }
    }

    // --- Step 2: find cycles in permutation b ---
    fill(vis.begin(), vis.end(), 0);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vector<int> cycle;
            int x = i;
            while (!vis[x]) {
                vis[x] = 1;
                cycle.push_back(x);
                x = b[x];
            }
            for (int v : cycle) cycB[v] = (int)cyclesB.size();
            cyclesB.push_back(cycle);
        }
    }

    int A = cyclesA.size(), B = cyclesB.size();
    BipartiteMatcher matcher(A, B);

    // --- Step 3: build bipartite graph ---
    for (int i = 1; i <= n; i++) {
        matcher.addEdge(cycA[i], cycB[i]);
    }

    // --- Step 4: compute maximum matching ---
    int M = matcher.maxMatching();

    // --- Step 5: determine untouched indices (edges in matching) ---
    vector<int> matchedA(A, -1);
    for (int v = 0; v < B; v++) {
        if (matcher.matchR[v] != -1)
            matchedA[matcher.matchR[v]] = v;
    }
    // w
    vector<int> keep; // untouched indices
    vector<int> used(B, 0);
    for (int v = 0; v < B; v++) {
        int u = matcher.matchR[v];
        if (u == -1) continue;
        // find the vertex (i) that connects cyclesA[u] and cyclesB[v]
        for (int i : cyclesA[u]) {
            if (cycB[i] == v) {
                keep.push_back(i);
                break;
            }
        }
    }

    // --- Step 6: output answer ---
    // all other indices must be operated on
    vector<int> ops;
    vector<int> keepMark(n+1, 0);
    for (int x : keep) keepMark[x] = 1;
    for (int i = 1; i <= n; i++)
        if (!keepMark[i]) ops.push_back(i);

    cout << (int)ops.size() << '\n';
    for (int i = 0; i < (int)ops.size(); i++)
        cout << ops[i] << (i + 1 == (int)ops.size() ? '\n' : ' ');
}
