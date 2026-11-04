#include<bits/stdc++.h>

using namespace std;

long long dp[300005][2];

int main(){
  long long n;
  cin >> n;
  vector<long long> x(n),y(n);
  for(long long i=0;i<n;i++){
    cin >> x[i] >> y[i];
  }

  for(long long i=0;i<=n;i++){
    dp[i][0]=-4e18;
    dp[i][1]=-4e18;
  }
  dp[0][0]=0;

  for(long long i=0;i<n;i++){
    if(x[i]==0){
      dp[i+1][0]=max(dp[i][0],max(dp[i][0],dp[i][1])+y[i]);
    }
    else{
      dp[i+1][1]=max(dp[i][1],dp[i][0]+y[i]);
    }

    dp[i+1][0]=max(dp[i+1][0],dp[i][0]);
    dp[i+1][1]=max(dp[i+1][1],dp[i][1]);
  }
  cout << max(dp[n][0],dp[n][1]) << "\n";
  return 0;
}
