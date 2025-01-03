#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  map<int, int> cnt;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    cnt[x]++;
  }
  map<int, int> groupedByCnt;
  for (auto[x, y] : cnt) {
    groupedByCnt[y]++;
  }

  int res = n;
  int left = 0, right = n, rightCnt = (int) cnt.size();
  for (auto[x, y] : groupedByCnt) {
    res = min(res, left + right - rightCnt * x);
    left += x * y;
    right -= x * y;
    rightCnt -= y;
  }
  cout << res << endl;
}


// how to see thsi w
int main() { 
  int tests;
  cin >> tests;
  while (tests-- > 0) {
    solve();
  }
  return 0;
}