#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define sz(a) int(a.size())
#define all(a) a.begin(), a.end()
#define forn(i, n) for(int i = 0; i < int(n); i++) 
#define fore(i, l, r) for(int i = int(l); i < int(r); i++)

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template <class A, class B> ostream& operator << (ostream& out, const pair<A, B> &a) {
	return out << "(" << a.x << ", " << a.y << ")";
}

template <class A> ostream& operator << (ostream& out, const vector<A> &v) {
	out << "[";
	forn(i, sz(v)) {
		if(i) out << ", ";
		out << v[i];
	}
	return out << "]";
}

mt19937 rnd(time(NULL));

const int INF = int(1e9);
const li INF64 = li(1e18);
const int MOD = INF + 7;
const ld EPS = 1e-9;
const ld PI = acos(-1.0);

const int N = 200 * 1000 + 13;

int n;
int a[N];
vector<int> g[N];

bool read () {
	if (scanf("%d", &n) != 1)
		return false;
	forn(i, n)
		g[i].clear();
	forn(i, n)
		scanf("%d", &a[i]);
	forn(i, n - 1){
		int x, y;
		scanf("%d%d", &x, &y);
		--x, --y;
		g[x].pb(y);
		g[y].pb(x);
	}
	return true;
}

vector<pt> dp[N];
int ans;

void calc(int v, int p = -1){
	vector<pt> chd;
	for (auto u : g[v]) if (u != p){
		calc(u, v);
		for (auto it : dp[u])
			chd.pb(it);
	}
	
	sort(all(chd));
	forn(i, sz(chd)){
		int j = i - 1;
		int mx1 = 0, mx2 = 0;
		while (j + 1 < sz(chd) && chd[j + 1].x == chd[i].x){
			++j;
			if (chd[j].y >= mx1)
				mx2 = mx1, mx1 = chd[j].y;
			else if (chd[j].y > mx2)
				mx2 = chd[j].y;
		}
		if (a[v] % chd[i].x == 0){
			ans = max(ans, mx1 + mx2 + 1);
			dp[v].pb(mp(chd[i].x, mx1 + 1));
			while (a[v] % chd[i].x == 0)
				a[v] /= chd[i].x;
		}
		else{
			ans = max(ans, mx1);
		}
		i = j;
	}
	
	for (int i = 2; i * i <= a[v]; ++i) if (a[v] % i == 0){
		dp[v].pb(mp(i, 1));
		ans = max(ans, 1);
		while (a[v] % i == 0)
			a[v] /= i;
	}
	
	if (a[v] > 1){
		dp[v].pb(mp(a[v], 1));
		ans = max(ans, 1);
	}
}

void solve() {
	forn(i, N) dp[i].clear();
	ans = 0;
	calc(0);
	printf("%d\n", ans);
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	
	int tt = clock();
	
#endif
	
	cerr.precision(15);
	cout.precision(15);
	cerr << fixed;
	cout << fixed;

#ifdef _DEBUG
	while(read()) {	
#else
	if (read()){
#endif
		solve();
		
#ifdef _DEBUG
	cerr << "TIME = " << clock() - tt << endl;
	tt = clock();
#endif

	}
    }