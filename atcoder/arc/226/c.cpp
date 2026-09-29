#include <bits/stdc++.h>
using namespace std;

struct Op {
    int r, c, s;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int H, W;
        cin >> H >> W;

        vector<Op> ans;

        auto add = [&](int r, int c, int s) {
            ans.push_back({r, c, s});
        };

        // n must satisfy n ≡ 1 (mod 4).
        auto square1 = [&](auto &&self, int n, int x, int y) -> void {
            if (n == 1) return;

            add(x, y, n - 1);

            for (int d = 1; d < n - 2; d += 2) {
                add(x, y + d, 1);
            }
            for (int d = 1; d < n - 2; d += 2) {
                add(x + d, y + n - 2, 1);
            }
            for (int d = n - 3; d > 1; d -= 2) {
                add(x + n - 2, y + d, 1);
            }
            for (int d = n - 3; d > 1; d -= 2) {
                add(x + d, y, 1);
            }

            self(self, n - 4, x + 2, y + 2);
        };

        // n must satisfy n ≡ 3 (mod 4).
        auto square3 = [&](int n, int x, int y) {
            square1(square1, n - 2, x, y);

            // Rightmost two columns, excluding final row.
            for (int d = 0; d < n - 1; d += 2) {
                add(x + d, y + n - 2, 1);
            }

            // Bottom two rows, excluding final column.
            for (int d = 0; d < n - 3; d += 2) {
                add(x + n - 2, y + d, 1);
            }
        };

        if (H % 2 == 0 || W % 2 == 0) {
            for (int r = 1; r < H; r += 2) {
                for (int c = 1; c < W; c += 2) {
                    add(r, c, 1);
                }
            }
        } else {
            int L = min(H, W);

            if (L % 4 == 1) {
                square1(square1, L, 1, 1);
            } else {
                square3(L, 1, 1);
            }

            if (H < W) {
                for (int r = 1; r < H; r += 2) {
                    for (int c = H + 1; c < W; c += 2) {
                        add(r, c, 1);
                    }
                }
            } else if (W < H) {
                for (int r = W + 1; r < H; r += 2) {
                    for (int c = 1; c < W; c += 2) {
                        add(r, c, 1);
                    }
                }
            }
        }

        cout << ans.size() << '\n';
        for (auto [r, c, s] : ans) {
            cout << r << ' ' << c << ' ' << s << '\n';
        }
    }
}
