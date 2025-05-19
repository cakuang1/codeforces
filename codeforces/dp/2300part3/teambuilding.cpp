#include <bits/stdc++.h>
using namespace std;
#define ll long long int
const ll M=1e5+5;
ll dp[M][(1<<7)+1],skill[M][7];
ll ind[M],a[M];
bool cmp(ll p,ll q)
{
	return a[p]>a[q];
}
int main()
{
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll n,p,k;
	cin>>n>>p>>k;
	memset(dp,-1,sizeof(dp));
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<=n;i++)
		for(ll j=0;j<p;j++)
			cin>>skill[i][j];
	for(ll i=1;i<=n;i++)
		ind[i]=i;
	sort(ind+1,ind+n+1,cmp);	
	dp[0][0]=0;
	for(ll i=1;i<=n;i++)
	{
		ll x=ind[i];
		for(ll mask=0;mask<(1<<p);mask++)
		{
			ll ct=0;
			for(ll j=0;j<p;j++)
				if((mask&(1<<j)))
					ct++;
			ll z=(i-1)-ct;
			if(z<k)
			{
				if(dp[i-1][mask]!=-1)
					dp[i][mask]=dp[i-1][mask]+a[x];
			}
			else
			{
				if(dp[i-1][mask]!=-1)
					dp[i][mask]=dp[i-1][mask];
			}
			for(ll j=0;j<p;j++)
			{
				if((mask&(1<<j)) && dp[i-1][(mask^(1<<j))]!=-1)
				{
					ll z=dp[i-1][(mask^(1<<j))]+skill[x][j];
					if(z>dp[i][mask])
						dp[i][mask]=z;
				}
			}
		}
	}
	cout<<dp[n][(1<<p)-1]<<"\n";
	return 0;
} 