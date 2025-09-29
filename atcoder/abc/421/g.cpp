#include <iostream>
#include <vector>
using namespace std;

#include "atcoder/convolution.hpp"
#include "atcoder/modint.hpp"
using mint = atcoder::modint998244353;

int main() {
  int N, A, B, C;
  cin >> N >> A >> B >> C;
  vector<mint> fac(N + 1), invfac(N + 1);
  fac[0] = 1;
  for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i;
  invfac[N] = fac[N].inv();
  for (int i = N; i >= 1; i--) invfac[i - 1] = invfac[i] * i;

  {
    vector<mint> F1(N + 1), F2(N + 1), F3(N + 1);
    for (int i = 0; i <= N; i++) {
      if (i % A == 0) F1[i] = 1;
      if (i % B == 0) F2[i] = 1;
      if (i % C == 0) F3[i] = 1;
    }
    auto mid = atcoder::convolution(F1, F2);
    auto F = atcoder::convolution(mid, F3);
    cout << F[N].val() << "\n";
  }

  {
    vector<mint> G1(N + 1), G2(N + 1), G3(N + 1);
    for (int i = 0; i <= N; i++) {
      if (i % A == 0) G1[i] = invfac[i];
      if (i % B == 0) G2[i] = invfac[i];
      if (i % C == 0) G3[i] = invfac[i];
    }
    auto mid = atcoder::convolution(G1, G2);
    auto G = atcoder::convolution(mid, G3);
    cout << (G[N] * fac[N]).val() << "\n";
  }
}


// wedfein wd pwer