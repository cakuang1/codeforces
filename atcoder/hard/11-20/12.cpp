#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <queue>
#include <bitset>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef long double ld;
#define mp make_pair
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll MOD = 998244353;
ll mult(ll x, ll y) {
	return (x * y) % MOD;
}

const int N = 100100;
int a[N];

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int n;
	scanf("%d", &n);
	int x;
	scanf("%d", &x);
	if (x != 0) {
		printf("0\n");
		return 0;
	}
	a[0] = 1;
	for (int i = 1; i < n; i++) {
		scanf("%d", &x);
		a[x]++;
	}
	if (a[0] != 1) {
		printf("0\n");
		return 0;
	}
	while(a[n] == 0) n--;
	ll ans = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < a[i + 1]; j++)
			ans = mult(ans, a[i]);
	printf("%lld\n", ans);

	return 0;
}
