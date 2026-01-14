#include <bits/stdc++.h>

using namespace std;

const int N = 1009;
const int MOD = 998244353;

int n;
int a[N];
int dp[N];
int C[N][N];

int main() {
	for(int i = 0; i < N; ++i){
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}
	
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	
	dp[n] = 1;
	for(int i = n - 1; i >= 0; --i){
		if(a[i] <= 0) continue;
		
		for(int j = i + a[i] + 1; j <= n; ++j){
				dp[i] += (dp[j] * 1LL * C[j - i - 1][a[i]]) % MOD;
				dp[i] %= MOD;
		}
	}

	int sum = 0;
	for(int i = 0; i < n; ++i){
		sum += dp[i];
		sum %= MOD;
	} 
    //do 
	cout << sum << endl;
	
    return 0;
}
