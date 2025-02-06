#include <bits/stdc++.h>
using namespace std;

const int N = 1004;
const double eps = 1e-7;
double dp[N];
int ans[N];

int main(){
	int k, q, d = 1;
	cin >> k >> q;
	dp[0] = 1;
	for(int n = 1; d <= 1000; ++n){
		for(int x = k; x > 0; --x){
			dp[x] = (x * dp[x] + (k - x + 1) * dp[x - 1]) / k;
		}
		while(d <= 1000 && 2000 * dp[k] >= (d - eps)){
			ans[d] = n;
			d++;
		} 
		dp[0] = 0;
	}
	while(q--){
		int x;
		cin >> x;
		cout << ans[x] << "\n";
	}
}