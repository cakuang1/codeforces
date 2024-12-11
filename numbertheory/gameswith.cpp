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
      ll n; 
      cin >> n;

        while (n --) {
            int c ;
            cin >> c; 
            
             // both players play optimally 
             if ((c + 1) % 3 == 0 || (c - 1 )% 3 == 0) {
                cout << "First" << endl ;
             } else {
                cout << "Second" << endl; 
             }
        } 
        // somebody here stinks 

      // duplciated w  

      return 0;

            
  }