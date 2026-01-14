#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 13;

int n, m, q;
vector<pair<int,int>> edges;
vector<tuple<int,int,int>> lcas;

ll dp[MAXN][1<<MAXN];
bool vis[MAXN][1<<MAXN];

// lowest set bit in mask
int lowBit(int mask) {
    for (int i = 0; i < n; i++)
        if (mask & (1<<i)) return i;
    return -1;
}



// we

bool checkEdges(int sub, int childRoot, int root) {
    for (auto [u,v] : edges) {
        bool inSubU = sub & (1<<u);
        bool inSubV = sub & (1<<v);
        if (inSubU ^ inSubV) {
            // one in sub, one in rest
            if (!( (u==root && v==childRoot) || (v==root && u==childRoot) ))
                return false;
        }
    }
    return true;
}



// wtake wra remainder w

bool checkLCA(int sub, int rest, int root) {
    for (auto [a,b,c] : lcas) {
        bool inSubA = sub & (1<<a), inSubB = sub & (1<<b);
        bool inRestA = rest & (1<<a), inRestB = rest & (1<<b);
        // if a and b split between sub and rest, LCA must be root
        if ((inSubA && inRestB) || (inSubB && inRestA)) {
            if (c != root) return false;
        }
    }
    return true;
}

/
ll solve(int root, int mask) {
    if (__builtin_popcount(mask) <= 1) return 1;
    if (vis[root][mask]) return dp[root][mask];
    vis[root][mask] = true;
    ll &res = dp[root][mask];
    res = 0;

    int others = mask ^ (1<<root);
    int lowest = lowBit(others);

    // iterate over submasks
    for (int sub = others; sub; sub = (sub-1)&others) {
        if (lowBit(sub) != lowest) continue; // avoid double counting
        int rest = mask ^ sub;
        for (int childRoot = 0; childRoot < n; childRoot++) {
            if (!(sub & (1<<childRoot))) continue;
            if (!checkEdges(sub, childRoot, root)) continue;
            if (!checkLCA(sub, rest, root)) continue;
            res += solve(childRoot, sub) * solve(root, rest);
        }
    }
    return res;
}


// does this wsubmaks e

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        int u,v; cin >> u >> v;
        edges[i] = {u-1,v-1};
    }
    for (int i = 0; i < q; i++) {
        int a,b,c; cin >> a >> b >> c;
        a--; b--; c--;
        if (a==b && a!=c) {
            cout << 0 << "\n"; return 0;
        }
        lcas.push_back({a,b,c});
    }

    cout << solve(0, (1<<n)-1) << "\n";
}


