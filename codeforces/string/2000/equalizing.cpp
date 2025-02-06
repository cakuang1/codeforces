#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		int n;
		string s, t;
		cin >> n >> s >> t;
		vector<int> cnts(26), cntt(26);
		for (int j = 0; j < n; ++j) {
			++cnts[s[j] - 'a'];
			++cntt[t[j] - 'a'];
		}
		bool ok = true;
		bool good = false;
		for (int j = 0; j < 26; ++j) {
			ok &= cnts[j] == cntt[j];
			good |= cnts[j] > 1;
		}
		if (!ok) {
			cout << "NO" << endl;
			continue;
		}
		if (good) {
			cout << "YES" << endl;
			continue;
		}
		int invs = 0, invt = 0;
		for (int l = 0; l < n; ++l) {
			for (int r = 0; r < l; ++r) {
				invs += s[l] > s[r];
				invt += t[l] > t[r];
			}
		}
		ok &= (invs & 1) == (invt & 1);
		if (ok) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	
	return 0;
} 

