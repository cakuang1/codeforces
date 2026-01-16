#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> c(N + 1);
  for (int x = 1; x * x <= N; x++) {
    for (int y = x + 1; x * x + y * y <= N; y++) {
      c[x * x + y * y]++;
    }
  }
  vector<int> ans;
  for (int n = 1; n <= N; n++) {
    if (c[n] == 1) ans.push_back(n);
  }
  cout << ans.size() << "\n";
  for (int i = 0; i < (int)ans.size(); i++) {
    cout << ans[i] << " \n]"[i + 1 == (int)ans.size()];
  }
}
