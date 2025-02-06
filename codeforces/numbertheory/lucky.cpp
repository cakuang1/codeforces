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
     vector<int> lucky; 




void dfs() {
     stack<int> st =  {4,7};

     for (!st.empty()){
        int top = st.top();
        lucky.push_back(top );
        st.pop(top);

        if ((top * 10 + 4) <= 500) {
            st.push((top * 10 + 4));
        }
        if ((top * 10 + 7) <= 500) {
            st.push((top * 10 + 7));
        }
                     
     } 

     
}

// find all numbers divisble by 4 and 7 


  int main() {
      ios::sync_with_stdio(false);
      cin.tie(NULL);
      int  t; 
      cin >> t; 
     // enumberat all lucky numbers 
        dfs();
      for (int l : lucky) {
        if ((t/l) == 0) {
            cout << "YES" <<  endl;
            return 0;
        }
      }

      cout << "NO" << endl;

      

      return 0;

            
  }