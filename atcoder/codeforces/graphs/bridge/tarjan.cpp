/**
 *    author : Lăng Trọng Đạt
 *    created: 11-06-2024 
**/
#include <bits/stdc++.h>
using namespace std;
#ifndef LANG_DAT
#define db(...) ;
#endif // LANG_DAT
#define int long long
#define mp make_pair
#define f first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using pii = pair<int, int>;
using vi = vector<int>;
#define FOR(i, a, b) for (int (i) = a; (i) <= (b); i++)
void mx(int& a, int b) { if (b > a) a = b; }
void mi(int& a, int b) { if (b < a) a = b; }
#define si(x) (int)(x.size())
const int INF = 1e18;
const int MOD = 1e9 + 7;

const int MAXN = 1e6 + 5;
int dp[MAXN], comp[MAXN];
vector<pii> adj[MAXN], comp_adj[MAXN];
int n, m, a, b, w, comp_cnt = 0;

int calc(int x) {
    int lo = 0, hi = x, res = 0, cnt = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (mid * (mid + 1) / 2 <= x) {
            db(x, mid)
            res = x * (mid + 1) - (mid + 2) * mid * (mid + 1) / 6;
            lo = mid + 1;
        } else hi = mid - 1;
    }
    return res;
}
vi path;
int low[MAXN], id[MAXN], timer = 1;
void dfs(int v) {
    path.pb(v);
    low[v] = id[v] = timer++;
    for (auto[u, w] : adj[v]) {
        if (comp[u]) continue;
        if (id[u]) mi(low[v], id[u]);
        else {
            dfs(u);
            mi(low[v], low[u]);
        }
    }
    if (low[v] == id[v]) {
        comp[v] = ++comp_cnt;
        while (path.back() != v) {
            int u = path.back(); path.pop_back();
            comp[u] = comp_cnt;
        }
        path.pop_back();
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    if (fopen("hi.inp", "r")) {
        freopen("hi.inp", "r", stdin);
//        freopen("hi.out", "w", stdout);
    } 

    cin >> n >> m;
    FOR(i, 1, m) {
        cin >> a >> b >> w;
        adj[a].pb({b, w});
    }    
    
    int root;
    cin >> root;
    dfs(root);

    FOR(v, 1, n) {
        for (auto[u, w] : adj[v]) {
            if (comp[v] != comp[u]) {
                comp_adj[comp[v]].pb({comp[u], w}); 
            } else {
                dp[comp[v]] += calc(w);
            }
        }
    }
    int ans = 0;
    FOR(i, 1, comp_cnt) {
        int mc = 0;
        for (auto[u, w] : comp_adj[i]) {
            mx(mc, dp[u] + w);
        }
        dp[i] += mc;
        mx(ans, dp[i]);
    }    

    cout << ans;
}