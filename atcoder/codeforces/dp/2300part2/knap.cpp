#include <bits/stdc++.h>

using namespace std;

const int N = 9;
const int L = 840;

typedef long long li;

li dp[N][L * N];
li W;
li cnt[N];

int main()
{
	cin >> W;
	for(int i = 0; i < 8; i++)
		cin >> cnt[i];
	for(int i = 0; i < N; i++) for(int j = 0; j < L * N; j++) dp[i][j] = -1;
	dp[0][0] = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < L * N; j++)
		{
			if(dp[i][j] == -1) continue;
			int b = L / (i + 1);
			if(cnt[i] < b)
				b = cnt[i];
			for(int k = 0; k <= b; k++)
			{
				li& d = dp[i + 1][j + k * (i + 1)];
				d = max(d, dp[i][j] + (cnt[i] - k) / (L / (i + 1)));
			}
		}
	}
	li ans = 0;
	for(int j = 0; j < L * N; j++)
	{
		if(j > W || dp[8][j] == -1)
			continue;
		ans = max(ans, j + L * (min(dp[8][j], (W - j) / L)));
	}
	cout << ans << endl;
}


    
