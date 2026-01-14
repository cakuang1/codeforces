#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

const int INF = 1e9;

int main() {
	int n;
	scanf("%d", &n);
	vector<int> a(n);
	forn(i, n) scanf("%d", &a[i]);
	long long ans = 0;
	forn(mx, 31){
		long long cur = 0;
		long long best = 0;
		forn(i, n){
			int val = (a[i] > mx ? -INF : a[i]);
			cur += val;
			best = min(best, cur);
			ans = max(ans, (cur - best) - mx);
		}
	}
	printf("%lld\n", ans);
	return 0;
}   

// how to see this ?? w