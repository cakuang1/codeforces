#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// max n, k
static const int MAXN = 3000;
static const int MAXK = 26;

// input
int n, k;
uint8_t grid[MAXN][MAXN];

// run‐length arrays
int R[MAXN][MAXN], D[MAXN][MAXN];
// answer per letter
ll ans[MAXK];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for(int i = 0; i < n; ++i){
        static char buf[MAXN+1];
        cin >> buf;
        for(int j = 0; j < n; ++j){
            grid[i][j] = buf[j] - 'A';
        }
    }

    // process each letter L
    for(int L = 0; L < k; ++L){
        // 1) build horizontal runs R[i][j]
        for(int i = 0; i < n; ++i){
            int run = 0;
            for(int j = n-1; j >= 0; --j){
                if(grid[i][j] == L) run++;
                else run = 0;
                R[i][j] = run;
            }
        }
        // 2) build vertical runs D[i][j]
        for(int j = 0; j < n; ++j){
            int run = 0;
            for(int i = n-1; i >= 0; --i){
                if(grid[i][j] == L) run++;
                else run = 0;
                D[i][j] = run;
            }
        }

        // 3) for each top-left (i,j), do a two‐stack sweep over s=1..S
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                int S = min(R[i][j], D[i][j]);
                if(S == 0) continue;

                // we will maintain two monotonic stacks:
                //   stkA over A_s = R[i+s-1][j]
                //   stkB over B_s = D[i][j+s-1]
                // and running totals ta, tb = # of s'≤current s with A_s'≥s' (resp. B_s'≥s').
                vector<pair<int,int>> stkA, stkB;
                int ta = 0, tb = 0;
                int total = 0;

                for(int s = 1; s <= S; ++s){
                    // the new values
                    int a = R[i+s-1][j];
                    int b = D[i][j+s-1];

                    // process A‐stack (vertical left side)
                    int wA = 1;
                    while(!stkA.empty() && stkA.back().first >= a){
                        // remove its full contribution
                        ta -= min(stkA.back().first, stkA.back().second);
                        wA += stkA.back().second;
                        stkA.pop_back();
                    }
                    stkA.emplace_back(a, wA);
                    // this block of width wA contributes min(a, wA) good s'
                    ta += min(a, wA);

                    // process B‐stack (horizontal top side)
                    int wB = 1;
                    while(!stkB.empty() && stkB.back().first >= b){
                        tb -= min(stkB.back().first, stkB.back().second);
                        wB += stkB.back().second;
                        stkB.pop_back();
                    }
                    stkB.emplace_back(b, wB);
                    tb += min(b, wB);

                    // now ta = # of s'≤s satisfying A_s'≥s'
                    //    tb = # of s'≤s satisfying B_s'≥s'
                    // the number of s'≤s that satisfy *both* is
                    //    overlap(s) = min(ta, tb)
                    // but we want to sum, for each s, the increment:
                    //    newSquaresAtThisS = overlap(s) - overlap(s-1)
                    // so we can accumulate simply the *minimum* at each step,
                    // provided we track the previous overlap.

                    static int prevOverlap = 0;
                    int ov = min(ta, tb);
                    total += (ov - prevOverlap);
                    prevOverlap = ov;
                }
                // clear static for next iteration
                stkA.clear();
                stkB.clear();

                // add for letter L
                ans[L] += total;
            }
        }
    }

    // output results
    for(int L = 0; L < k; ++L){
        cout << ans[L] << "\n";
    }
    return 0;
}
