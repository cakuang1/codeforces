#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const int MAXN = 3000;
static const int MAXK = 26;
static const int INF  = 10000;

int n, k;
// grid[i][j] in [0..k-1]
uint8_t grid[MAXN][MAXN];
// need[i][j] = minimal side so that square at (i,j) contains all letters
uint16_t need[MAXN][MAXN];

// fdp_next[L][j] is f_L[i+1][j], fdp_cur[L] is f_L[i][j+1], diag[L] is f_L[i+1][j+1]
uint16_t fdp_next[MAXK][MAXN+1];
uint16_t fdp_cur [MAXK];
uint16_t diag_row[MAXK];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  for(int i = 0; i < n; i++){
    static char buf[MAXN+1];
    cin >> buf;
    for(int j = 0; j < n; j++){
      grid[i][j] = buf[j] - 'A';
      need[i][j] = 1;   // at least side 1
    }
  }

  // Initialize fdp_next[*][j] = INF for row n and col n boundary
  for(int L = 0; L < k; L++){
    for(int j = 0; j <= n; j++){
      fdp_next[L][j] = INF;
    }
  }

  // Sweep from bottom row up
  for(int i = n - 1; i >= 0; i--){
    // For each letter, set the "right boundary" fdp_cur[L] = INF
    for(int L = 0; L < k; L++){
      fdp_cur[L] = INF;
      diag_row[L] = INF;  // f_L[i+1][n] before we start j loop
    }
    
    // sweep from lef f wto right and find the min whow ? werwe
    // Sweep each column j from right to left
    for(int j = n - 1; j >= 0; j--){
      uint16_t bestSide = 1;  // local max side = f + 1
         
      // For each letter L update its fdp at (i,j)
      for(int L = 0; L < k; L++){
        uint16_t dp;
        if(grid[i][j] == L){
          dp = 0;
        } else {
          // min of down (fdp_next[L][j]),
          //        right (fdp_cur[L]),
          //        diag (diag_row[L]):
          uint16_t m = fdp_next[L][j] < fdp_cur[L] ? fdp_next[L][j] : fdp_cur[L];
          if(diag_row[L] < m) m = diag_row[L];
          dp = m + 1;
        }
        // rotate the three states for next column:
        diag_row[L] = fdp_next[L][j];  // old down becomes next diag
        fdp_cur  [L] = dp;            // this row right boundary
        fdp_next [L][j] = dp;         // store for next iteration up

        // compute the required side = dp+1 and track max
        uint16_t side = dp + 1;
        if(side > bestSide) bestSide = side;
      }

      // only one write per cell:
      need[i][j] = bestSide;
    }
  }

  // Finally sum up all‑letter squares
  ll answer = 0;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      int maxS = n - max(i,j);
      int req  = need[i][j];
      if(req <= maxS){
        answer += (maxS - req + 1);
      }
    }
  }

  cout << answer << "\n";
  return 0;
}
