#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll,ll>
#define rep(i, n) for(int i = 0; i < n; ++i)
#define N (int)1000
#define M (int)5e+4
#define INF (ll)1e+18


int main(void){
	int n,m,l,r;
	int p[N];
	ll v[N];
	ll dp[N+1][M+1]={};
	ll dp2[N+1][M+1]={};
	ll tgt;
	string ans="";

	cin >> n >> m;
	for(int i=0;i<n;i++)cin >> p[i] >> v[i];

	for(int i=0;i<n;i++){
		for(int j=0;j<=m;j++){
			if(j<p[i])dp[i+1][j]=dp[i][j];
			if(j>=p[i])dp[i+1][j]=max(dp[i][j],dp[i][j-p[i]]+v[i]);
		}
	}

	for(int i=n-1;i>=0;i--){
		for(int j=0;j<=m;j++){
			if(j<p[i])dp2[i][j]=dp2[i+1][j];
			if(j>=p[i])dp2[i][j]=max(dp2[i+1][j],dp2[i+1][j-p[i]]+v[i]);
		}
	}

	tgt=dp[n][m];
	for(int i=0;i<n;i++){
		long long mx_woi=0;
		for(int j=0;j<=m;j++)mx_woi=max(mx_woi,dp[i][j]+dp2[i+1][m-j]);
		long long mx_wi=0;
		for(int j=0;j<=m-p[i];j++)mx_wi=max(mx_wi,dp[i][j]+dp2[i+1][m-p[i]-j]);
		if(mx_woi<tgt)ans+='A';
		else if(mx_wi<tgt-v[i])ans+='C';
		else ans+='B';
	}

	cout<<ans<<endl;

	return 0;
}
