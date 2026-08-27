#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<string> S(N);
    for (auto &s : S) cin >> s;

    // ps[i][j] = sum of good cells in rows [0,i), cols [0,j)
    vector<vector<int>> ps(N + 1, vector<int>(N + 1, 0));

    for (int r = 0; r + 1 < N; ++r) {
        for (int c = 0; c + 1 < N; ++c) {
            int good =
                S[r][c] == '.' &&
                S[r + 1][c] == '.' &&
                S[r][c + 1] == '.' &&
                S[r + 1][c + 1] == '.';

            ps[r + 1][c + 1] = good;
        }
    }

    // Build 2D prefix sums.
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            ps[r + 1][c + 1] +=
                ps[r][c + 1] +
                ps[r + 1][c] -
                ps[r][c];
        }
    }

    // Sum over half-open rectangle [r1,r2) x [c1,c2)
    auto rect_sum = [&](int r1, int c1, int r2, int c2) {
        return ps[r2][c2]
             - ps[r1][c2]
             - ps[r2][c1]
             + ps[r1][c1];
    };

    while (Q--) {
        int U, D, L, R;
        cin >> U >> D >> L >> R;

        // Convert cells to 0-indexing.
        --U;
        --D;
        --L;
        --R;

        /*
            Query cells are:
                rows U..D
                cols L..R

            Valid 2x2 top-left corners are:
                rows U..D-1
                cols L..R-1

            As half-open ranges:
                [U, D)
                [L, R)
        */
        cout << rect_sum(U, L, D, R) << '\n';
    }

    return 0;
}


// werpco mepseue hsi
/w