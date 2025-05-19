#include<cstdio>
#include<cstring>

using namespace std;

#define MAXN 5005

int dp[MAXN][MAXN], inf = 1000000000;

int main() {
	int n, a[MAXN];
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= n; j++) {
			dp[i][j] = inf;
		}
	}
	dp[0][0] = 0;
	
	for(int i = 1; i <= n; i++) {
		int k = -1, s = 0;
		for(int j = i; j <= n; j++) {
			s += a[j];
			while(k+1<=n && dp[i-1][k+1] <= s) {
				k++;
			}
			
			if(k>=0 && dp[j][k+1]>s) {
				dp[j][k+1]=s;
			}
		}
		
		for(int k = n-1; k >= 0; k--) {
			if(dp[i][k]>dp[i][k+1]) {
				dp[i][k]=dp[i][k+1];
			}
		}
	}
	
	int res = inf;
	for(int k = 1; k <= n; k++) {
		if(dp[n][k] < inf) {
			res = k;
		}
	}
	
	printf("%d\n", n-res);
} 