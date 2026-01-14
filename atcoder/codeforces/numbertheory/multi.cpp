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
      ios::sync_with_stdio(false);
      cin.tie(NULL);
      ll n,x ; 
      cin >> n >> x;
      int res = 0 ; 
      for (int i = 1 ; i <= n ; i ++) {
        if (((x % i) == 0 )&& ((x/i) <= n)) {
            res ++ ;
        }
      }

      cout << res << endl;



      return 0;

            
  }