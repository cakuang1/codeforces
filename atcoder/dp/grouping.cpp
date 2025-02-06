#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
 
#define fi first
#define se second
#define mp make_pair
#define pb push_back
 
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<int> vi;
typedef unsigned long long ull;
typedef long double ld; 
typedef tree<ii, null_type, less<ii>, rb_tree_tag, tree_order_statistics_node_update> pbds;

ll a[18][18];
ll G[(1<<17)];
ll dp[(1<<17)];

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin>>n;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=0;i<(1<<n);i++)
	{
		G[i]=0;
		for(int j=0;j<n;j++)
		{
			for(int k=j+1;k<n;k++)
			{
				if(i&(1<<j))
				{
					if(i&(1<<k))
					{
						G[i]+=a[j][k];
					}
				}
			}
		}
	}
	dp[0]=0;
	for(int i=1;i<(1<<n);i++)
	{
		dp[i]=-ll(1e18);
		for(int j=i;;j=(j-1)&i)
		{
			dp[i]=max(dp[i],G[j]+dp[i^j]);
			if(j==0) break;
		}
	}
	cout<<dp[(1<<n)-1]<<'\n';
}

