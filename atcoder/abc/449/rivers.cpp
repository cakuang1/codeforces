#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll)4e18;

int n, k;
ll w[105];
int parent_[105];
ll distRoot[105];
int depth_[105];
int ancAtDepth[105][105];          // ancAtDepth[v][d] = ancestor of v at depth d
vector<pair<int,int>> adj[105];    // {child, edge length}

// dp[v][used][d]
ll dp[105][55][105];
int subSize[105];

void dfs1(int v) {
    for (auto [to, len] : adj[v]) {
        depth_[to] = depth_[v] + 1;
        distRoot[to] = distRoot[v] + len;
        parent_[to] = v;

        // build ancestor table by depth
        for (int d = 0; d <= depth_[v]; d++) {
            ancAtDepth[to][d] = ancAtDepth[v][d];
        }
        ancAtDepth[to][depth_[to]] = to;

        dfs1(to);
    }
}

//we sjdst sfwerw
void dfs2(int v) {
    subSize[v] = 1;

    for (int used = 0; used <= k + 1; used++) {
         for (int d = 0; d <= n; d++) {
            dp[v][used][d] = INF;
        }
    }
    // ws sehsif mssl wrhw wer
    for (int d = 0; d <= depth_[v]; d++) {
        int a = ancAtDepth[v][d];

        if (a == v) {
            // nearest sawmill is v itself
            dp[v][0][d] = INF; // impossible to have nearest sawmill at v with 0 sawmills in subtree
            dp[v][1][d] = 0;   // build sawmill at v
        } else {
            // 0 sawmills in subtree: v's logs go up to a
            dp[v][0][d] = w[v] * (distRoot[v] - distRoot[a]);

            // 1 sawmill in subtree: put it at v
            dp[v][1][d] = 0;
        }
    }

    // merge children
    for (auto [to, len] : adj[v]) {
        dfs2(to);

        static ll ndp[55][105];
        for (int used = 0; used <= k + 1; used++) {
            for (int d = 0; d <= n; d++) {
                ndp[used][d] = INF;
            }
        }

        for (int d = 0; d <= depth_[v]; d++) {
            for (int s1 = 0; s1 <= min(subSize[v], k + 1); s1++) {
                if (dp[v][s1][d] >= INF) continue;
                for (int s2 = 0; s2 <= min(subSize[to], k + 1 - s1); s2++) {
                    if (dp[to][s2][d] >= INF) continue;
                    ndp[s1 + s2][d] = min(ndp[s1 + s2][d], dp[v][s1][d] + dp[to][s2][d]);
                }
            }
        }

        subSize[v] += subSize[to];
        for (int used = 0; used <= min(subSize[v], k + 1); used++) {
            for (int d = 0; d <= depth_[v]; d++) {
                dp[v][used][d] = ndp[used][d];
            }
        }
    }

    // important trick:
    // if you can place a sawmill at v, then for any ancestor depth d < depth[v],
    // that solution is also valid there, because logs stop at v before reaching higher ancestor
    for (int d = depth_[v] - 1; d >= 0; d--) {
        for (int used = 0; used <= min(subSize[v], k + 1); used++) {
            dp[v][used][d] = min(dp[v][used][d], dp[v][used][depth_[v]]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // villages 1..n, root = 0
    for (int i = 1; i <= n; i++) {
        int v, d;
        cin >> w[i] >> v >> d;
        adj[v].push_back({i, d});
    }
    
    depth_[0] = 0;
    distRoot[0] = 0;
    parent_[0] = -1;
    ancAtDepth[0][0] = 0;

    dfs1(0);
    dfs2(0);

    // root's sawmill is included, so total sawmills = k + 1
    cout << dp[0][k + 1][0] << '\n';
    return 0;
}