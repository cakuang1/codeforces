#include <iostream>
using std::cin;
using std::cout;
using std::min;
using std::max;
#include <vector>
using std::vector;

typedef long long int ll;

ll n, x, y;
vector<ll> a;

ll solve () {
	ll mina = a[0];
	for (ll i = 0; i < n; i++) {
		mina = min(mina, a[i]);
	}

	ll sum = 0;
	ll w = mina * y;
	for (ll i = 0; i < n; i++) {
		ll vs = (a[i] - mina) * y;
		ll vt = (y - x);
		if (vs % vt != 0) {
			return -1;
		}
		ll minor = vs / vt;
		if (minor > a[i]) {
			return -1;
		}
		sum += (a[i] - minor);
	}

	return sum;
}

int main (void) {
	// input
	cin >> n >> x >> y;
	a.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}

	ll ans = solve();
	cout << ans << "\n";
	

	return 0;
}
