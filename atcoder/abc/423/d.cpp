#include <iostream>
using std::cin;
using std::cout;
#include <vector>
using std::vector;
using std::pair;
#include <queue>
using std::priority_queue;
using std::greater;
using std::max;

typedef long long int ll;
typedef pair<ll, ll> P;


ll n, k;
vector<ll> a, b, c;

void solve () {
	priority_queue<P, vector<P>, greater<P> > que;

	vector<ll> ans(n, -1);
	ll sum = 0;
	ll t = 0;
	for (ll i = 0; i < n; i++) {
		t = max(t, a[i]);
		while (sum + c[i] > k) {
			P q = que.top(); que.pop();
			t = max(t, q.first);
			sum -= q.second;
		}

		ans[i] = t;
		que.push({t + b[i], c[i]});
		sum += c[i];
	}

	for (ll i = 0; i < n; i++) {
		cout << ans[i] << "\n";
	}
}

int main (void) {
	cin >> n >> k;
	a.resize(n);
	b.resize(n);
	c.resize(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i] >> b[i] >> c[i];
	}

	solve();
	
	return 0;
}

// su mwew off subarary w we