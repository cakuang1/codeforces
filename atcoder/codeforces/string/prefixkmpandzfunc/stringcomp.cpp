#include <bits/stdc++.h>

void build_kmp(std::string::const_iterator ist, std::string::const_iterator ied, std::vector<int>::iterator ost) {
  std::vector<int>::iterator oit = ost;
  int ind = *oit = -1;
  for (std::string::const_iterator it = ist; it != ied; ++it) {
    while (~ind && *it != ist[ind]) ind = ost[ind];
    *++oit = ++ind;
  }
}

int Dp(const std::string &s) {
  std::vector<int> dp(s.size() + 1, 0x3f3f3f3f);
  dp[0] = 0;
  std::vector<int> kmp(s.size() + 1);
  for (int i = 0; i < s.size(); ++i) {
    build_kmp(s.begin() + i, s.end(), kmp.begin() + i);
    for (int j = i + 1; j <= s.size(); ++j) {
      int plen = (j - i) % (j - i - kmp[j]) == 0 ? j - i - kmp[j] : j - i;
      std::function<int(int)> get_len = [&](int x) {
        for (int i = 0, j = 1; ; ++i, j *= 10) {
          if (x < j) return i;
        }
      };
      dp[j] = std::min(dp[j], dp[i] + plen + get_len((j - i) / plen));
    }
  }
  return dp[s.size()];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::string S;
  std::cin >> S;
  std::cout << Dp(S) << std::endl;
  return 0;
} 

// doeshwe rhis t rally rwrok weandwrwhow you weld wosut ewolvesi ht