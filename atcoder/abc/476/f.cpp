#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <vector>
using std::vector;
using std::pair;
#include <map>
using std::map;
using std::max;
using std::min;


#ifdef DEBUG
const int debug = 1;
#else
const int debug = 0;
#endif

using ll = int64_t;
using P = pair<ll, ll>;

const ll FOD = 998244353;
#include <atcoder/modint>
using mint = atcoder::modint998244353;
#include <atcoder/convolution>
using atcoder::convolution;

ll n, k, h, w, m;
vector<ll> a, b;

inline void output (const ll x) {
	cout << x << "\n";
}

void solve() {
	ll c[n][n];
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			c[i][j] = a[i] * b[j] % m;
		}
	}

	const ll nn = 3*n+1;
	const ll offset = n;
	ll sx[nn][nn], sy[nn][nn], s[nn][nn];
	for (ll i = 0; i < nn; i++) {
		for (ll j = 0; j < nn; j++) {
			sx[i][j] = 0;
			sy[i][j] = 0;
			s[i][j] = 0;
		}
	}

	ll outsum = 0;
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			outsum += c[i][j] * n;

			sx[(offset+i) - (n-1) - 0][(offset+j) - (n-1) - 0] += c[i][j] * (-1);
			sx[(offset+i) + (n+0) + 1][(offset+j) + (n+0) + 1] -= c[i][j] * (-1);

			sy[(offset+i) - (n-1) - 0][(offset+j) + (n+0) + 0] += c[i][j] * (+1);
			sy[(offset+i) + (n+0) + 1][(offset+j) - (n-1) - 1] -= c[i][j] * (+1);

		}
	}

	// sx, sy
	for (ll i = 0; i < nn; i++) {
		for (ll j = 0; j < nn; j++) {
			if (i - 1 >= 0 && j - 1 >= 0) sx[i][j] += sx[i - 1][j - 1];
			if (i - 1 >= 0 && j + 1 < nn) sy[i][j] += sy[i - 1][j + 1];

			s[i][j] = sx[i][j] + sy[i][j];
		}
	}

	for (ll i = 0; i < nn; i++) {
		ll x = 0;
		for (ll j = 0; j < nn; j++) {
			s[i][j] += x;
			x = s[i][j];
		}
	}
	for (ll j = 0; j < nn; j++) {
		ll x = 0;
		for (ll i = 0; i < nn; i++) {
			s[i][j] += x;
			x = s[i][j];
		}
	}

	ll ans = 0;
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			ll item = outsum + s[offset+i][offset+j];
			if (debug) {
				cerr << i << " " << j << ": " << item << endl;
			}

			ans ^= (item + i*n + j);
		}
	}

	output(ans);


	return;
}

int main (void) {
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);

	cin >> n;
	cin >> m;
	a.resize(n);
	b.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < n; i++) {
		cin >> b[i];
	}

	
	solve();

	return 0;
}
