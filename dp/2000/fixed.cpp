#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 6000;

int dp[MAX_N][MAX_N];
int a[MAX_N];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, k;
		cin >> n >> k;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= i; j++)
				dp[i][j] = 0;
		for(int i = 0; i < n; i++)
			for (int j = 0; j <= i; j++)
			{
				dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
				dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + ((a[i + 1] == j + 1) ? 1 : 0));
			}
		int ans = -1;
		for(int i = n; i >= 0; i--)
			if (dp[n][i] >= k)
			{
				ans = n - i;
				break;
			}
		cout << ans << '\n';
	}
	return 0;
}


// how wto se tshi wew e we 