#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e4+7;
int dp[105][maxn]; // 前i个我选择j个，容量为k的时候，最多能装多少
int a[105],b[105],n,suma,sumb;
int main() {
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>a[i]>>b[i];
		suma+=a[i];
		sumb+=b[i];
	}
	for (int i=0;i<=n;i++) {
		for (int j=0;j<=10000;j++) {
			dp[i][j]=-1e9;
		}
	}
	dp[0][0]=0;
	for (int i=1;i<=n;i++) {
		for (int j=n;j>=1;j--) {
			for (int c=suma;c>=a[i];c--) {
				dp[j][c]=max(dp[j][c],dp[j-1][c-a[i]]+b[i]);
			}
		}
	}

	for (int j=1;j<=n;j++) {
		double ans = 0.0;
		for (int c=0;c<=suma;c++) {
			// dp[j][c]+(sumb-dp[j][c])/2
			ans = max(ans, min(1.0*dp[j][c]+sumb, 2.0*c));
		}
		printf("%.10f ", ans/2.0);
	}
}
