#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)
const ll INF = 1000000000000000010;
template<class T, class U> inline bool chmax(T& a, const U& b) { if (a < b) { a = b; return true; } return false; }

int main() {
	ll n;
	cin >> n;
	vector<ll> a(n), b(n), c(n);
	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];
	rep(i, n) cin >> c[i];
	vector<array<ll, 4>> dp(n + 1);
	rep(i, n + 1) rep(j, 4) dp[i][j] = -INF;
	dp[0][0] = 0;
	rep(i, n) {
		for (int j = 0; j <= 1; j++) chmax(dp[i + 1][1], dp[i][j] + a[i]);
		for (int j = 1; j <= 2; j++) chmax(dp[i + 1][2], dp[i][j] + b[i]);
		for (int j = 2; j <= 3; j++) chmax(dp[i + 1][3], dp[i][j] + c[i]);
	}
	cout << dp[n][3] << '\n';
}
