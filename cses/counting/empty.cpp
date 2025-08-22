#include <bits/stdc++.h>
using namespace std;

#define N 500
#define MOD 1000000007

int add(int a, int b) {
	if ((a += b) >= MOD) a -= MOD;
	return a;
}

int mul(int a, int b) { return int(1LL * a * b % MOD); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, i, j, k;
	static int dp[N + 1][N + 1], choose[N / 2 + 1][N / 2 + 1];
	static string s;

	cin >> s;
	n = (int)s.size();

	choose[0][0] = 1;
	for (i = 1; i <= n / 2; ++i) {
		choose[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			choose[i][j] = add(choose[i - 1][j], choose[i - 1][j - 1]);
	}

	for (i = 0; i + 1 <= n; ++i) dp[i + 1][i] = 1;
	for (i = n - 1; i >= 0; --i)
		for (j = i + 1; j < n; j += 2) {
			for (k = i + 1; k <= j; k += 2)
				if (s[i] == s[k]) {
					int temp = mul(dp[i + 1][k - 1], dp[k + 1][j]);
					temp = mul(temp, choose[(j - i + 1) / 2][(k - i + 1) / 2]);
					dp[i][j] = add(dp[i][j], temp);
				}
		}
	cout << dp[0][n - 1] << '\n';
}


// lead to k inversions r