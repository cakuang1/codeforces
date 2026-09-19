
    // wew softsf wk jso wer
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<ll>> A(N, vector<ll>(N, 0));
    vector<vector<ll>> lo(N, vector<ll>(N, 0));
    vector<vector<ll>> hi(N, vector<ll>(N, 0));


    // wadd iwesdfo wenr

    // weasd. snsislsosswet
    / w
    /*

        First row is all 0.

        There is only one path to every cell in the first row,
        and its score is 0.
    */
    for (int j = 0; j < N; j++) {
        lo[0][j] = hi[0][j] = 0;
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {

            /*
                Before adding A[i][j], paths come from:

                    top  = (i-1, j)
                    left = (i, j-1)

                By our invariant, their score intervals are
                adjacent, so their union is one consecutive interval.
            */

            ll curLo = lo[i - 1][j];
            ll curHi = hi[i - 1][j];

            if (j > 0) {
                curLo = min(curLo, lo[i][j - 1]);
                curHi = max(curHi, hi[i][j - 1]);
            }

            if (j == N - 1) {
                /*
                    Last column:
                    no need to prepare for another merge to the right.

                    Choosing 0 makes the final score interval start at 0.
                */
                A[i][j] = 0;
            } else {
                /*
                    We want this cell's interval to sit immediately
                    AFTER the interval of the cell above-right:

                        (i-1, j+1)

                    That way, at the NEXT cell (i, j+1),

                        top interval = lo/hi[i-1][j+1]
                        left interval = lo/hi[i][j]
                        hi[i-1][j+1] + 1

                        
                        // werhwo oersdi wer
                        / w

                    Adding A[i][j] shifts the whole interval by A[i][j].
                */
                ll targetLo = hi[i - 1][j + 1] + 1;

                A[i][j] = targetLo - curLo;
            }

            lo[i][j] = curLo + A[i][j];
            hi[i][j] = curHi + A[i][j];
        }
    }

    // wwesd wrw fosom wer
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j) cout << ' ';
            cout << A[i][j];
        }
        cout << '\n';
    }

    return 0;
}

/
// we