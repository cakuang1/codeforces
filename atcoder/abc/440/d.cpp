#include <iostream>
using std::cin;
using std::cout;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
using std::lower_bound;

typedef long long int ll;

ll n, q;
vector<ll> a;

void solve () {
	sort(a.begin(), a.end());
	for (ll qi = 0; qi < q; qi++) {
		ll x, y;
		cin >> x >> y;

		// a[0, si) < x && a[si, n) >= x
		ll si = lower_bound(a.begin(), a.end(), x) - a.begin();

		// youngest ti where |{x, x+1, ..., a[ti]} - {a[si], a[si+1], ..., a[ti]}| >= y
		ll ti;
		{
			ll ok = n, ng = si-1;
			while (ng + 1 < ok) {
				ll med = (ok + ng) / 2;
				if ((a[med] - x + 1) - (med - si + 1) >= y) {
					ok = med;
				} else {
					ng = med;
				}
			}
			ti = ok;
		}

		ll ans = x + (y-1) + (ti - si + 0);

		cout << ans << "\n";
	}
}

int main (void) {
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	
	cin >> n >> q;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}

	solve();

	return 0;
}
