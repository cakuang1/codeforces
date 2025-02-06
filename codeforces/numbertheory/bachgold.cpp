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
        // somebody here stinks 
        int count = n/2;
        
        cout << count << endl;
        for (int i = 0 ; i < count - 1 ; i ++) {
            cout << 2 << " "; 
        }

        if (n % 2 == 1) {
            cout << 3 << " "; 
        } else {
            cout << 2 << " "; 
        }
      // duplciated w  

      return 0;

            
  }