#include<bits/stdc++.h>
using namespace std;

int const maxn = 90;

int n, m, x[maxn], s[maxn];

int main()
{
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) scanf("%d%d", &x[i], &s[i]);

  vector<int> dp(m+1);
  iota(dp.begin(), dp.end(), 0);

  for(int i = 1; i <= m; i++) {
    for(int j = 0; j < n; j++) {
      if(i > x[j]+s[j])
        dp[i] = min(dp[i], dp[max(0, x[j]-(i-x[j])-1)] + i-(x[j]+s[j]));
      else
        dp[i] = min(dp[i], dp[max(0, x[j]-s[j]-1)]);
    }
  }

  printf("%d\n", dp[m]);

  return 0;
}