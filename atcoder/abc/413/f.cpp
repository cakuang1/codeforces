#include <stdio.h>
#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define Inf32 1000000005
#define Inf64 4000000000000000001LL

int main(){
	int n,c;
	cin>>n>>c;
	
	vector<int> a(n);
	rep(i,n)cin>>a[i];
	c--;
	a[c]++;
	vector<int> memo(3005,0);
	long long sum = 0;
	rep(i,n){
		sum += a[i];
		memo[a[i]]++;
	}
	long long csum = sum;
	vector<mint> dp(3005,0);
	for(int i=3004;i>=1;i--){
		if(memo[i]==0)continue;
		//keep
		{
			mint si = i-1 + sum - csum;
			mint bo = sum - 1;
			dp[i] = bo / si;
		}
		//increase
		mint bo = sum - csum;
		bo += i-1;
		bo = bo.inv();
		for(int j=i+1;j<=3004;j++){
			dp[i] +=dp[j] * bo * (j*memo[j]);
		}
		csum -= memo[i] * i;
	}
	cout<<dp[a[c]].val()<<endl;
	return 0;} 
    // w wesdt seh sers i thsi isexists wer
    // 1