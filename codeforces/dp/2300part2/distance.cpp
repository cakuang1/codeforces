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

int mul(int x, int y)
{
 	return (x * 1ll * y) % MOD;
}

int main()
{
	int n;
	cin >> n;
	int k;
	cin >> k;
	vector<vector<int>> dp(n + 1, vector<int>(k + 1));
	dp[0][0] = 1;
	vector<int> sum(k + 1);
	sum[0] = 1;

    
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= k; j++)
		{
			int& d = dp[i + 1][min(j + 1, k)];
		 	d = add(d, sum[j]);
		 	if(i >= 2 && i != n - 1)
		 		d = add(d, -dp[i - 1][j]); 
		}
		for(int j = 0; j <= k; j++)
			sum[j] = add(sum[j], dp[i + 1][j]);
	}
	cout << dp[n][k] << endl;
}





