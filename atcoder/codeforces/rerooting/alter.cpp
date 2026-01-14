#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 200000;
const ll MOD = 1000000007;

int n;
ll arr[MAXN+1];
vector<int> adj[MAXN+1];

ll cnt[MAXN+1];
ll downSum[MAXN+1];
ll ansPerRoot[MAXN+1];

// first DFS: compute cnt[u] = size of subtree at u,
// and downSum[u] = sum of A(u, x) over all x in u’s subtree
void dfs1(int u, int p) {
    cnt[u] = 1;
    downSum[u] = arr[u] % MOD; 
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(v, u);
        cnt[u] = (cnt[u] + cnt[v]) % MOD;
        // for each x in v's subtree, A(u,x) = arr[u] - A(v,x)
        ll contrib = ( (cnt[v] * arr[u]) % MOD - downSum[v] ) % MOD;
        if (contrib < 0) contrib += MOD;
        downSum[u] = (downSum[u] + contrib) % MOD;
    }
}

// second DFS: reroot the tree to compute ansPerRoot[u] = sum A(u, x) over all x
void dfs2(int u, int p) {
    ansPerRoot[u] = downSum[u];
    for (int v : adj[u]) {
        if (v == p) continue;
        // save originals
        ll du = downSum[u], dv = downSum[v];
        ll cu = cnt[u], cv = cnt[v];

        // remove v-subtree contribution from u
        ll back = ( (cv * arr[u]) % MOD - dv ) % MOD;
        if (back < 0) back += MOD;
        downSum[u] = (downSum[u] - back) % MOD;
        if (downSum[u] < 0) downSum[u] += MOD;
        cnt[u] = (cnt[u] - cv + MOD) % MOD;

        // add the rest-of-tree contribution into v
        // now v's "subtree" size becomes original n
        ll add = ( (cnt[u] * arr[v]) % MOD - downSum[u] ) % MOD;
        if (add < 0) add += MOD;
        downSum[v] = (downSum[v] + add) % MOD;
        cnt[v] = (cnt[v] + cnt[u]) % MOD;

        // recurse
        dfs2(v, u);

        // restore
        downSum[u] = du;
        downSum[v] = dv;
        cnt[u] = cu;
        cnt[v] = cv;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] = (arr[i] % MOD + MOD) % MOD;
    }
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(1, 0);
    dfs2(1, 0); 
    
    /

    ll answer = 0;
    for (int u = 1; u <= n; u++) {
        answer = (answer + ansPerRoot[u]) % MOD;
    }
    cout << answer << "\n";
    return 0;
}
