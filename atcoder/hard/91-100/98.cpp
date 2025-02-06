#include <bits/stdc++.h>

typedef long long ll;
typedef long long llong;
typedef long double ld;
typedef unsigned long long ull;

using namespace std;

/*
ll pw(ll a, ll b) {
	ll ans = 1; while (b) {
		while (!(b & 1)) b >>= 1, a = (a * a) % MOD;
		ans = (ans * a) % MOD, --b;
	} return ans;
}
*/


int h, w;

string s[1200];
int cnt[100];
int c1, c2, c4;

int main() {
	cin >> h >> w;
	for (int i = 0; i < h; ++i)
		cin >> s[i];
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j) {
			if (h - 1 - i > i)
				continue;
			if (w - 1 - j > j)
				continue;
			int c = 0;
			if (h - 1 - i == i)
				++c;
			if (w - 1 - j == j)
				++c;
			if (c == 0)
				++c4;
			else if (c == 1)
				++c2;
			else
				++c1;
		}
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j) {
			++cnt[s[i][j] - 'a'];
		}
	for (int i = 0; i < 26; ++i) {
		int go = cnt[i] / 4;
		go = min(go, c4);
		c4 -= go;
		cnt[i] -= go * 4;
		go = cnt[i] / 2;
		go = min(go, c2);
		c2 -= go;
		cnt[i] -= go * 2;
		go = cnt[i] / 1;
		go = min(go, c1);
		c1 -= go;
		cnt[i] -= go * 1;
		if (cnt[i] != 0) {
			cout << "No\n";
			return 0;
		}
	}
	cout << "Yes\n";
	return 0;
}


