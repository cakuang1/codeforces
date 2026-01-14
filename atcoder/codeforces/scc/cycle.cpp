#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1000000007;

ll modExp(ll base, ll power) {
    if (power == 0) return 1;
    ll cur = modExp(base, power/2) % MOD;
    cur = (cur * cur) % MOD;
    if (power & 1) cur = (cur * base) % MOD;
    return cur;
}
ll inv(ll x) { return modExp(x, MOD-2); }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll add(ll a, ll b) { return (a+b) % MOD; }
ll sub(ll a, ll b) { return (a - b + MOD) % MOD; }

const int MAXN = 100005;
int n, m, k;
vector<int> adj[MAXN];
int parentArr[MAXN];
int depthArr[MAXN];
int startNode = -1, endNode = -1, cycleSize = -1;

void dfs(int u, int p, int d) {
    parentArr[u] = p;
    depthArr[u] = d;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (depthArr[v] == 0) {
            // tree-edge
            dfs(v, u, d+1);
        } else {
            // back-edge to an ancestor ⇒ found a cycle
            int len = depthArr[u] - depthArr[v] + 1;
            if (len >= k+1 && cycleSize == -1) {
                startNode = u;
                endNode   = v;
                cycleSize = len;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0, 1);

    if (cycleSize == -1) {
        cout << "-1\n";  // no such cycle
        return 0;
    }

    cout << cycleSize << "\n";
    vector<int> path;
    int cur = startNode;
    while (cur != endNode) {
        path.push_back(cur);
        cur = parentArr[cur];
    }
    path.push_back(endNode);
    for (int x : path) {
        cout << x << " ";
    }
    cout << "\n";
    return 0;
}
