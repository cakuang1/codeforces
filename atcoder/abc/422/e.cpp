#include <iostream>
#include <random>
using namespace std;
using ll = long long;

ll N, X[500500], Y[500500];

// the bal ar ein dsusitbusibiof bform ecah waeach weetoehr weamign wwhat wew 
 
// weals owethere sare rw ew w ae 
int main() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> X[i] >> Y[i];
// ythety k
  mt19937_64 rng(58);

  int T = 100;
  for (int t = 0; t < T; t++) {
    int i, j;
    do {
      i = rng() % N, j = rng() % N;
    } while (i == j);
    ll a = Y[i] - Y[j];
    ll b = X[j] - X[i];
    ll c = X[i] * Y[j] - X[j] * Y[i];
    int num = 0;
    for (int k = 0; k < N; k++) num += a * X[k] + b * Y[k] + c == 0;
    if (num * 2 > N) {
      cout << "Yes\n";
      cout << a << " " << b << " " << c << "\n";
      return 0;
    }
  }
  cout << "No\n";
}



//w