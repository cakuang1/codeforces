#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN    = 100000;
const int MAXLOG  = 18;  // enough for 2^17=131072>1e5
const int MAXA    = 10;  // maximum 'a' in queries

int n, m, q;
vector<int> adj[MAXN+1];
int parent_[MAXN+1], depth[MAXN+1], up[MAXN+1][MAXLOG];
vector<int> city[MAXN+1];
vector<int> dp[MAXN+1][MAXLOG];

// Merge two sorted vectors A,B into R, stopping once size=limit
vector<int> merge_limit(const vector<int>& A, const vector<int>& B, int limit) {
    vector<int> R;
    R.reserve(limit);
    int i = 0, j = 0, na = A.size(), nb = B.size();
    while ((i < na || j < nb) && (int)R.size() < limit) {
        if (j == nb || (i < na && A[i] <= B[j])) {
            R.push_back(A[i++]);
        } else {
            R.push_back(B[j++]);
        }
    }
    return R;
}

// 1) BFS to set parent_[] and depth[]
void build_tree(int root = 1) {
    queue<int> q;
    q.push(root);
    parent_[root] = 0;
    depth[root]   = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (v == parent_[u]) continue;
            parent_[v] = u;
            depth[v]   = depth[u] + 1;
            q.push(v);
        }
    }
}

// 2) LCA via binary lifting
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a,b);
    int diff = depth[a] - depth[b];
    for (int j = 0; j < MAXLOG; j++) {
        if (diff & (1<<j)) {
            a = up[a][j];
        }
    }
    if (a == b) return a;
    for (int j = MAXLOG-1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return parent_[a];
}

// 3) Collect the first 'k' people IDs on the path of length 'steps'
//    starting at x and going up toward the root.
//    This includes the starting node and climbs exactly 'steps' nodes,
//    merging dp[x][j] blocks whenever that bit is set.
vector<int> collect(int x, int steps) {
    vector<int> R;
    R.reserve(MAXA);
    for (int j = 0; j < MAXLOG && x; j++) {
        if (steps & (1<<j)) {
            R = merge_limit(R, dp[x][j], MAXA);
            x = up[x][j];
        }
    }
    return R;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 0; i < n-1; i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 1) build tree from node 1
    build_tree(1);

    // 2) read city assignments
    //    person IDs are 1..m, living in city c
    for (int id = 1; id <= m; id++) {
        int c;
        cin >> c;
        city[c].push_back(id);
    }

    // 3) initialize level-0 ancestors and dp lists
    for (int v = 1; v <= n; v++) {
        up[v][0]    = parent_[v];
        // dp[v][0] = the people in city v, sorted already by increasing id
        dp[v][0] = city[v];
        if ((int)dp[v][0].size() > MAXA)
            dp[v][0].resize(MAXA);
    }

    // 4) build binary-lifting table and dp for j >= 1
    for (int j = 1; j < MAXLOG; j++) {
        for (int v = 1; v <= n; v++) {
            int mid = up[v][j-1];
            up[v][j] = mid ? up[mid][j-1] : 0;
            if (mid) {
                dp[v][j] = merge_limit(dp[v][j-1], dp[mid][j-1], MAXA);
            } else {
                dp[v][j].clear();
            }
        }
    }

    // 5) answer queries
    while (q--) {
        int v,u,a;
        cin >> v >> u >> a;
        // find LCA
        int w = lca(v,u);
        // collect from v up to w (inclusive)
        int dist1 = depth[v] - depth[w] + 1;
        auto A = collect(v, dist1);
        // collect from u up to just below w
        int dist2 = depth[u] - depth[w];
        auto B = collect(u, dist2);
        // merge the two result lists, limit to 'a'
        auto ans = merge_limit(A, B, a);
        // output
        cout << ans.size();
        for (int id : ans) cout << ' ' << id;
        cout << "\n";
    }

    return 0;
}

