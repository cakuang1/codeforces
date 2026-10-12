#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;

    vector<string> S(H);
    for (string& row : S) cin >> row;

    // Enumerate row pairs along the smaller dimension.
    if (H > W) {
        vector<string> transposed(W, string(H, '#'));

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                transposed[j][i] = S[i][j];
            }
        }

        S = move(transposed);
        swap(H, W);
    }

    ll answer = 1; // The unchanged grid.

    vector<int> good(W);
    vector<int> pref(W + 1);

    for (int top = 0; top < H; ++top) {
        fill(good.begin(), good.end(), 0);

        for (int bottom = top; bottom < H; ++bottom) {
            // good[c]: column c has a white between top and bottom.
            pref[0] = 0;
            for (int c = 0; c < W; ++c) {
                good[c] |= (S[bottom][c] == '.');
                pref[c + 1] = pref[c] + good[c];
            }

            int lastTop = -1;
            int lastBottom = -1;

            for (int right = 0; right < W; ++right) {
                if (S[top][right] == '.') {
                    lastTop = right;
                }
                if (S[bottom][right] == '.') {
                    lastBottom = right;
                }

                // The right side must contain a white cell.
                if (!good[right]) continue;

                int limit = min(lastTop, lastBottom);

                // Count eligible left endpoints in [0, limit].
                answer += pref[limit + 1];
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
