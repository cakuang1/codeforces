#include <iostream>
#include <iomanip>
#include <string.h>
#include <vector>
using namespace std;
vector<int> v[100005];
int arr[100005][25];
long long dp[100005][25][2],ans[25];
void dfs(int node,int pnode)
{
	long long s[25][2];
	memset(s,0,sizeof(s));
	for (int i=0;i<25;i++)
	dp[node][i][arr[node][i]]=1;
	for (int i=0;i<v[node].size();i++)
	{
		if (v[node][i]!=pnode)
		{
			dfs(v[node][i],node);
			for (int j=0;j<25;j++)
			{
				for (int x=0;x<2;x++)
				{
					dp[node][j][x]+=dp[v[node][i]][j][x^arr[node][j]];
					s[j][x]+=dp[v[node][i]][j][x];
				}
			}
		}
	}
	for (int j=0;j<25;j++)
	{
		long long x0=0,x1=0;
		for (int i=0;i<v[node].size();i++)
		{
			if (v[node][i]!=pnode)
			{
				x0+=(s[j][1]-dp[v[node][i]][j][1])*dp[v[node][i]][j][1]+(s[j][0]-dp[v[node][i]][j][0])*dp[v[node][i]][j][0];
				x1+=(s[j][1]-dp[v[node][i]][j][1])*dp[v[node][i]][j][0]+(s[j][0]-dp[v[node][i]][j][0])*dp[v[node][i]][j][1];
			}
		}
		if (arr[node][j])
		ans[j]+=x0/2;
		else
		ans[j]+=x1/2;
	}
	for (int j=0;j<25;j++)
	ans[j]+=dp[node][j][1];
}
int main()
{
	int n;
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		int a;
		cin >> a;
		for (int x=0;x<25;x++)
		arr[i][x]=(bool)(a&(1<<x));
	}
	for (int i=1;i<n;i++)
	{
		int a,b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	dfs(1,0);
	long long res=0;
	for (int i=0;i<25;i++)
    res+=(ans[i]*(1LL<<i));
	cout<< res << endl;
}