#pragma GCC optimize("O2,Ofast,inline,unroll-all-loops,-ffast-math")
#pragma GCC target("popcnt")
#include <bits/stdc++.h>
#define maxn 2010
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define pii pair<int, int>
#define pil pair<int, ll>
#define pll pair<ll, ll>
#define IL inline
#define ss system
using namespace std;

int up[maxn][maxn], down[maxn][maxn], lef[maxn][maxn], rig[maxn][maxn], n, m;
char s[maxn][maxn];
template <class T> void read(T &x) {
  char ch = x = 0;
  bool fl = false;
  while (!isdigit(ch))
    fl |= ch == '-', ch = getchar();
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getchar();
  x = fl ? -x : x;
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> s[i] + 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      up[i][j] = (up[i - 1][j] + 1) * (s[i][j] == '.');
      lef[i][j] = (lef[i][j - 1] + 1) * (s[i][j] == '.');
    }
  }
  for (int i = n; i; i--) {
    for (int j = m; j; j--) {
      down[i][j] = (down[i + 1][j] + 1) * (s[i][j] == '.');
      rig[i][j] = (rig[i][j + 1] + 1) * (s[i][j] == '.');
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans = max(ans, up[i][j] + down[i][j] + lef[i][j] + rig[i][j] - 3);
    }
  }
  cout << ans << endl;
  return 0;
}