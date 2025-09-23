#include<bits/stdc++.h>
using namespace std;

#define fore(i, l, r) for(int i = int(l); i < int(r); i++)

#define sz(a) int((a).size())
#define all(a) (a).begin(), (a).end()

#define mp make_pair
#define pb push_back

#define x first
#define y second

typedef long long li;
typedef pair<int, int> pt;

const int INF = int(1e9);
const int N = 411;

int n, m;
int a[N];
vector< pair<pt, pt> > qs;

inline bool read() {
	if(!(cin >> n >> m))
		return false;
	fore(i, 0, n)
		cin >> a[i];
	qs.resize(m);
	fore(i, 0, m) {
		cin >> qs[i].x.x >> qs[i].x.y >> qs[i].y.x >> qs[i].y.y;
		qs[i].x.x--; qs[i].x.y--;
	}
	return true;
}

vector<int> ids[N];
int d[N][N];

inline void solve() {
	fore(i, 0, m)
		ids[qs[i].x.x].push_back(i);
	li ans = -1;
	
	fore(l, 0, n) {
		fore(r, l, n)
			d[0][r] = a[r] - a[l];
		
		fore(k, 1, n + 1) {
			int opt = l;
			fore(r, l, n) {
				while(opt < r && max(d[k - 1][opt], a[r] - a[opt]) >= max(d[k - 1][opt + 1], a[r] - a[opt + 1]))
					opt++;
				
				d[k][r] = max(d[k - 1][opt], a[r] - a[opt]);
			}
		}
		
		for(int id : ids[l])
			ans = max(ans, d[qs[id].y.y][qs[id].x.y] * 1ll * qs[id].y.x);
	}
	
	cout << ans << endl;
}

// 
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	int tt = clock();
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(15);
	
	if(read()) {
		solve();
		
#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
#endif
	}
	return 0;
}