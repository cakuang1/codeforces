struct Dinic {     // flow template
	using F = ll;  // flow type
	struct Edge {
		int to;
		F flo, cap;
	};
	int N;
	V<Edge> eds;
	V<vi> adj;
	void init(int _N) {
		N = _N;
		adj.rsz(N), cur.rsz(N);
	}
	/// void reset() { trav(e,eds) e.flo = 0; }
	void ae(int u, int v, F cap, F rcap = 0) {
		assert(min(cap, rcap) >= 0);
		adj[u].pb(sz(eds));
		eds.pb({v, 0, cap});
		adj[v].pb(sz(eds));
		eds.pb({u, 0, rcap});
	}
	vi lev;
	V<vi::iterator> cur;
	bool bfs(int s, int t) {  // level = shortest distance from source
		lev = vi(N, -1);
		F0R(i, N) cur[i] = begin(adj[i]);
		queue<int> q({s});
		lev[s] = 0;
		while (sz(q)) {
			int u = q.ft;
			q.pop();
			trav(e, adj[u]) {
				const Edge &E = eds[e];
				int v = E.to;
				if (lev[v] < 0 && E.flo < E.cap) q.push(v), lev[v] = lev[u] + 1;
			}
		}
		return lev[t] >= 0;
	}
	F dfs(int v, int t, F flo) {
		if (v == t) return flo;
		for (; cur[v] != end(adj[v]); cur[v]++) {
			Edge &E = eds[*cur[v]];
			if (lev[E.to] != lev[v] + 1 || E.flo == E.cap) continue;
			F df = dfs(E.to, t, min(flo, E.cap - E.flo));
			if (df) {
				E.flo += df;
				eds[*cur[v] ^ 1].flo -= df;
				return df;
			}  // saturated >=1 one edge
		}
		return 0;
	}
	F maxFlow(int s, int t) {
		F tot = 0;
		while (bfs(s, t))
			while (F df = dfs(s, t, numeric_limits<F>::max())) tot += df;
		return tot;
	}
};

int main() {
	int n;
	re(n);
	Dinic D;
	D.init(2 * n + 2);
	F0R(i, n) {
		D.ae(0, i + 1, 1);
		D.ae(i + 1 + n, 2 * n + 1, 1);
		F0R(j, n) {
			char c;
			re(c);
			if (c == 'o') D.ae(i + 1, j + 1 + n, MOD);  // some big capacity -> not cut
		}
	}
	ps(D.maxFlow(0, 2 * n + 1));
	D.bfs(0, 2 * n + 1);
	FOR(i, 1, n + 1) if (D.lev[i] < 0) ps(1, i);  // edge from 0 to i is cut
	FOR(i, 1, n + 1)
	if (D.lev[i + n] >= 0) ps(2, i);  // edge from i+n to 2*n+1 is cut
}



// w