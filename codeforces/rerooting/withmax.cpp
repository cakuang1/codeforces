#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 200000;

int n;
ll a[MAXN+1];
vector<int> adj[MAXN+1];
ll sumA[MAXN+1];      // sum of a[] in subtree
ll distSum[MAXN+1];   // weighted distance sum at each root
ll totalA = 0;
ll answer = LLONG_MIN;

// First DFS: compute sumA[u] and distSum[1] (rooted at 1)
void dfs1(int u, int p, int depth) {
    sumA[u] = a[u];
    distSum[1] += a[u] * depth;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(v, u, depth + 1);
        sumA[u] += sumA[v];
    }
}

// Second DFS: reroot from u to v
void dfs2(int u, int p) {
    // update answer at u
    answer = max(answer, distSum[u]);
    for (int v : adj[u]) {
        if (v == p) continue;
        // when rerooting from u -> v:
        // nodes in v-subtree get distance -1 each (sumA[v])
        // nodes outside v-subtree get distance +1 each (totalA - sumA[v])
        distSum[v] = distSum[u] + totalA - 2*sumA[v];
        dfs2(v, u);
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        totalA += a[i];
    }
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 1) dfs1 computes sumA[] and distSum[1]
    dfs1(1, 0, 0);

    // 2) dfs2 reroots and fills distSum[u] for all u
    dfs2(1, 0);

    // Each cost is distSum[u], but original problem multiplies by a_v?
    // Actually cost is sum_i dist(i,v)*a_i = distSum[v].
    // If the problem wanted a_v * that, replace answer = max(answer, a[u]*distSum[u]);
    cout << answer << "\n";
    return 0;
}
