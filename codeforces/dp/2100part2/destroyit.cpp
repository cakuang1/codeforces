#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long li;

const li INF64 = li(1e18);

const int N = 200043;
vector<int> cards[N][4];
li dp[N][10];
int n;
li dp2[4][2];

int main()
{
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	for(int i = 0; i < N; i++)
		for(int j = 0; j < 10; j++)
			dp[i][j] = -INF64;
	dp[0][0] = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int k;
		scanf("%d", &k);
		for (int j = 0; j < k; j++)
		{
			int c, d;
			scanf("%d %d", &c, &d);
			cards[i][c].push_back(d);
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			int s = (j == 1 ? 3 : 1);
			sort(cards[i][j].begin(), cards[i][j].end());
			reverse(cards[i][j].begin(), cards[i][j].end());
			while (cards[i][j].size() > s)
				cards[i][j].pop_back();
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 2; k++)
				dp2[j][k] = -INF64;
		dp2[0][0] = 0;
		vector<pair<int, int> > cur;
		for (int j = 1; j <= 3; j++)
			for (auto x : cards[i][j])
				cur.push_back(make_pair(j, x));
		sort(cur.begin(), cur.end());
		do
		{
			int mana = 3;
			li score = 0;
			li mx = 0;
			int cnt = 0;
			for (auto x : cur)
			{
				cnt++;
				if (mana < x.first)
					break;
				mana -= x.first;
				mx = max(mx, li(x.second));
				score += x.second;
				dp2[cnt][0] = max(dp2[cnt][0], score);
				dp2[cnt][1] = max(dp2[cnt][1], score + mx);
			}
		} while (next_permutation(cur.begin(), cur.end()));
		for(int j = 0; j < 10; j++)
			for (int k = 0; k <= 3; k++)
			{
				int nxt = (j + k) % 10;
				int f = (j + k >= 10 ? 1 : 0);
				dp[i + 1][nxt] = max(dp[i + 1][nxt], dp[i][j] + dp2[k][f]);
			}
	}
	li ans = 0;
	for (int i = 0; i <= 9; i++)
		ans = max(ans, dp[n][i]);
	printf("%lld\n", ans);
	return 0;
}