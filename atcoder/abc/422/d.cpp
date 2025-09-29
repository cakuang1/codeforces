#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;
  vector<int> ans{K};
  for (int n = 0; n < N; n++) {
    vector<int> nxt;
    for (int a : ans) {
      nxt.push_back(a / 2);
      nxt.push_back(a - a / 2);
    }
    ans = nxt;
  }
  int max = *max_element(begin(ans), end(ans));
  int min = *min_element(begin(ans), end(ans));
  cout << max - min << "\n";
  for (int i = 0; i < (int)ans.size(); i++) {
    cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
  }
}

// randomaizd algorithwt mw are what w