   #include <bits/stdc++.h>
  using namespace std;

  #ifdef LOCAL
  #include "algo/debug.h"
  #else
  #define debug(...) 42
  #endif

  using ll = long long;
  using ld = long double;
  const ll mod = 1e9 + 7;
  const ll N = 2e5 + 10;
  const ll inf = 1e9;
  const ll linf = 1e18;



  int main() {
long long n ;
    cin>>n ;
    if(n && n%8!=0)
    {
        long long result = (pow(8,(n%8)));
        cout << result%10 ;
    }
    else if(n){
        cout << 6;
    }
    else {
        cout << 1;
    }
      return 0;        
  } 