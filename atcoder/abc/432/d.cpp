#include <iostream>
using std::cin;
using std::cout;
using std::min;
using std::max;
#include <vector>
using std::vector;
using std::pair;
#include <algorithm>
using std::sort;
#include <string>
using std::string;

typedef long long int ll;

#include <atcoder/dsu>
using atcoder::dsu;

ll n, h, w;
vector<string> c;
vector<ll> a, b;

typedef struct {
	ll xl;
	ll xr;
	ll yl;
	ll yr;
} Rect;

void solve () {
	vector<Rect> curr = {
		{0, h-1, 0, w-1}
	};

	for (ll qi = 0; qi < n; qi++) {
		vector<Rect> prev = curr;
		curr.clear();

		for (Rect r : prev) {
			if (c[qi] == "X") {
				if (r.xr < a[qi]) {
					curr.push_back({r.xl,  r.xr,    r.yl - b[qi], r.yr - b[qi]});
				} else if (r.xl >= a[qi]) {
					curr.push_back({r.xl,  r.xr,    r.yl + b[qi], r.yr + b[qi]});
				} else {
					curr.push_back({r.xl,  a[qi]-1, r.yl - b[qi], r.yr - b[qi]});
					curr.push_back({a[qi], r.xr,    r.yl + b[qi], r.yr + b[qi]});
				}
			} else if (c[qi] == "Y") {
				if (r.yr < a[qi]) {
					curr.push_back({r.xl - b[qi], r.xr - b[qi], r.yl,  r.yr});
				} else if (r.yl >= a[qi]) {
					curr.push_back({r.xl + b[qi], r.xr + b[qi], r.yl,  r.yr});
				} else {
					curr.push_back({r.xl - b[qi], r.xr - b[qi], r.yl,  a[qi]-1});
					curr.push_back({r.xl + b[qi], r.xr + b[qi], a[qi], r.yr});
				}
			} else {
				abort();
			}
		}
	}

	dsu d(curr.size());
	for (ll i = 0; i < curr.size(); i++) {
		for (ll j = i+1; j < curr.size(); j++) {
			Rect s = curr[i], t = curr[j];

			bool xtouch = (!(s.xr+1 <= t.xl) && !(t.xr+1 <= s.xl));
			bool ytouch = (!(s.yr+1 <= t.yl) && !(t.yr+1 <= s.yl));
			bool istouch = false;
			if ((s.xr+1 == t.xl) || (t.xr+1 == s.xl)) {
				if (ytouch) istouch = true;
			}
			if ((s.yr+1 == t.yl) || (t.yr+1 == s.yl)) {
				if (xtouch) istouch = true;
			}

			if (istouch) {
				d.merge(i, j);
			}
		}
	}
	vector<vector<int> > vs = d.groups();
	vector<ll> sizes(vs.size(), 0);
	for (ll i = 0; i < vs.size(); i++) {
		for (ll j = 0; j < vs[i].size(); j++) {
			Rect r = curr[vs[i][j]];
			ll area = (r.xr - r.xl + 1) * (r.yr - r.yl + 1);

			sizes[i] += area;
		}
	}
	
	sort(sizes.begin(), sizes.end());

	cout << sizes.size() << "\n";
	for (ll i = 0; i < sizes.size(); i++) {
		if (i > 0) cout << " ";
		cout << sizes[i];
	}
	cout << "\n";

	return;
}

int main (void) {
	
	cin >> n >> h >> w;
	
	c.resize(n);
	a.resize(n);
	b.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> c[i] >> a[i] >> b[i];
	}

	solve();
	

	return 0;
}
