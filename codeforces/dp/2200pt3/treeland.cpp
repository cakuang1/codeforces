#include<bits/stdc++.h>
#define LL long long
#define fi first
#define se second
#define mk make_pair
#define PLL pair<LL, LL>
#define PLI pair<LL, int>
#define PII pair<int, int>
#define SZ(x) ((int)x.size())
#define ull unsigned long long

using namespace std;

const int N = 6000 + 7;
const int inf = 0x3f3f3f3f;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int mod = 1e9 + 7;
const double eps = 1e-8;
const double PI = acos(-1);

int n, tot, ans, r[N], hs[N];
short up[N][N], dn[N][N];
vector<int> G[N];

void dfs(int u, int fa) {
    for(int i = r[u]; i <= tot; i++) up[u][i] = 1;
    for(int i = 1; i <= r[u]; i++) dn[u][i] = 1;
    for(auto& v : G[u]) {
        if(v == fa) continue;
        dfs(v, u);
        int mx1 = 0, mx2 = 0;
        for(int i = 1; i <= tot; i++) {
            if(up[v][i] + dn[u][i + 1] > ans) ans = up[v][i] + dn[u][i + 1];
            if(dn[v][i] + up[u][i - 1] > ans) ans = dn[v][i] + up[u][i - 1];
        }
        for(int i = 1; i <= tot; i++) {
            if(up[v][i] > up[u][i]) up[u][i] = up[v][i];
            if(dn[v][i] > dn[u][i]) dn[u][i] = dn[v][i];
            if(i < r[u] && up[v][i] > mx1) mx1 = up[v][i];
            if(i > r[u] && dn[v][i] > mx2) mx2 = dn[v][i];
        }
        if(mx1 + 1 > up[u][r[u]]) up[u][r[u]] = mx1 + 1;
        if(mx2 + 1 > dn[u][r[u]]) dn[u][r[u]] = mx2 + 1;
        for(int i = 1; i <= tot; i++) up[u][i] = max(up[u][i], up[u][i - 1]);
        for(int i = tot; i >= 1; i--) dn[u][i] = max(dn[u][i], dn[u][i + 1]);
    }
    if(up[u][tot] > ans) ans = up[u][tot];
    if(dn[u][1] > ans) ans = dn[u][1];
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
        hs[++tot] = r[i];
    }
    sort(hs + 1, hs + tot + 1);
    tot = unique(hs + 1, hs + tot + 1) - hs - 1;
    for(int i = 1; i <= n; i++)
        r[i] = lower_bound(hs, hs + tot, r[i]) - hs;
    for(int i = 2; i <= n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    printf("%d\n", max(1, ans));
    return 0;
}


// left   e