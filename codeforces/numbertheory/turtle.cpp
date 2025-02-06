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
      ll t; 
      cin >> t; 
    
    
     
    while (t --) {
        int n ;
        cin >> n;
        vector<int> s(n);
        int sum = 0;
        bool flag = false;
        for (int i = 0 ; i < n ; i++) {
            int curr;
            cin >> curr; 
            sum += curr; 
            
            if ((curr % 3) == 1) {
                flag = true;
            }
        }    
        
        int resi = sum % 3;
        if (resi == 0) {
            cout << 0 << endl; 
        } else if (resi == 2 || flag) {
            cout << 1 << endl;
        } else {
            cout << 2 << endl;
        }



        
    }

      return 0;

            
  }