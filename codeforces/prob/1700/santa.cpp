#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define pb push_back
#define mp make_pair
#define sqr(a) ((a) * (a))
#define sz(a) int((a).size())
#define all(a) (a).begin(), (a).end()
#define forn(i, n) for (int i = 0; i < int(n); ++i)

const int MOD = 998244353;
const int N = 1e6 + 7;

int n;
vector<int> a[N];
int cnt[N];
int inv[N];

int add(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}

int mul(int a, int b) {
	return a * 1ll * b % MOD;
}

int binpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

int main() {
	scanf("%d", &n);
	forn(i, n) {
		int k;
		scanf("%d", &k);
		a[i].resize(k);
		forn(j, k) scanf("%d", &a[i][j]);
		forn(j, k) cnt[a[i][j]]++;
	}
	
	forn(i, N) inv[i] = binpow(i, MOD - 2);
	
	int ans = 0;
	forn(i, n) for (auto x : a[i])
		ans = add(ans, mul(mul(inv[n], inv[sz(a[i])]), mul(cnt[x], inv[n])));
			
	printf("%d\n", ans);
}