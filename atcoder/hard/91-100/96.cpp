#include <bits/stdc++.h>

using namespace std;

using int64 = long long;

int main() {
  int H, W, V[500][500];
  cin >> H >> W;
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      cin >> V[i][j];
    }
  }
  vector< tuple< int, int, int, int > > tt;
  for(int i = H - 1; i >= 0; i--) {
    if(i % 2 == 0) {
      for(int j = 0; j < W; j++) {
        if(V[i][j] % 2 == 1) {
          V[i][j]--;
          if(j + 1 == W) {
            if(i > 0) {
              tt.emplace_back(i, j, i - 1, j);
              V[i - 1][j]++;
            }
          } else {
            tt.emplace_back(i, j, i, j + 1);
            V[i][j + 1]++;
          }
        }
      }
    } else {
      for(int j = W - 1; j >= 0; j--) {
        if(V[i][j] % 2 == 1) {
          V[i][j]--;
          if(j == 0) {
            if(i > 0) {
              tt.emplace_back(i, j, i - 1, j);
              V[i - 1][j]++;
            }
          } else {
            tt.emplace_back(i, j, i, j - 1);
            V[i][j - 1]++;
          }
        }
      }
    }
  }
  cout << tt.size() << endl;
  for(auto &p : tt) {
    int a, b, c, d;
    tie(a, b, c, d) = p;
    cout << a + 1 << " " << b + 1 << " " << c + 1 << " " << d + 1 << endl;
  }
}