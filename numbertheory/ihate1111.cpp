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

    vector<int> l = {1 , 11, 111 , 1111 , 11111, 111111, 1111111, 11111111, 111111111};
    bool dp[inf + 1]; 
    dp[0] = true;
    void preprocess() {
        for (int i = 1 ;i <= inf ; i ++) {
            

            for (int k : l) {
                if ((i - k) < 0) {
                    break;
                }
                
                dp[i] = dp[i] || dp[i - k]; 
            }

            
        }
    }

  int main() {
      ios::sync_with_stdio(false);
      cin.tie(NULL);
      ll t; 
      cin >> t; 
      preprocess();

      while (t --) {
        int n ;
        cin >> n;
        if (dp[n]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
      }
        // somebody here stinks 

      // duplciated w  

      return 0;

            
  }