/*
 
p_b_p_b txdy
AThousandSuns txdy
Wu_Ren txdy
Appleblue17 txdy
 
*/
 
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second
#define mems(a, x) memset((a), (x), sizeof(a))
 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;
 
const int maxn = 210;
const ll mod = 1000000007;
const ll inv2 = (mod + 1) / 2;
 
ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) {
			res = res * b % mod;
		}
		b = b * b % mod;
		p >>= 1;
	}
	return res;
}
 
ll n, head[maxn], len, f[maxn][maxn];
int dep[maxn], sz[maxn], son[maxn], fa[maxn];
int top[maxn];
bool vis[maxn];
 
struct edge {
	int to, next;
} edges[maxn << 1];
 
void add_edge(int u, int v) {
	edges[++len].to = v;
	edges[len].next = head[u];
	head[u] = len;
}
 
int dfs(int u, int f, int d) {
	fa[u] = f;
	dep[u] = d;
	sz[u] = 1;
	int maxson = -1;
	for (int i = head[u]; i; i = edges[i].next) {
		int v = edges[i].to;
		if (v == f) {
			continue;
		}
		sz[u] += dfs(v, u, d + 1);
		if (sz[v] > maxson) {
			son[u] = v;
			maxson = sz[v];
		}
	}
	return sz[u];
}
 
void dfs2(int u, int tp) {
	top[u] = tp;
	vis[u] = 1;
	if (!son[u]) {
		return;
	}
	dfs2(son[u], tp);
	for (int i = head[u]; i; i = edges[i].next) {
		int v = edges[i].to;
		if (!vis[v]) {
			dfs2(v, v);
		}
	}
}
 
int querylca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) {
			swap(x, y);
		}
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) {
		swap(x, y);
	}
	return x;
}
 
void solve() {
	scanf("%lld", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	for (int i = 1; i <= n; ++i) {
		f[i][0] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			f[i][j] = (f[i - 1][j] + f[i][j - 1]) % mod * inv2 % mod;
		}
	}
	ll ans = 0;
	for (int rt = 1; rt <= n; ++rt) {
		mems(dep, 0);
		mems(sz, 0);
		mems(fa, 0);
		mems(son, 0);
		mems(top, 0);
		mems(vis, 0);
		dfs(rt, -1, 1);
		dfs2(rt, rt);
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				int lca = querylca(i, j);
				ans = (ans + f[dep[i] - dep[lca]][dep[j] - dep[lca]]) % mod;
			}
		}
	}
	ans = ans * qpow(n, mod - 2) % mod;
	printf("%lld\n", ans);
}
 
int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

// count the first and last 