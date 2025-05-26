#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ——— KACTL‐style LineContainer for max‐hull ———
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x)        const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	static const ll inf = LLONG_MAX;
	// floored division
	ll div(ll a, ll b) {
		return a/b - ((a^b)<0 && a%b);
	}
	// intersects x with next line y; returns true if y is made obsolete
	bool isect(iterator x, iterator y) {
		if (y == end()) { 
			x->p = inf; 
			return false; 
		}
		if (x->k == y->k) 
			x->p = x->m > y->m ? inf : -inf;
		else 
			x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k,m,0}), y = z++, x = y;
		while (isect(y,z))          z = erase(z);
		if (x!=begin() && isect(--x,y))
			isect(x, y = erase(y));
		while ((y = x)!=begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	// returns max(k*x + m)
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k*x + l.m;
	}
};

// ——— Problem setup ———
struct Rect {
	ll x, y, a;
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<Rect> R(n);
	for(int i = 0; i < n; i++){
		cin >> R[i].x >> R[i].y >> R[i].a;
	}
	// sort by x ascending
	sort(R.begin(), R.end(), [&](auto &A, auto &B){
		return A.x < B.x;
	});

	vector<ll> dp(n);
	LineContainer cht;
    ll ans = 0;
    cht.add(0,0); 
	for(int i = 0; i < n; i++){
		// best = max_j ( dp[j] - x_j * y_i )
		ll best = cht.query(R[i].y);

		dp[i] = R[i].x * R[i].y - R[i].a + best;
		ans   = max(ans, dp[i]);

		// insert fᵢ(y) = dp[i] - x_i*y  =>  k = -x_i, m = dp[i]
		cht.add(-R[i].x, dp[i]);
	}

	cout << ans << "\n";
	return 0;
}
