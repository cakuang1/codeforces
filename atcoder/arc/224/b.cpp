#include<bits/stdc++.h>

using namespace std;
using ll=long long;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while(t--){
    ll n;
    cin >> n;
    ll k=sqrt(n);
    while(k*k<n){k++;}
    while(k*k>=n){k--;}
    if(n<=k*(k+1)){
      cout << 2*n-(k+k+1) << "\n";
    }
    else{
      cout << 2*n-2*(k+1) << "\n";
    }
  }
  return 0;
}

