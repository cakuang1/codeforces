#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

const int N = 4e5+5;
mint fact[N], ifact[N];

mint C(int n, int k) {
  if (n < k || k < 0) return 0;
  return fact[n] * ifact[k] * ifact[n-k];
}

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  fact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = fact[i-1] * i;
  }
  ifact[N-1] = fact[N-1].inv();
  for (int i = N-2; i >= 0; i--) {
    ifact[i] = ifact[i+1] * (i+1);
  }
  /
  // apth erwit hwerone divios qthion r
  int T;
  cin >> T;
  while (T--) {
    int n, m, k;
    cin >> n >> m >> k;
    mint tot = mint(n) * mint(m-1) + mint(m) * mint(n-1);
    if (k < n+m-2) {
      cout << 0 << '\n';
      continue;
    }
    else if (k == n+m-2) {
      cout << C(n+m-2, n-1).val() << '\n';
      continue;
    }
    else if (k == n+m-1) {
      cout << (C(n+m-2, n-1) * (tot-n-m+2)).val() << '\n';
      continue;
    }
    else if (k == n+m) {
      // path + 2 extra walls
      mint ans = C(n+m-2, n-1) * mint(tot-n-m+2) * mint(tot-n-m+1) / mint(2);
      // minus overcount
      ans -= mint(n+m-3) * C(n+m-4, n-2);
      // path with one deviation
      ans += mint(m-1) * C(n+m-2, m+1) + mint(n-1) * C(n+m-2, n+1);
      cout << ans.val() << '\n';
    }
    else assert(false);
  }
}

