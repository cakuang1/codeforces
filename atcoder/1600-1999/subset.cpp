#include<bits/stdc++.h>
#define mod 998244353

using namespace std;

int dp[5005]={0};

int main(){
  int q,k;
  cin >> q >> k;
  dp[0]=1;
  while(q>0){
    q--;
    string s;
    int x;
    cin >> s >> x;
    if(s=="+"){
      for(int i=k;i>=x;i--){
        dp[i]+=dp[i-x];
        dp[i]%=mod;
      }
    }
    else{
      for(int i=x;i<=k;i++){
        dp[i]+=(mod-dp[i-x]);
        dp[i]%=mod;
      }
    }
    cout << dp[k] << "\n";
  }
  return 0;
}
 



