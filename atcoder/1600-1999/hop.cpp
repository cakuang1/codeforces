#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) { cin >> a[i]; }

	int x = (int)sqrt(n);
	vector<int> dp(n, 1);
	vector<vector<int>> s(x + 1, vector<int>(x + 1));
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] > x) {
			for (int j = i + a[i]; j < n; j += a[i]) {
				dp[i] += dp[j];
				dp[i] %= MOD;
			}
		} else {
			dp[i] += s[a[i]][i % a[i]];
			dp[i] %= MOD;
		}
		for (int j = 1; j <= x; j++) {
			s[j][i % j] += dp[i];
			s[j][i % j] %= MOD;
		}
	}

	cout << dp[0] << endl;
}