#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int MAX_N = 1e5 + 1;
constexpr int LG = 17;

int tin[MAX_N], tout[MAX_N], d[MAX_N], lift[MAX_N][LG], timer;
ll dp[MAX_N];
vector<int> adj[MAX_N], vadj[MAX_N], at_d[MAX_N];

void dfs(int v, int p) {
	d[v] = v ? d[p] + 1 : 0;
	at_d[d[v]].push_back(v);
	tin[v] = timer++;

	lift[v][0] = p;
	for (int i = 1; i < LG; i++) { lift[v][i] = lift[lift[v][i - 1]][i - 1]; }

	for (int u : adj[v]) {
		if (u == p) { continue; }
		dfs(u, v);
	}

	tout[v] = timer++;
}

int is_ancestor(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }

int lca(int u, int v) {
	if (is_ancestor(u, v)) { return u; }
	if (is_ancestor(v, u)) { return v; }

	for (int i = LG - 1; i >= 0; i--) {
		if (!is_ancestor(lift[u][i], v)) { u = lift[u][i]; }
	}
	return lift[u][0];
}

bool sort_tin(const int &a, const int &b) { return tin[a] < tin[b]; }

vector<int> vtree(vector<int> &key) {
	// construct virtual tree from set of nodes
	if (key.empty()) return {};

	vector<int> res = key;
	sort(res.begin(), res.end(), sort_tin);

	for (int i = 1; i < (int)key.size(); i++) {
		res.push_back(lca(key[i - 1], key[i]));
	}

	sort(res.begin(), res.end(), sort_tin);
	res.erase(unique(res.begin(), res.end()), res.end());

	for (int v : res) { vadj[v].clear(); }

	vector<int> stk = {res[0]};

	for (int i = 1; i < (int)res.size(); i++) {
		while (tin[res[i]] > tout[stk.back()]) { stk.pop_back(); }

		vadj[stk.back()].push_back(res[i]);
		stk.push_back(res[i]);
	}

	return res;
}

// BeginCodeSnip{RMQ Template}
template <class T> class MinSegmentTree {
  private:
	const T DEFAULT = numeric_limits<T>().max();

	vector<T> segtree;
	int len;

  public:
	MinSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}

	void set(int ind, T val) {
		ind += len;
		segtree[ind] = val;
		for (; ind > 1; ind /= 2) {
			segtree[ind / 2] = min(segtree[ind], segtree[ind ^ 1]);
		}
	}

	T range_min(int start, int end) {
		T res = DEFAULT;
		for (start += len, end += len; start < end; start /= 2, end /= 2) {
			if (start % 2 == 1) { res = min(res, segtree[start++]); }
			if (end % 2 == 1) { res = min(res, segtree[--end]); }
		}
		return res;
	}
};
// EndCodeSnip

int main() {
	int test_num;
	cin >> test_num;
	for (int t = 0; t < test_num; t++) {
		int n;
		cin >> n;

		for (int i = 0; i <= n; i++) {
			adj[i].clear();
			at_d[i].clear();
		}

		MinSegmentTree<int> rmq(n);
		for (int i = 0; i < n; i++) {
			int a;
			cin >> a;
			rmq.set(i, a);
		}

		for (int i = 1; i < n; i++) {
			int u, v;
			cin >> u >> v;
			u--, v--;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		dfs(0, 0);

		ll ans = 0;

		for (int dep = 0; dep < n; dep++) {
			vector<int> vt = vtree(at_d[dep]);
			reverse(vt.begin(), vt.end());

			for (int v : vt) {
				dp[v] = rmq.range_min(dep - d[v], dep + 1);

				if (!vadj[v].empty()) {
					ll sum = 0;
					for (int u : vadj[v]) { sum += dp[u]; }
					dp[v] = min(dp[v], sum);
				}
			}

			if (!vt.empty()) { ans += dp[vt.back()]; }
		}

		cout << ans << "\n";
	}
}