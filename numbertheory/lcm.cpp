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
        int a , b;
        cin >> a >> b;
        if ((2 * a) > b) {
          cout << -1 << " " << -1 << endl;
        }  else {
          cout << a << " " << 2 * a << endl; 
        } 

    }

      return 0;

            
  }