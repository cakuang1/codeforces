#include<bits/stdc++.h>
#define mod 998244353

using namespace std;

int main(){
  long long n,m;
  cin >> n >> m;
  vector<string> s(n);
  for(auto &nx : s){cin >> nx;}

  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if(s[i][j]=='#'){
        if(i!=(n-1)){s[i+1][j]='#';}
        if(i!=(n-1) && j!=(m-1)){s[i+1][j+1]='#';}
      }
    }
  }
  vector<long long> dp(m+1,0);
  dp[m]=1;
  for(int c=-m+1;c<=n-1;c++){
    for(int j=m-1;j>=0;j--){
      dp[j]+=dp[j+1];
      dp[j]%=mod;
    }
    for(int j=0;j<m;j++){
      int i=j+c;
      if(i<0){dp[j]=0;}
      else if(i>=n || s[i][j]=='#'){dp[j+1]=0;}
    }
  }
  long long res=0;
  for(auto &nx : dp){res+=nx;res%=mod;}
  cout << res << "\n";
  return 0;
}


// determine 