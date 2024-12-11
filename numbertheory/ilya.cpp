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
      string t; 
      cin >> t; 
        

        if (t[0] == '-') {
            if (t.length() == 2) {
                cout << 0 << endl;
            } else {
                // remove the last digit 
                
                string removelast = t.substr(0, t.length() - 1)  ; 
                string removesecond = t.substr(0 ,t.length() - 2 ) + t.back(); 
                

                ll o1 = stoll(removelast);
                ll o2 = stoll(removesecond);

                cout << max(o1,o2) << endl;
            }
        } else {
            cout << t << endl; 
        }
        
        // somebody here stinks 

      // duplciated w  

      return 0;

            
  }