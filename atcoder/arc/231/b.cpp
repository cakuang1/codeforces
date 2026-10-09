#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937_64 rng(
        chrono::steady_clock::now().time_since_epoch().count()
    );

    int T;
    cin >> T;

    while (T--) {
        int A, B, C;
        cin >> A >> B >> C;

        // X must contain x < A, and Y must contain y < B.
        // If one such pair has x XOR y = C, it is impossible.
        bool impossible = false;

        for (int x = 0; x < A; ++x) {
            if ((x ^ C) < B) {
                impossible = true;
                break;
            }
        }

        if (impossible) {
            cout << "No\n";
            continue;
        }

        while (true) {
            vector<int> X, Y;
            vector<bool> inX(2048, false);

            // Required elements of X.
            for (int x = 0; x < A; ++x) {
                X.push_back(x);
                inX[x] = true;
            }

            // Random large elements do not change mex(X).
            for (int x = 1024; x <= 2026; ++x) {
                if (rng() & 1ULL) {
                    X.push_back(x);
                    inX[x] = true;
                }
            }

            // Include every safe element in Y.
            for (int y = 0; y <= 2026; ++y) {
                if (y == B) continue;

                // Including y would create C iff y XOR C is in X.
                if (!inX[y ^ C]) {
                    Y.push_back(y);
                }
            }

            // Check that all values below C are obtainable.
            vector<bool> seen(C, false);
            int remaining = C;

            for (int x : X) {
                for (int y : Y) {
                    int value = x ^ y;

                    if (value < C && !seen[value]) {
                        seen[value] = true;
                        --remaining;
                    }
                }

                if (remaining == 0) break;
            }

            if (remaining != 0) continue;

            cout << "Yes\n";

            cout << X.size();
            for (int x : X) cout << ' ' << x;
            cout << '\n';

            cout << Y.size();
            for (int y : Y) cout << ' ' << y;
            cout << '\n';

            break;
        }
    }

    return 0;
}

