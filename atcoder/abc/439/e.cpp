#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int N;
  cin >> N;
  vector<pair<int, int>> AB(N);
  for (auto& [a, b] : AB) cin >> a >> b;
  sort(begin(AB), end(AB), [&](auto& l, auto& r) {
    if (l.first == r.first) return l.second > r.second;
    return l.first < r.first;
  });
  vector<int> dp;
  for (auto& [_, b] : AB) {
    int i = lower_bound(begin(dp), end(dp), b) - begin(dp);
    if (i == (int)dp.size()) {
      dp.push_back(b);
    } else {
      dp[i] = b;
    }
  }
  cout << dp.size() << "\n";
}

//wesursthsi ss sdtihis dowtiw worwk w
// R hwo woui