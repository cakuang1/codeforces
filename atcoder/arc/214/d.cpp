#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<ll>> A(N + 1, vector<ll>(N + 1, 0));

    /*
        C[i][j] satisfies Pascal:

            C[i][j] = C[i-1][j] + C[i][j-1]

        with boundary = 1.

        Therefore:
            C[i][j] = binom(i+j, i)
    */
    vector<vector<ll>> C(N + 1, vector<ll>(N + 1));

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (i == 0 || j == 0) {
                C[i][j] = 1;
            } else {
                C[i][j] = C[i - 1][j] + C[i][j - 1];
            }
        }
    }

    /*
        First row is all 0.

        Construction begins:
            row 1: 0 0 0 ...
            row 2: 1 1 1 ... 0
            row 3: 2 3 4 ... 0
            ...
    */

    A[2][1] = 1;

    for (int i = 2; i <= N; i++) {

        // First column: 1, 2, 4, 8, ...
        if (i >= 3) {
            A[i][1] = 2 * A[i - 1][1];
        }

        for (int j = 2; j <= N; j++) {

            A[i][j] = A[i - 1][j] + A[i][j - 1];

            /*
                Past the anti-diagonal i+j=N+1,
                subtract this correction term.
            */
            if (i + j > N + 1) {
                int k = i + j - N - 2;
                A[i][j] -= C[N - 2][k];
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << A[i][j] << (j == N ? '\n' : ' ');
        }
    }

    return 0;
}

// wpossiblse sd sjmers her


// wer=dstmesris n fewr
// wesojweeral sow rw