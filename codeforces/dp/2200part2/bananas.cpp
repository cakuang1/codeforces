#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int inf = 1 << 30;
const int MOD = 1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int> A(n+1);
    for (int i=0; i<n; i++) cin >> A[i];
    vector<int> B(m);
    for (int i=0; i<m; i++) cin >> B[i];
    vector nxt(n, vector<int>(m));
    for (int k=0; k<m; k++) {
      int r = -1, sum = 0;
      for (int i=0; i<n; i++) {
        while (r < n && sum <= B[k]) sum += A[++r];
        nxt[i][k] = r;
        sum -= A[i];
      }
    }
    vector dp(n+1, vector<array<int,2>>(m, {inf, 0}));
    vector upd(n+1, vector(m, vector<array<int,3>>()));
    upd[0][0].push_back({0, 0, 1});
    upd[1][0].push_back({1, 0, 1});
    for (int k=0; k<m; k++) {
      map<int,array<int,2>> mp;
      for (int i=0; i<=n; i++) {
        for (auto [t, move, count] : upd[i][k]) {
          if (t == 0) {
            auto &[a, b] = mp[move];
            a += 1;
            (b += count) %= MOD;
          } else {
            auto &[a, b] = mp[move];
            a -= 1;
            (b += MOD - count) %= MOD;
            if (a == 0) mp.erase(move);
          }
        }
        if (mp.empty()) continue;
        auto &[move, info] = *mp.begin();
        dp[i][k] = {move, info[1]};
        if (i == n) continue;
        if (k < m-1) {
          upd[i][k+1].push_back({0, move, info[1]});
          upd[i+1][k+1].push_back({1, move, info[1]});
        }
        if (nxt[i][k] > i) {
          upd[i+1][k].push_back({0, move + (m - k - 1), info[1]});
          if (nxt[i][k] < n) {
            upd[nxt[i][k]+1][k].push_back({1, move + (m - k - 1), info[1]});
          }
        }
      }
    }
    map<int,int> mp;
    for (int k=0; k<m; k++) {
      auto &[move, count] = dp[n][k];
      (mp[move] += count) %= MOD;
    }
    auto &[move, count] = *mp.begin();
    if (move == inf) {
      cout << "-1\n";
    } else {
      cout << move << " " << count << "\n";
    }
  }

  return 0;
}