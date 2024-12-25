#include <bits/stdc++.h>
 
#define forn(i, n) for (int i = 0; i < int(n); i++)
 
using namespace std;
 
const int INF = 1e9;
 
vector<int> in, out;
vector<vector<int>> g;
vector<int> dp;
 
int calc(int v){
    if (dp[v] != -1) return dp[v];
    if (in[v] >= 2 && out[v] >= 2){
        dp[v] = 1;
        for (int u : g[v])
            dp[v] = max(dp[v], calc(u) + 1);
    }
    else if (in[v] >= 2){
        dp[v] = 1;
    }
    else{
        dp[v] = -INF;
    }
    return dp[v];
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    g.resize(n);
    in.resize(n);
    out.resize(n);
    forn(i, m){
        int v, u;
        scanf("%d%d", &v, &u);
        --v, --u;
        g[v].push_back(u);
        ++in[u];
        ++out[v];
    }
    int ans = 1;
    dp.resize(n, -1);
    forn(v, n) if (out[v] >= 2){
        for (int u : g[v]){
            ans = max(ans, calc(u) + 1);
        }
    }
    printf("%d\n", ans);
    return 0;
}