#include<bits/stdc++.h>
 
using namespace std;
 
const int MOD = 998244353;
 
int add(int x, int y)
{
	x += y;
	while(x >= MOD) x -= MOD;
	while(x < 0) x += MOD;
	return x;
}
 
int sub(int x, int y)
{
	return add(x, -y);
}
 
int mul(int x, int y)
{
	return (x * 1ll * y) % MOD;
}
 
int binpow(int x, int y)
{
	int z = 1;
	while(y > 0)
	{
		if(y & 1) z = mul(z, x);
		x = mul(x, x);
		y /= 2;
	}
	return z;
}
 
int main()
{
	int n, k;
	cin >> n >> k;
	int ans = 0;
	vector<vector<int>> dp(n + 1, vector<int>(k, 0));
	dp[0][0] = 1;
	for(int i = 0; i < n; i++)
	{
		int cur = 0;
		for(int j = k - 1; j >= 1; j--)
		{
			cur = add(cur, dp[i][j]);
			dp[i + 1][j] = cur;
		}
		for(int j = k - 1; j >= 0; j--)
		{
			int nxt = (j + 1) % k;
			dp[i + 1][nxt] = add(dp[i + 1][nxt], mul(dp[i][j], k - j));
		}
		ans = add(ans, mul(dp[i + 1][0], binpow(k, n - (i + 1))));
	}
	cout << ans << endl;
}


