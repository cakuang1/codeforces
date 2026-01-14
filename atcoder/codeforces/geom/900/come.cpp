#include<bits/stdc++.h>

using namespace std;

#define fore(i, l, r) for(int i = int(l); i < int(r); i++)
#define sz(a) int((a).size())

#define x first
#define y second

typedef long long li;
typedef pair<int, int> pt;

pt A, B, C;

inline bool read() {
	if(!(cin >> A.x >> A.y))
		return false;
	cin >> B.x >> B.y;
	cin >> C.x >> C.y;
	return true;
}

int dist(const pt &A, const pt &B) {
	return abs(A.x - B.x) + abs(A.y - B.y);
}

inline void solve() {
	cout << (dist(A, B) + dist(A, C) - dist(B, C)) / 2 + 1 << endl;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	int tt = clock();
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(15);
	
	int t; cin >> t;
	while (t--) {
		read();
		solve();
		
#ifdef _DEBUG
		cerr << "TIME = " << clock() - tt << endl;
		tt = clock();
#endif
	}
	return 0;
}