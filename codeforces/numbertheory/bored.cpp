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
      ll t,y; 
      cin >> t >> y; 


        ll mini = min(t,y);

        ll res = 1; 
        for (int i = mini ; i >= 1 ; i --) {
            res *= i;
        } 

        cout <<res << endl;
        // how to see this 

      return 0;

            
  }