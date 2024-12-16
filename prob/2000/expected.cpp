#include <bits/stdc++.h>
using namespace std;
int fast_exp(int b, int e, int mod){
	int ans = 1;
	while(e){
		if(e&1) ans = (1ll*ans*b) % mod;
		b = (1ll*b*b) % mod;
		e >>= 1;
	}
	return ans;
}
const int mod = 1e9+7;
const int bits = 11;
 
int inv(int n){
	return fast_exp(n,mod-2,mod);
}
 
const int inverse_1e4 = inv(10000);
int dp[bits][bits][2][2];
void transition(int a, int p){
	p = (1ll*p*inverse_1e4) % mod;
	int negp = (mod+1-p) % mod;
	int bin[bits];
	for(int i = 0; i < bits; i++){
		bin[i] = a&1;
		a >>= 1;
	}
	for(int i = 0; i < bits; i++){
		for(int j = 0; j < bits; j++){
			int temp[2][2];
 
			for(int k : {0,1}) for(int l : {0,1}) temp[k][l] = (1ll*dp[i][j][k][l]*negp + 1ll*dp[i][j][k^bin[i]][l^bin[j]]*p) % mod;
 
			for(int k : {0,1}) for(int l : {0,1}) dp[i][j][k][l] = temp[k][l];
		} 
	}
}
int main() {
    int t;
    cin >> t;
    while(t--){
    	int n;
    	cin >> n;
    	int a[n],p[n];
    	for(int i = 0; i < n; i++) cin >> a[i];
    	for(int i = 0; i < n; i++) cin >> p[i];
    	for(int i = 0; i < bits; i++) for(int j = 0; j < bits; j++) dp[i][j][0][0] = 1;
    	for(int i = 0; i < n; i++) transition(a[i],p[i]);
    	int ans = 0;
    	for(int i = 0; i < bits; i++){
    		for(int j = 0; j < bits; j++){
    			int pw2 = (1ll<<(i+j)) % mod;
    			ans += (1ll*pw2*dp[i][j][1][1]) % mod;
    			ans %= mod;
    			for(int k : {0,1}) for(int l : {0,1}) dp[i][j][k][l] = 0;
    		}
    	}
    	cout << ans << "\n";
    }
	return 0;
}