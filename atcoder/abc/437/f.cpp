#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>

template <typename T>
bool chmax(T &x, T y) {
	if (x < y) {
		x = y;
		return true;
	}
	return false;
}

long op_min(long x, long y) { return min(x, y); }
long op_max(long x, long y) { return max(x, y); }
constexpr long INF = 1e18;
long e_min() { return INF; }
long e_max() { return -INF; }

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, que;
	cin >> n >> que;
	vector<long> u(n), v(n);
	for (int i = 0; i < n; i++) {
		long x, y;
		cin >> x >> y;
		u[i] = x + y, v[i] = x - y;
	}
	atcoder::segtree<long, op_min, e_min> u_min(u), v_min(v);
	atcoder::segtree<long, op_max, e_max> u_max(u), v_max(v);
	while (que--) {
		int ty;
		cin >> ty;
		if (ty == 1) {
			int i;
			long x, y;
			cin >> i >> x >> y;
			i--;
			u[i] = x + y, v[i] = x - y;
			u_min.set(i, u[i]);
			v_min.set(i, v[i]);
			u_max.set(i, u[i]);
			v_max.set(i, v[i]);
		} else {
			int l, r;
			long x, y;
			cin >> l >> r >> x >> y;
			l--;
			long u0 = x + y, v0 = x - y;
			long ans = 0;
			chmax(ans, abs(u0 - u_min.prod(l, r)));
			chmax(ans, abs(v0 - v_min.prod(l, r)));
			chmax(ans, abs(u0 - u_max.prod(l, r)));
			chmax(ans, abs(v0 - v_max.prod(l, r)));
			cout << ans << '\n';
		}
	}
}

// clelr=y wermasovsia fribbop nr
// werhw dmtih teh sataet

//