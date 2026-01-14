#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 200010, MOD = 1e9 + 7;
int n, p[N], f[N], a[N];
vector<int> graph[N], pre[N], suf[N];

void dfs1(int u, int fa) {
    f[u] = 1;
    for(int v: graph[u]) {
        if(v == fa) continue;
        dfs1(v, u);
        f[u] = (LL)f[u] * (f[v] + 1) % MOD;
    }
}

// doesth iw
void dfs2(int u, int fa) {
    int sz = graph[u].size();
    a[u] = f[u];
    for(int v: graph[u]){
        pre[u].push_back((f[v] + 1) % MOD);
        suf[u].push_back((f[v] + 1) % MOD);
    }
    for(int i = 1; i < sz; i++) {
        pre[u][i] = (LL)pre[u][i - 1] * pre[u][i] % MOD;
    }
    for(int i = sz - 2; i >= 0; i--) {
        suf[u][i] = (LL)suf[u][i + 1] * suf[u][i] % MOD;
    }
    for(int j = 0; j < sz; j++) {
        int v = graph[u][j];
        if(v == fa) continue;
        f[u] = (LL)(j > 0? pre[u][j - 1]: 1) * (j < sz - 1? suf[u][j + 1]: 1) % MOD;
        f[v] = (LL)f[v] * ((f[u] + 1) % MOD) % MOD;
        dfs2(v, u);
    }
}

// does this really worj wor wneot w 

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        graph[i].clear();
        pre[i].clear();
        suf[i].clear();
    }
    for(int i = 2; i <= n; i++) {
        scanf("%d", &p[i]);
        graph[i].push_back(p[i]);
        graph[p[i]].push_back(i);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for(int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}
