#include <bits/stdc++.h>
 
using namespace std;
 
const int MOD = 998244353;
 
int add(int x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
  if (x < 0) x += MOD;
  return x;
}
 
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> p(n), d(n);
    vector<vector<int>> vs(n);
    for (int v = 1; v < n; ++v) {
      cin >> p[v];
      --p[v];
      d[v] = d[p[v]] + 1;
      vs[d[v]].push_back(v);
    }
    vector<int> dp(n), tot(n);
    dp[0] = tot[0] = 1;
    for (int i = 1; i < n; ++i) {
      for (int v : vs[i]) {
        dp[v] = add(tot[d[v] - 1], d[v] == 1 ? 0 : -dp[p[v]]);
        tot[d[v]] = add(tot[d[v]], dp[v]);
      }
    }
    int ans = 0;
    for (int v = 0; v < n; ++v) {
      ans = add(ans, dp[v]);
    }
    cout << ans << '\n';
  }
}