#include <iostream>
#include <vector>
#include <climits>
#include <set>
using namespace std;
 
#define ll long long
 
vector<int> z_function(string s) {
  int n = s.size();
  vector<int> z(n);
  int l = 0, r = 0;
  for(int i = 1; i < n; ++i) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}
 
void solve() {
  int n; // cin >> n;
  string s; cin >> s;
  n = s.length();
  vector<int> nona(n, n);
  for (int i = n - 1; i >= 0; --i) {
    if (s[i] != 'a') nona[i] = i;
    else if (i + 1 < n) nona[i] = nona[i + 1];
  }
  if (nona[0] == n) {
    cout << n - 1 << '\n';
    return;
  }
  string s2 = "";
  int i1 = nona[0];
  for (int i = i1; i < n; ++i) s2 += s[i];
  vector<int> z = z_function(s2);
  ll ans = 0;
  for (int len = 1; i1 + len <= n; ++len) {
    int cur = i1 + len;
    int mn = i1;
    bool works = true;
    while (cur < n) {
      if (nona[cur] == n) break;
      int bt = nona[cur] - cur;
      mn = min(mn, bt);
      cur += bt;
      if (z[cur - i1] < len) {
        works = false;
        break;
      }
      cur += len;
    }
    if (works) ans += mn + 1;
  }
  cout << ans << '\n';
}
 
int main() {
  int t; cin >> t;
  for (int i = 0; i < t; ++i) solve();
  return 0;
}